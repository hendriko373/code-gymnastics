//
//  RandomParkMiller.cpp
//  random
//
//  Created by Hendrik Jennen on 11/9/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include "RandomParkMiller.hpp"

using namespace std;

RandomParkMiller::RandomParkMiller(unsigned long dimensionality,
                                   unsigned long seed)
: Random(dimensionality), generator(seed), seed_(seed)
{
    reciprocal_ = 1.0/(1.0+ParkMiller::max());
}

RandomParkMiller* RandomParkMiller::clone() const
{
    return new RandomParkMiller(*this);
}

void RandomParkMiller::getUniforms(vector<double> &variates)
{
    for (vector<double>::iterator i = variates.begin();
         i != variates.begin() + getDimensionality(); ++i) {
        *i = generator.generateRandomInteger() * reciprocal_;
    }
}

void RandomParkMiller::skip(unsigned long noPaths)
{
    vector<double> temp(getDimensionality());
    for (unsigned long i = 0; i != noPaths; ++i) {
        getUniforms(temp);
    }
}

void RandomParkMiller::setSeed(unsigned long seed)
{
    seed_ = seed;
    generator.setSeed(seed);
}

void RandomParkMiller::reset()
{
    generator.setSeed(seed_);
}

void RandomParkMiller::setDimensionality(unsigned long dimensionality)
{
    Random::setDimensionality(dimensionality);
    generator.setSeed(seed_);
}