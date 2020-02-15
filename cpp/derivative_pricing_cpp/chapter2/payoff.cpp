#include <algorithm>
#include <iostream>
#include "payoff.hpp"

using namespace std;

Payoff::Payoff(double strike, OptionType optionType)
        : strike_(strike), optionType_(optionType) {}

Payoff::Payoff(double barrierOne, double barrierTwo, OptionType optionType)
        : optionType_(optionType)
{
    if (barrierOne < barrierTwo) {
        strike_ = barrierOne;
        strikeTwo_ = barrierTwo;
    }
    else {
        strike_ = barrierTwo;
        strikeTwo_ = barrierOne;
    }
}

double Payoff::operator()(double spot) const
{
    if (optionType_ == call)
        return max(spot - strike_, 0.0);

    else if (optionType_ == put)
        return max(strike_ - spot, 0.0);

    else if (optionType_ == digitalCall) {
        if (spot > strike_)
            return 1;
        else return 0;
    }
    else if (optionType_ == digitalPut) {
        if (spot < strike_)
            return 1;
        else return 0;
    }
    else if (optionType_ == doubleDigital) {
        if (spot > strike_ && spot < strikeTwo_)
            return 1;
        else return 0;
    }
    else if (optionType_ == forward)
        return spot - strike_;
    else
        throw("Unkown option type found.");
}
