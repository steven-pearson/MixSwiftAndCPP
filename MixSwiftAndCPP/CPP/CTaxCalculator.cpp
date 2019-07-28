//
//  CTaxCalculator.cpp
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#include "CTaxCalculator.h"
#include <string.h>

CTaxCalculator::CTaxCalculator(CTransactionDto *dto) :
    _dto(dto),
    Net("net", this, [=](){ return this->_dto->_net; }, [=](const double value) { this->_dto->_net = value; }),
    Tax("tax", this, [=](){ return this->_dto->_tax; }, [=](const double value) { this->_dto->_tax = value; }),
    TaxRate("taxRate", this, [=](){ return this->_dto->_taxRate; }, [=](const double value) { this->_dto->_taxRate = value; }),
    Gross("gross", this, [=](){ return this->_dto->_gross; })
{
    _netChangedHandlerID = Net.Changed.Subscribe([=](CPropertyChangedEventArgs<double>& args) { CalculateTax(); });
    _taxRateChangedHandlerID = TaxRate.Changed.Subscribe([=](CPropertyChangedEventArgs<double>& args) { CalculateTax(); });
    _taxChangedHandlerID = Tax.Changed.Subscribe([=](CPropertyChangedEventArgs<double>& args) { CalculateGross(); });
}

CTaxCalculator::~CTaxCalculator() {
    Net.Changed.Unsubscribe(_netChangedHandlerID);
    Tax.Changed.Unsubscribe(_taxChangedHandlerID);
    TaxRate.Changed.Unsubscribe(_taxRateChangedHandlerID);
}

void CTaxCalculator::OnNetChanged(CEventArgs& args) {
    CalculateTax();
}

void CTaxCalculator::OnTaxChanged(CEventArgs& args) {
    CalculateGross();
}

void CTaxCalculator::OnTaxRateChanged(CEventArgs& args) {
    CalculateTax();
}

void CTaxCalculator::CalculateTax() {
    Tax = Net * TaxRate;
}

void CTaxCalculator::CalculateGross() {
    // gross is not writable so update the DTO but fire notifications
    Gross.OnChanging(_dto->_gross);
    _dto->_gross = Net + Tax;
    Gross.OnChanged(_dto->_gross);
}

void CTaxCalculator::OnPropertyChanging(CNotifyPropertyChangingEventArgs& args) const {
    PropertyChanging.Notify(args);
}

void CTaxCalculator::OnPropertyChanged(CNotifyPropertyChangedEventArgs& args) const {
    PropertyChanged.Notify(args);
}



