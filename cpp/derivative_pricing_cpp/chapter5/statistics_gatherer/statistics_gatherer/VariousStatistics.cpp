//
//  VariousStatistics.cpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/5/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include "VariousStatistics.hpp"
#include "Handle.hpp"

using namespace std;

VariousStatistics::VariousStatistics(const vector<Handle<Statistics>>& statistics)
                        : statistics_(statistics) {}

VariousStatistics* VariousStatistics::clone() const
{
    return new VariousStatistics(*this);
}

void VariousStatistics::dumpResult(double result)
{
    for (vector<Handle<Statistics>>::const_iterator i = statistics_.begin();
         i != statistics_.end(); ++i) {
        (*i)->dumpResult(result);
    }
}

vector<vector<double>> VariousStatistics::getStatistics() const
{
    vector<vector<double>> ret;
    
    vector<Handle<Statistics>>::size_type statisticsNr = 1;
    
    for (vector<Handle<Statistics>>::const_iterator i = statistics_.begin();
         i != statistics_.end(); ++i) {
        vector<vector<double>> temp((*i)->getStatistics());
        
        // Label the results by putting the statisticsNr at the end of each
        // line in ret
        for (vector<vector<double>>::iterator j = temp.begin();
             j != temp.end(); ++j) {
            j->push_back(statisticsNr);
        }
        ret.insert(ret.end(), temp.begin(), temp.end());
        ++statisticsNr;
    }
    return ret;
}