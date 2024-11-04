#include <dlfcn.h>
#include <string.h>

typedef int (*remove_file_type)(const char *);

int remove(const char *filename) {
    int err_code = 0;
    if (!strstr(filename, "PROTECT")) {
        err_code = ((remove_file_type)(dlsym(RTLD_NEXT, "unlink")))(filename);
    }
    return err_code;
}
