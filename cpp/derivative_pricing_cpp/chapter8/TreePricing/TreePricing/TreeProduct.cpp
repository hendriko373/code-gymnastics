//
//  TreeProduct.cpp
//  TreePricing
//
//  Created by Hendrik Jennen on 3/11/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <algorithm>

#include "TreeProduct.hpp"

using namespace std;

TreeProduct::TreeProduct(double maturity) : maturity_(maturity) {}

double TreeProduct::getMaturity() const
{
    return maturity_;
}

TreeEuropean::TreeEuropean(double maturity, const Handle<Payoff>& payoff)
    : TreeProduct(maturity), payoff_(payoff) {}

TreeEuropean* TreeEuropean::clone() const
{
    return new TreeEuropean(*this);
}

double TreeEuropean::getPayoff(double spot) const
{
    return (*payoff_)(spot);
}

double TreeEuropean::getPresentValue(double spot, double price) const
{
    return price;
}

TreeAmerican::TreeAmerican(double maturity, const Handle<Payoff>& payoff)
    : TreeProduct(maturity), payoff_(payoff) {}

TreeAmerican* TreeAmerican::clone() const
{
    return new TreeAmerican(*this);
}

double TreeAmerican::getPayoff(double spot) const
{
    return (*payoff_)(spot);
}

double TreeAmerican::getPresentValue(double spot, double price) const
{
    return max(getPayoff(spot), price);
}