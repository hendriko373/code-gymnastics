//
//  ConvergenceTable.hpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/3/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef ConvergenceTable_hpp
#define ConvergenceTable_hpp

#include <vector>
#include "MC_Statistics.hpp"
#include "Handle.hpp"

class ConvergenceTable : public Statistics
{
public:
    ConvergenceTable(const Handle<Statistics>& statistic);
    virtual ConvergenceTable* clone() const;
    
    virtual void dumpResult(double result);
    virtual std::vector<std::vector<double>> getStatistics() const;
private:
    Handle<Statistics> statistic_;
    std::vector<std::vector<double>> results_;
    unsigned long stoppingPoint_;
    unsigned long noPaths_;
};

#endif /* ConvergenceTable_hpp */
