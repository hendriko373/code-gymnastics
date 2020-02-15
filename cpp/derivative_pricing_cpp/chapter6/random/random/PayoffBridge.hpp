//
//  PayoffBridge.hpp
//  bridge
//
//  Created by Hendrik Jennen on 10/29/15.
//
//

#ifndef PayoffBridge_hpp
#define PayoffBridge_hpp

#include "payoff.hpp"

class PayoffBridge
{
public:
    PayoffBridge(const Payoff& payoff);
    PayoffBridge(const PayoffBridge& payoffBridge);
    PayoffBridge& operator=(const PayoffBridge& payoffBridge);
    ~PayoffBridge();

    inline double operator()(double spot) const;
private:
    Payoff* payoff_;
};

inline double PayoffBridge::operator()(double spot) const
{
    return (*payoff_)(spot);
}

#endif /* PayoffBridge_hpp */
