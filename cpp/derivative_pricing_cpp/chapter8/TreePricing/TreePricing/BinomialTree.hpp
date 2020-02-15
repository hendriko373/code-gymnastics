//
//  BinomialTree.hpp
//  TreePricing
//
//  Created by Hendrik Jennen on 3/11/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#ifndef BinomialTree_hpp
#define BinomialTree_hpp

#include <vector>
#include <utility>

#include "Handle.hpp"
#include "TreeProduct.hpp"
#include "Parameter.hpp"

class BinomialTree
{
public:
    BinomialTree(const Handle<Parameter>& r, const Handle<Parameter>& d,
                 double vol, double finalTime, unsigned long n, double initialSpot);
    
    double computePriceProduct(const TreeProduct& product);
    
protected:
    void buildTree();
    
    typedef std::vector<std::vector<std::pair<double, double>>> Tree;
    typedef Tree::size_type TreeSzTp;
    typedef std::vector<std::pair<double, double>>::size_type TimeHorSzTp;
    
private:
    Handle<Parameter> r_;       // interest rate
    Handle<Parameter> d_;       // dividend rate
    double vol_;                // volatility
    double finalTime_;
    unsigned long n_;           // timesteps
    double initialSpot_;
    
    bool treeBuilt_;
    std::vector<std::vector<std::pair<double, double>>> tree_;
        /* The tree is a vector of vectors of pairs (of spot and derivative
         value). Each vector of pairs represents a time tick horizon, where the
         vector starts at the lowest node, going up to the highest.
         */
    
    std::vector<double> discounts_;
};

#endif /* BinomialTree_hpp */
