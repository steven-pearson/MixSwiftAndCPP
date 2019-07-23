//
//  TimeInfo.m
//  MixSwiftAndCPP
//
//  Created by Steve Pearson  on 13/06/2019.
//  Copyright © 2019 Steve Pearson . All rights reserved.
//

#import "TimeInfo.h"

@interface TimeInfo()
{
    NSString *_internal;
}

-(void)updateTime;

@end

@implementation TimeInfo

NSDateFormatter *_formatter;

-(id)init {
    self = [super init];
    if (self) {
        _formatter = [[NSDateFormatter alloc] init];
        [_formatter setDateFormat:@"HH:mm:ss"];

        [self updateTime];
        [NSTimer scheduledTimerWithTimeInterval:1.0
                                         target:self
                                       selector:@selector(updateTime)
                                       userInfo:nil
                                        repeats:YES];
    }
    return self;
}

-(void)updateTime {
    [self willChangeValueForKey:@"currentTime"];
    
    _internal = [_formatter stringFromDate:[NSDate date]];
    
    [self didChangeValueForKey:@"currentTime"];
}

-(NSString*)currentTime {
    return _internal;
}

@end
