//
//  VanillaOption.hpp
//  virtual_constr
//
//  Created by Hendrik Jennen on 10/29/15.
//
//

#ifndef VanillaOption_hpp
#define VanillaOption_hpp

#include "payoff.hpp"

class VanillaOption
{
public:
    VanillaOption(Payoff& payoff, double expiry);
    VanillaOption(const VanillaOption& option);
    VanillaOption& operator=(const VanillaOption& option);
    ~VanillaOption();
    
    double getPayoff(double spot) const;
    double getExpiry() const;
    
private:
    Payoff* payoff_;
    double expiry_;
};

#endif /* VanillaOption_hpp */