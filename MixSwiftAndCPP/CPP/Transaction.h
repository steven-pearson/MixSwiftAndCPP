//
//  Transaction.h
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#ifndef Transaction_h
#define Transaction_h

#include <stdio.h>

namespace tax {
    class Transaction {
    public:
        double _net;
        double _tax;
        double _taxRate;
        double _gross;
    };
}

#endif /* Transaction_h */
