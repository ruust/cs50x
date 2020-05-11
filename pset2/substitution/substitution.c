#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 26

int match(regex_t *pexp, char *sz);

int main(int argc, string argv[])
{
    bool keyIsValid = false;
    //Init regex
    regex_t regex;
    int reti;
    //Regex pattern to check against anything other than word characters
    char *Expression = "[^A-Za-z]";
    //Check if an argument has been provided by the user
    if (argc == 2 && strlen(argv[1]) == MAX_SIZE)
    {
        //Check if its a valid key
        //printf("success test %s\n", argv[1]);
        string key = argv[1];

        //TODO check there are nothing other than A-Z or a-z characters in the key (regex)
        reti = regcomp(&regex, Expression, REG_EXTENDED | REG_ICASE);
        if (reti != 0)
        {
            printf("regcomp failed\n");
        }


        /* Execute regular expression */
        reti = regexec(&regex, key, 0, NULL, 0);
        if (!reti)
        {
            //Something other than A-Z or a-z is in the key. Reject key.
            printf("Error, key must not contain anything other than alphabetical characters.\n");
            return 1;
        }
        else if (reti == REG_NOMATCH)
        {
            //Key has no illegal characters.
            //char keyInArray[] = key;
            //Using a 2D array to check for repeated characters in the key
            int keyRepeatStore[MAX_SIZE][2];
            int asciiIndex = 65;
            for (int i = 0; i < MAX_SIZE; i++)
            {
                keyRepeatStore[i][0] = asciiIndex;
                keyRepeatStore[i][1] = 0;
                asciiIndex++;
            }

            //Iterate through the key and check against the 2D Array for repeated characters in the key.
            for (int i = 0; i < MAX_SIZE; i++)
            {
                //Regardless of case, convert character to upper case for easy reference.
                char UpperCaseLetter = toupper(key[i]);
                int Letter_In_ASCII = (int)UpperCaseLetter;
                //Because the 2D Array is populated in ASCII in alphabetical order, we can deduce that index[0] will be the reference for A(65), index[1] is B(66) so on and so forth.
                int indexForArray = Letter_In_ASCII - 65;
                if (keyRepeatStore[indexForArray][1])
                {
                    
                }
                //printf("%i\n", Letter_In_ASCII);
            }
            keyIsValid = true;
        }
        regfree(&regex);

        if (keyIsValid)
        {
            //TODO when key has no repeated characters
        }
    }
    else if (argc == 2)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

int match(regex_t *pexp, char *sz)
{
    // we just need the whole string match in this example
    regmatch_t whole_match;

    int count = 0;

    // we store the eflags in a variable, so that we can make
    // ^ match the first time, but not for subsequent regexecs
    int eflags = 0;
    int match = 0;
    size_t offset = 0;
    size_t length = strlen(sz);

    while (regexec(pexp, sz + offset, 1, &whole_match, eflags) == 0)
    {
        // do not let ^ match again.
        eflags = REG_NOTBOL;
        match = 1;
        /*printf("range %zd - %zd matches\n",
               offset + whole_match.rm_so,
               offset + whole_match.rm_eo);*/

        count++;
        // increase the starting offset
        offset += whole_match.rm_eo;

        // a match can be a zero-length match, we must not fail
        // to advance the pointer, or we'd have an infinite loop!
        if (whole_match.rm_so == whole_match.rm_eo)
        {
            offset += 1;
        }

        // break the loop if we've consumed all characters. Note
        // that we run once for terminating null, to let
        // a zero-length match occur at the end of the string.
        if (offset > length)
        {
            break;
        }
    }
    if (! match)
    {
        //printf("\"%s\" does not contain a match\n", sz);
    }
    return count;
}