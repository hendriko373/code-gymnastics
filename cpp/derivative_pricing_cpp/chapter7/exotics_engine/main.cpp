//
//  main.cpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 2/1/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include <iostream>
#include <random>
#include <cmath>

#include "BlackScholesEngine.hpp"
#include "RandomParkMiller.hpp"
#include "AsianOption.hpp"
#include "Parameter.hpp"
#include "MC_Statistics.hpp"
#include "GeometricAsianOption.hpp"

using namespace std;

int main()
{
    vector<double> lookTimes(10);
    int n = 1;
    for (vector<double>::iterator i = lookTimes.begin();
         i != lookTimes.end(); ++i) {
        *i = 1.0/10*n;
        ++n;
    }
    
    double T = 1.0;
    double S0 = 100;
    double K = 100;
    double r = 0.05;
    double d = 0.03;
    double vol = 0.18;
    
    random_device rd;
    BlackScholesEngine asianBS(new RandomParkMiller(lookTimes.size(), rd()),
                               new Asian(lookTimes, new PayoffCall(K), T),
                               new ConstantParameter(r),
                               new ConstantParameter(d),
                               new ConstantParameter(vol),
                               S0);
    
    Mean priceAsianBS;
    asianBS.doSimulation(priceAsianBS, 100000);
    
    BlackScholesEngine geomAsianBS(
                            new RandomParkMiller(lookTimes.size(), rd()),
                            new AsianGeometric(lookTimes, new PayoffPut(K), T),
                            new ConstantParameter(r),
                            new ConstantParameter(d),
                            new ConstantParameter(vol),
                            S0);
    
    Mean priceGeomAsianBS;
    geomAsianBS.doSimulation(priceGeomAsianBS, 1000000);
    
    cout << "The price of the arithmetic Asian call option is "
            << priceAsianBS.getStatistics()[0][0] << endl;
    
    cout << "The price of the geometric Asian call option is "
        << priceGeomAsianBS.getStatistics()[0][0] << endl;
}

