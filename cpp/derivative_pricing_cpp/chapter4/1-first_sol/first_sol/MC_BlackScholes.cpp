#include <random>
#include <list>
#include <cmath>
#include <numeric>
#include <iostream>

#include "MC_BlackScholes.hpp"
#include "VanillaOption.hpp"

using namespace std;

double mcBlackScholes(
        const VanillaOption& option,
        double S_0,
        double vol,
        double r,
        unsigned long noIters)
{
    // Normal distribution with mean 0 and standard dev 1
    random_device rd;
    mt19937 generator(rd());
    normal_distribution<double> normalDist(0.0, 1.0);
    
    double T = option.getExpiry();
    double driftS_T = S_0*exp((r-vol*vol/2)*T);
    double rootTotVariance = vol*sqrt(T);

    double sumPayoffs = 0.0;

    for (unsigned long i = 0; i != noIters; ++i) {
        double randomNr = normalDist(generator);

        // Stock price at expiration
        double S_T = driftS_T*exp(rootTotVariance*randomNr);

        // Running sum of payoffs at expiration
        double payoff = option.getPayoff(S_T);
        sumPayoffs += payoff;
    }
    return exp(-r*T)*sumPayoffs/noIters;
}
