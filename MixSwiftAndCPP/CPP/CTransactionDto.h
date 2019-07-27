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

//namespace legacy {
    class CTransactionDto {
    public:
        double _net;
        double _tax;
        double _taxRate;
        double _gross;
        
    public:
        CTransactionDto() {
            _net = 0;
            _tax = 0;
            _taxRate = 0;
            _gross = 0;
        }
        ~CTransactionDto() {}
    };
//}

#endif /* CTransactionDto_h */
