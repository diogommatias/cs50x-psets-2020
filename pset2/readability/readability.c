#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool is_letter(char letter);
bool has_word_ended(char letter);
bool has_sentence_ended(char character);
int coleman_liau_index(int num_letters, int num_words, int num_sentences);

int main(void)
{
    // "input" the text that will be evaluated
    string text = get_string("Text: ");

    int num_letters = 0, num_words = 0, num_sentences = 0;

    int length = strlen(text);
    // boolean/flag to know if we are treating a word in the text. 1 for yes, otherwise 0
    int flag_word = 1;
    // this loop gives us all the info about the text: number of letters, number of words and number of sentences;
    for (int i = 0; i < length; i++)
    {
        if (is_letter(text[i]))
        {
            num_letters++;
            flag_word = 1;
        }
        if (flag_word == 1 && has_word_ended(text[i]))
        {
            num_words++;
            flag_word = 0;
        }
        if (has_sentence_ended(text[i]))
        {
            num_sentences++;
        }
    }

    // grade the text based on the Coleman-Liau index formula
    int index = coleman_liau_index(num_letters, num_words, num_sentences);

    // "output" the grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// return true if it is a letter, otherwise return false
bool is_letter(char letter)
{
    return ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'));
}

// return true if the character does not belong to a word, otherwise return false
bool has_word_ended(char character)
{
    return (!((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')) && character != '-'
            && (int) character != 39);
}

// return true if the character is a sentence ended character, otherwise return false
bool has_sentence_ended(char character)
{
    return (character == '.' || character == '!' || character == '?' || character == '\0');
}

/*
Coleman-Liua index formula
return the US grade level needed to understand the text
*/
int coleman_liau_index(int num_letters, int num_words, int num_sentences)
{
    float L = (float) num_letters * 100.0 / (float) num_words;
    float S = (float) num_sentences * 100.0 / (float) num_words;

    return round(0.0588 * L - 0.296 * S - 15.8);
}

