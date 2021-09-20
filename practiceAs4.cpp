#include <iostream>
#include <vector>
#include <mutex>
#include <string>
#include <thread>

using namespace std;


void factorial(int x);
mutex t_lock;

int main()
{
    vector<thread> threadPool; //a vector of threads makes the process simpler, because we can access the different parts of the vector thus the threads, easier
    int maxThreads = thread::hardware_concurrency(); //This lets you know how many you can spawn, this helps you can access more threads than the pc can handle




    for(int i = 1; i <= 10; i++)
    {
        threadPool.push_back(thread(factorial, i));
        //So we spawn a thread using thread(), that thread will spawn an instance of the function
        //that thread will finish the function and pass in the result into the threadPool
        //threadPool[0] is out first thread
        //we will want to wait to make sure they are all done

        //checking to see if we have exceeding the amount of threads
        if(threadPool.size() % maxThreads == 0)
        {
            for(int i = 0; i < threadPool.size(); i++)
            {
                threadPool[i].join();
            }
            threadPool.clear(); //this will join all the threads together, and then clear the threads
        }
    }
    
    for(int i = 0; i < threadPool.size(); i++)
    {
        threadPool[i].join();   //This will make sure that all of the threads are done accessing the function and everything will be put into the vector
        //g++ -pthread practiceAs4.cpp
    }
   
    threadPool.clear(); //all of these joined threads are no longer running, the threads are simply remains since they have been used, so we clear
    //also deallocates the elements and makes sure we are accessing a dead thread,

    for(int i = 1; i <= 10; i++)
    {
        threadPool.push_back(thread(factorial, i));
        //So we spawn a thread using thread(), that thread will spawn an instance of the function
        //that thread will finish the function and pass in the result into the threadPool
        //threadPool[0] is out first thread
        //we will want to wait to make sure they are all done
    }
    //and then we can spawn more threads without worrying about the other ones


    cout << "All done" << endl;
    return 0;
}


void factorial(int n )
{
    unsigned long long r = 1; //since the numbers can get very large we dont want to overwrite anything, so make sure to use the correce size
    for(int i = 1; i <= n; i++)
    {
        r = r * i;
    }
    t_lock.lock();
    cout << n << "=" << r << endl;  //So the first thread that reaches this get a token, then every other thread is waiting for this thread to be unlocked, and then it keeps going
    t_lock.unlock();
}

//written at 8:45, with the first version of this code, every thread is trying to access the function and each thread has different speeds, so this will give undefined output
//this is where locking the thread comes into play, so that they can be finished before the others access the function. 
//we want the correct parts to be locked, so we still want them to compute their answer, but we want the cout to be done separately.
//at 8:48, we added the lock functions, we want to make sure this is placed in the right time, since they calculate their own individual parts of the factorial we can keep that
//MAKE SURE TO ALWAYS UNLOCK THE THREAD