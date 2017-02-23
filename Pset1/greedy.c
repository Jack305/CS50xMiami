/**
 * Name - Greedy
 * Program spits out the minimum number of coins with which said change can be made.
 * 
 *  Author: Evgeny Nagimov, 01/2017
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

void calc_coins(int x, int *change_p, int *coins_p);

int main(void)
{
    int change;
    int coins = 0;
    do
    {
    printf("How much change is owed?\n");
    change = round(GetFloat() * 100);
    }
    while (change < 0);

    calc_coins(25, &change, &coins);
    calc_coins(10, &change, &coins);
    calc_coins(5, &change, &coins);
    calc_coins(1, &change, &coins);
    printf("%i\n", coins);
}

/**
 * Function calculates the number of coins of the certain value (25C/10C/5/1C) in the remaining change
*/
void calc_coins(int x, int *change_p, int *coins_p)
{
    if (*change_p >= x)
    {
        *coins_p += (*change_p / x);
        *change_p = *change_p - (*change_p / x * x);
    } 
}
