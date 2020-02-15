//
//  PayoffBridge.cpp
//  bridge
//
//  Created by Hendrik Jennen on 10/29/15.
//
//

#include "PayoffBridge.hpp"
#include "payoff.hpp"

PayoffBridge::PayoffBridge(const Payoff& payoff)
{
    payoff_ = payoff.clone();
}

PayoffBridge::PayoffBridge(const PayoffBridge& payoffBridge)
{
    payoff_ = payoffBridge.payoff_->clone();
}

PayoffBridge& PayoffBridge::operator=(const PayoffBridge& payoffBridge)
{
    if (this != &payoffBridge)
    {
        delete payoff_;
        payoff_ = payoffBridge.payoff_->clone();
    }
    return *this;
}

PayoffBridge::~PayoffBridge()
{
    delete payoff_;
}