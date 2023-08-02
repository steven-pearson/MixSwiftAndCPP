//
//  TaxCalculator.cpp
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#include "include/TaxCalculator.h"
// LCOV_EXCL_START
#include <string.h>
// LCOV_EXCL_STOP

TaxCalculator::TaxCalculator(Transaction *data) :
    Net("Net", this, [this](){ return _data->_net; }, [this](const double value) { _data->_net = value; }),
    Tax("Tax", this, [this](){ return _data->_tax; }, [this](const double value) { _data->_tax = value; }),
    TaxRate("TaxRate", this, [this](){ return _data->_taxRate; }, [this](const double value) { _data->_taxRate = value; }),
    Gross("Gross", this, [this](){ return _data->_gross; }),
    _data(data)
{
    _netChangedHandlerID = Net.Changed.Subscribe([this](PropertyChangedEventArgs<double>& args) { CalculateTax(); });
    _taxRateChangedHandlerID = TaxRate.Changed.Subscribe([this](PropertyChangedEventArgs<double>& args) { CalculateTax(); });
    _taxChangedHandlerID = Tax.Changed.Subscribe([this](PropertyChangedEventArgs<double>& args) { CalculateGross(); });
}

TaxCalculator::~TaxCalculator() {
    Net.Changed.Unsubscribe(_netChangedHandlerID);
    Tax.Changed.Unsubscribe(_taxChangedHandlerID);
    TaxRate.Changed.Unsubscribe(_taxRateChangedHandlerID);
}

void TaxCalculator::CalculateTax() {
    Tax = Net * TaxRate;
}

void TaxCalculator::CalculateGross() {
    // gross is not writable so update the DTO but fire notifications
    if (Gross.OnChanging(_data->_gross)) {
        _data->_gross = Net + Tax;
        Gross.OnChanged(_data->_gross);
    }
}


