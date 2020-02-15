//
//  Parameters.hpp
//  parameters
//
//  Created by Hendrik Jennen on 10/30/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef ParameterFunctions_hpp
#define ParameterFunctions_hpp

class ParameterFunction
{
    friend class Parameter;
public:
    virtual ~ParameterFunction(){}
    
protected:
    virtual ParameterFunction* clone() const =0;
    
    virtual double getIntegral(double timeInit, double timeFin) const =0;
    virtual double getSqrIntegral(double timeInit,
                                  double timeFin) const =0;
};

class ConstantParameter : public ParameterFunction
{
public:
    ConstantParameter(double constParam);
    
protected:
    virtual ConstantParameter* clone() const;
    
    virtual double getIntegral(double timeInit, double timeFin) const;
    virtual double getSqrIntegral(double timeInit, double timeFin) const;
    
private:
    double constParam_;
};

#endif /* ParametersFunctions_hpp */