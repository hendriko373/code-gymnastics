//
//  GeometricAsianOption.hpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 3/2/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef GeometricAsianOption_hpp
#define GeometricAsianOption_hpp

#include <vector>

#include "AsianOption.hpp"

class AsianGeometric : public Asian
{
public:
    AsianGeometric(const std::vector<double>& lookTimes,
                   const Handle<Payoff>& payoff, double maturity);
    virtual AsianGeometric* clone() const override;
    
    virtual unsigned long computeCashFlows(
                            const std::vector<double>& spotValues,
                            std::vector<CashFlow>& cashFlows) const override;
};

#endif /* GeometricAsianOption_hpp */
