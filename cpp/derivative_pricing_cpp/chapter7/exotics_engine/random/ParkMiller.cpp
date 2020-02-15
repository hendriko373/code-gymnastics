//
//  ParkMiller.cpp
//  random
//
//  Created by Hendrik Jennen on 11/9/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include "ParkMiller.hpp"

const long a = 16807;
const long m = 2147483647;
const long q = 127773;
const long r = 2836;

ParkMiller::ParkMiller(long seed) : seed_(seed)
{
    if (seed_ == 0)
        seed_ = 1;
}

void ParkMiller::setSeed(long seed)
{
    seed_ = seed;
}

long ParkMiller::generateRandomInteger()
{
    long k = seed_/q;
    seed_ = a*(seed_ - k*q) - r*k;
    if (seed_ < 0)
        seed_ += m;
    return seed_;
}

unsigned long ParkMiller::max()
{
    return m-1;
}

unsigned long ParkMiller::min()
{
    return 1;
}