#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "akinator.c"

void test_letterToInteger() {
    assert(letterToInteger('I') == 1);
    assert(letterToInteger('V') == 5);
    assert(letterToInteger('X') == 10);
    assert(letterToInteger('L') == 50);
    assert(letterToInteger('C') == 100);
    printf("All letterToInteger tests passed!\n");
}

void test_romanToInteger() {
    assert(romanToInteger("I") == 1);
    assert(romanToInteger("III") == 3);
    assert(romanToInteger("IV") == 4);
    assert(romanToInteger("IX") == 9);
    assert(romanToInteger("XLII") == 42);
    assert(romanToInteger("XC") == 90);
    assert(romanToInteger("C") == 100);
    printf("All romanToInteger tests passed!\n");
}

void test_integerToRoman() {
    assert(strcmp(integerToRoman(1), "I") == 0);
    assert(strcmp(integerToRoman(3), "III") == 0);
    assert(strcmp(integerToRoman(4), "IV") == 0);
    assert(strcmp(integerToRoman(9), "IX") == 0);
    assert(strcmp(integerToRoman(42), "XLII") == 0);
    assert(strcmp(integerToRoman(90), "XC") == 0);
    assert(strcmp(integerToRoman(100), "C") == 0);
    assert(strcmp(integerToRoman(400), "CD") == 0);
    assert(strcmp(integerToRoman(900), "CM") == 0);
    assert(strcmp(integerToRoman(1994), "MCMXCIV") == 0);
    printf("All integerToRoman tests passed!\n");
}

int main() {
    test_letterToInteger();
    test_romanToInteger();
    test_integerToRoman();
    printf("All tests passed!\n");
    return 0;
}
