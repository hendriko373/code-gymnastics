#include <iostream>
#include <cmath>

#include "payoff.hpp"
#include "MC_BlackScholes.hpp"

using namespace std;

int main()
{
    double S_0 = 94;
    double T = 0.25;
    double vol = 0.1;
    double K = 97;
    double K2 = 103;
    double r = 0.05;
    double noIters = 1000000;

    Payoff callPO(K, Payoff::call);
    Payoff putPO(K, Payoff::put);
    Payoff digCallPO(K, Payoff::digitalCall);
    Payoff dblDigPO(K, K2, Payoff::doubleDigital);
    Payoff forwardPO(K, Payoff::forward);

    double priceCall = mcBlackScholes(callPO, T, S_0, vol, r, noIters);
    double pricePut = mcBlackScholes(putPO, T, S_0, vol, r, noIters);
    double priceDigCal = mcBlackScholes(digCallPO, T, S_0, vol, r, noIters);
    double priceDblDig = mcBlackScholes(dblDigPO, T, S_0, vol, r, noIters);
    double priceFor = mcBlackScholes(forwardPO, T, S_0, vol, r, noIters);

    cout << "Price of call: " << priceCall << endl;
    cout << "Price of put: " << pricePut << endl;
    cout << "Put-Call parity: " << priceCall - pricePut << " ~ "
        << S_0 - K*exp(-r*T) << endl;
    cout << "Price of forward: " << priceFor << endl;
    cout << "Price of digital call: " << priceDigCal << endl;
    cout << "Price of double digital: " << priceDblDig << endl;
    
    return 0;
}

