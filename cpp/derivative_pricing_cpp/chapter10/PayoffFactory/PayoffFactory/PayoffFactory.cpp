//
//  PayoffFactory.cpp
//  PayoffFactory
//
//  Created by Hendrik Jennen on 3/16/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <map>
#include <string>
#include <stdexcept>

#include "PayoffFactory.hpp"

using namespace std;

PayoffFactory& PayoffFactory::getInstance()
{
    static PayoffFactory theFactory;
    return theFactory;
}

void PayoffFactory::registerPayoff(string payoffID, IPayoffMaker* payoff)
{
    payoffMakers_.insert(pair<string, IPayoffMaker*>(payoffID, payoff));
}

Payoff* PayoffFactory::createPayoff(string payoffID, double strike) const
{
    map<string, IPayoffMaker*>::const_iterator i = payoffMakers_.find(payoffID);
    
    if (i == payoffMakers_.end()) {
        throw runtime_error("Unknown payoff ID given.");
    }
    
    return (i->second)->create(strike);
}