#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include <vector>

#include "payoff.hpp"
#include "MC_BlackScholes.hpp"
#include "PayoffPower.hpp"
#include "VanillaOption.hpp"
#include "SimpleParameter.hpp"
#include "MC_Statistics.hpp"
#include "ConvergenceTable.hpp"
#include "FirstFourMoments.hpp"
#include "VariousStatistics.hpp"
#include "Handle.hpp"


using namespace std;

int main()
{
    double S_0 = 100;
    double T = 1;
    double K = 100;
    unsigned long noIters = 1000000;
    
    ConstantParameter r(0.05);
    ConstantParameter vol(0.18);
    
    PayoffPut putPO(K);
    
    VanillaOption putOpt(putPO, T);
    
    vector<Handle<Statistics>> statistics;
    statistics.push_back(new Mean);
    statistics.push_back(new ConvergenceTable(new Mean));
    statistics.push_back(new FirstFourMoments);
    
    VariousStatistics threeStatistics(statistics);

    mcBlackScholes(putOpt, S_0, vol, r, noIters, threeStatistics);
    vector<vector<double>> results = threeStatistics.getStatistics();
   
    for (vector<vector<double>>::const_iterator i = results.begin();
         i != results.end(); ++i) {
        cout << "statistic no. " << (*i)[i->size()-1] << " : ";
        for (vector<double>::const_iterator j = i->begin(); j != i->end()-1; ++j) {
            cout << setw(8) << *j;
        }
        cout << endl;
    }
    
    return 0;
}

