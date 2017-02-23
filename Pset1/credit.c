/**
 * Program determines whether a provided credit card number is valid according to Luhn’s algorithm
 * & defines the credit card (CC) type by number provided by user.
 * 
 *  Author: Evgeny Nagimov, 01/2017
 */

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int array[16];
    printf("CC Number: ");
    long cc_number = get_long_long();
    
    // determing if "t" is in the CC possible numbers range 
    if ((cc_number < 4000000000000) || (cc_number > 5599999999999999))
    {
        printf("INVALID\n");     
    } 
    else 
    {
        // assigning each digit to an array element
        int i = 0;
        while (cc_number)
        {
            array[i] = cc_number % 10;
            cc_number /= 10;
            i++;
        }
        // calculating the sums of digits - odd and even 
        int sum_even = 0, sum_odd = 0;
        int two_digits;
        for (int x = 0; x <= 15; x++)
        {
            if (x % 2 == 0)
            {
                sum_even += array[x];     
            } 
            else 
            {
                two_digits = array[x] * 2;
                // finding the sum of digits if the number has > 2 digits
                if (two_digits > 9)
                {
                    while (two_digits)
                    {
                        sum_odd += two_digits % 10;
                        two_digits /= 10;
                    }
                } 
                else 
                {
                    sum_odd += two_digits;
                }
            }
        }
        // finding the last digit of sum1 + sum2
        int lastDigit = (sum_odd + sum_even) % 10;
        
        // determing the CC card type
        if (lastDigit == 0)
        {
            if ((array[14] == 3) && ((array[13] == 7) || (array[13] == 4)))
            {
                printf("AMEX\n");
            } 
            else if ((array[15] == 5) && ((array[14] == 1) || 
            (array[14] == 2) || (array[14] == 3) || 
            (array[14] == 4) || (array[14] == 5)))
            {
                printf("MASTERCARD\n");
            } 
            else if ((array[12] == 4) || (array[15] == 4))
            {
                printf("VISA\n");
            }
            else printf("INVALID\n");
        } 
        else printf("INVALID\n"); 
    }
    return 0;
}
