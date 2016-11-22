//
//  Portfolio.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include <numeric>
#include "Portfolio.hpp"

void Portfolio::addPosition(const std::shared_ptr<Security> security, double positionSize) {
    m_positions.push_back(std::make_shared<Position>(security, positionSize));
    
}

double Portfolio::value(const MarketScenario& scenario) const{
    double value = 0;
    for(auto pPosition : m_positions) {
        value += pPosition->value(scenario);
    }
    return value;
}

double Portfolio::value(const MarketScenario& scenario, const MarketSimulation& sim) const{
    double value = 0;
    for(auto pPosition : m_positions) {
        value += pPosition->value(scenario,sim);
    }
    return value;
}

//profits(scenairio, #historical simulations, #simulations)
std::vector<double> Portfolio::profits(const MarketScenario& scenario, int historicalReturns, int sims){
    //double profit=0;
    //MarketSimulation->MarketSimulation(historicalReturns) sim;
    std::vector<double> profit;
    const double todaysValue=value(scenario);
    for (int i=0; i!=sims; ++i){
        const double tomorrowsValue=value(scenario,MarketSimulation(historicalReturns));
        profit.push_back(tomorrowsValue-todaysValue);
    }
return profit;
}

double VaR(std::vector<double> profit, double confidence){
    std::sort (profit.begin(),profit.end());
    //double confidence=0.95;
    size_t varIndex =round((1-confidence)*profit.size());
    double VaR= -profit[varIndex];
    return VaR;
}

double es(std::vector<double> profit, double confidence){
    std::sort (profit.begin(),profit.end());
    size_t MaxvarIndex=round((1-confidence)*profit.size());
    double sum=0;
    double sample_CI=0;
    for (size_t varIndex=0; varIndex!=MaxvarIndex; ++varIndex){
        sum=+(VaR(profit, sample_CI)/sample_CI);
        sample_CI=varIndex*(confidence/MaxvarIndex);
    }
    double es=sum;
    return es;
}

