//
//  VanillaOption.cpp
//  bridge
//
//  Created by Hendrik Jennen on 10/29/15.
//
//

#include "VanillaOption.hpp"
#include "PayoffBridge.hpp"

VanillaOption::VanillaOption(const PayoffBridge& payoffBridge,
        double expiry) : payoffBridge_(payoffBridge), expiry_(expiry) {}

double VanillaOption::getPayoff(double spot) const
{
    return payoffBridge_(spot);
}

double VanillaOption::getExpiry() const
{
    return expiry_;
}