#include <stdio.h>
#include <string.h>
#include <cs50.h>

string findCreditCardCompany(long cardNumber);

bool luhnsAlgorithm(long cardNumber);

int main(void)
{
    long cardNumber;

    /** 
    ask the user the number of his credit card and store it in cardNumber
        condition: the number needs to be positive
    **/
    do
    {
        cardNumber = get_long("Number: ");
    }
    while (cardNumber < 0);

    // check if the credit card number exists
    string company = findCreditCardCompany(cardNumber);

    // luhnsAlgorithm check if the credit card number is valid
    if (!(strcmp(company, "NOT_FOUND") == 0) && luhnsAlgorithm(cardNumber))
    {
        printf("%s\n", company);
    }
    else
    {
        printf("%s\n", "INVALID");
    } 
}

/**
find the company to whom the credit card number belongs
long cardNumber: credit card number to search
    return: NOT_FOUND if it is not a credit card number,
            otherwise returns the company of the card (AMEX, VISA, ...)
**/
string findCreditCardCompany(long cardNumber)
{
    string creditCardCompany = "NOT_FOUND";
    int numberDigits = 0, digit = -1, previousDigit = -1;
    
    // retrive the number of digits and the two first digits of the credit card number
    while (cardNumber > 0 && numberDigits < 17)
    {
        previousDigit = digit;

        digit = cardNumber % 10;
        cardNumber = cardNumber / 10;

        numberDigits++;
    }

    // find the company of the credit card number
    if (numberDigits > 12 && numberDigits < 17) 
    {
        if (digit == 4) 
        {
            creditCardCompany = "VISA";
        }
        else if (numberDigits == 15 && digit == 3 
                 && (previousDigit == 4 || previousDigit == 7)) 
        {
            creditCardCompany = "AMEX";
        }
        else if (numberDigits == 16 && digit == 5 
                 && (previousDigit > 0 && previousDigit < 6))
        {
            creditCardCompany = "MASTERCARD";
        }
    }

    return creditCardCompany;
}

/**
check (syntactically) if the credit card number is valid
long cardNumber: credit card number to check
    return: true if the credit card number is valid,
            otherwise returns false
**/
bool luhnsAlgorithm(long cardNumber)
{
    int numberDigits = 0, digit = -1, firstSum = 0, secondSum = 0;
    
    /** 
    first (firstSum) and second (secondSum) phase of the luhns algorithm:
        first  - multiply every other digit by 2, starting on second-to-last digit, 
                  and then add those products' digits together
        second - add the firstSum to the secondSum of the digits that weren’t multiplied by 2
    **/
    while (cardNumber > 0)
    {
        digit = cardNumber % 10;
        cardNumber = cardNumber / 10;

        // if true goes to first phase, otherwise goes to second phase
        if (numberDigits % 2 == 1)
        {
            int numberMultiplied = digit * 2;
            
            /**
            if the number has two digits, decompose the number into two numbers and sums them
            **/
            if (numberMultiplied > 9) 
            {
                int digitMultiplied = numberMultiplied % 10;
                numberMultiplied = numberMultiplied / 10;

                firstSum += digitMultiplied + numberMultiplied;
            }
            else
            {
                firstSum += numberMultiplied;
            }
        }
        else
        {
            secondSum += digit;
        }

        numberDigits++;
    }

    /**
    third phase:
        if the last digit of the sum between firstSum and secondSum is 0, 
        the credit card number is valid. Otherwise, the credit card is invalid 
    **/
    return ((firstSum + secondSum) % 10 == 0) ? true : false;
}
