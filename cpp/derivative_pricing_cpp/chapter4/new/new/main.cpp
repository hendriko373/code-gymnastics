//
//  main.cpp
//  new
//
//  Created by Hendrik Jennen on 11/1/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <iostream>
#include <chrono>

using namespace std;
using Clock = chrono::high_resolution_clock;

chrono::microseconds getTimeDynamical(size_t size)
{
    double* pointers[10000];
    
    Clock::time_point tI = Clock::now();

    for (size_t i = 0; i != 10000; ++i)
        pointers[i] = new double[size];
    
    Clock::time_point tF = Clock::now();
    
    chrono::microseconds time = chrono::duration_cast<chrono::microseconds>
                                                                    (tF-tI);
    
    for (size_t i = 0; i != 10000; ++i)
        delete[] pointers[i];
    
    return time;
}

chrono::microseconds getTimeAutomatic(size_t size)
{
    Clock::time_point tI = Clock::now();
    
    for (size_t i = 0; i != 10000; ++i)
        double temp[size];
    
    Clock::time_point tF = Clock::now();
    
    chrono::microseconds time = chrono::duration_cast<chrono::microseconds>
                                                                (tF-tI);
    
    return time;
}

int main(int argc, const char * argv[]) {
    
    cout << getTimeDynamical(200000).count() << endl;
    cout << getTimeAutomatic(200000).count() << endl;
    
    return 0;
}
