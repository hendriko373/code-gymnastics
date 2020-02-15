//
//  BSfunctions.cpp
//  solvers
//
//  Created by Hendrik Jennen on 3/14/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include "BSfunctions.hpp"
#include "BlackScholesFormulas.hpp"

BSCall::BSCall(double r, double d, double strike, double spot, double T)
    : r_(r), d_(d), strike_(strike), spot_(spot), T_(T) {}

double BSCall::operator()(double vol) const
{
    return BlackScholesCall(spot_, strike_, r_, d_, vol, T_);
}

BSCallBis::BSCallBis(double r, double d, double strike, double spot, double T)
    : r_(r), d_(d), strike_(strike), spot_(spot), T_(T) {}

double BSCallBis::getPrice(double vol) const
{
    return BlackScholesCall(spot_, strike_, r_, d_, vol, T_);
}

double BSCallBis::getVega(double vol) const
{
    return BlackScholesCallVega(spot_, strike_, r_, d_, vol, T_);
}
