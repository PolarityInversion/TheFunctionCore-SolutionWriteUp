/*
 * Neon District - Function Core Solution
 * Credit to "mk" for solving the challenge
 * Write-up & C-solver by PolarityInversion - 2021/01/17
 * 
 * PNG Image: https://pbs.twimg.com/media/Dzqs4BjUcAAcx_a?format=jpg&name=small
 * SVG Image: https://neon-district-easter-egg.s3.amazonaws.com/w3Lc0Me_tO-7h3.FuNc710nc0rE-GlHf.svg
 * 
 * See readme for solution write-up. Lots of magic numbers and bad practice here. Quick and dirty.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* input_file = "w3Lc0Me_tO-7h3.FuNc710nc0rE-GlHf.svg";
const int colour_map[] = { 0x335533, 0x884466, 0x668844, 0x446688 };

int main(int argc, char* argv[])
{
    FILE* inFile;
    char buffer[1024];
    char outputString[65];

    inFile = fopen(input_file, "r");

    /*
     * Read segments in the order they appear in the SVG file and parse each unique colour 
     * and line width into 2-bit values 0-3 (presumably found via brute force originally).
     * Would've been a nice touch if these were randomized in the file, so the solver 
     * would have to reorder them by their position parameters.
     */
    int nCurSegment = 0;
    int strokes[64], colours[64];

    while (fgets(buffer, sizeof(buffer), inFile))
    {
        int r, g, b, nColour, nStroke;
        char* colour = strstr(buffer, "rgb(");
        char* stroke = strstr(buffer, "stroke-width: ");

        if (!colour || !stroke)
            continue;

        /*
         * Technically we can just parse only one of r, g, or b, since there is no overlap
         * in each primary colour value across the set of colours, however this is more general.
         */
        sscanf(colour, "rgb(%d, %d, %d)", &r, &g, &b);
        nColour = r << 16 | g << 8 | b;

        /*
         * Colour map appears to be randomly chosen. It would've been a nice touch for it to be
         * numerically ordered as the strokes are.
         */
        for (int i = 0; i < 4; i++)
            if (nColour == colour_map[i])
            {
                colours[nCurSegment] = i;
                break;
            }

        sscanf(stroke, "stroke-width: %d;", &nStroke);
        
        /* Stroke widths are ordered by numerical value and vary in increments of 5 */
        strokes[nCurSegment++] = nStroke / 5 - 1;
    }

    fclose(inFile);

    int rings[16];
    memset(rings, 0, sizeof(rings));

    /*
     * Iterate through each segment to compose the aggregate ring value. We rely on the direction as 
     * provided by the SVG file, however the original solver likely included provisions for searching
     * through a variety of parameters.
     */
    for (int i = 0; i < 64; i++)
    {
        int ring = i / 4;
        int seg = i % 4;

        rings[ring] |= (strokes[i] << 2 | colours[i]) << ((3 - seg) * 4);
    }

    
    for (int i = 0; i < 16; i++)
    {
        /* 
         * First operation on the ring values - circluarly shift the bits by i bits where i is the ring
         * number starting from inner to outer. 
        */
        int ringValue = ((rings[i] & ((1 << i) - 1)) << (16 - i)) | rings[i] >> i;
    
        /*
        * Final manipulation step of the solution. The hint given by cybourgeoisie was f_i(x_i, y_(i-1)). 
        * The original solver determined this meant to subtract result of the previous step by the
        * next closest inner ring value prior to the circular shift above. 
        */
        ringValue -= i ? rings[i - 1] : 0;

        /*
        * Truncate to 16-bits
        */
        ringValue &= (1 << 16) - 1;

        sprintf(outputString+(i*4),"%04x", ringValue);
    }

    printf("%s\n", outputString);
    return 0;
}