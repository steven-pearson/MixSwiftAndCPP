//
//  TaxCalc.h
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 16/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#import <Foundation/Foundation.h>

//using namespace legacy;

@class TaxCalcBridge;

@interface TaxCalcBridge : NSObject {
}
@property (nonatomic, retain, readwrite) NSNumber * _Nonnull net;
@property (nonatomic, retain, readwrite) NSNumber * _Nonnull tax;
@property (nonatomic, retain, readwrite) NSNumber * _Nonnull taxRate;
@property (nonatomic, retain, readwrite) NSNumber * _Nonnull gross;

//-(id _Nonnull )initWithObject:(nonnull CTaxCalculator*)object;

@end
