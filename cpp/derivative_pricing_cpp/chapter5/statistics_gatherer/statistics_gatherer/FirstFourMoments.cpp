//
//  FirstFourMoments.cpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/4/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include <cmath>
#include "FirstFourMoments.hpp"

using namespace std;

FirstFourMoments::FirstFourMoments() : noPaths_(0UL)
{
    vector<double> temp(4, 0);
    runningSum_ = temp;
}

FirstFourMoments* FirstFourMoments::clone() const
{
    return new FirstFourMoments(*this);
}

void FirstFourMoments::dumpResult(double result)
{
    for (vector<double>::size_type i = 0; i != runningSum_.size(); ++i) {
        runningSum_[i] += pow(result, i+1);
    }
    ++noPaths_;
}

vector<vector<double>> FirstFourMoments::getStatistics() const
{
    vector<double> temp = runningSum_;
    for (vector<double>::iterator i = temp.begin(); i != temp.end(); ++i) {
        *i = *i/noPaths_;
    }
    vector<vector<double>> ret(1, temp);
    return ret;
}