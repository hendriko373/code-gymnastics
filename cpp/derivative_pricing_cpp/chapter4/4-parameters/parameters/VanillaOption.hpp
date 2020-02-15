//
//  VanillaOption.hpp
//  bridge
//
//  Created by Hendrik Jennen on 10/29/15.
//
//

#ifndef VanillaOption_hpp
#define VanillaOption_hpp

#include "PayoffBridge.hpp"

class VanillaOption
{
public:
    VanillaOption(const PayoffBridge& payoffBridge, double expiry);
    
    double getPayoff(double spot) const;
    double getExpiry() const;
private:
    PayoffBridge payoffBridge_;
    double expiry_;
};

#endif /* VanillaOption_hpp */
