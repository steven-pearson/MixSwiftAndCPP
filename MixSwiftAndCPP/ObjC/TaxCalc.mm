//
//  TaxCalc.m
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#import "TaxCalc.h"

#import "../CPP/CTaxCalculator.h"
#import "../CPP/Event.h"

@implementation TaxCalc

CTaxCalculator* _object;
EventHandlerID _grossChangingId;
EventHandlerID _grossChangedId;
EventHandlerID _taxChangingId;
EventHandlerID _taxChangedId;

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

    _propertyChangedId = _object->PropertyChanged.Subscribe(^(CPropertyChangedEventArgs &args) {
        NSLog(@"Property changed is %s", args.name().c_str());
        [self didChangeValueForKey:[NSString stringWithCString:args.name().c_str() encoding:NSASCIIStringEncoding]];
    });

    _propertyChangingId = _object->PropertyChanging.Subscribe(^(CPropertyChangingEventArgs &args) {
        NSLog(@"Property changing is %s", args.name().c_str());
        [self willChangeValueForKey:[NSString stringWithCString:args.name().c_str() encoding:NSASCIIStringEncoding]];
    });
    
    _grossChangingId = _object->Gross.Changing.Subscribe(^(CPropertyChangingEventArgs &args) {
        //NSLog(@"Gross changing value is-%f", (const double)self.gross);
        [self willChangeValueForKey:@"gross"];
    });
    _grossChangedId = _object->Gross.Changed.Subscribe(^(CPropertyChangedEventArgs &args) {
        //NSLog(@"Gross changed value is-%f", (const double)self._object.Gross);
        [self didChangeValueForKey:@"gross"];
    });
    _taxChangingId = _object->Tax.Changing.Subscribe(^(CPropertyChangingEventArgs &args) {
        //NSLog(@"Tax changing value is-%f", (const double)self._object.Tax);
        [self willChangeValueForKey:@"tax"];
    });
    _taxChangedId = _object->Tax.Changed.Subscribe(^(CPropertyChangedEventArgs &args) {
        //NSLog(@"Tax changed value is-%f", (const double)self._object.Tax);
        [self didChangeValueForKey:@"tax"];
    });
}

-(void)detachObject {
    /*_object->Gross.OnChanging.Unsubscribe(_grossChangingId);
    _object->Gross.OnChanged.Unsubscribe(_grossChangedId);
    _object->Tax.OnChanging.Unsubscribe(_taxChangingId);
    _object->Tax.OnChanged.Unsubscribe(_taxChangedId);*/
    _object = NULL;
}

-(NSNumber*)net {
    return [NSNumber numberWithDouble:_object->Net];
}

-(void)setNet:(NSNumber *)value {
    NSLog(@"Trying to change Net to %@", value);
    _object->Net = [value doubleValue];
}

-(NSNumber*)tax {
    return [NSNumber numberWithDouble:_object->Tax];
}

-(void)setTax:(NSNumber *)value {
    NSLog(@"Trying to change Tax to %@", value);
    _object->Tax = [value doubleValue];
}

-(NSNumber*)taxRate {
    return [NSNumber numberWithDouble:_object->TaxRate];
}

-(void)setTaxRate:(NSNumber *)value {
    _object->TaxRate = [value doubleValue];
}

-(NSNumber*)gross {
    return [NSNumber numberWithDouble:_object->Gross];
}

@end


