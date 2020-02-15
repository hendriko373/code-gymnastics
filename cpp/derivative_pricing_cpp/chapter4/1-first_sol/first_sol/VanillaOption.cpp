//
//  VanillaOption.cpp
//  first_sol
//
//  Created by Hendrik Jennen on 10/29/15.
//
//

#include "VanillaOption.hpp"
#include "payoff.hpp"

VanillaOption::VanillaOption(Payoff& payoff, double expiry)
    : payoff_(payoff), expiry_(expiry) {}

double VanillaOption::getPayoff(double spot) const
{
    return payoff_(spot);
}

double VanillaOption::getExpiry() const
{
    return expiry_;
}