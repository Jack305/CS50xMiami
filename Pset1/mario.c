/**
 * Name - Mario
 * Program prints out a double half-pyramid of a specified height
 * 
 * Author: Evgeny Nagimov, 01/2017
 */

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Gets positive int from user which is < 24
    int height;
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    // prints out a number of lines set by user
    for (int x = 0; x < height; x++)
    {
        for (int i = 1; i < height - x; i++)
        {
            printf(" ");
        }
        for (int i = 0; i <= x + 1; i++)
        {
            printf("#");
        } 
        printf("\n");
    }
}
