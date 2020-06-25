//
//  TaxCalc.m
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#import "TaxCalcBridge.h"

#import "../CPP/CTaxCalculator.h"
#import "../CPP/Event.h"

@implementation TaxCalcBridge

CTaxCalculator* _object;

EventHandlerID _propertyChangedId;
EventHandlerID _propertyChangingId;

-(instancetype)init {
    return [self initWithObject:new CTaxCalculator(new CTransactionDto())];
}

-(instancetype)initWithObject:(nonnull CTaxCalculator*)object {
    self = [super init];
    if (self) {
        [self attachObject:object];
    }
    return self;
}

-(void)dealloc {
    [self detachObject];
}

-(void)attachObject:(nonnull CTaxCalculator*)object {
    _object = object;

    //_propertyChangedId = _object->PropertyChanged.Subscribe(^(CNotifyPropertyChangedEventArgs &args) {
        //NSLog(@"Property changed is %s", args.name().c_str());
        //[self didChangeValueForKey:[NSString stringWithCString:args.name().c_str() encoding:NSASCIIStringEncoding]];
    //});

    //_propertyChangingId = _object->PropertyChanging.Subscribe(^(CNotifyPropertyChangingEventArgs &args) {
        //NSLog(@"Property changing is %s", args.name().c_str());
        //[self willChangeValueForKey:[NSString stringWithCString:args.name().c_str() encoding:NSASCIIStringEncoding]];
    //});
}

-(void)detachObject {
    //_object->PropertyChanged.Unsubscribe(_propertyChangedId);
    //_object->PropertyChanging.Unsubscribe(_propertyChangingId);
    _object = NULL;
}

-(NSNumber*)net {
    NSLog(@"Getting Net %f", (const double)_object->Net);
    return [NSNumber numberWithDouble:_object->Net];
}

-(void)setNet:(NSNumber *)value {
    NSLog(@"Trying to change Net to %@", value);
    _object->Net = [value doubleValue];
}

-(NSNumber*)tax {
    NSLog(@"Getting Tax %f", (const double)_object->Tax);
    return [NSNumber numberWithDouble:_object->Tax];
}

-(void)setTax:(NSNumber *)value {
    NSLog(@"Trying to change Tax to %@", value);
    _object->Tax = [value doubleValue];
}

-(NSNumber*)taxRate {
    NSLog(@"Getting Tax Rate %f", (const double)_object->TaxRate);
    return [NSNumber numberWithDouble:_object->TaxRate];
}

-(void)setTaxRate:(NSNumber *)value {
    _object->TaxRate = [value doubleValue];
}

-(NSNumber*)gross {
    NSLog(@"Getting Gross %f", (const double)_object->Gross);
    return [NSNumber numberWithDouble:_object->Gross];
}

@end


