//
//  ValueAtRisk.hpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/4/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef ValueAtRisk_hpp
#define ValueAtRisk_hpp

#include <vector>
#include "MC_Statistics.hpp"

class ValueAtRisk : public Statistics
{
public:
    ValueAtRisk(double alpha);
    virtual ValueAtRisk* clone() const;
    
    virtual void dumpResult(double result);
    virtual std::vector<std::vector<double>> getStatistics() const;
private:
    double alpha_;
    std::vector<double> sampleValues_;
};

#endif /* ValueAtRisk_hpp */
