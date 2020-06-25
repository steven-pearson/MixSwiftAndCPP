//
//  CTransactionDto.h
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#ifndef CTransactionDto_h
#define CTransactionDto_h

#include <stdio.h>

namespace tax {
    class CTransactionDto {
    public:
        double _net;
        double _tax;
        double _taxRate;
        double _gross;
    };
}

#endif /* CTransactionDto_h */
