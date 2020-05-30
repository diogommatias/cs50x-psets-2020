#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // ask until the user gives a integer from 1 to 8, and store it in height
    do 
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // algorithm to print the pyramids with the height given
    for (int i = 1; i <= height; i++) 
    {
        // number of spaces in the row until first block
        int numberEmptyBlock = height - i;

        // print the spaces in the row
        for (int j = 0; j < numberEmptyBlock; j++) 
        {
            printf(" ");
        }

        // to know if the gap in the row was already printed
        bool gapPrintedFlag = false;
        // print the right side, gap and left side of the pyramid in the row
        for (int times = 2; times > 0; times--) 
        {
            // print the blocks in the row
            for (int j = 0; j < i; j++) 
            {
                printf("#");
            }

            if (!gapPrintedFlag) 
            {
                printf("  ");
                gapPrintedFlag = true;
            }
        }

        printf("\n");
    }
}
