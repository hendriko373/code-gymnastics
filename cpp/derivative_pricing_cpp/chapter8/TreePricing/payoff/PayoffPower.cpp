#include <cmath>
#include <algorithm>

#include "PayoffPower.hpp"

using namespace std;

PayoffPower::PayoffPower(double strike, double power)
    : strike_(strike), power_(power) {}

double PayoffPower::operator()(double spot) const
{
    return max(pow(spot, power_) - strike_, 0.0); 
}
