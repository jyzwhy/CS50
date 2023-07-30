#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_string(int num, string s);
void onerow(int hash_num, int space_num);

int main(void)
{
    // get height number
    int height = get_height();
    // loop tp print hash # row by row
    for (int i = 0; i < height; i++)
    {
        onerow(i + 1, height - i - 1);
    }
}

int get_height(void)
{
    int height;
    do {
        height = get_int("Height: ");
    }
    while(height < 1 || height > 8);
    return height;
}

void print_string(int num, string s)
{
    for (int i = 0; i < num; i++)
    {
        printf("%s",s);
    }
}

void onerow(int hash_num, int space_num)
{
    print_string(space_num, " ");
    print_string(hash_num, "#");
    printf("  ");
    print_string(hash_num, "#");
    printf("\n");
}

