//
//  PathDependent.cpp
//  exotics_engine
//
//  Created by Hendrik Jennen on 1/3/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <vector>
#include "PathDependent.hpp"

using namespace std;

PathDependent::PathDependent(const vector<double>& lookTimes) :
    lookTimes_(lookTimes) {}

const vector<double>& PathDependent::getLookTimes() const
{
    return lookTimes_;
}