//
//  CTaxCalculator.h
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#import "CTransactionDto.h"
#import "Property.h"

//using namespace legacy;

class CTaxCalculator : public INotifyPropertyChange {
public:
    CTaxCalculator(CTransactionDto *transactionEntity);
    ~CTaxCalculator();
        
    CProperty<const double> Net;
    CProperty<const double> Tax;
    CProperty<const double> TaxRate;
    CProperty<const double> Gross;
    
    CEventBase<CNotifyPropertyChangingEventArgs> PropertyChanging;
    CEventBase<CNotifyPropertyChangedEventArgs> PropertyChanged;

private:
    CTransactionDto *_dto;
    
    void OnNetChanged(CEventArgs& args);
    void OnTaxChanged(CEventArgs& args);
    void OnTaxRateChanged(CEventArgs& args);
    
    void OnPropertyChanging(CNotifyPropertyChangingEventArgs& args) const;
    void OnPropertyChanged(CNotifyPropertyChangedEventArgs& args) const;

    void CalculateTax();
    void CalculateGross();
    
    EventHandlerID _netChangedHandlerID;
    EventHandlerID _taxChangedHandlerID;
    EventHandlerID _taxRateChangedHandlerID;
};
