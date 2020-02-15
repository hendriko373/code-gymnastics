//
//  PathDependent.hpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 1/3/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef PathDependent_hpp
#define PathDependent_hpp

#include <vector>

class CashFlow
{
public:
    CashFlow(double amount=0.0, unsigned long timeIndex = 0UL) :
        amount_(amount), timeIndex_(timeIndex) {}
    
    double amount_;
    unsigned long timeIndex_;
};

class PathDependent
{
public:
    PathDependent(const std::vector<double>& lookTimes);
    virtual PathDependent* clone() const =0;
    virtual ~PathDependent(){}
    
    virtual unsigned long maxNoCashFlows() const =0;
    virtual std::vector<double> possibleCashFlowTimes() const =0;
    virtual unsigned long computeCashFlows(
                            const std::vector<double>& spotValues,
                            std::vector<CashFlow>& cashFlows) const =0;
    
    const std::vector<double>& getLookTimes() const;

protected:
    std::vector<double> lookTimes_;
};

#endif /* PathDependent_hpp */
