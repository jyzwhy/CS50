#include <cs50.h>
#include <stdio.h>

bool isInrange(int low, int high, char c);

bool isValid(string map);

int main(int argc, string argv[])
{
    // program just accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string map = argv[1];

    // isValid will judge whether the map is valid and change all the lower char in map to upper form
    if (!isValid(map))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string plain = get_string("plaintext:  ");

    int index = 0;

    while (plain[index] != '\0')
    {
        if (isInrange('a', 'z' + 1, plain[index]))
        {
            plain[index] = map[plain[index] - 'a'] + 'a' - 'A';
        }
        else if(isInrange('A', 'Z' + 1, plain[index]))
        {
            plain[index] = map[plain[index] - 'A'];
        }
        index++;
    }

    printf("ciphertext: %s\n", plain);
    return 0;
}

bool isInrange(int low, int high, char c)
{
    return (c >= low && c < high);
}

bool isValid(string map)
{
    int exist[26], index = 0;

    for (int i = 0; i < 26; i ++)
    {
        exist[i] = 0;
    }

    while (map[index] != '\0')
    {
        if(isInrange('a', 'z' + 1, map[index]))
        {
            map[index] += ('A' - 'a');
            exist[map[index] - 'A'] += 1;
        }
        else if(isInrange('A', 'Z' + 1, map[index]))
        {
            exist[map[index] - 'A'] += 1;
        }
        else
        {
            return 0;
        }
        index++;
    }

    if(index != 26) {return 0;}

    for (int i = 0; i < 26 ; i++)
    {
        if(exist[i] != 1)
        {
            return 0;
        }
    }

    return 1;
}
