//
//  AntiThetic.hpp
//  random
//
//  Created by Hendrik Jennen on 11/10/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef AntiThetic_hpp
#define AntiThetic_hpp

#include <vector>
#include "Random.hpp"
#include "Handle.hpp"

class AntiThetic : public Random
{
public:
    AntiThetic(const Handle<Random>& random);
    virtual AntiThetic* clone() const;
    
    virtual void getUniforms(std::vector<double>& variates);
    virtual void skip(unsigned long noPaths);
    virtual void setSeed(unsigned long seed);
    virtual void reset();
    virtual void setDimensionality(unsigned long dimensionality);
    
private:
    Handle<Random> random_;
    std::vector<double> antiTheticVariates;
    bool atOdd;
};

#endif /* AntiThetic_hpp */
