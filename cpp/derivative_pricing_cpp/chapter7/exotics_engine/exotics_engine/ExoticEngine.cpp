//
//  ExoticEngine.cpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 1/27/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include <cmath>

#include "ExoticEngine.hpp"
#include "Handle.hpp"
#include "PathDependent.hpp"
#include "Parameter.hpp"

#include <iostream>

using namespace std;

ExoticEngine::ExoticEngine(const Handle<PathDependent>& product,
                           const Handle<Parameter>& r) :
    product_(product), r_(r), discountFactors_(product->possibleCashFlowTimes()),
    tempCashFlows_(product->maxNoCashFlows())
{
    for (vector<double>::iterator i = discountFactors_.begin();
         i != discountFactors_.end(); ++i) {
        *i = exp(-r_->getIntegral(0.0, *i));
    }
}

void ExoticEngine::doSimulation(Statistics &statistic, unsigned long noPaths)
{
    vector<double> spots(product_->getLookTimes().size());
    
    double temp;
    for (unsigned long i = 0; i != noPaths; ++i) {
        generateSpots(spots);
        temp = priceCashFlows(spots);
        statistic.dumpResult(temp);
    }
}

double ExoticEngine::priceCashFlows(const std::vector<double>& spots) const
{
    double ret(0.0);
    product_->computeCashFlows(spots, tempCashFlows_);
    
    for (vector<CashFlow>::const_iterator i = tempCashFlows_.begin();
         i != tempCashFlows_.end(); ++i) {
        ret += discountFactors_[i->timeIndex_]*(i->amount_);
    }
    
    return ret;
}