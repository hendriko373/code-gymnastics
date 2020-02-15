//
//  main.cpp
//  random
//
//  Created by Hendrik Jennen on 11/9/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <iostream>
#include <vector>

#include "VanillaOption.hpp"
#include "payoff.hpp"
#include "ParameterFunctions.hpp"
#include "MC_Statistics.hpp"
#include "ConvergenceTable.hpp"
#include "RandomParkMiller.hpp"
#include "AntiThetic.hpp"
#include "MC_BlackScholes.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    double S0 = 100;
    double K = 100;
    double T = 1;
    
    PayoffCall callPayoff(K);
    VanillaOption callOption(callPayoff, T);
    
    ConstantParameter r(0.05);
    ConstantParameter vol(0.1);
    
    ConvergenceTable meanConvergenceOne(new Mean);
    ConvergenceTable meanConvergenceTwo(new Mean);
    
    RandomParkMiller genOne(1);
    AntiThetic genTwo(new RandomParkMiller(1));
    
    unsigned long iterations = 10000000;
    
    mcBlackScholes(callOption, S0, vol, r,
                   iterations, meanConvergenceOne, genOne);
    mcBlackScholes(callOption, S0, vol, r,
                   iterations, meanConvergenceTwo, genTwo);
    
    vector<vector<double>> resultsOne = meanConvergenceOne.getStatistics();
    vector<vector<double>> resultsTwo = meanConvergenceTwo.getStatistics();
    
    for (vector<vector<double>>::const_iterator i = resultsOne.begin();
         i != resultsOne.end(); ++i)
        cout << (*i)[1] << '\t' << (*i)[0] << '\n';
    
    cout << endl;
    for (vector<vector<double>>::const_iterator i = resultsTwo.begin();
         i != resultsTwo.end(); ++i)
        cout << (*i)[1] << '\t' << (*i)[0] << '\n';
    return 0;
}
