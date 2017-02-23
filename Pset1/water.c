/**
 * Name - Water
 * Program reports a user’s water usage, 
 * converting minutes spent in the shower to bottles of drinking water.
 * 
 * Author: Evgeny Nagimov, 01/2017
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Minutes: ");
    int minutes = GetInt();
    printf("Bottles: %i\n", minutes * 12);
}
