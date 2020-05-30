from cs50 import get_int


def main():
    """
    ask the user the number of his credit card and store it in cardNumber
        condition: the number needs to be positive
    """
    while True:
        cardNumber = get_int("Number: ")
        if not (cardNumber < 0):
            break

    # check if the credit card number exists
    company = findCreditCardCompany(cardNumber)

    # luhnsAlgorithm check if the credit card number is valid
    if not(company == "NOT_FOUND") and luhnsAlgorithm(cardNumber):
        print(company)
    else:
        print("INVALID")


"""
find the company to whom the credit card number belongs
long cardNumber: credit card number to search
    return: NOT_FOUND if it is not a credit card number,
            otherwise returns the company of the card (AMEX, VISA, ...)
"""


def findCreditCardCompany(cardNumber):
    creditCardCompany = "NOT_FOUND"
    numberDigits = 0
    digit = -1
    previousDigit = -1

    # retrive the number of digits and the two first digits of the credit card number
    while cardNumber > 0 and numberDigits < 17:
        previousDigit = digit

        digit = int(cardNumber % 10)
        cardNumber = int(cardNumber / 10)

        numberDigits += 1

    # find the company of the credit card number
    if numberDigits > 12 and numberDigits < 17:
        if digit == 4:
            creditCardCompany = "VISA"
        elif numberDigits == 15 and digit == 3 and (previousDigit == 4 or previousDigit == 7):
            creditCardCompany = "AMEX"
        elif numberDigits == 16 and digit == 5 and (previousDigit > 0 and previousDigit < 6):
            creditCardCompany = "MASTERCARD"

    return creditCardCompany


"""
check (syntactically) if the credit card number is valid
long cardNumber: credit card number to check
    return: true if the credit card number is valid,
            otherwise returns false
"""


def luhnsAlgorithm(cardNumber):
    numberDigits = 0
    digit = -1
    firstSum = 0
    secondSum = 0

    """
    first (firstSum) and second (secondSum) phase of the luhns algorithm:
        first  - multiply every other digit by 2, starting on second-to-last digit,
                  and then add those products' digits together
        second - add the firstSum to the secondSum of the digits that weren’t multiplied by 2
    """
    while cardNumber > 0:
        digit = int(cardNumber % 10)
        cardNumber = int(cardNumber / 10)

        # if true goes to first phase, otherwise goes to second phase
        if int(numberDigits % 2) == 1:
            numberMultiplied = digit * 2

            # if the number has two digits, decompose the number into two numbers and sums them
            if numberMultiplied > 9:
                digitMultiplied = int(numberMultiplied % 10)
                numberMultiplied = int(numberMultiplied / 10)

                firstSum += digitMultiplied + numberMultiplied
            else:
                firstSum += numberMultiplied
        else:
            secondSum += digit

        numberDigits += 1

    """
    third phase:
        if the last digit of the sum between firstSum and secondSum is 0,
        the credit card number is valid. Otherwise, the credit card is invalid
    """
    return True if (firstSum + secondSum) % 10 == 0 else False


main()