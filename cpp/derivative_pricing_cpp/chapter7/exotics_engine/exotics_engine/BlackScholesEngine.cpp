//
//  BlackScholesEngine.cpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 1/29/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include <cmath>

#include "ExoticEngine.hpp"
#include "BlackScholesEngine.hpp"
#include "Handle.hpp"
#include "PathDependent.hpp"
#include "Parameter.hpp"

using namespace std;

BlackScholesEngine::BlackScholesEngine(const Handle<Random>& randomGenerator,
                                       const Handle<PathDependent>& product,
                                       const Handle<Parameter>& r,
                                       const Handle<Parameter>& dividend,
                                       const Handle<Parameter>& vol,
                                       double initialSpot)
    : ExoticEngine(product,r),
        randomGenerator_(randomGenerator),
        drifts_(product->getLookTimes().size()),
        vols_(product->getLookTimes().size()),
        logInitialSpot_(log(initialSpot)),
        variates_(product->getLookTimes().size()),
        noLookTimes_(product->getLookTimes().size())
{
    randomGenerator_->setDimensionality(noLookTimes_);
    
    vector<double> t = product->getLookTimes();
    vector<double>::size_type i = 0;
    
    drifts_[0] = r->getIntegral(0.0, t[i])
                    - dividend->getIntegral(0.0, t[i])
                    - 0.5*vol->getSqrIntegral(0.0, t[i]);
    vols_[0] = sqrt(vol->getSqrIntegral(0.0, t[i]));
    
    while (i != noLookTimes_-1) {
        
        drifts_[i] = r->getIntegral(t[i-1], t[i])
                        - dividend->getIntegral(t[i-1], t[i])
                        - 0.5*vol->getSqrIntegral(t[i-1], t[i]);
        vols_[i] = sqrt(vol->getSqrIntegral(t[i-1], t[i]));
        ++i;
    }
}

void BlackScholesEngine::generateSpots(vector<double>& spots)
{
    randomGenerator_->getGaussians(variates_);
    
    double tempLogSpot = logInitialSpot_;
    
    for (vector<double>::size_type i = 0; i != noLookTimes_; ++i) {
        
        tempLogSpot = tempLogSpot + drifts_[i] + vols_[i]*variates_[i];
        spots[i] = exp(tempLogSpot);
    }
}
