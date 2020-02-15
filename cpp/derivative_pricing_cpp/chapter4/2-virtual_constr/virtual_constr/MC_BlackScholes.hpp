#ifndef MC_BLACKSHOLES_HPP
#define MC_BLACKSHOLES_HPP

#include "VanillaOption.hpp"

/** Calculates Black-Scholes price of an option
 * @param   PO      payoff function object 
 * @param   T       time to expiration 
 * @param   S_0     present spot price underlying
 * @param   vol     volatility of underlying
 * @param   r       risk-free interest rate
 * @param   noiters iteration Monte Carlo simulation
 * @return  Black-Scholes price of the option
 */
double mcBlackScholes(
        const VanillaOption& option,
        double S_0,
        double vol,
        double r,
        unsigned long noIters);

#endif
