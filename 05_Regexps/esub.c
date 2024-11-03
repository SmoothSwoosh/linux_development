#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

enum ProgramArgs {
    REGEXP           = 1,
    SUBSTITUTION     = 2,
    INPUT            = 3,
    ARGS_NUM         = 4
};

enum Constants {
    MAX_BAGS_NUM     = 10,
    MAX_ERRBUF_SIZE  = 100,
    MAX_OUTPUT_SIZE  = 4096
};

enum Errors {
    BAD_ARGS_NUM     = 1,
    BAD_REG_COMP     = 2,
    BAD_REG_EXEC     = 3,
    BAD_BAG_REF      = 4
};

void print_regerror(int errcode, regex_t *preg) {
    char errbuf[MAX_ERRBUF_SIZE];
    regerror(errcode, preg, errbuf, MAX_ERRBUF_SIZE);
    printf("%s\n", errbuf);
}

void substitute(const char *input, const char *substitution, const regmatch_t *bags, char *output) {
    size_t input_size = strlen(input);
    size_t sub_size   = strlen(substitution);
    size_t output_idx = 0;
    for (size_t input_idx = 0; input_idx < input_size; ++input_idx) {
        if (input_idx != bags[0].rm_so) {
            output[output_idx++] = input[input_idx];
        } else {
            for (size_t j = 0; j < sub_size; ++j) {
                if (substitution[j] != '\\') {
                    output[output_idx++] = substitution[j];
                } else if (j + 1 < sub_size) {
                    ++j;
                    if ('0' <= substitution[j] && substitution[j] <= '9') {
                        int bag_num  = substitution[j] - '0';
                        int start    = bags[bag_num].rm_so;
                        int end      = bags[bag_num].rm_eo;
                        if (start == -1) {
                            fprintf(stderr, "Bag %d doesn't exist\n", bag_num);
                            exit(BAD_BAG_REF);
                        } else {
                            strncpy(output + output_idx, input + start, end - start);
                            output_idx += end - start;
                        }
                    } else if (substitution[j] == '\\') {
                        output[output_idx++] = '\\';
                    } else {
                        output[output_idx++] = '\\';
                        output[output_idx++] = substitution[j];
                    }
                }
            }
            input_idx = bags[0].rm_eo - 1;
        }
    }
    output[output_idx++] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != ARGS_NUM) {
        fprintf(stderr, "Usage: %s <regexp> <substitution> <string>\n", argv[0]);
        return BAD_ARGS_NUM;
    }

    int errcode;
    const char *regexp       = argv[1];
    const char *substitution = argv[2];
    const char *input        = argv[3];

    regex_t preg;
    errcode = regcomp(&preg, regexp, REG_EXTENDED);
    if (errcode != 0) {
        print_regerror(errcode, &preg);
        return BAD_REG_COMP;
    }

    regmatch_t bags[MAX_BAGS_NUM];
    errcode = regexec(&preg, input, MAX_BAGS_NUM, bags, 0);
    if (errcode == REG_NOMATCH) {
        regfree(&preg);
        return 0;
    } else if (errcode != 0) {
        print_regerror(errcode, &preg);
        regfree(&preg);
        return BAD_REG_EXEC;
    }

    char output[MAX_OUTPUT_SIZE];
    substitute(input, substitution, bags, output);
    printf("%s\n", output);

    regfree(&preg);

    return 0;
}
