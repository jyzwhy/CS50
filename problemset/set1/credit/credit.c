#include <cs50.h>
#include <stdio.h>

int get_dignum(long number);
bool isValid(long number, int dig_num);
string isWhichBank(int bank_num);
long pow10(int num);
int sum_dig(int num);

int main(void)
{
    // Get the number
    long number = get_long("Number: ");
    // Get the num of digits of the number
    int dig_num = get_dignum(number);
    // Get bank code prefix
    int bank_num = (int) (number / pow10(dig_num - 2));
    // Get bank name
    string bank = isWhichBank(bank_num);

    if (bank[0] == "I")
    {
        printf("%s", bank);
    }
    else
    {
        // validate whether the number is valid
        bool isvalid = isValid(number, dig_num);
        if (isvalid)
        {
            // If valid, print the name of bank
            printf("%s", bank);
        }
        else
        {
            // If not valid, print INVALID
            printf("INVALID\n");
        }
    }
}

int get_dignum(long number)
{
    int i = 0;
    while (number != 0)
    {
        number /= 10;
        i++;
    }
    return i;
}

long pow10(int num)
{
    long pow = 1;
    for (int i = 0; i < num; i++)
    {
        pow *= 10;
    }
    return pow;
}

bool isValid(long number, int dig_num)
{
    // Detecting incorrect input
    if (dig_num != 16 && dig_num != 15 && dig_num != 13)
    {
        return 0;
    }

    // checksum
    int double_sum = 0, sum = 0;
    for (int i = 0; i < dig_num; i++)
    {
        if (i % 2 == 0)
        {
            sum += (number % 10);
        }
        else
        {
            double_sum += sum_dig(2 * (number % 10));
        }
        number = number / 10;
    }
    sum += double_sum;

    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string isWhichBank(int bank_num)
{
    if (bank_num == 34 || bank_num == 37)
    {
        return "AMEX\n";
    }
    else if (bank_num >= 40 && bank_num < 50)
    {
        return "VISA\n";
    }
    else if (bank_num >= 51 && bank_num <= 55)
    {
        return "MASTERCARD\n";
    }
    else
    {
        return "INVALID\n";
    }
}

int sum_dig(int num)
{
    int sum = 0;
    while (num != 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}
