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

int main(int argc, char *argv[])
{
    srand(time(NULL));

    const size_t nbChars = strlen(characters);

    FILE *fptr = fopen(DEFAULT_FILE_NAME, "w");

    fprintf(fptr, "random passwords\n");
    fprintf(fptr, "number : %d passwords\n", DEFAULT_NB_PASSWORDS);
    fprintf(fptr, "size : %d characters\n", DEFAULT_PASSWORD_SIZE);
    fprintf(fptr, "character pool :\n%s\n", characters);
    fprintf(fptr, "\n");

    int n = 0;

    while (n < DEFAULT_NB_PASSWORDS)
    {
        char password[DEFAULT_PASSWORD_SIZE + 1];
        password[DEFAULT_PASSWORD_SIZE] = '\0';
        int lowercase = 0, uppercase = 0, number = 0, special = 0;

        for (size_t i = 0; i < DEFAULT_PASSWORD_SIZE; i++)
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