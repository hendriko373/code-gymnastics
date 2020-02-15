//
//  VariousStatistics.hpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/5/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef VariousStatistics_hpp
#define VariousStatistics_hpp

#include <vector>
#include "MC_Statistics.hpp"
#include "Handle.hpp"

class VariousStatistics : public Statistics
{
public:
    VariousStatistics(const std::vector<Handle<Statistics>>& statistics);
    virtual VariousStatistics* clone() const;
    
    virtual void dumpResult(double result);
    virtual std::vector<std::vector<double>> getStatistics() const;
private:
    std::vector<Handle<Statistics>> statistics_;
};

#endif /* VariousStatistics_hpp */

