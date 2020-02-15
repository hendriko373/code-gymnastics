//
//  BSfunctions.hpp
//  solvers
//
//  Created by Hendrik Jennen on 3/14/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef BSfunctions_hpp
#define BSfunctions_hpp

class BSCall
{
public:
    BSCall(double r, double d, double strike, double spot, double T);
    
    double operator()(double vol) const;
    
private:
    double r_;
    double d_;
    double strike_;
    double spot_;
    double T_;
};

class BSCallBis
{
public:
    BSCallBis(double r, double d, double strike, double spot, double T);
    
    double getPrice(double vol) const;
    double getVega(double vol) const;
    
private:
    double r_;
    double d_;
    double strike_;
    double spot_;
    double T_;
};

#endif /* BSfunctions_hpp */
