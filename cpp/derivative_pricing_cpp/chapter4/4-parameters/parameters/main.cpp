#include <iostream>
#include <cmath>
#include <map>

#include "payoff.hpp"
#include "MC_BlackScholes.hpp"
#include "PayoffPower.hpp"
#include "VanillaOption.hpp"
#include "SimpleParameter.hpp"

using namespace std;

int main()
{
    double S_0 = 100;
    double T = 1;
    double K = 95;
    double K2 = 105;
    double noIters = 1000000;

    PayoffCall callPO(K);
    PayoffPut putPO(K);
    PayoffDoubleDig dblDigPO(K, K2);
    PayoffPower powerPO(K, 1.5);
    
    VanillaOption callOpt(callPO, T);
    VanillaOption putOpt(putPO, T);
    VanillaOption dblDigOpt(dblDigPO, T);
    VanillaOption powerOpt(powerPO, T);
    
    ConstantParameter r(0.05);
    ConstantParameter vol(0.1);

    double priceCall = mcBlackScholes(callOpt, S_0, vol, r, noIters);
    double pricePut = mcBlackScholes(putOpt, S_0, vol, r, noIters);
    double priceDblDig = mcBlackScholes(dblDigOpt, S_0, vol, r, noIters);
    double pricePow = mcBlackScholes(powerOpt, S_0, vol, r, noIters);

    cout << "Price of call: " << priceCall << endl;
    cout << "Price of put: " << pricePut << endl;
    cout << "Price of double digital: " << priceDblDig << endl;
    cout << "Price of power: " << pricePow << endl;
    
    map<double, double> funcVol;
    funcVol[0]=0.1;
    funcVol[0.25]=0.1;
    funcVol[0.50]=0.5;

    SimpleParameter funcVolTemp(funcVol);
    Parameter funcVolParam(funcVolTemp);
    
    double priceCall2 = mcBlackScholes(callOpt, S_0, funcVolParam, r, noIters);
    cout << priceCall2 << endl;
    
    return 0;
}

