//
//  TaxCalc.cpp
//  MixSwiftAndCPP
//
//  Created by Steven Pearson on 25/06/2020.
//  Copyright © 2020 Steve Pearson . All rights reserved.
//

#include "TaxCalc.hpp"
#include "TaxCalculator.h"

const void *createInstance() {
    TaxCalculator* instance = new TaxCalculator(new tax::Transaction());
    instance->TaxRate = 0.2;
    return instance;
}

int subscribeToPropertyChanged(const void * context, property_event_callback callback, const void * obj) {

    TaxCalculator* calc = (TaxCalculator*)context;
        
    std::function<void(const NotifyPropertyChangingEventArgs&)> lambda = [=](const NotifyPropertyChangingEventArgs& s) {
        callback(s.name().c_str(), obj);
    };
    
    return calc->Changing.Subscribe(lambda);
}

double getNet(const void * context) {
    TaxCalculator* calc = (TaxCalculator*)context;
    
    return calc->Net;
}

void setNet(const void * context, double value) {
    TaxCalculator* calc = (TaxCalculator*)context;
    
    calc->Net = value;
}

double getTaxRate(const void * context) {
    TaxCalculator* calc = (TaxCalculator*)context;
    
    return calc->TaxRate;
}

void setTaxRate(const void * context, double value) {
    TaxCalculator* calc = (TaxCalculator*)context;
    
    calc->TaxRate = value;
}

double getTax(const void * context) {
    TaxCalculator* calc = (TaxCalculator*)context;
    
    return calc->Tax;
}

void setTax(const void * context, double value) {
    TaxCalculator* calc = (TaxCalculator*)context;
    
    calc->Tax = value;
}

double getGross(const void * context) {
    TaxCalculator* calc = (TaxCalculator*)context;
    
    return calc->Gross;
}
