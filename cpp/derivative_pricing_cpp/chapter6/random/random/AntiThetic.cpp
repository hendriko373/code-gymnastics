//
//  AntiThetic.cpp
//  random
//
//  Created by Hendrik Jennen on 11/10/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include "AntiThetic.hpp"
#include "Handle.hpp"

using namespace std;

AntiThetic::AntiThetic(const Handle<Random>& random)
    : Random(*random), random_(random),
        antiTheticVariates(getDimensionality()), atOdd(true)
{
    random_->reset();
}

AntiThetic* AntiThetic::clone() const
{
    return new AntiThetic(*this);
}

void AntiThetic::getUniforms(vector<double> &variates)
{
    if (atOdd) {
        random_->getUniforms(variates);
        
        for (vector<double>::size_type i = 0; i != getDimensionality(); ++i)
            antiTheticVariates[i] = 1-variates[i];
        atOdd = false;
    }
    else {
        for (vector<double>::size_type i = 0; i != getDimensionality(); ++i)
            variates[i] = antiTheticVariates[i];
        atOdd = true;
    }
}

void AntiThetic::skip(unsigned long noPaths)
{
    if (!atOdd) {
        atOdd = true;
        --noPaths;
    }
    random_->skip(noPaths/2);
    
    if (noPaths%2) {
        vector<double> temp(getDimensionality());
        getUniforms(temp);
    }
}

void AntiThetic::setSeed(unsigned long seed)
{
    random_->setSeed(seed);
    atOdd = true;
}

void AntiThetic::reset()
{
    atOdd = true;
    random_->reset();
}

void AntiThetic::setDimensionality(unsigned long dimensionality)
{
    Random::setDimensionality(dimensionality);
    random_->setDimensionality(dimensionality);
    antiTheticVariates.resize(dimensionality);
}