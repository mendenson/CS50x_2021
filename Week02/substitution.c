#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void convertToUpperCase();
bool validateKey();
bool verifyKeyOnlyContainsLetters();
bool checkIfKeyContainsAllUniqueCharacters();
string convertToCipherText(string plaintext);

string key;

int main(int argc, string argv[])
{
    //Checks if no key has been provided.
    if (argv[1] == NULL)
    {
        printf("You must provide a 26 digit alphabet key containing each letter");
        printf("e.g VCHPRZGJNTLSKFBDQWAXEUYMOI\n");
        return 1;
    }

    key = argv[1];
    convertToUpperCase(key);

    if (!validateKey())
    {
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: %s\n", convertToCipherText(plaintext));
    return 0;
}

void convertToUpperCase()
{
    for (int i = 0; i < strlen(key); i++)
    {
        key[i] = toupper(key[i]);
    }
}

bool validateKey()
{
    if (!verifyKeyOnlyContainsLetters())
    {
        printf("Key must only contain letters.\n");
        return false;
    }
    if (strlen(key) != 26)
    {
        printf("Key must contain exactly 26 characters.\n");
        return false;
    }

    if (!checkIfKeyContainsAllUniqueCharacters())
    {
        printf("Key must contain each character once and only once.\n");
        return false;
    }

    return true;
}

bool verifyKeyOnlyContainsLetters()
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (!(isupper(key[i])))
        {
            return false;
        }
    }
    return true;
}

bool checkIfKeyContainsAllUniqueCharacters()
{
    int containsLetter = 0;

    for (char currentChar = 'A'; currentChar <= 'Z'; currentChar++)
    {
        for (int i = 0; i <= strlen(key); i++)
        {
            if (currentChar == key[i])
            {
                containsLetter++;
                break;
            }
        }
    }
    return (containsLetter == 26);
}

string convertToCipherText(string plaintext)
{
    string ciphertext = plaintext;

    for (int i = 0; i < strlen(ciphertext); i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = key[plaintext[i] - 65];
        }
        if (islower(plaintext[i]))
        {
            ciphertext[i] = key[plaintext[i] - 97];
            ciphertext[i] = tolower(ciphertext[i]);
        }
    }
    return ciphertext;
}