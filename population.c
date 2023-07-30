#include <stdio.h>
#include <cs50.h>

int end_population(int begin_p);
int get_size(int smallest_number, bool isStart);
int main(void)
{
    // get the start size
    int start_size = get_size(9, 1);
    // get the end size
    int end_size = get_size(start_size, 0);

    // init the number of years
    int n = 0;
    // loop to count n
    while (start_size < end_size)
    {
        start_size = end_population(start_size);
        n = n + 1;
    }
    // print the results
    printf("Years: %i\n", n);
}

int get_size(int smallest_number, bool isStart)
{
    int size;
    do {
        if (isStart) { size = get_int("Start size: ");}
        else { size = get_int("End size: ");}
    }
    while (size < smallest_number);
    return size;
}

int end_population(int begin_p)
{
    return begin_p - begin_p / 4 + begin_p / 3;
}

