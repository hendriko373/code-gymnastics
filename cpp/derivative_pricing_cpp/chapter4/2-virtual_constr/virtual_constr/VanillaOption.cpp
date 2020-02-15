//
//  VanillaOption.cpp
//  virtual_constr
//
//  Created by Hendrik Jennen on 10/29/15.
//
//

#include "VanillaOption.hpp"
#include "payoff.hpp"

VanillaOption::VanillaOption(Payoff& payoff, double expiry)
    : expiry_(expiry)
{
    payoff_ = payoff.clone();
}

VanillaOption::VanillaOption(const VanillaOption& option)
    : expiry_(option.getExpiry())
{
    payoff_ = option.payoff_->clone();
}

VanillaOption& VanillaOption::operator=(const VanillaOption& option)
{
    if (this != &option)
    {
        delete payoff_;
        expiry_ = option.expiry_;
        payoff_ = option.payoff_->clone();
    }
    return *this;
}

VanillaOption::~VanillaOption()
{
    delete payoff_;
}

double VanillaOption::getPayoff(double spot) const
{
    return (*payoff_)(spot);
}

double VanillaOption::getExpiry() const
{
    return expiry_;
}