//
//  BisectionSolver.hpp
//  solvers
//
//  Created by Hendrik Jennen on 3/14/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef Solvers_hpp
#define Solvers_hpp

#include <cmath>
#include <iostream>

template <class T>
double BisectionSolver(double rhs, double low, double high,
                       double tolerance, T f)
{
    double x = 0.5*(low + high);
    double y = f(x);
    
    while (std::abs(y - rhs) > tolerance) {
        if (y < rhs)
            low = x;
        else
            high = x;
        
        x = 0.5*(low + high);
        y = f(x);
    }
    
    return x;
}

template <class T, double (T::* value)(double) const,
                double (T::* derivative)(double) const>
double NewtonRaphsonSolver(double rhs, double seed, double tolerance, T f)
{
    double x = seed;
    double y = (f.*value)(x);
    
    while (std::abs(y - rhs) > tolerance) {
        x = (rhs - y)/(f.*derivative)(x) + x;
        y = (f.*value)(x);
    }
    
    return x;
}


#endif /* Solvers_hpp */
