//
//  PayoffFactory.hpp
//  PayoffFactory
//
//  Created by Hendrik Jennen on 3/16/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef PayoffFactory_hpp
#define PayoffFactory_hpp

#include <map>
#include <string>

#include "payoff.hpp"

class IPayoffMaker; // Forward declaration

class PayoffFactory
{
public:
    static PayoffFactory& getInstance();
    
    void registerPayoff(std::string payoffID, IPayoffMaker* payoff);
    Payoff* createPayoff(std::string payoffID, double strike) const;
    
private:
    PayoffFactory(){}
    PayoffFactory(const PayoffFactory&);
    PayoffFactory& operator=(const PayoffFactory&);
    
    std::map<std::string, IPayoffMaker*> payoffMakers_;
};

class IPayoffMaker
{
public:
    virtual ~IPayoffMaker(){}
    virtual Payoff* create(double strike) const =0;
};

template <class T>
class PayoffMaker : public IPayoffMaker
{
public:
    PayoffMaker(std::string payoffID) {
        PayoffFactory::getInstance().registerPayoff(payoffID, this);
    }
    
    Payoff* create(double strike) const {
        return new T(strike);
    }
};

#endif /* PayoffFactory_hpp */
