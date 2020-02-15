#include <random>
#include <list>
#include <cmath>
#include <numeric>
#include <vector>
#include <iostream>

#include "MC_BlackScholes.hpp"
#include "VanillaOption.hpp"
#include "MC_Statistics.hpp"
#include "Random.hpp"

using namespace std;

void mcBlackScholes(
        const VanillaOption& option,
        double S_0,
        const Parameter& vol,
        const Parameter& r,
        unsigned long noIters,
        Statistics& stat,
        Random& generator)
{
    double T = option.getExpiry();
    double totR = r.getIntegral(0, T);
    double totVar = vol.getSqrIntegral(0, T);
    double driftS_T = S_0*exp(totR-totVar/2);
    double rootTotVar = sqrt(totVar);
    double discount = exp(-totR);

    generator.setDimensionality(1);
        // we only need to generate one price at a time
    vector<double> randomNr(1);
    double S_T, payoff;
    for (unsigned long i = 0; i != noIters; ++i) {
        generator.getGaussians(randomNr);

        // Stock price at expiration
        S_T = driftS_T*exp(rootTotVar*randomNr[0]);

        // Running sum of payoffs at expiration
        payoff = option.getPayoff(S_T);
        stat.dumpResult(discount*payoff);
    }
}
