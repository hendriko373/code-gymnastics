//
//  AsianOption.hpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 2/1/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef AsianOption_hpp
#define AsianOption_hpp

#include <vector>

#include "Handle.hpp"
#include "PathDependent.hpp"
#include "payoff.hpp"

class Asian : public PathDependent
{
public:
    Asian(const std::vector<double>& lookTimes, const Handle<Payoff>& payoff, double maturity);
    virtual Asian* clone() const;
    
    virtual unsigned long maxNoCashFlows() const;
    virtual std::vector<double> possibleCashFlowTimes() const;
    virtual unsigned long computeCashFlows(
                            const std::vector<double>& spotValues,
                            std::vector<CashFlow>& cashFlows) const;
    
protected:
    Handle<Payoff> payoff_;
    double maturity_;
};

#endif /* AsianOption_hpp */
