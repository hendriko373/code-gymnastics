//
//  main.cpp
//  solvers
//
//  Created by Hendrik Jennen on 3/14/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <iostream>

#include "Solvers.hpp"
#include "BSfunctions.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    BSCall callBSPrice(0.05, 0.00, 100, 95, 1.00);
    double callMarketPrice = 5.05;
    
    double callImpliedVol = BisectionSolver(callMarketPrice, 0.00, 100.00,
                                            0.0001, callBSPrice);
    
    cout << "Implied volatility with bisection: " << callImpliedVol << endl;
    
    BSCallBis callBS(0.05, 0.00, 100, 95, 1.00);
    
    double callImpliedVolNR = NewtonRaphsonSolver<BSCallBis, &BSCallBis::getPrice,
        &BSCallBis::getVega>(callMarketPrice, 0.40, 0.0001, callBS);
    
    cout << "Implied volatility with Newton-Raphson: " << callImpliedVolNR << endl;
    
    return 0;
}
