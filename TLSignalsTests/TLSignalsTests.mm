//
//  TLSignalsTests.m
//  TLSignalsTests
//
//  Created by BSiDeUp on 11.12.12.
//  Copyright (c) 2012 Trylogic. All rights reserved.
//

#import "TLSignalsTests.h"
#import "TLSignals.h"


@implementation TLSignalsTests

- (void)testTarget
{
	auto signal = new TLSignal<NSString *, BOOL>(self);
	STAssertEquals(self, signal->getTarget(), @"Signal target must be presented");
}

-(void)testAddedOnlyOnce
{
	auto signal = new TLSignal<NSString *, BOOL>(self);
	__block int value = 0;
	
	auto observerBlock = ^(id target, NSString *stringParam, BOOL boolParam)
	{
		value += 42;
	};
	
	signal->addObserver(observerBlock);
	signal->addObserver(observerBlock);
	signal->addObserver(observerBlock);
	signal->addObserver(observerBlock);
	signal->addObserver(observerBlock);
	
	signal->notify(@"not used", YES);
	
	STAssertEquals(value, 42, @"value must be equals 0 + 42 (only 1 iteration)");
}

-(void)testRemovingObserver
{
	auto signal = new TLSignal<NSString *, BOOL>(self);
	__block int value = 0;
	
	auto observerBlock = ^(id target, NSString *stringParam, BOOL boolParam)
	{
		value += 42;
	};
	
	auto observerBlock2 = ^(id target, NSString *stringParam, BOOL boolParam)
	{
		value += 1;
	};
	
	signal->addObserver(observerBlock);
	signal->addObserver(observerBlock2);
	
	signal->notify(@"not used", YES);
	
	signal->removeObserver(observerBlock);
	
	signal->notify(@"not used", YES);
	
	STAssertEquals(value, 44, @"value must be equals 0 + 42 + 1 + 1 (only 1 iteration for first block and 2 iterations for second block)");
	
}

-(void)testRemoveAllObservers
{
	auto signal = new TLSignal<NSString *, BOOL>(self);
	__block int value = 42;
	
	auto observerBlock = ^(id target, NSString *stringParam, BOOL boolParam)
	{
		value = 9000;
	};
	
	auto observerBlock2 = ^(id target, NSString *stringParam, BOOL boolParam)
	{
		value = 100500;
	};
	
	signal->addObserver(observerBlock);
	signal->addObserver(observerBlock2);
	
	signal->removeAllObservers();
	
	signal->notify(@"not used", YES);
	
	STAssertEquals(value, 42, @"value must not be changed after notification");
}

-(void)testNotification
{
	auto signal = new TLSignal<NSString *, BOOL>(self);
	
	__block int value;
	
	auto observerBlock = ^(id target, NSString *stringParam, BOOL boolParam)
	{
		value = boolParam ? 42 : 9000;
	};
	
	signal->addObserver(observerBlock);
	
	signal->notify(@"not used", YES);
	
	STAssertEquals(value, 42, @"value must be 42 after notification");
}

@end
