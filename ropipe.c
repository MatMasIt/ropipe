#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>

#define MAX_ROMAN_LEN 77 // 76 characters + 1 for the null terminator
#define MAX_INT_LEN 6    // 65535 (5 characters) + 1 for the null terminator

#define NUM_SYMBOLS 13

const uint16_t values[NUM_SYMBOLS] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
const char *symbols[NUM_SYMBOLS] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
const uint8_t symbols_len[NUM_SYMBOLS] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

void print_usage(const char *program_name)
{
    printf("Usage: %s [options] [input]\n", program_name);
    printf("Options:\n");
    printf("  -r: Convert a Roman numeral to an integer\n");
    printf("  -s: Fails silently, with no output\n");
    printf("  -k: Don't quit on invalid input\n");
    printf("  -q: Accept quirky Roman numerals like IIII for IV (only valid with -r)\n");
    printf("  -h: Display this help message\n");
}

void int_to_roman(uint16_t num, char result[MAX_ROMAN_LEN])
{
    if (num == 0)
        return;

    char *result_ptr = result;
    for (uint8_t i = 0; i < NUM_SYMBOLS; i++)
    {
        while (num >= values[i])
        {
            num -= values[i];
            result_ptr += sprintf(result_ptr, "%s", symbols[i]);
        }
    }
}

void upper(char *str)
{
    for (char *p = str; *p; p++)
    {
        *p = toupper(*p);
    }
}

bool roman_to_int(char roman[MAX_ROMAN_LEN], uint16_t *result, bool allow_quirky)
{
    *result = 0;
    upper(roman);
    const char *roman_ptr = roman;

    int repetitions = 0;
    char last_char = '\0';

    for (uint8_t i = 0; i < NUM_SYMBOLS; i++)
    {
        while (strncmp(roman_ptr, symbols[i], symbols_len[i]) == 0)
        {
            // Validate repetition of the same numeral
            if (!allow_quirky)
            {
                if (last_char == symbols[i][0])
                {
                    repetitions++;
                    if ((symbols_len[i] == 1 && repetitions >= 3 && symbols[i][0] != 'M') ||
                        (symbols_len[i] == 2 && repetitions >= 1))
                    {
                        return false; // Invalid due to too many repetitions
                    }
                }
                else
                {
                    repetitions = 0;
                }
            }

            *result += values[i];
            roman_ptr += symbols_len[i];
            last_char = symbols[i][0];
        }
    }
    return *roman_ptr == '\0';
}

typedef uint8_t flag;

#define ROMAN_TO_INT 0
#define INT_TO_ROMAN 1

#define SILENT 0
#define VERBOSE 1

#define QUIT 0
#define NO_QUIT 1

int handle_int_to_roman(flag verbosity, flag quit)
{
    char line[MAX_INT_LEN];
    while (fgets(line, MAX_INT_LEN, stdin) != NULL)
    {
        char *endptr;
        errno = 0;
        long num = strtol(line, &endptr, 10);
        if (errno != 0 || (*endptr != '\n' && *endptr != '\0') || num <= 0 || num > UINT16_MAX)
        {
            if (verbosity == VERBOSE)
            {
                fprintf(stderr, "Error: input must be a non-zero positive integer less than or equal to %d\n", UINT16_MAX);
            }
            if (quit == QUIT)
            {
                return 1;
            }
        }
        else
        {
            char result[MAX_ROMAN_LEN];
            int_to_roman(num, result);
            printf("%s\n", result);
        }
    }
    return 0;
}

int handle_roman_to_int(flag verbosity, flag quit, bool allow_quirky)
{
    char line[MAX_ROMAN_LEN];
    while (fgets(line, MAX_ROMAN_LEN, stdin) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        uint16_t result;
        if (!roman_to_int(line, &result, allow_quirky))
        {
            if (verbosity == VERBOSE)
            {
                fprintf(stderr, "Error: input must be a valid Roman numeral\n");
            }
            if (quit == QUIT)
            {
                return 1;
            }
        }
        else
        {
            printf("%d\n", result);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    flag mode = INT_TO_ROMAN;
    flag verbosity = VERBOSE;
    flag quit = QUIT;
    bool allow_quirky = false;

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            char *arg = argv[i];

            if (arg[0] == '-')
            {
                for (int j = 1; arg[j] != '\0'; j++)
                {
                    switch (arg[j])
                    {
                    case 'r':
                        mode = ROMAN_TO_INT;
                        break;
                    case 's':
                        verbosity = SILENT;
                        break;
                    case 'k':
                        quit = NO_QUIT;
                        break;
                    case 'q':
                        if (mode == ROMAN_TO_INT)
                        {
                            allow_quirky = true;
                        }
                        else
                        {
                            fprintf(stderr, "Error: Option -q is only valid with -r (Roman to integer conversion)\n");
                            return 1;
                        }
                        break;
                    case 'h':
                        print_usage(argv[0]);
                        return 0;
                    default:
                        fprintf(stderr, "Error: Unknown option '%c'\n", arg[j]);
                        return 1;
                    }
                }
            }
            else
            {
                fprintf(stderr, "Error: Unknown argument '%s'\n", arg);
                return 1;
            }
        }
    }

    switch (mode)
    {
    case INT_TO_ROMAN:
        return handle_int_to_roman(verbosity, quit);
    case ROMAN_TO_INT:
        return handle_roman_to_int(verbosity, quit, allow_quirky);
    default:
        fprintf(stderr, "Invalid mode\n");
        return 1;
    }
}
