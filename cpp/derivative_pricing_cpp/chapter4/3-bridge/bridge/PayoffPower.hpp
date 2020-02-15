#ifndef PAYOFFPOWER_HPP
#define PAYOFFPOWER_HPP

#include "payoff.hpp"

class PayoffPower : public Payoff
{
public:
    PayoffPower(double strike, double power);
    virtual ~PayoffPower(){}

    virtual double operator()(double spot) const;
    
protected:
    virtual PayoffPower* clone() const;
    
private:
    double strike_;
    double power_;
};

#endif
