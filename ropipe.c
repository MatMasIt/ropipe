#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RDIGITS 14
/*
 * Returns the value of a roman numeral digit
 * @param {char} c - Roman digit
*/
static int roman_to_integer(char c)
{
    switch (c)
    {
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
    case 'D':
        return 500;
    case 'M':
        return 1000;
    default:
        return 0;
    }
}
/*
 * Returns the interger value of a roman number
 * @param {string} s - Roman number
*/
int roman_to_int(char *s)
{
    int i, int_num = roman_to_integer(s[0]);

    for (i = 1; s[i] != '\0'; i++)
    {
        int prev_num = roman_to_integer(s[i - 1]);
        int cur_num = roman_to_integer(s[i]);
        if (prev_num < cur_num)
        {
            int_num = int_num - prev_num + (cur_num - prev_num);
        }
        else
        {
            int_num += cur_num;
        }
    }
    return int_num;
}
/*
 * Map of roman digits symbols and their value
 * @elem {string} sym - digit symbol
 * @elem {int} val - digit symbol
*/
typedef struct
{
    char *sym;
    int val;
} numeral;
/*
 * Returns greatest numeral index
 * @elem {numeral} nu - map of roman digits symbols and their value
 * @elem {int} num - number
*/
int maxNume(numeral *nu, int num)
{
    int i, index;
    for (i = 0; i < RDIGITS; i++)
    { //RDIGITS numerals in array
        if (nu[i].val <= num)
            index = i;
    }
    //gretest value numeral index, not greater than number
    return index;
}
/*
 * Prints roman number from integer
 * @elem {numeral} nu - map of roman digits symbols and their value
 * @elem {int} num - number
*/
void decToRoman(numeral *nu, int num)
{
    int max;
    if (num != 0)
    {
        max = maxNume(nu, num);
        printf("%s", nu[max].sym);
        num -= nu[max].val;  //decrease number
        decToRoman(nu, num); //recursively print numerals
    }
}
/*
 * Main
 * @elem {int} argc - Argument count
 * @elem {string[]} argv - Strings array
*/
int main(int argc, char *argv[])
{
    int direction = 0;
    /*
    * 0: integer to roman (default)
    * 1: roman to integer
    */
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-r"))
        {
            direction = 1;
        }
        else
        {
            direction = 0;
        }
    }
    numeral nume[RDIGITS] = {{"I", 1}, {"IV", 4}, {"V", 5}, {"IX", 9}, {"X", 10}, {"XL", 40}, {"L", 50}, {"XC", 90}, {"C", 100}, {"CD", 400}, {"D", 500}, {"CM", 900}, {"M", 1000}, {"MMMM", 4000}};
    char *str1;
    int inputint = 0;
    switch (direction)
    {
    case 0:
        while (scanf("%s", &str1) && !feof(stdin)) // read integers and convert to roman
        {
            printf("%d\n", roman_to_int(&str1));
        }
        break;
    case 1:
        while (scanf("%d", &inputint) && !feof(stdin)) // read roman and  convert to integers
        {
            decToRoman(nume, inputint);
            printf("\n");
        }
        break;
    }
    return 0;
}
