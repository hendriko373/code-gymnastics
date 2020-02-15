//
//  BinomialTree.cpp
//  TreePricing
//
//  Created by Hendrik Jennen on 3/11/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include <iostream>

#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>

#include "BinomialTree.hpp"

using namespace std;

BinomialTree::BinomialTree(const Handle<Parameter>& r, const Handle<Parameter>& d,
                           double vol, double finalTime, unsigned long n,
                           double initialSpot)
    : r_(r), d_(d), vol_(vol), finalTime_(finalTime), n_(n),
        initialSpot_(initialSpot), treeBuilt_(false) {}

void BinomialTree::buildTree()
{
    tree_.resize(n_+1); // n_ timesteps
    double dt = finalTime_/n_;
    double stDev = vol_*sqrt(dt);
    
    tree_[0].resize(1);
    tree_[0][0].first = initialSpot_;
    
    for (TreeSzTp i = 1; i != tree_.size(); ++i) {
        tree_[i].resize(i+1);   // i+1 nodes at time i -- recombinant tree
        
        double drift = r_->getIntegral(0.0, i*dt) - d_->getIntegral(0.0, i*dt);
        drift = drift - 0.5*vol_*vol_*i*dt;
        
        long k = -static_cast<long>(i);
        for (TimeHorSzTp j = 0; j != tree_[i].size(); ++j, k+=2)
            tree_[i][j].first = initialSpot_*exp(drift + stDev*k);
    }
    treeBuilt_ = true;
    
    // We also precompute the discount factors along each time step
    discounts_.resize(n_);
    for (TreeSzTp i = 0; i != discounts_.size(); ++i)
        discounts_[i] = exp(-r_->getIntegral(i*dt, (i+1)*dt));
}

double BinomialTree::computePriceProduct(const TreeProduct &product)
{
    if (product.getMaturity() != finalTime_)
        throw runtime_error("Maturities of tree and product do not match.");
    
    if (!treeBuilt_)
        buildTree();
    
    for (TimeHorSzTp j = 0; j != tree_[n_].size(); ++j)
        tree_[n_][j].second = product.getPayoff(tree_[n_][j].first);
    
    for (TreeSzTp i = n_; i != 0; --i) {
        for (TimeHorSzTp j = 0; j != tree_[i-1].size(); ++j) {
            tree_[i-1][j].second = discounts_[i-1]*0.5*(tree_[i][j].second +
                                                        tree_[i][j+1].second);
            tree_[i-1][j].second = product.getPresentValue(tree_[i-1][j].first,
                                                           tree_[i-1][j].second);
        }
    }
    
    return tree_[0][0].second;
}