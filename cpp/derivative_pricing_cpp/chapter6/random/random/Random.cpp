//
//  Random.cpp
//  random
//
//  Created by Hendrik Jennen on 11/9/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include "Random.hpp"
#include "Normals.h"

using namespace std;

Random::Random(unsigned long dimensionality) : dimensionality_(dimensionality) {}

void Random::getGaussians(std::vector<double>& variates)
{
    getUniforms(variates);
    for (vector<double>::iterator i = variates.begin();
         i != variates.begin()+dimensionality_; ++i) {
        *i = InverseCumulativeNormal(*i);
    }
}

void Random::setDimensionality(unsigned long dimensionality)
{
    dimensionality_ = dimensionality;
}