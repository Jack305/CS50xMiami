/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 * 
 * Updated by Jack Rus on 02/2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(void)
{
    // open input file 
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 2;
    }
    
    // block size 512 bytes
    BYTE block[512];
    
    // filename
    char namejpg[7]; 
    
    // filename number counter
    int count = 0;
    
    // open output file
    FILE* outptr = NULL;
    
    while(1)
    {
            // read RGB triple from infile
            fread(&block, sizeof(block), 1, inptr);
            
            // if reaches EOF - close in and out files
            if (feof(inptr))
            {
                fclose(inptr);
                // close previously opened output file if opened
                if (outptr != NULL)
                    fclose(outptr);
                return 0;
            }

            // if it is a beginning of the file 
            if ((block[0] == 0xff) && 
                (block[1] == 0xd8) && 
                (block[2] == 0xff) && 
                (block[3] == 0xe0 || block[3] == 0xe1))
            {
                
                // if there is open file - close it
                if (outptr != NULL)
                {
                    fclose(outptr);
                }
               
                // create a new file
                sprintf(namejpg, "%03d.jpg", count);
                
                // opens new file
                outptr = fopen(namejpg, "a");
                
                // closes programm if can't open the file
                if (outptr == NULL)
                {
                    fclose(inptr);
                    fprintf(stderr, "Could not create %s.\n", namejpg);
                    return 3;
                }
                
                // increments the filename number if file is open
                count++;
                
                // write block into a file
                fwrite(&block, sizeof(block), 1, outptr);
            }
            
            // if it's not a beginning of the file and there is open file
            else if (outptr != NULL)
            {
                // write block into a file
                fwrite(&block, sizeof(block), 1, outptr);
            }
    } // end of while
}
