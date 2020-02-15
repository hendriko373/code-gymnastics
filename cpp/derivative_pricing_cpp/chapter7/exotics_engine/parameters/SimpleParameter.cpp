//
//  SimpleParameter.cpp
//  parameters
//
//  Created by Hendrik Jennen on 10/31/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <map>
#include <cmath>
#include <iostream>

#include "SimpleParameter.hpp"

using namespace std;

SimpleParameter::SimpleParameter(const map<double, double>& simpleParams)
                    : simpleParams_(simpleParams) {};

SimpleParameter* SimpleParameter::clone() const
{
    return new SimpleParameter(*this);
}

double SimpleParameter::getIntegral(double timeInit, double timeFin) const
{
    map<double, double>::const_iterator i = simpleParams_.begin();
    
    // If simpleParams_ is empty we return 0
    if (i == simpleParams_.end())
        return 0;
    
    // Look for element in simpleParams_ whose time follows timeInit directly
    while (i != simpleParams_.end() && timeInit >= i->first)
        ++i;
    
    // init points to the element whose time comes directly before timeInit
    map<double, double>::const_iterator init = --i;
    
    // final points to the element whose time comes directly before timeFin
    while (i != simpleParams_.end() && timeFin >= i->first)
        ++i;
        
    map<double, double>::const_iterator final = --i;
    
    if (init == final)
        return init->second * (timeFin - timeInit);
    
    i = init;
    map<double, double>::const_iterator j = ++i;
    
    double total = init->second * (j->first - timeInit);
    ++j;
    while (i != final) {
        total += i->second * (j->first - i->first);
        ++i;
        ++j;
    }
    total += final->second * (timeFin - i->first);
    
    return total;
}

double SimpleParameter::getSqrIntegral(double timeInit, double timeFin) const
{
    map<double, double>::const_iterator i = simpleParams_.begin();
    
    // If simpleParams_ is empty we return 0
    if (i == simpleParams_.end())
        return 0;
    
    // Look for element in simpleParams_ whose time follows timeInit directly
    while (i != simpleParams_.end() && timeInit >= i->first)
        ++i;
    
    // init points to the element whose time comes directly before timeInit
    map<double, double>::const_iterator init = --i;
    
    // final points to the element whose time comes directly before timeFin
    while (i != simpleParams_.end() && timeFin >= i->first)
        ++i;
    
    map<double, double>::const_iterator final = --i;
    
    if (init == final)
        return pow(init->second, 2) * (timeFin - timeInit);
    
    i = init;
    map<double, double>::const_iterator j = ++i;
    
    double total = pow(init->second, 2) * (j->first - timeInit);
    ++j;
    while (i != final) {
        total += pow(i->second, 2) * (j->first - i->first);
        ++i;
        ++j;
    }
    total += pow(final->second, 2) * (timeFin - i->first);
    
    return total;
}