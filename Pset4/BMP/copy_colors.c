/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4q
 *
 * Resizes the original BMP piece by piece, each pixel in the infile has a different color in outfile.
 * 
 * Modified by Jack (Evgeny NAgimov) 02/2017
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember the N (ratio)
    int n = atoi(argv[1]);
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // remember original padding
    int paddingOld =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //size of a line of pixels in bytes (no padding)
    int sizeLine = bi.biWidth * sizeof(RGBTRIPLE);
    
    // new dimentions of the picture
    bi.biWidth *= n;
    bi.biHeight *= n;
    
    // new padding for outfile
    int paddingNew =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // new picture size (including padding)
    bi.biSizeImage = (sizeLine + paddingNew) * abs(bi.biHeight);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // color switcher
    int color = 1;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight/n); i < biHeight; i++)
    {
        // repeats the same line n times
        for(int m = 0; m < n; m++)
        {
            // iterates over pixels in scanline
            for (int j = 0; j < bi.biWidth/n; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write RGB triple to outfile
                for (int y = 0; y < n; y++)
                {
                    int reminder = color % 4;
                    
                    switch (reminder) 
                    {
                        case 0:
                            // red
                            triple.rgbtRed = 0xFF;
                            triple.rgbtBlue = 0x00;
                            triple.rgbtGreen = 0x00;
                            break;
                        case 1:
                            // blue
                            triple.rgbtRed = 0x00;
                            triple.rgbtBlue = 0xFF;
                            triple.rgbtGreen = 0x00;
                            break; 
                        case 2:
                            // green
                            triple.rgbtRed = 0x00;
                            triple.rgbtBlue = 0x00;
                            triple.rgbtGreen = 0xFF;
                            break; 
                        case 3:
                            triple.rgbtRed = 0xFF;
                            triple.rgbtBlue = 0x00;
                            triple.rgbtGreen = 0xFF;
                            break; 
                    }
                    color ++;                
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            // skip over padding, if any
            fseek(inptr, paddingOld, SEEK_CUR);
        
            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingNew; k++)
            {
                fputc(0x00, outptr);
            }
            
            // move cursor to the beginning of the current line if needs to repeat it again
            if (m < n - 1)
            {
                fseek(inptr, - (sizeLine + paddingOld), SEEK_CUR);
            }
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
