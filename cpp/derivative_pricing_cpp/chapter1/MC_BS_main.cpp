#include <random>
#include <list>
#include <cmath>
#include <numeric>
#include <iostream>

using namespace std;

// This function draws noIters times the price of a stock following geometric
// Brownian motion with a risk free drift and returns the discounted average
// payoff price, i.e., the option price.
double monteCarloBS(
        double T,
        double K,
        double S_0,
        double vol,
        double r,
        int noIters)
{
    // Normal distribution with mean 0 and standard dev 1
    random_device rd;
    mt19937 generator(rd());
    normal_distribution<double> normalDist(0.0, 1.0);
     
    // List containing drawn payoffs
    list<double> listPayoffs; 

    double driftS_T = S_0*exp((r-vol*vol/2)*T);
    double rootTotVariance = vol*sqrt(T);

    for (int i = 0; i != noIters; ++i) {
        double randomNr = normalDist(generator);

        // Stock price at expiration
        double S_T = driftS_T*exp(rootTotVariance*randomNr);

        // Payoff at expiration
        double payoff;
        if (S_T > K)
            payoff = S_T - K;
        else
            payoff = 0;
        listPayoffs.push_back(payoff);
    }
    return exp(-r*T)*accumulate(listPayoffs.begin(),
                                    listPayoffs.end(), 0.0)/noIters;
}

int main()
{
    cout << monteCarloBS(0.25, 100, 100, 0.1, 0, 10000000) << endl;
}


