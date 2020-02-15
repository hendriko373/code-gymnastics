//
//  Parameter.hpp
//  parameters
//
//  Created by Hendrik Jennen on 10/30/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef Parameter_hpp
#define Parameter_hpp

#include "ParameterFunctions.hpp"

// Handle class for ParameterFunction
class Parameter
{
public:
    Parameter(const ParameterFunction& paramFunction);
    Parameter(const Parameter& parameter);
    Parameter& operator=(const Parameter& parameter);
    ~Parameter();
    
    inline double getIntegral(double timeInit, double timeFin) const;
    inline double getSqrIntegral(double timeInit, double timeFin) const;
    
private:
    ParameterFunction* parameter_;
};

inline double Parameter::getIntegral(double timeInit, double timeFin) const
{
    return parameter_->getIntegral(timeInit, timeFin);
}

inline double Parameter::getSqrIntegral(double timeInit, double timeFin) const
{
    return parameter_->getSqrIntegral(timeInit, timeFin);
}

#endif /* Parameter_hpp */