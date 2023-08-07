from cs50 import get_string


def count_letters(text):
    count = 0
    for letter in text:
        if 'a' <= letter.lower() <= 'z':
            count += 1
    return count


def count_words(text):
    count = 0
    begin = False
    for letter in text:
        if letter != ' ':
            if not begin:
                count += 1
                begin = True
        else:
            begin = False
    return count


def count_sentences(text):
    count = 0
    begin = False
    for letter in text:
        if letter not in ['!', '.', '?']:
            if not begin:
                begin = True
        else:
            if begin:
                count += 1
            begin = False
    return count


def main():
    text = get_string("Text: ")
    letter_num = count_letters(text)
    word_num = count_words(text)
    sentence_num = count_sentences(text)

    grade = 0.0588 * letter_num * 100 / word_num - 0.296 * sentence_num * 100 / word_num - 15.8 + 0.5
    grade = int(grade)
    if grade < 1:
        print("Before Grade 1")
    elif grade < 16:
        print(f'Grade {grade}')
    else:
        print("Grade 16+")


main()
