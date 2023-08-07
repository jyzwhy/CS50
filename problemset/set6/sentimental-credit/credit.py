from cs50 import get_string


def check_length(card_number):
    if len(card_number) in [13, 15, 16]:
        return True
    else:
        return False


def check_head(card_number):
    num = int(card_number[0:2])

    if num == 34 or num == 37:
        return 'AMEX'
    elif 51 <= num <= 55:
        return 'MASTERCARD'
    elif 40 <= num <= 49:
        return 'VISA'
    else:
        return 'INVALID'


def sum_digit(digit):
    double = 2 * int(digit)
    double = str(double)
    double += '0'
    return int(double[1]) + int(double[0])


def check_valid(card_number):
    digit_sum = 0
    length = len(card_number)
    for i in range(length):
        if (length - i - 1) % 2 == 1:
            digit_sum += sum_digit(card_number[i])
        else:
            digit_sum += int(card_number[i])
    if digit_sum % 10 == 0:
        return True
    else:
        return False


number = get_string("Number: ")
if check_length(number):
    bank = check_head(number)
    if bank == 'INVALID':
        print(bank)
    elif check_valid(card_number=number):
        print(bank)
    else:
        print("INVALID")
else:
    print("INVALID")
