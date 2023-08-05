#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Read header
    // TODO #3
    WAVHEADER header;

    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }
    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);
    // Use get_block_size to calculate size of block
    // TODO #7
    int size = get_block_size(header);
    // Write reversed audio to file
    long begin = ftell(input);

    fseek(input, 0, SEEK_END);

    long end = ftell(input);

    fseek(input, begin, SEEK_SET);

    BYTE audio[end - begin];

    fread(audio, sizeof(BYTE), end - begin, input);

    long block_num = (end - begin) / size;

    for (int i = 0; i < block_num; i++)
    {
        fwrite(audio + end - begin - size * (i + 1), sizeof(BYTE), size, output);
    }
    // TODO #8

    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    char wav[4] = "WAVE";

    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != wav[i])
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * header.bitsPerSample / 8;
}
