#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int validate_key(string key);
string encrypt(string text, string key);

int main(int argc, string argv[])
{
    // exit program if no arguments were given
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // validate the key
    int key_validation = validate_key(argv[1]);
    if (key_validation == 0)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (key_validation == -1)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    else if (key_validation == -2)
    {
        printf("Key must not contain duplicated characters.\n");
        return 1;
    }
    else
    {
        // get as input the text to be encrypted
        string plain_text = get_string("plaintext: ");
        // encrypt the text
        string cipher_text = encrypt(plain_text, argv[1]);
        // output the encrypted text
        printf("ciphertext: %s\n", cipher_text);
    }
}

/*
Validates the key string and returns a personalized value with the type of error occured.
Return: A int value between -2 and 1, inclusive:
    - 1, key is valid;
    - 0, key does not contain 26 characters;
    - -1, key contains a non-alphabetic characters;
    - -2, key contains a duplicate.
*/
int validate_key(string key)
{
    int key_validation = 1;

    int length = strlen(key);
    // key must contain 26 characters
    if (length == 26)
    {
        for (int i = 0; i < length; i++)
        {
            // key must only contain alphabetic characters
            if (isalpha(key[i]) != 0)
            {
                for (int j = 0; j < i; j++)
                {
                    // key must not contain duplicates
                    if (tolower(key[i]) == tolower(key[j]))
                    {
                        key_validation = -2;
                        break;
                    }
                }
            }
            else
            {
                key_validation = -1;
                break;
            }
            // if the key contains duplicates, the validation is over and no need to keep validate
            if (key_validation == -2)
            {
                break;
            }
        }
    }
    else
    {
        key_validation = 0;
    }

    return key_validation;
}

/*
Encrypts the text string based on the key string. Converts the alphabetic characters
of the text to the corresponding alphabetic characters given by the key string.
Return: A string with the text encrypted.
*/
string encrypt(string text, string key)
{
    int length_text = strlen(text);
    for (int i = 0; i < length_text; i++)
    {
        // is just to convert the alphabetic characters of text
        if (isalpha(text[i]))
        {
            // find the index position of the alphabetic letter of the text, in the key string
            int index_alphabet = toupper(text[i]) - 65;
            // convert the letter to its cipher, preserving the letter if it is lowercase or uppercase
            if (islower(text[i]))
            {
                text[i] = tolower(key[index_alphabet]);
            }
            else
            {
                text[i] = toupper(key[index_alphabet]);
            }
        }
    }

    return text;
}