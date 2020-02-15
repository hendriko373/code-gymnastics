//
//  AsianOption.cpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 2/1/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include <numeric>

#include "AsianOption.hpp"

using namespace std;

Asian::Asian(const vector<double>& lookTimes, const Handle<Payoff>& payoff,
             double maturity)
    : PathDependent(lookTimes), payoff_(payoff), maturity_(maturity) {}

Asian* Asian::clone() const
{
    return new Asian(*this);
}

unsigned long Asian::maxNoCashFlows() const
{
    return 1;
}

vector<double> Asian::possibleCashFlowTimes() const
{
    return vector<double>(1, maturity_);
}

unsigned long Asian::computeCashFlows(const vector<double> &spotValues,
                                      vector<CashFlow> &cashFlows) const
{
    double amount = accumulate(spotValues.begin(), spotValues.end(), 0.0);
    amount = amount/lookTimes_.size();
    amount = (*payoff_)(amount);
    
    CashFlow temp(amount, 0);
    cashFlows[0] = temp;
    
    return 1;
}
