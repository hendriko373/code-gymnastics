#include <algorithm>
#include "payoff.hpp"

using namespace std;

PayoffCall::PayoffCall(double strike) : strike_(strike) {}

double PayoffCall::operator()(double spot) const
{
    return max(spot - strike_, 0.0);
}

PayoffPut::PayoffPut(double strike) : strike_(strike) {}

double PayoffPut::operator()(double spot) const
{
    return max(strike_ - spot, 0.0);
}

PayoffDoubleDig::PayoffDoubleDig(double lowBarrier, double highBarrier)
    : lowBarrier_(lowBarrier), highBarrier_(highBarrier) {}

double PayoffDoubleDig::operator()(double spot) const
{
    if (spot > lowBarrier_ && spot < highBarrier_)
        return 1.0;
    else
        return 0.0;
}
