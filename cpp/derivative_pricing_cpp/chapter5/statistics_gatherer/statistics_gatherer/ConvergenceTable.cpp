//
//  ConvergenceTable.cpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/3/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include "MC_Statistics.hpp"
#include "ConvergenceTable.hpp"
#include "Handle.hpp"

using namespace std;

ConvergenceTable::ConvergenceTable(const Handle<Statistics>& statistic)
            : statistic_(statistic), stoppingPoint_(2UL), noPaths_(0UL) {}

ConvergenceTable* ConvergenceTable::clone() const
{
    return new ConvergenceTable(*this);
}

void ConvergenceTable::dumpResult(double result)
{
    statistic_->dumpResult(result);
    ++noPaths_;
    
    if (noPaths_ == stoppingPoint_) {
        stoppingPoint_ *= 2;
        
        vector<vector<double>> temp(statistic_->getStatistics());
        for (vector<vector<double>>::iterator i = temp.begin();
             i != temp.end(); ++i) {
            i->push_back(noPaths_);
        }
        results_.insert(results_.end(), temp.begin(), temp.end());
    }
}

vector<vector<double>> ConvergenceTable::getStatistics() const
{
    vector<vector<double>> ret(results_);
    
    if (2*noPaths_ != stoppingPoint_) {
        vector<vector<double>> temp(statistic_->getStatistics());
        
        for (vector<vector<double>>::iterator i = temp.begin();
             i != temp.end(); ++i) {
            i->push_back(noPaths_);
        }
        ret.insert(ret.end(), temp.begin(), temp.end());
    }
    return ret;
}
