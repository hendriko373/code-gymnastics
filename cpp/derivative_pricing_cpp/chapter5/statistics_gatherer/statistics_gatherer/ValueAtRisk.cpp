//
//  ValueAtRisk.cpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/4/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include <algorithm>
#include <cmath>
#include "ValueAtRisk.hpp"

using namespace std;

ValueAtRisk::ValueAtRisk(double alpha) : alpha_(alpha) {}

ValueAtRisk* ValueAtRisk::clone() const
{
    return new ValueAtRisk(*this);
}

void ValueAtRisk::dumpResult(double result)
{
    sampleValues_.push_back(result);
}

vector<vector<double>> ValueAtRisk::getStatistics() const
{
    vector<vector<double>> ret(1);
    
    vector<double> temp(sampleValues_);
    sort(temp.begin(), temp.end());
    vector<double>::size_type q = round(alpha_*sampleValues_.size());
    ret.begin()->push_back(temp[q]);
    
    return ret;
}