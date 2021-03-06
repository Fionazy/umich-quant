//
//  main.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/21/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//
// This program supports:
// 1. read in table of t+1 prices for m assets
// 2. given current price levels, generate simulations of m asset prices
//

#include <iostream>
#include <fstream>
#include <boost/date_time.hpp>

#include "Market.hpp"
#include "Portfolio.hpp"
#include "Security.hpp"
#include "MarketScenario.hpp"
#include "MarketSimulation.hpp"

int main(int argc, const char * argv[]) {
    std::ifstream inputPrices("IBM_T_NKE_AAPL_20141001-20160930.csv");
    if (!inputPrices.is_open()) {
        return 1; //file not open
    }
    Market market(inputPrices);
    
    const auto pApple = market.marketFactor("AAPL");
    std::cout << "AAPL variance = " << pApple->variance() << std::endl; //td::endl---flushes the output buffer
    
    int numberHistoricalReturns = market.numberHistoricalReturns();
    MarketSimulation simulation0(numberHistoricalReturns);
    std::cout << "AAPL return = " << pApple->simulatedReturn(simulation0) << std::endl;
    MarketSimulation simulation1(numberHistoricalReturns);
    
    Portfolio portfolio;
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("AAPL")), 1000);
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("IBM")), 1500);
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("T")), 10000);
    portfolio.addPosition(std::make_shared<Security>(*market.marketFactor("NKE")), 3000);
    
    
    //Pete: This is what we are working on next. Tt is missing implementation.
    const MarketScenario scenario(market, 2016, 9, 30);
    std::cout << portfolio.value(scenario) << std::endl;
    std::cout << portfolio.value(scenario,simulation1) << std::endl;
    
    //calculate 95% CI VaR of the portfolio
    /*int sims=10000;
    std::vector<double> profit=portfolio.profits(scenario,numberHistoricalReturns,sims);
    std::sort (profit.begin(),profit.end());
    double confidence=0.95;
    size_t varIndex =round((1-confidence)*profit.size());
    std::cout << -profit[varIndex] << std::endl;*/
    
    int sims=10000;
    std::vector<double> profit=portfolio.profits(scenario,numberHistoricalReturns,sims);
    std::cout << portfolio.VaR(profit,0.95) << std::endl;
    std::cout << portfolio.VaR(profit,0.99) << std::endl;
    std::cout << portfolio.es(profit,0.99) << std::endl;
    
    
    
    //class portfolioSimResults{
    /*
    private:
    const double portfolioProfit;
    const vector<double> portfolio positionProfit;
     }
*/