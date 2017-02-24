/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // checks if n != 0 or NULL
    if (n < 0) return false;
    
    // binary search
    int start = 0;
    int end = n - 1;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        
        if (value < values[mid])
            end = mid - 1;
        
        else if (value > values[mid])
            start = mid + 1;
        
        // return true if found value
        else if (value == values[mid] || value == values[start] || value == values[end])
            return true;
        // return false if value isn't in the array
        else
            return false;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool check = true;
    while (check == true)
    {
        // keeps check = false if there are no swaps to terminate loop
        check = false;
        for (int i = 0; i < n - 1; i++)
        {
            // swaps values in previous greater than next
            if (values[i] > values[i + 1])
            {
               int sub = values[i];
               values[i] = values[i + 1];
               values[i + 1] = sub;
               check = true;
            }
        }
    }
    return;
}


