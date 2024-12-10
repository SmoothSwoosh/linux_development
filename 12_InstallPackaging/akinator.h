#define _(STRING) gettext(STRING)
#define LOCALE_PATH "."

/**
 * Convert roman @p c into arabic integer
 * @param c letter
 */
int letterToInteger(char c);

/**
 * Convert roman number @p s into arabic integer
 * @param s roman number
 */
int romanToInteger(const char *s);

/**
 * Convert arabic integer @p number into roman
 * @param number integer number
 */
char * integerToRoman(int number);

/**
 * Game "Guess a number"
 * 
 * Flags:
 * -h, --help   help
 * -r           use roman notation
 * 
 */
void run(int argc, char *argv[]);
