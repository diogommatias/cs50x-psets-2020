from cs50 import get_int

# ask until the user gives a integer from 1 to 8, and store it in height
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# algorithm to print the pyramids with the height given
for i in range(height):
    # number of spaces in the row until first block
    numberEmptyBlock = height - (i + 1)

    # print the spaces in the row
    for j in range(numberEmptyBlock):
        print(" ", end="")

    # to know if the gap in the row was already printed
    gapPrintedFlag = False

    # print the right side, gap and left side of the pyramid in the row
    for j in range(2):
        # print the blocks in the row
        for k in range(i + 1):
            print("#", end="")

        if not gapPrintedFlag:
            print("  ", end="")
            gapPrintedFlag = True

    print()