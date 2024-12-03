#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

/**
 * Convert roman @p c into arabic integer
 * @param c letter
 */
int letterToInteger(char c) {
    switch (c) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
    }
}

/**
 * Convert roman number @p s into arabic integer
 * @param s roman number
 */
int romanToInteger(const char *s) {
    size_t n   = strlen(s);
    int number = 0;

    for (int i = 0; i < n - 1; ++i) {
        int letter      = letterToInteger(s[i]);
        int next_letter = letterToInteger(s[i + 1]);
        number          += (letter < next_letter ? -1 : 1) * letter;
    }

    return number + letterToInteger(s[n - 1]);
}

/**
 * Convert arabic integer @p number into roman
 * @param number integer number
 */
char * integerToRoman(int number) {
    // https://rosettacode.org/wiki/Roman_numerals/Encode#C.2B.2B

    static char roman[10];

    static struct Digit {
        char string[4];
        int  value;
    } digits[] = {
        {"M", 1000}, {"CM", 900}, {"D", 500}, {"CD", 400},
        {"C", 100 }, {"XC", 90}, {"L",  50}, {"XL", 40},
        {"X", 10}, {"IX", 9}, {"V", 5}, {"IV", 4}, {"I", 1},
        {"?", 0}
    };

    *roman              = '\0';
    struct Digit* digit = &digits[0];

    while (digit->value)
    {
        while (number >= digit->value)
        {
            number -= digit->value;
            strcat(roman, digit->string);
        }
        ++digit;
    }

    return roman;
}

/**
 * Game "Guess a number"
 * 
 * Flags:
 * -h, --help   help
 * -r           use roman notation
 * 
 */
int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bindtextdomain("akinator", LOCALE_PATH);
    textdomain("akinator");

    int r = 0;
    if (argc == 2) {
        if (!strcmp(argv[1], "-r")) r = 1;
        if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
            printf(_("Usage: %s [-r]\n"), argv[0]);
            printf(_("Guess a number from 1 to 100 answering yes or no\n"));
            printf(_("-h, --help \t help\n"));
            printf(_("-r \t\t use roman notation\n"));
            return 0;
        }
    }

    int l = 1, h = 100;
    char response[10];
    while (l < h) {
        int mid = (l + h) >> 1;
        if (r) {
            printf(_("Is your number greater than %s? Answer yes or no\n"), integerToRoman(mid));
        } else {
            printf(_("Is your number greater than %d? Answer yes or no\n"), mid);
        }
        int _ = scanf("%s", response);
        if (!strcmp(response, _("yes"))) {
            l = mid + 1;
        } else {
            h = mid;
        }
    }

    if (r) {
        printf(_("Your number is %s\n"), integerToRoman(l));
    } else {
        printf(_("Your number is %d\n"), l);
    }

    return 0;
}
