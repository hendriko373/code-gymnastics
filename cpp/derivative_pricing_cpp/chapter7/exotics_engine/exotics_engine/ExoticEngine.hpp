//
//  ExoticEngine.hpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 1/27/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef ExoticEngine_hpp
#define ExoticEngine_hpp

#include <vector>

#include "Handle.hpp"
#include "PathDependent.hpp"
#include "Parameter.hpp"
#include "MC_Statistics.hpp"

class ExoticEngine
{
public:
    ExoticEngine(const Handle<PathDependent>& product, const Handle<Parameter>& r);
    virtual ~ExoticEngine(){}
    
    // Template design pattern
    void doSimulation(Statistics& statistic, unsigned long noPaths);
    virtual void generateSpots(std::vector<double>& spots) =0;
    double priceCashFlows(const std::vector<double>& spots) const;
    
private:
    Handle<PathDependent> product_;
    Handle<Parameter> r_;
    std::vector<double> discountFactors_;
    mutable std::vector<CashFlow> tempCashFlows_;
};

#endif /* ExoticEngine_hpp */
