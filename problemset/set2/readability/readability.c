#include <cs50.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Test: ");
    int letter_num = count_letters(text);
    int word_num = count_words(text);
    int sentence_num = count_sentences(text);
    float grade = 0.0588 * letter_num * 100 / ((float) word_num) - 0.296 * sentence_num * 100 / ((float) word_num) - 15.8;
    int Grade = grade + 0.5;
    if (Grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (Grade < 16)
    {
        printf("Grade %i\n", Grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int index = 0, count = 0;
    while(text[index] != '\0')
    {
        if ((text[index] >= 'a' && text[index] <= 'z') || (text[index] >= 'A' && text[index] <= 'Z'))
        {
            count += 1;
        }
        index++;
    }
    return count;
}

int count_words(string text)
{
    int index = 0, count = 0;
    bool begin = false;
    while(text[index] != '\0')
    {
        if(text[index] != ' ')
        {
            if (begin == false)
            {
                count ++;
                begin = true;
            }
        }
        else
        {
            begin = false;
        }
        index ++;
    }
    return count;
}

int count_sentences(string text)
{
    int index = 0, count = 0;
    bool begin = false;
    while(text[index] != '\0')
    {
        if (text[index] != '!' && text[index] != '.' && text[index] != '?')
        {
            if (begin == false)
            {
                begin = true;
            }
        }
        else
        {
            if(begin == true)
            {
                count ++;
            }
            begin = false;
        }
        index ++;
    }
    return count;
}
