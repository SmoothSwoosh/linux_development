#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <sys/types.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// program arguments
enum PROGRAM_ARGS {
    FILENAME = 1,
    ARGS_NUM = 2
};

// program errors
enum ERRORS {
    BAD_ARGS_NUM = 1
};

// signals to text window
enum SIGNALS {
    EXIT = 27,
    SPACE = 32,
    DOWN = 258,
    UP = 259,
    LEFT = 260,
    RIGHT = 261
};

// program constants
enum CONSTANTS {
    TEXT_WINDOW_DY = 4,
    TEXT_WINDOW_DX = 8
};

// storage for file
struct FileStorage {
    char **lines;
    int *line_lenghts;
    int nlines;
    int ncols;
    int capacity;
    int ratio;
};

// window to display text from file
struct TextWindow {
    const struct FileStorage *file;
    WINDOW *frame;
    WINDOW *text;
    int nlines;
    int ncols;
    int begin_y;
    int begin_x;
    int shift_y;
    int shift_x;
};

// create empty file storage
struct FileStorage * FileStorage__create() {
    struct FileStorage *fst = (struct FileStorage *)malloc(sizeof(struct FileStorage));
    fst->nlines = 0;
    fst->ncols = 0;
    fst->capacity = 1;
    fst->ratio = 2;
    fst->lines = (char **)malloc(fst->capacity * sizeof(char *));
    fst->line_lenghts = (int *)malloc(fst->capacity * sizeof(int));
    for (int i = 0; i < fst->capacity; ++i) {
        fst->lines[i] = NULL;
        fst->line_lenghts[i] = 0;
    }
    return fst;
}

// fill file storage with file's content
void FileStorage__fill(struct FileStorage *fst, const char *filename) {
    FILE *fp;
    size_t len = 0;
    ssize_t bytes_read;

    fp = fopen(filename, "r");

    while ((bytes_read = getline(&fst->lines[fst->nlines], &len, fp)) > 0) {
        fst->line_lenghts[fst->nlines] = bytes_read;
        if (fst->lines[fst->nlines][bytes_read - 1] == '\n') {
            fst->lines[fst->nlines][bytes_read - 1] = '\0';
            fst->line_lenghts[fst->nlines] -= 1;
        }
        fst->ncols = max(fst->ncols, fst->line_lenghts[fst->nlines]);
        ++fst->nlines;
        if (fst->nlines == fst->capacity) {
            fst->capacity *= fst->ratio;
            fst->lines = (char **)realloc(fst->lines, fst->capacity * sizeof(char *));
            fst->line_lenghts = (int *)realloc(fst->line_lenghts, fst->capacity * sizeof(int));
        }
    }

    fclose(fp);
}

// return number of lines in file
int FileStorage__nlines(const struct FileStorage *fst) {
    return fst->nlines;
}

void FileStorage__destruct(struct FileStorage *fst) {
    for (int i = 0; i < fst->capacity; ++i) {
        free(fst->lines[i]);
    }
    free(fst->lines);
    free(fst->line_lenghts);
}

// nlines, ncols, dx, dy -- number of lines, number of columns, delta x, delta y for TEXT window respectively
struct TextWindow * TextWindow__create(int nlines, int ncols, int dy, int dx) {
    // create frame and text windows
    struct TextWindow * window = (struct TextWindow *)malloc(sizeof(struct TextWindow));
    window->file = NULL;
    window->frame = newwin(nlines + 2, ncols + 2, dy - 1, dx - 1);
    window->text = newwin(nlines, ncols, dy, dx);
    window->nlines = nlines;
    window->ncols = ncols;
    window->begin_y = dy;
    window->begin_x = dx;
    window->shift_y = 0;
    window->shift_x = 0;

    // configure frame and text windows
    keypad(window->text, TRUE);
    scrollok (window->text, TRUE);
    box(window->frame, 0, 0);
    wrefresh(window->frame);

    return window;
}

// attach file storage to window
void TextWindow__attach(struct TextWindow *window, const struct FileStorage *fst) {
    window->file = fst;
}

// move text inside window
void TextWindow__mvtext(struct TextWindow *window, int direction) {
    switch (direction) {
        case DOWN:
        case SPACE:
            // do not scroll below the last line of the file
            window->shift_y = min(window->shift_y + 1, max(0, window->file->nlines - window->nlines));
            break;
        case UP:
            window->shift_y = max(0, window->shift_y - 1);
            break;
        case RIGHT:
            // do not move right when window is already empty
            window->shift_x = min(window->shift_x + 1, window->file->ncols);
            break;
        case LEFT:
            window->shift_x = max(0, window->shift_x - 1);
            break;
        default:
            return;
    }
}

int TextWindow__wgetch(struct TextWindow *window) {
    return wgetch(window->text);
}

void TextWindow__werase(struct TextWindow *window) {
    werase(window->text);
}

void TextWindow__wrefresh(struct TextWindow *window) {
    wrefresh(window->text);
}

// printw file to window
void TextWindow__printw(struct TextWindow *window) {
    TextWindow__werase(window);   // clear text window
    for (int i = 0; i < min(window->file->nlines, window->nlines); ++i) {
        if (window->shift_x < window->file->line_lenghts[i + window->shift_y]) {
            mvwaddnstr(window->text, i, 0, window->file->lines[i + window->shift_y] + window->shift_x, window->ncols);
        } else {
            mvwaddnstr(window->text, i, 0, "", window->ncols);
        }
    }
    TextWindow__wrefresh(window); // refresh text window
}

void TextWindow__destruct(struct TextWindow *window) {
    delwin(window->text);
    delwin(window->frame);
    free(window);
}

int main(int argc, char* argv[]) {
    if (argc != ARGS_NUM) {
        printf("Wrong number of arguments!\n");
        return BAD_ARGS_NUM;
    }

    // create storage for file
    struct FileStorage *fst = FileStorage__create();

    // fill up the file with the content of given file
    FileStorage__fill(fst, argv[FILENAME]);

    // initialize and configure main window
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();

    // print filename and size to main window
    int size = FileStorage__nlines(fst);
    printw("File: %s; size: %d\n", argv[FILENAME], size);
    refresh();

    // create text window with frame
    struct TextWindow *window = TextWindow__create(LINES - 2 * TEXT_WINDOW_DY, COLS - 2 * TEXT_WINDOW_DX, TEXT_WINDOW_DY, TEXT_WINDOW_DX);

    // attach file storage to window
    TextWindow__attach(window, fst);

    // print file to text window
    int signal = 0;
    do {
        TextWindow__mvtext(window, signal);  // move text in window
        TextWindow__printw(window);          // print file
    } while((signal = TextWindow__wgetch(window)) != EXIT);

    // free memory
    TextWindow__destruct(window);
    FileStorage__destruct(fst);

    endwin();

    return 0;
}