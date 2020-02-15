//
//  Parameter.cpp
//  parameters
//
//  Created by Hendrik Jennen on 10/30/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include "Parameter.hpp"
#include "ParameterFunctions.hpp"

Parameter::Parameter(const ParameterFunction& paramFunction)
{
    parameter_ = paramFunction.clone();
}

Parameter::Parameter(const Parameter& parameter)
{
    parameter_ = parameter.parameter_->clone();
}

Parameter& Parameter::operator=(const Parameter& parameter)
{
    if (this != &parameter)
    {
        delete parameter_;
        parameter_ = parameter.parameter_->clone();
    }
    return *this;
}

Parameter::~Parameter()
{
    delete parameter_;
}