#include <rhash.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "config.h"

#ifdef READLINE
    #include <readline/readline.h>
#endif

enum Errors {
    BAD_ALGO_GET        = 1,
    BAD_FILESTRING_NAME = 2,
    BAD_ALGO_NAME       = 3,
    BAD_FILE_HASH       = 4,
    BAD_STRING_HASH     = 5
};

enum Constants {
    BUFF_SIZE   = 64,
    RESULT_SIZE = 130
};

void handle_error(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

int main(int argc, char *argv[]) {
    char *line = NULL;
    unsigned char buf[BUFF_SIZE];
    char result[RESULT_SIZE];

    rhash_library_init();

    while (!NULL) {
        #ifdef READLINE
            line = (char *)readline(NULL);
            if (!line) {
                break;
            }
        #else
            int nread;
            size_t len;
            nread = getline(&line, &len, stdin);
            if (nread < 0) {
                break;
            }
        #endif

        char *algo = strtok(line, " ");
        if (!algo) {
            handle_error("Cannot read name of algorithm. Error code: %d\n", BAD_ALGO_GET);
            continue;
        }

        char *file_or_string = strtok(NULL, " ");
        if (!file_or_string) {
            handle_error("Cannot read filename/string. Error code: %d\n", BAD_FILESTRING_NAME);
            continue;
        }

        if (file_or_string[strlen(file_or_string) - 1] == '\n') {
            file_or_string[strlen(file_or_string) - 1] = '\0';
        }

        int hash_name;
        if (!strcasecmp(algo, "sha1")) {
            hash_name = RHASH_SHA1;
        } else if (!strcasecmp(algo, "tth")) {
            hash_name = RHASH_TTH;
        } else if (!strcasecmp(algo, "md5")) {
            hash_name = RHASH_MD5;
        } else {
            handle_error("Bad algorithm name. Error code: %d\n", BAD_ALGO_NAME);
            continue;
        }

        int hash_type = algo[0] == tolower(algo[0]) ? RHPR_BASE64 : RHPR_HEX;

        ssize_t err_code;
        if (file_or_string[0] != '"') {
            err_code = rhash_file(hash_name, file_or_string, buf);
            if (err_code < 0) {
                handle_error("Cannot hash file %s. Error code: %d\n", file_or_string, BAD_FILE_HASH);
                continue;
            }
        } else {
            err_code = rhash_msg(hash_name, file_or_string + 1, strlen(file_or_string + 1), buf);
            if (err_code < 0) {
                handle_error("Cannot hash string: %s. Error code: %d\n", file_or_string, BAD_STRING_HASH);
                continue;
            }
        }

        rhash_print_bytes(result, buf, rhash_get_digest_size(hash_name), hash_type);

        printf("%s\n", result);
    }

    free(line);

    return 0;
}
