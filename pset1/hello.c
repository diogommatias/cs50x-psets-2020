#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // ask for user input and store it in variable name
    string name = get_string("What's your name?\n");

    // greet the user with what he wrote as input
    printf("hello, %s\n", name);
}
