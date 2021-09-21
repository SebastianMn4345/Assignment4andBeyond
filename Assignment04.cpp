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
int returnCarry(int product);  //takes the product of multiplication, and returns the carry-over
int returnAnswer(int product);


mutex t_lock;   //Will be used in conjunction with the threads to lock them
vector<short> topNums;  //multiplicand
vector<short> botNums;  //multiplier
vector<vector<short>> resultVector;   //Stores the result of the individual multiplication at the place value
vector<short> fillResult;
vector<thread> threadPool;  //this will help us keep track of the threads and maintain what they are assigned to, as well as make it easier to clear the thread

int maxThreads = thread::hardware_concurrency();    //will be using this to check how many threads the pc running this program has. Need to use this throughout the program.

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
    int row = 0;
    int col = 0;
    int carry = 0;
    int answer = 0;

    for(int i = botNums.size() - 1; i >= 0; i--)
    {
        int currentBotNum;
        currentBotNum = topNums[i];
        cout << "botNums last number: " << currentBotNum << endl;
         if(i > 0)
        {
            for(int k = 0; k < i; k++)
            {
                fillResult.push_back(0);
            }
        }

        //we have 9, now we multiply it through the topNum
        for(int j = topNums.size() - 1; j >= 0; j--)
        {
            int currentTopNum; 
            currentTopNum = botNums[j];
            cout << "topNums last number: " << currentTopNum << endl;

            int product = currentBotNum * currentTopNum;
        //=============================================================
            if(carry > 0)   //if there was a previous carry;
            {
                product = product + carry;
            }
            else
            {
            }
        //============================================================
            if(product > 9) //means that there is a carry
            {
                carry = returnCarry(product);
                answer = returnAnswer(product);
                //store answer at the end of vector, and then move to left
            }
            else
            {
                answer = product;
                carry = 0; //reset carry since there isn't one
            }
        //=======================================================
            if(j == 0)
            {
                //we're checking to see if we need to store the carry, if we are on the last operation
                if(carry == 0)
                {
                    fillResult.push_back(answer);
                }
                else
                {
                    //store the answer first and then the carry, we will rearrange the vector.
                    fillResult.push_back(answer);
                    fillResult.push_back(carry);
                }
            }
            else
            {
                fillResult.push_back(answer);
            }
        //=======================================================
            cout << "initial product(might be with a carry): " << product << endl;
            cout << "Carry : " << carry << endl;
            cout << "Answer to be stored: " << answer << endl;

            //fillResult.push_back(answer);

            col++;
        }
        resultVector.push_back(fillResult);
        fillResult.clear();
        row++;
        col = 0;
        carry = 0;
    }

    //we are going to want to reverse the vectors so that they are the correct orientation for the result


    //now that the resultVector is filled, we will need to use long addition for the final result
    //we might also need to resort the entire list so that it goes using the opposite way
    cout << "Now time to cout the result 2d vector" << endl;
    for(int i = 0; i < resultVector.size(); i++)
    {
        for(int j = 0; j < resultVector[i].size(); j++)
        {
            cout << resultVector[i][j];
        }
        cout << endl;
    }











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

//returns the int that we will be carrying over to ADD to the next place value result
int returnCarry(int product)
{
    int carry;
    carry = product / 10;
    return carry;
}

//returns the palce value's current answer that will be put into the 2d vector
int returnAnswer(int product)
{
    int answer;
    answer = product % 10;
    return answer;
}