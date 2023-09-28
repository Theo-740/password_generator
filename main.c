#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "assert.h"
#define DEFAULT_NB_PASSWORDS 100
#define DEFAULT_PASSWORD_SIZE 20
#define DEFAULT_FILE_NAME "password.txt"

const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789&~#{}()[]-|_@=+*$?,.;/:!<>\\\"'";

int strtopint(char *str)
{
    int i;
    if (sscanf(str, "%d", &i) == 1 && i > 0)
    {
        return i;
    }
    else
    {
        fprintf(stderr, "error: expected positive integer got '%s'\n", str);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    int nbPasswords = DEFAULT_NB_PASSWORDS, passwordSize = DEFAULT_PASSWORD_SIZE;
    char *fileName = DEFAULT_FILE_NAME;
    int i = 0;
    while (++i < argc)
    {
        char *arg = argv[i];
        if (arg[0] == '-' && arg[1] != '\0')
        {
            if (arg[2] == '\0')
            {
                switch (arg[1])
                {
                case 'n':
                    nbPasswords = strtopint(argv[++i]);
                    break;

                case 's':
                    passwordSize = strtopint(argv[++i]);
                    break;

                case 'o':
                    fileName = argv[++i];
                    break;

                default:
                    fprintf(stderr, "error: unrecognized command line option '%s'\n", arg);
                    exit(EXIT_FAILURE);
                    break;
                }
            }
            else
            {
                fprintf(stderr, "error: unrecognized command line option '%s'\n", arg);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            fprintf(stderr, "error: expected command line option got '%s'\n", arg);
            exit(EXIT_FAILURE);
        }
    }
    srand(time(NULL));

    const size_t nbChars = strlen(characters);

    FILE *fptr = fopen(fileName, "w");

    fprintf(fptr, "random passwords\n");
    fprintf(fptr, "number : %d passwords\n", nbPasswords);
    fprintf(fptr, "size : %d characters\n", passwordSize);
    fprintf(fptr, "character pool :\n%s\n", characters);
    fprintf(fptr, "\n");

    int n = 0;

    while (n < nbPasswords)
    {
        char password[passwordSize + 1];
        password[passwordSize] = '\0';
        int lowercase = 0, uppercase = 0, number = 0, special = 0;

        for (size_t i = 0; i < passwordSize; i++)
        {
            size_t c = rand() % nbChars;
            password[i] = characters[c];
            if (c < 26)
            {
                lowercase = 1;
            }
            else if (c < 52)
            {
                uppercase = 1;
            }
            else if (c < 62)
            {
                number = 1;
            }
            else
            {
                special = 1;
            }
        }
        if (lowercase && uppercase && number && special)
        {
            fprintf(fptr, "%s\n", password);
            n++;
        }
    }
}