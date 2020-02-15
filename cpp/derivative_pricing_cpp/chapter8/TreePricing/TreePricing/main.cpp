//
//  main.cpp
//  TreePricing
//
//  Created by Hendrik Jennen on 3/11/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <iostream>

#include "TreeProduct.hpp"
#include "BinomialTree.hpp"
#include "Parameter.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    BinomialTree binTree(new ConstantParameter(0.05),
                         new ConstantParameter(0.00),
                         0.18,
                         1,
                         1000,
                         100);
    
    TreeEuropean eurCall(1, new PayoffCall(100));
    TreeAmerican amCall(1, new PayoffCall(100));
    
    cout << binTree.computePriceProduct(eurCall) << endl;
    cout << binTree.computePriceProduct(amCall) << endl;
    cout << endl;
    
    TreeEuropean eurPut(1, new PayoffPut(100));
    TreeAmerican amPut(1, new PayoffPut(100));
    
    cout << binTree.computePriceProduct(eurPut) << endl;
    cout << binTree.computePriceProduct(amPut) << endl;
    
    return 0;
}
