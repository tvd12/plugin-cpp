//
//  GoogleAdmobHelper.m
//  advertising-integrations
//
//  Created by Dung Ta Van on 5/28/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#import "GoogleAdmobHelper.h"

#import <GoogleMobileAds/GoogleMobileAds.h>
#import "GoogleAdmobBridgeHelper.h"

using namespace std;
using namespace com::tvd::plugin;

@interface AdmobDelegateBridge : NSObject<GADInterstitialDelegate>

@end

static GADInterstitial* sInterstitial = nil;
static AdmobDelegateBridge* sDelegateBridge = nil;

GoogleAdmobHelper::GoogleAdmobHelper() :
mTestDevices(vector<string>()) {
    sDelegateBridge = [[AdmobDelegateBridge alloc] init];
}

void GoogleAdmobHelper::initInterstitial(const std::string &admobId,
                                         bool debug) {
    setAdUnitId(admobId);
    
}

void GoogleAdmobHelper::addTestDevices(const std::vector<std::string> &devices) {
    mTestDevices.insert(mTestDevices.end(), devices.begin(), devices.end());
}

void GoogleAdmobHelper::requestInterstitial() {
    sInterstitial = [[GADInterstitial alloc]
                     initWithAdUnitID:[NSString stringWithUTF8String:getAdUnitId().c_str()]];
    [sInterstitial setDelegate: sDelegateBridge];
    
    GADRequest *request = [GADRequest request];
    NSMutableArray* testDevices = [[NSMutableArray alloc] init];
    for(int i = 0 ; i < mTestDevices.size() ; i++) {
        [testDevices addObject:[NSString stringWithUTF8String:mTestDevices[i].c_str()]];
    }
    request.testDevices = testDevices;
    [sInterstitial loadRequest:[GADRequest request]];
}

void GoogleAdmobHelper::showInterstitial() {
    if([sInterstitial isReady]) {
        [sInterstitial presentFromRootViewController:
                             [GoogleAdmobBridgeHelper getViewController]];
    }
}

bool GoogleAdmobHelper::isInterstitialReady() {
    return (bool)[sInterstitial isReady];
}

/**
 * Interstitial delegate
 */
@implementation AdmobDelegateBridge

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad {
    string adUniId = [[ad adUnitID] UTF8String];
    GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
    ->interstitialDidReceiveAd(adUniId);
}

- (void)interstitial:(GADInterstitial *)ad
didFailToReceiveAdWithError:(GADRequestError *)error {
    string adUniId = [[ad adUnitID] UTF8String];
    string errorStr = [[error localizedDescription] UTF8String];
    int errorCode = [error code];
    switch (errorCode) {
        case kGADErrorInternalError:
            errorStr = "INTERNAL_ERROR";
            break;
        case kGADErrorInvalidRequest:
            errorStr = "INVALID_REQUEST";
            break;
        case kGADErrorNetworkError:
            errorStr = "NETWORK_ERROR";
            break;
        case kGADErrorNoFill:
            errorStr = "NO_FILL";
            break;
            
        default:
            break;
    }
    
    GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
    ->interstitial(adUniId, errorStr);
}

#pragma mark Display-Time Lifecycle Notifications
- (void)interstitialWillPresentScreen:(GADInterstitial *)ad {
    string adUniId = [[ad adUnitID] UTF8String];
    GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
    ->interstitialWillPresentScreen(adUniId);
}

- (void)interstitialWillDismissScreen:(GADInterstitial *)ad {
    string adUniId = [[ad adUnitID] UTF8String];
    GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
    ->interstitialWillDismissScreen(adUniId);
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)ad {
    string adUniId = [[ad adUnitID] UTF8String];
    GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
    ->interstitialDidDismissScreen(adUniId);
}

- (void)interstitialWillLeaveApplication:(GADInterstitial *)ad {
    string adUniId = [[ad adUnitID] UTF8String];
    GoogleAdmobHelper::getInstance()->getInterstitialDelegate()
    ->interstitialWillLeaveApplication(adUniId);
}

@end

/**
 * Bridge to set view controller
 */
@implementation GoogleAdmobBridgeHelper

static UIViewController* sViewController;

+ (void)setViewController:(UIViewController *)uiViewController {
    sViewController = uiViewController;
}

+ (UIViewController*)getViewController {
    return sViewController;
}

@end
