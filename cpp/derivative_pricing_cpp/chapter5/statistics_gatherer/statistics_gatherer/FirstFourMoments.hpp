//
//  FirstFourMoments.hpp
//  statistics_gatherer
//
//  Created by Hendrik Jennen on 11/4/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef FirstFourMoments_hpp
#define FirstFourMoments_hpp

#include <vector>
#include "MC_Statistics.hpp"

class FirstFourMoments : public Statistics
{
public:
    FirstFourMoments();
    virtual FirstFourMoments* clone() const;
    
    virtual void dumpResult(double result);
    virtual std::vector<std::vector<double>> getStatistics() const;
private:
    unsigned long noPaths_;
    std::vector<double> runningSum_;
};

#endif /* FirstFourMoments_hpp */
