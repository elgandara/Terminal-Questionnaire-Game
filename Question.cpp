// *********************************************************
// Filename: Question.cpp
// Description:
//
// Author:
// Created On:
// Last Modified:
// *********************************************************

#include "Question.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cmath>
#include <ctype.h>
#include <string>
using namespace std;

Question::Question()
{
    srand(time(NULL));
    file_name = "file.txt";

    for (int i = 0; i < 8; i++)
    {
        past_questions[i] = 0;
        for (int j = 0; j < 4; j++)
        {
            answers[i][j] = "";
        }
    }

    Question::createNewQuestion();
}

int Question::stringToInt(string str)
{
    int total = 0;
    int value = 0;
    bool isDigit = true;

    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[0]))
        {
            isDigit = false;
        }
    }

    if (isDigit)
    {
        for (unsigned int i = 0; i < str.length(); i++)
        {
            value = (str[i] - 48);
            total += value * pow(10, str.length() - 1 - i);
        }
    }
    else
        total = -1;

    return total;
}

void Question::displayAnswers()
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            cout << answers[row][col] << ", ";
        }
        cout << endl;
    }
}

void Question::createNewQuestion()
{
    ifstream in;
    string input;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            answers[i][j] = "";
        }
    }

    question_number = (rand() % 2) + 1;
    in.open(file_name.c_str());

    if(in.fail())       // Check to make sure the file opens properly
    {
        cout << "Error opening file " << file_name << endl;     // Will display message and exit program if file opening fails
        exit(1);
    }

    // For testing purposes
    //question_number = 1;
    // Ending testing code


    while (!in.eof() && Question::stringToInt(input) != question_number + 1)
    {
        getline(in, input, ',');        // Will get the first character of a line from a file
        while (input[0] == '\n')
        {
            input = input.substr(1, input.length());
        }

        if (Question::stringToInt(input) == question_number)
        {
            getline(in, question, ',');

            int row = 0;
            int col = 0;
            while (!in.eof() && Question::stringToInt(input) != question_number + 1)
            {
                getline(in, input, ',');
                while (input[0] == '\n')
                {
                    input = input.substr(1, input.length());
                }

                if (isdigit(input[0]) && Question::stringToInt(input) != question_number + 1)
                {
                    answers[row][3] = input;
                    row++;
                    col = 0;
                }
                else if (Question::stringToInt(input) != question_number + 1)
                {
                    answers[row][col] = input;
                    col++;
                }

            }
        }

        //cout << "Input:" << input << ":End" << endl;

    }

    in.close();     // Closes file

}

int Question::checkAnswers(string answer)     // returns row of answer if answer matches the possible answers, -1 otherwise
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (Question::tolowercase(answer) == Question::tolowercase(answers[row][col]))
            {
                return row;
            }
        }
    }

    return -1;
}

int Question::getScore(string answer)
{
    if (Question::checkAnswers(answer) != -1)
        return Question::stringToInt(answers[Question::checkAnswers(answer)][3]);
    else
        return 0;
}

string Question::tolowercase(string word)
{
    for (unsigned int i = 0; i < word.length(); i++)
    {
        word[i] = tolower(word[i]);
    }

    return word;
}
