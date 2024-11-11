#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("akinator", LOCALE_PATH);
    textdomain("akinator");

    printf(_("Think of a number from 1 to 100\n"));
    int l = 1, r = 100;
    char response[10];
    while (l < r) {
        int mid = (l + r) >> 1;
        printf(_("Is your number bigger than %d? Answer yes or no\n"), mid);
        int _ = scanf("%s", response);
        if (!strcmp(response, _("yes"))) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    printf(_("Your number is %d\n"), l);
}
