//
//  PayoffRegistration.cpp
//  PayoffFactory
//
//  Created by Hendrik Jennen on 3/17/16.
//  Copyright © 2016 Hendrik Jennen. All rights reserved.
//

#include "PayoffFactory.hpp"
#include "payoff.hpp"

namespace  {
    PayoffMaker<PayoffCall> RegistrationCall("call");
    PayoffMaker<PayoffPut> RegistrationPut("put");
}
