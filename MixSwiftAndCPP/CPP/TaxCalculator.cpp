//
//  TaxCalculator.cpp
//  MixSwiftAndCPP
//
//  Created by Steven Pearson on 25/06/2020.
//  Copyright © 2020 Steve Pearson . All rights reserved.
//

#include "TaxCalculator.hpp"
#include "CTaxCalculator.h"

const void *createInstance() {
    CTaxCalculator* instance = new CTaxCalculator(new tax::CTransactionDto());
    instance->TaxRate = 0.2;
    return instance;
}

int subscribeToPropertyChanged(const void * context, property_event_callback callback, const void * obj) {

    CTaxCalculator* calc = (CTaxCalculator*)context;
        
    std::function<void(const CNotifyPropertyChangingEventArgs&)> lambda = [=](const CNotifyPropertyChangingEventArgs& s) {
        callback(s.name().c_str(), obj);
    };
    
    return calc->PropertyChanging.Subscribe(lambda);
}

double getNet(const void * context) {
    CTaxCalculator* calc = (CTaxCalculator*)context;
    
    return calc->Net;
}

void setNet(const void * context, double value) {
    CTaxCalculator* calc = (CTaxCalculator*)context;
    
    calc->Net = value;
}

double getTaxRate(const void * context) {
    CTaxCalculator* calc = (CTaxCalculator*)context;
    
    return calc->TaxRate;
}

void setTaxRate(const void * context, double value) {
    CTaxCalculator* calc = (CTaxCalculator*)context;
    
    calc->TaxRate = value;
}

double getTax(const void * context) {
    CTaxCalculator* calc = (CTaxCalculator*)context;
    
    return calc->Tax;
}

void setTax(const void * context, double value) {
    CTaxCalculator* calc = (CTaxCalculator*)context;
    
    calc->Tax = value;
}

double getGross(const void * context) {
    CTaxCalculator* calc = (CTaxCalculator*)context;
    
    return calc->Gross;
}
