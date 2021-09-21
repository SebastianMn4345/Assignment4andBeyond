//Ararat Mesrobian
//CS302 Assignment 4
//9/20/2021
//Using threading
#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

int convertToInt(string input, int i);

vector<short> topNums;  //will be reading the input into these
vector<short> botNums;
vector<vector<short>> result;

int main(int argc, char* arg[])
{
    string input; //going to read the numbers then convert

    cout << "Enter number 1: " << endl;
    cin >> input;

    int size;
    size = input.size();
    for(int i = 0; i < size; i++)
    {
        topNums.push_back(convertToInt(input, i));
    }
    
    cout << "Enter number 2: " << endl;
    cin >> input;

    size = input.size();
    for(int i = 0; i < size; i++)
    {
        botNums.push_back(convertToInt(input, i));
    }

    //at this point the numbers have been read in and converted
    
    

    return 0;
}

//this will take in the input and convert it into an int
int convertToInt(string input, int i)
{
    int size = input.size();
    char temp2;
    int temp;

    temp2 = input[i];
    temp = temp2;
    temp -= 48;

    return temp;
}