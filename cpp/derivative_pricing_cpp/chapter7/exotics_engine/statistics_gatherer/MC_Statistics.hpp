//
//  MC_Statistics.hpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/1/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef MC_Statistics_hpp
#define MC_Statistics_hpp

#include <vector>

class Statistics
{
public:
    virtual ~Statistics(){}
    virtual Statistics* clone() const =0;
    
    virtual void dumpResult(double result) =0;
    virtual std::vector<std::vector<double>> getStatistics() const =0;
};

class Mean : public Statistics
{
public:
    Mean();
    virtual Mean* clone() const;
    
    virtual void dumpResult(double result);
    virtual std::vector<std::vector<double>> getStatistics() const;
private:
    double runningSum_;
    unsigned long noPaths_;
};

#endif /* MC_Statistics_hpp */
