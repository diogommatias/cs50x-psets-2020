from cs50 import get_string
import re


def main():
    text = get_string("Text: ")

    # number of letters
    num_letters = len(re.findall('[a-z]', text, flags=re.IGNORECASE))
    # number of words
    num_words = len(re.findall('\S+', text))
    # number of sentences
    num_sentences = len(re.split('[.!?]', text)) - 1

    grade = coleman_liau_index(num_letters, num_words, num_sentences)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


"""
Coleman-Liua index formula
return the US grade level needed to understand the text
"""


def coleman_liau_index(num_letters, num_words, num_sentences):
    L = num_letters * 100.0 / num_words
    S = num_sentences * 100.0 / num_words

    return round(0.0588 * L - 0.296 * S - 15.8)


main()