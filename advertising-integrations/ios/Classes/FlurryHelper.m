//
//  FlurryHelper.m
//  advertising-integrations
//
//  Created by Dung Ta Van on 4/27/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#import "Flurry.h"
#import "FlurryAdInterstitial.h"
#import "FlurryAdInterstitialDelegate.h"
#include "FlurryHelper.h"
#include "FlurryBridgeHelper.h"


using namespace std;
using namespace com::tvd::plugin;

@interface FlurryAdInterstitialDelegateBridge : NSObject<FlurryAdInterstitialDelegate>

@end

static FlurryAdInterstitial* sAdInterstitial = nil;
static FlurryAdInterstitialDelegateBridge *sAdInterstitialDelegateBridge = nil;

FlurryHelper::FlurryHelper() {
    sAdInterstitialDelegateBridge = [[FlurryAdInterstitialDelegateBridge alloc] init];
}

void FlurryHelper::init(const std::string &apiKey) {
    [Flurry startSession:[NSString stringWithUTF8String:apiKey.c_str()]];
}

void FlurryHelper::initAdInterstitial(const std::string &adSpaceName) {
    sAdInterstitial = [[FlurryAdInterstitial alloc]
                       initWithSpace:[NSString stringWithUTF8String:adSpaceName.c_str()]];
    sAdInterstitial.adDelegate = sAdInterstitialDelegateBridge;
}

void FlurryHelper::fetchAdInterstitial() {
    [sAdInterstitial fetchAd];
}

void FlurryHelper::showAdInterstitial() {
    if([sAdInterstitial ready]) {
        [sAdInterstitial presentWithViewController:
                                [FlurryBridgeHelper getViewController]];
    }
    else {
        fetchAdInterstitial();
    }
}

@implementation FlurryAdInterstitialDelegateBridge

#pragma mark - adInterstitial delegates

//Invoked when an ad is received for the specified  interstitialAd object.
- (void) adInterstitialDidFetchAd:(FlurryAdInterstitial*)interstitialAd {
    // you can choose to present the ad as soon as it is received
    FlurryHelper::getInstance()->getDelegate()
    ->onAdInterstitialDidRender();
}

//  Invoked when the interstitial ad is rendered.
- (void) adInterstitialDidRender:(FlurryAdInterstitial *)interstitialAd {
    FlurryHelper::getInstance()->getDelegate()
    ->onAdInterstitialDidRender();
}

//Informs the app that a video associated with this ad has finished playing.
//Only present for rewarded & client-side rewarded ad spaces
- (void) adInterstitialVideoDidFinish:(FlurryAdInterstitial *)interstitialAd {
    FlurryHelper::getInstance()->getDelegate()
    ->onAdInterstitialVideoDidFinish();
}

//Informational callback invoked when there is an ad error
- (void) adInterstitial:(FlurryAdInterstitial*)interstitialAd
                adError:(FlurryAdError) adError
       errorDescription:(NSError*) errorDescription
{
    // @param interstitialAd The interstitial ad object associated with the error
    // @param adError an enum that gives the reason for the error.
    // @param errorDescription An error object that gives additional information on the cause of the ad error.
    FlurryHelper::getInstance()->getDelegate()
    ->onAdInterstitial(adError);
}

@end

/**
 * Bridge to set view controller
 */
@implementation FlurryBridgeHelper

static UIViewController* sViewController;

+ (void)setViewController:(UIViewController *)uiViewController {
    sViewController = uiViewController;
}

+ (UIViewController*)getViewController {
    return sViewController;
}

@end