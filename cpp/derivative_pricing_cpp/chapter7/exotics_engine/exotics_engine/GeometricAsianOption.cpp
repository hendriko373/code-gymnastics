//
//  GeometricAsianOption.cpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 3/2/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

#include "GeometricAsianOption.hpp"

using namespace std;

AsianGeometric::AsianGeometric(const vector<double>& lookTimes,
                               const Handle<Payoff>& payoff,
                               double maturity)
    : Asian(lookTimes, payoff, maturity) {}

AsianGeometric* AsianGeometric::clone() const
{
    return new AsianGeometric(*this);
}

unsigned long AsianGeometric::computeCashFlows(
                                const std::vector<double>& spotValues,
                                vector<CashFlow>& cashFlows) const
{
    vector<double> logSpotValues(spotValues.size());
    transform(spotValues.begin(), spotValues.end(), logSpotValues.begin(), ::log);
    double amount = accumulate(logSpotValues.begin(), logSpotValues.end(), 0.0);
    amount = exp(amount/lookTimes_.size());
    amount = (*payoff_)(amount);
    
    CashFlow temp(amount, 0UL);
    cashFlows[0] = temp;
    
    return 1;
}