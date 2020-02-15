//
//  SimpleParameter.hpp
//  parameters
//
//  Created by Hendrik Jennen on 10/31/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef SimpleParameter_hpp
#define SimpleParameter_hpp

#include <map>

#include "ParameterFunctions.hpp"

class SimpleParameter : public ParameterFunction
{
public:
    SimpleParameter(const std::map<double, double>& simpleParams);
 protected:
    virtual SimpleParameter* clone() const;
    
    virtual double getIntegral(double timeInit, double timeFin) const;
    virtual double getSqrIntegral(double timeInit, double timeFin) const;
private:
    std::map<double, double> simpleParams_;
    /* The simple function is modeled as \sum_i=0^n p_i 1_[t_i, t_(i+1))
     * where t_(n+1) -> infty. The keys store the t_i, the values the p_i.
     */
};

#endif /* SimpleParameter_hpp */