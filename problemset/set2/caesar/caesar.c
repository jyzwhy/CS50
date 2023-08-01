#include <cs50.h>
#include <stdio.h>

const int upperbegin = 'A';
const int upperend = 'Z';
const int lowerbegin = 'a';
const int lowerend = 'z'; 
const int numberbegin = '0';
const int numberend = '9';

char cipher(char plain, int move);

bool isInrange(int low, int high, char c);

int parse(string s);

int pow10(int power);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


    int move = parse(argv[1]);

    if (move == -1)
    {
       printf("Usage: ./caesar key\n");
       return 1;
    }

    string plain = get_string("plaintext:  ");

    int index = 0;

    while (plain[index] != '\0')
    {
        plain[index] = cipher(plain[index], move);
        index++;
    }

    printf("ciphertext: %s\n", plain);
    return 0;
}

char cipher(char plain, int move)
{
    if (isInrange(upperbegin, upperend + 1, plain))
    {
        plain = upperbegin + (plain - upperbegin + move) % (upperend - upperbegin + 1);
    }
    if (isInrange(lowerbegin, lowerend + 1, plain))
    {
        plain = lowerbegin + (plain - lowerbegin + move) % (lowerend - lowerbegin + 1);
    }
    return plain;
}

int parse(string s)
{
    int index = 0, sum = 0;
    while (s[index] != '\0')
    {
        if (isInrange(numberbegin, numberend + 1, s[index]))
        {
            index ++;
        }
        else
        {
            return -1;
        }
    }

    for (int i = 0; i < index; i++)
    {
        sum += pow10(index - i -1) * (s[i] - numberbegin);
    }
    return sum;

}

bool isInrange(int low, int high, char c)
{
    return (c >= low && c < high);
}

int pow10(int power)
{
    int end = 1;
    for (int i = 0; i < power; i++)
    {
        end *= 10;
    }
    return end;
}
