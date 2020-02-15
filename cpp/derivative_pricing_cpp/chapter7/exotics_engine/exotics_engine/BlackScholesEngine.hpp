//
//  BlackScholesEngine.hpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 1/29/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef BlackScholesEngine_hpp
#define BlackScholesEngine_hpp

#include <vector>

#include "ExoticEngine.hpp"
#include "Handle.hpp"
#include "PathDependent.hpp"
#include "Parameter.hpp"
#include "Random.hpp"

class BlackScholesEngine : public ExoticEngine
{
public:
    BlackScholesEngine(const Handle<Random>& randomGenerator,
                       const Handle<PathDependent>& product,
                       const Handle<Parameter>& r,
                       const Handle<Parameter>& dividend,
                       const Handle<Parameter>& vol,
                       double initialSpot);
    
    virtual void generateSpots(std::vector<double>& spots);
    
private:
    Handle<Random> randomGenerator_;
    std::vector<double> drifts_;
    std::vector<double> vols_;
    double logInitialSpot_;
    std::vector<double> variates_;
    std::vector<double>::size_type noLookTimes_;
};

#endif /* BlackScholesEngine_hpp */
