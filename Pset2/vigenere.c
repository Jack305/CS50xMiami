/**
 * Name - Vigenere
 * Program encrypts messages using Vigenère’s cipher. 
 * This program must accept a single command-line argument: 
 * a keyword, k, composed entirely of alphabetical characters. 
 *
 * Created by Jack Rus
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // checks if user gave more than 1 argument, or none.
    if (argc != 2)
    {
        printf("ERROR!!! ONE, and only ONE argument is allowed and it HAS to be positive INT.\n");
        return 1;
    }
    
    // checks if user gave a non-alphabetic key.
    int key_lng = strlen(argv[1]);
    for (int i = 0; i < key_lng; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("ERROR!!! ONE, and only ONE argument is allowed and it HAS to be positive INT.\n");
            return 1;
        }
    }
    
    // gets string from user
    string line = GetString();
    
    int count = 0;
    int k;
    for (int i = 0; i < strlen(line); i++)
    {
        //defines the k 
        count = count % key_lng;
        k = argv[1][count];
        k >= 65 && k <= 90 ? (k = k - 65) : (k = k - 97); 
        
        // if char line[i] is an uppercase 
        if ((line[i] >= 65) && (line[i] <= 90))
        {
            line[i] + k <= 90 ? (line[i] = line[i] + k) : (line[i] = line[i] + k - 26);
            count++;
        } 
        // if char is an lowercase
        else if ((line[i] >= 97) && (line[i] <= 122))
        {
            line[i] + k <= 122 ? (line[i] = line[i] + k) : (line[i] = line[i] + k - 26);
            count++;
        }
    }
    printf("%s\n", line);
    return 0;
}
