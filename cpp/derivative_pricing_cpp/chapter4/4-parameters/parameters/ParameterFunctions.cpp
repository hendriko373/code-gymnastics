//
//  Parameters.cpp
//  parameters
//
//  Created by Hendrik Jennen on 10/30/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include "ParameterFunctions.hpp"

ConstantParameter::ConstantParameter(double constParam) : constParam_(constParam)
{}

ConstantParameter* ConstantParameter::clone() const
{
    return new ConstantParameter(*this);
}

double ConstantParameter::getIntegral(double timeInit, double timeFin) const
{
    return constParam_*(timeFin-timeInit);
}

double ConstantParameter::getSqrIntegral(double timeInit, double timeFin) const
{
    return constParam_*constParam_*(timeFin-timeInit);
}
