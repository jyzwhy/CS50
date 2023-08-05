#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int size = 512;

bool isJPEG(BYTE buffer[size]);

int main(int argc, char *argv[])
{
    // check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // open input file
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[size];

    char name[8];
    int i = -1;
    bool begin = false;
    FILE *output;

    while (fread(buffer, size, 1, file))
    {
        if (isJPEG(buffer) || begin == true)
        {
            if (isJPEG(buffer))
            {
                if (begin != false)
                {
                    fclose(output);
                }
                i += 1;
                sprintf(name, "%03d.jpg", i);

                output = fopen(name, "w");
                if (output == NULL)
                {
                    printf("Could not open file.\n");
                    return 1;
                }
            }
            if (begin == false)
            {
                begin = true;
            }

            fwrite(buffer, size, 1, output);
        }
    }
    fclose(file);
    fclose(output);
}

bool isJPEG(BYTE buffer[size])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef;
}
