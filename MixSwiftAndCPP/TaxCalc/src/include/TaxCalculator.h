//
//  TaxCalculator.h
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#include "Transaction.h"
#include "Property.h"

using namespace tax;

class TaxCalculator : public INotifyPropertyChange {
public:
    TaxCalculator(Transaction *data);
    virtual ~TaxCalculator();
        
    Property<double> Net;
    Property<double> Tax;
    Property<double> TaxRate;
    Property<double> Gross;
    
private:
    Transaction *_data;

    void CalculateTax();
    void CalculateGross();
    
    EventHandlerID _netChangedHandlerID;
    EventHandlerID _taxChangedHandlerID;
    EventHandlerID _taxRateChangedHandlerID;
};
