#include <iostream>
#include <cmath>

#include "payoff.hpp"
#include "MC_BlackScholes.hpp"
#include "PayoffPower.hpp"
#include "VanillaOption.hpp"

using namespace std;

int main()
{
    double S_0 = 100;
    double T = 0.25;
    double vol = 0.1;
    double K = 105;
    double K2 = 105;
    double r = 0.05;
    double noIters = 10000000;

    PayoffCall callPO(K);
    PayoffPut putPO(K);
    PayoffDoubleDig dblDigPO(K, K2);
    PayoffPower powerPO(K, 1.5);
    
    VanillaOption callOpt(callPO, T);
    VanillaOption putOpt(putPO, T);
    VanillaOption dblDigOpt(dblDigPO, T);
    VanillaOption powerOpt(powerPO, T);

    double priceCall = mcBlackScholes(callOpt, S_0, vol, r, noIters);
    double pricePut = mcBlackScholes(putOpt, S_0, vol, r, noIters);
    double priceDblDig = mcBlackScholes(dblDigOpt, S_0, vol, r, noIters);
    double pricePow = mcBlackScholes(powerOpt, S_0, vol, r, noIters);

    cout << "Price of call: " << priceCall << endl;
    cout << "Price of put: " << pricePut << endl;
    cout << "Put-Call parity: " << priceCall - pricePut << " ~ "
        << S_0 - K*exp(-r*T) << endl;
    cout << "Price of double digital: " << priceDblDig << endl;
    cout << "Price of power: " << pricePow << endl;
 
    return 0;
}

