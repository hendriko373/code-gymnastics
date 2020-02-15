//
//  Parameters.hpp
//  parameters
//
//  Created by Hendrik Jennen on 10/30/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef Parameter_hpp
#define Parameter_hpp

class Parameter
{
public:
    virtual ~Parameter(){}
    virtual Parameter* clone() const =0;
    
    virtual double getIntegral(double timeInit, double timeFin) const =0;
    virtual double getSqrIntegral(double timeInit,
                                  double timeFin) const =0;
};

class ConstantParameter : public Parameter
{
public:
    ConstantParameter(double constParam);
    virtual ConstantParameter* clone() const;
    
    virtual double getIntegral(double timeInit, double timeFin) const;
    virtual double getSqrIntegral(double timeInit, double timeFin) const;
    
private:
    double constParam_;
};

#endif /* ParametersFunctions_hpp */