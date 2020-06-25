//
//  TaxCalculator.hpp
//  MixSwiftAndCPP
//
//  Created by Steven Pearson on 25/06/2020.
//  Copyright © 2020 Steve Pearson . All rights reserved.
//

#ifndef TaxCalculator_hpp
#define TaxCalculator_hpp

#ifdef __cplusplus
extern "C" {
#endif

    typedef void(*property_event_callback)(const char *, const void *);

    const void *createInstance();
    double getNet(const void * context);
    void setNet(const void * context, double value);
    double getTaxRate(const void * context);
    void setTaxRate(const void * context, double value);
    double getTax(const void * context);
    double getGross(const void * context);
    int subscribeToPropertyChanged(const void * context, property_event_callback callback, const void * obj);

#ifdef __cplusplus
}
#endif

#endif /* TaxCalculator_hpp */
