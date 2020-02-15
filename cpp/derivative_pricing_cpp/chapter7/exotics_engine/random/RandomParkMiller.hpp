//
//  RandomParkMiller.hpp
//  random
//
//  Created by Hendrik Jennen on 11/9/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef RandomParkMiller_hpp
#define RandomParkMiller_hpp

#include <vector>
#include "Random.hpp"
#include "ParkMiller.hpp"

class RandomParkMiller : public Random
{
public:
    RandomParkMiller(unsigned long dimensionality, unsigned long seed = 1);
    virtual RandomParkMiller* clone() const;
    
    virtual void getUniforms(std::vector<double>& variates);
    virtual void skip(unsigned long noPaths);
    virtual void setSeed(unsigned long seed);
    virtual void reset();
    virtual void setDimensionality(unsigned long dimensionality);
private:
    ParkMiller generator;
    unsigned long seed_;
        /* One should be careful because the seed in ParkMiller is of type
         * long so that it cannot store every value seed_ can have.
         */
    double reciprocal_;
};

#endif /* RandomParkMiller_hpp */
