//
//  TaxCalculator.cpp
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#include "TaxCalculator.h"
#include <string.h>

TaxCalculator::TaxCalculator(Transaction *data) :
    _data(data),
    Net("net", this, [=](){ return this->_data->_net; }, [=](const double value) { this->_data->_net = value; }),
    Tax("tax", this, [=](){ return this->_data->_tax; }, [=](const double value) { this->_data->_tax = value; }),
    TaxRate("taxRate", this, [=](){ return this->_data->_taxRate; }, [=](const double value) { this->_data->_taxRate = value; }),
    Gross("gross", this, [=](){ return this->_data->_gross; })
{
    _netChangedHandlerID = Net.Changed.Subscribe([=](PropertyChangedEventArgs<double>& args) { CalculateTax(); });
    _taxRateChangedHandlerID = TaxRate.Changed.Subscribe([=](PropertyChangedEventArgs<double>& args) { CalculateTax(); });
    _taxChangedHandlerID = Tax.Changed.Subscribe([=](PropertyChangedEventArgs<double>& args) { CalculateGross(); });
}

TaxCalculator::~TaxCalculator() {
    Net.Changed.Unsubscribe(_netChangedHandlerID);
    Tax.Changed.Unsubscribe(_taxChangedHandlerID);
    TaxRate.Changed.Unsubscribe(_taxRateChangedHandlerID);
}

void TaxCalculator::OnNetChanged(NotifyPropertyChangedEventArgs& args) {
    CalculateTax();
}

void TaxCalculator::OnTaxChanged(NotifyPropertyChangedEventArgs& args) {
    CalculateGross();
}

void TaxCalculator::OnTaxRateChanged(NotifyPropertyChangedEventArgs& args) {
    CalculateTax();
}

void TaxCalculator::CalculateTax() {
    Tax = Net * TaxRate;
}

void TaxCalculator::CalculateGross() {
    // gross is not writable so update the DTO but fire notifications
    Gross.OnChanging(_data->_gross);
    _data->_gross = Net + Tax;
    Gross.OnChanged(_data->_gross);
}

void TaxCalculator::OnChanging(NotifyPropertyChangingEventArgs& args) const {
    Changing.Notify(args);
}

void TaxCalculator::OnChanged(NotifyPropertyChangedEventArgs& args) const {
    Changed.Notify(args);
}



