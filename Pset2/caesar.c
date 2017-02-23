/**
 * Name - Caesar
 * Program encrypts messages using Caesar’s cipher and the key provided by user
 * 
 * Author: Jack Rus
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // checks if user gave more than 1 argument, or none
    if ((argc != 2) || (atoi(argv[1]) < 1))
    {
        printf("ERROR!!! ONE, and only ONE argument is allowed and it HAS to be positive INT.\n");
        return 1;
    }
    // excludes k > 26
    int k = atoi(argv[1]) % 26;
    string line = GetString();
    
    // encrypts chars according to the key (k) 
    for (int i = 0, x = strlen(line); i < x; i++)
    {
        // if char is an uppercase
        if ((line[i] >= 65) && (line[i] <= 90))
            line[i] + k <= 90 ? (line[i] = line[i] + k): (line[i] = line[i] + k - 26);
        // if char is a lowercase
        else if ((line[i] >= 97) && (line[i] <= 122))
            line[i] + k <= 122 ? (line[i] = line[i] + k): (line[i] = line[i] + k - 26);
    }
    printf("%s\n", line);
    return 0;
}
