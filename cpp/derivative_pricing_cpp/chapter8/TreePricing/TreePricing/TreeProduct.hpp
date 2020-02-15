//
//  TreeProduct.hpp
//  TreePricing
//
//  Created by Hendrik Jennen on 3/11/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef TreeProduct_hpp
#define TreeProduct_hpp

#include "Handle.hpp"
#include "payoff.hpp"

class TreeProduct
{
public:
    TreeProduct(double maturity);
    virtual ~TreeProduct(){};
    virtual TreeProduct* clone() const =0;
    
    double getMaturity() const;
    
    virtual double getPayoff(double spot) const =0;
    virtual double getPresentValue(double spot, double price) const =0;
    
private:
    double maturity_;
};

class TreeEuropean : public TreeProduct
{
public:
    TreeEuropean(double maturity, const Handle<Payoff>& payoff);
    virtual ~TreeEuropean(){}
    virtual TreeEuropean* clone() const;
    
    virtual double getPayoff(double spot) const;
    virtual double getPresentValue(double spot, double price) const;
    
private:
    Handle<Payoff> payoff_;
};

class TreeAmerican : public TreeProduct
{
public:
    TreeAmerican(double maturity, const Handle<Payoff>& payoff);
    virtual ~TreeAmerican(){}
    virtual TreeAmerican* clone() const;
    
    virtual double getPayoff(double spot) const;
    virtual double getPresentValue(double spot, double price) const;
    
private:
    Handle<Payoff> payoff_;
};

#endif /* TreeProduct_hpp */
