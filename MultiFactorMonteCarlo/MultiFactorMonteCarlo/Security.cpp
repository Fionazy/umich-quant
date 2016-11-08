//
//  Security.cpp
//  MultiFactorMonteCarlo
//
//  Created by Peter Benson on 10/29/16.
//  Copyright © 2016 Peter Benson. All rights reserved.
//

#include "Security.hpp"

Security::Security(const std::string& name):m_name(name){
}

double Security::valueOfOneUnit(const MarketScenario& scenario) const {
    return 1;
}
