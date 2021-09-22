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
vector<vector<short>> finalResultVector; //the sorted and correct vector
vector<short> fillResult;
vector<thread> threadPool;  //this will help us keep track of the threads and maintain what they are assigned to, as well as make it easier to clear the thread
vector<short> additionVector;

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

    cout << "bottom number after conversion" << endl;
    for(int i = 0; i < botNums.size(); i++)
    {
        cout << botNums[i] << endl;
    }

    cout << "Top number after conversion" << endl;
    for(int i = 0; i < topNums.size(); i++)
    {
        cout << topNums[i] << endl;
    }
    //at this point the numbers have been read in and converted
    int row = 0;
    int col = 0;
    int carry = 0;
    int answer = 0;

    for(int i = botNums.size() - 1; i >= 0; i--)
    {
        int currentBotNum = 0;
        currentBotNum = botNums[i];
        cout << "botNums last number: " << currentBotNum << endl;

        //we have 9, now we multiply it through the topNum
        for(int j = topNums.size() - 1; j >= 0; j--)
        {
            int currentTopNum = 0; 
            currentTopNum = topNums[j];
            /*
            cout << "This is where j is at: " << j << endl;
            cout << "topNums last Number but with index at 1 operator: " << topNums[j] << endl;
            cout << "topNums last number: " << currentTopNum << endl;
            */
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
            //cout << "initial product(might be with a carry): " << product << endl;
            //cout << "Carry : " << carry << endl;
            //cout << "Answer to be stored: " << answer << endl;
            col++;
        }
        resultVector.push_back(fillResult);
        fillResult.clear();
        row++;
        col = 0;
        carry = 0;
    }

    //we will need to fill in the zeroes for the place values
    
    
    //lets rearrange the zeroes we just placed
    vector<short> tempVec;
    for(int i = 0; i < resultVector.size(); i++)
    {
        for(int j = resultVector[i].size() - 1; j >= 0; j--)
        {
            tempVec.push_back(resultVector[i][j]);
        }
        finalResultVector.push_back(tempVec);
        tempVec.clear();
    }
    
    for(int i = 0; i < finalResultVector.size(); i++)
    {
        if(i < finalResultVector.size())
        {
            for(int k = i; k > 0; k--)
            {
                finalResultVector[i].push_back(0);
            }
        }
    }

    //now lets insert leading 0's so that the index's in the vector can be aligned
    int finalRow;   //grab the final row which will have the highest offset(since we put zeroes into the back)
    finalRow = finalResultVector.size() - 1;
    //access the last row with finalRow
    int finalRowSize = 0;
    finalRowSize = finalResultVector[finalRow].size();
    //cout << "This is the size of the final row in finalRowVector: " << finalRowSize << endl; 
    for(int i = 0; i < finalResultVector.size(); i++)
    {
        if(finalResultVector[i].size() != finalRowSize)
        {
            while(finalResultVector[i].size() != finalRowSize)
            {
                finalResultVector[i].insert(finalResultVector[i].begin(), 0);
            }
        }
    }


    //now that the resultVector is filled, we will need to use long addition for the final result
    //we might also need to resort the entire list so that it goes using the opposite way
    //cout << "Now time to cout the finalresult 2d vector" << endl;
    for(int i = 0; i < finalResultVector.size(); i++)
    {
        for(int j = 0; j < finalResultVector[i].size(); j++)
        {
            //cout << finalResultVector[i][j];
        }
        //cout << endl;
    }

    carry = 0;
    //now lets add up the results of all this
    for(int col = finalRowSize - 1; col >= 0; col--)
    {
        int sum = 0;


        for(int row = 0; row < finalResultVector.size(); row++)
        {
            sum += finalResultVector[row][col];
        }

        sum = carry + sum;
        //we have the sum
        //need to check if there is a carry
        if(sum > 9)
        {
            carry = returnCarry(sum);
            answer = returnAnswer(sum);
        }
        else
        {
            carry = 0;
            answer = sum;
        }

        if(col == 0)
        {
            if(carry == 0)
            {
                additionVector.insert(additionVector.begin(), answer);
            }
            else
            {
                additionVector.insert(additionVector.begin(), answer);
                additionVector.insert(additionVector.begin(), carry);
            }
        }
        else
        {
            additionVector.insert(additionVector.begin(), answer);
        }
        
        //cout << "Addition sum: " << sum << endl;
        //cout << "Addition carry: " << carry << endl;
         
    }

    //cout << "Printing the addition VECTOR" << endl;
    for(int i = 0; i < additionVector.size(); i++)
    {
        cout << additionVector[i];
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