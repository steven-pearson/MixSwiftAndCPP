//
//  TaxCalculator.h
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#import "Transaction.h"
#import "Property.h"

using namespace tax;

class TaxCalculator : public INotifyPropertyChange {
public:
    TaxCalculator(Transaction *data);
    ~TaxCalculator();
        
    Property<double> Net;
    Property<double> Tax;
    Property<double> TaxRate;
    Property<double> Gross;
    
    EventBase<NotifyPropertyChangingEventArgs> Changing;
    EventBase<NotifyPropertyChangedEventArgs> Changed;

private:
    Transaction *_data;
    
    void OnNetChanged(NotifyPropertyChangedEventArgs& args);
    void OnTaxChanged(NotifyPropertyChangedEventArgs& args);
    void OnTaxRateChanged(NotifyPropertyChangedEventArgs& args);
    
    void OnChanging(NotifyPropertyChangingEventArgs& args) const;
    void OnChanged(NotifyPropertyChangedEventArgs& args) const;

    void CalculateTax();
    void CalculateGross();
    
    EventHandlerID _netChangedHandlerID;
    EventHandlerID _taxChangedHandlerID;
    EventHandlerID _taxRateChangedHandlerID;
};
