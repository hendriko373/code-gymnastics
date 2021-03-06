//
//  VanillaOption.hpp
//  first_sol
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
    
    double getPayoff(double spot) const;
    double getExpiry() const;
    
private:
    Payoff& payoff_;
    double expiry_;
};

#endif /* VanillaOption_hpp */