#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string s = get_string("Message: ");

    int bits[BITS_IN_BYTE], index = 0;

    while (s[index] != '\0')
    {
        for (int i = 0; i < BITS_IN_BYTE; i++)
        {
            bits[i] = s[index] % 2;
            s[index] /= 2;
        }
        for (int i = 0; i < BITS_IN_BYTE; i++)
        {
            print_bulb(bits[BITS_IN_BYTE - i - 1]);
        }
        printf("\n");
        index += 1;
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

