//
//  MC_Statistics.cpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/1/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <vector>

#include "MC_Statistics.hpp"

using namespace std;

Mean::Mean() : runningSum_(0), noPaths_(0UL) {}

Mean* Mean::clone() const
{
    return new Mean(*this);
}

void Mean::dumpResult(double result)
{
    runningSum_ += result;
    ++noPaths_;
}

vector<vector<double>> Mean::getStatistics() const
{
    vector<vector<double>> ret(1);
    ret[0].resize(1);
    
    ret[0][0] = runningSum_/noPaths_;
    return ret;
}