#include <stdio.h>

void bubble_sort(int array[], int size);

int main(void) {
    int num[6] = {10, 2, 6, 11, 8, 14};

    // before sort
    for(int i = 0; i < 6; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");

    bubble_sort(num, sizeof(num)/sizeof(int));

    // after sort
    for(int i = 0; i < 6; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
}


void bubble_sort(int array[], int size)
{
    int limit = size-1;
    int num_switch = -1;
    while(num_switch != 0) {
        num_switch = 0;

        for(int i = 0; i < limit; i++) {
            int num_right_votes = array[i];
            int num_left_votes = array[i+1];

            if(num_right_votes > num_left_votes) {
                int tmp = array[i+1];
                array[i+1] = array[i];
                array[i] = tmp;
                num_switch++;
            }
        }

        limit--;
    }
}