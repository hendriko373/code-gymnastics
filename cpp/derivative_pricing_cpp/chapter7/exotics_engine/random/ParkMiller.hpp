//
//  ParkMiller.hpp
//  random
//
//  Created by Hendrik Jennen on 11/9/15.
//  Copyright © 2015 Hendrik Jennen. All rights reserved.
//

#ifndef ParkMiller_hpp
#define ParkMiller_hpp

class ParkMiller
{
public:
    ParkMiller(long seed = 1);
    
    void setSeed(long seed);
    long generateRandomInteger();
    
    static unsigned long max();
    static unsigned long min();
    
private:
    long seed_;
};

#endif /* ParkMiller_hpp */
