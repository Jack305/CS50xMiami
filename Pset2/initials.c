/**
 * Name - Initials
 * Program prompts a user for their name 
 * and then outputs their initials in uppercase with no spaces or periods.
 * 
 * Author Jack Rus, 01/2017
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string name = GetString();
    char initials[5];
    int count = 0;
    for (int i = 0; i < strlen(name); i++)
    {
        //determines if the char is an initial - is the 1st letter in word
        if (((i - 1 >= 0) && (name[i - 1] == ' ') && (name[i] != ' ')) || (i == 0)) 
        {
            //checks if initial is CAP or not 
            name[i] >= 97 ? (initials[count] = name[i] - 32) : (initials[count] = name[i]);
            count++;
        }
    }
    printf("%s\n", initials);
}
