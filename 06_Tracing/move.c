#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

#define ERR_OPEN      "Cannot open file: %s\n"
#define ERR_READ      "Error while reading from the file: %s\n"
#define ERR_WRITE     "Error while writing to the file: %s\n"
#define ERR_CLOSE     "Cannot close file: %s\n"
#define ERR_REMOVE    "Cannot remove file: %s\n"

enum ProgramArgs {
    INFILE    = 1,
    OUTFILE   = 2,
    ARGS_NUM  = 3
};

enum Constants {
    BUF_SIZE = 1024
};

enum Errors {
    BAD_ARGS_NUM    = 1,
    BAD_READ_FILE   = 2,
    BAD_WRITE_FILE  = 3,
    BAD_OPEN_FILE   = 4,
    BAD_CLOSE_FILE  = 5,
    BAD_REMOVE_FILE = 6
};

void print_error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

int open_file(const char *filename, int flags, mode_t mode) {
    int fd = open(filename, flags, mode);
    if (fd < 0) {
        print_error(ERR_OPEN, filename);
        exit(BAD_OPEN_FILE);
    }
    return fd;
}

void remove_file(const char *filename) {
    int err_code = remove(filename);
    if (err_code < 0) {
        print_error(ERR_REMOVE, filename);
        exit(BAD_REMOVE_FILE);
    }
}

void close_file(int fd, const char *filename) {
    int err_code = close(fd);
    if (err_code < 0) {
        print_error(ERR_CLOSE, filename);
        exit(BAD_CLOSE_FILE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != ARGS_NUM) {
        print_error("Usage: %s <infile> <outfile>\n", argv[0]);
        exit(BAD_ARGS_NUM);
    }

    int input, output;
    char buf[BUF_SIZE];
    ssize_t nread = 1, nwrite;
    const char *infile  = argv[INFILE];
    const char *outfile = argv[OUTFILE];

    input  = open_file(infile, O_RDONLY, 0);
    output = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);

    while (nread > 0) {
        nread = read(input, buf, sizeof(buf));
        if (nread < 0) {
            print_error(ERR_READ, infile);
            close_file(input, infile);
            remove_file(outfile);
            exit(BAD_READ_FILE);
        }
        nwrite = write(output, buf, nread);
        if (nwrite < nread) {
            print_error(ERR_WRITE, outfile);
            close_file(input, infile);
            remove_file(outfile);
            exit(BAD_WRITE_FILE);
        }
    }

    close_file(output, outfile);

    remove_file(infile);

    return 0;
}
