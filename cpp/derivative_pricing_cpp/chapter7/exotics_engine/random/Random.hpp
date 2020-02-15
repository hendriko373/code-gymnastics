//
//  Random.hpp
//  random
//
//  Created by Hendrik Jennen on 11/9/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef Random_hpp
#define Random_hpp

#include <vector>

class Random
{
public:
    Random(unsigned long dimensionality);
    virtual ~Random(){}
    virtual Random* clone() const =0;
    
    virtual void getUniforms(std::vector<double>& variates) =0;
    virtual void skip(unsigned long noPaths) =0;
    virtual void setSeed(unsigned long seed) =0;
    virtual void reset() =0;
    void getGaussians(std::vector<double>& variates);
    inline unsigned long getDimensionality() const;
    virtual void setDimensionality(unsigned long dimensionality);
private:
    unsigned long dimensionality_;
};

inline unsigned long Random::getDimensionality() const
{
    return dimensionality_;
}

#endif /* Random_hpp */
