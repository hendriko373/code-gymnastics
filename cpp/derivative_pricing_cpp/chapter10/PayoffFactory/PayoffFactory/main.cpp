//
//  main.cpp
//  PayoffFactory
//
//  Created by Hendrik Jennen on 3/16/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <iostream>

#include "payoff.hpp"
#include "PayoffFactory.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Payoff* call = PayoffFactory::getInstance().createPayoff("call", 100);
    Payoff* put = PayoffFactory::getInstance().createPayoff("put", 100);
    
    cout << (*call)(150) << endl;
    cout << (*put)(120) << endl;
    
    delete call;
    delete put;
    
    return 0;
}
