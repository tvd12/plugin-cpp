//
//  ChartboostHelper.m
//  chartboost-integrations
//
//  Created by Dung Ta Van on 4/16/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Chartboost/Chartboost.h>
#import <Chartboost/CBNewsfeed.h>
#include "ChartboostHelper.h"

using namespace com::tvd::plugin;

// ChartboostDelegateBridge
@interface ChartboostDelegateBridge : NSObject<ChartboostDelegate>

- (std::string)getLocation: (CBLocation) cblocation;

@end
static ChartboostDelegateBridge* sDelegateBridge = nil;

ChartboostHelper::ChartboostHelper() {
    sDelegateBridge = [[ChartboostDelegateBridge alloc] init];
}

void ChartboostHelper::init(const std::string pAppId,
                            const std::string pAppSignature) {
    setAppId(pAppId);
    setAppSignature(pAppSignature);
    
    NSString* appId = [NSString stringWithUTF8String:getAppId().c_str()];
    NSString* appSignature = [NSString stringWithUTF8String:getAppSignature().c_str()];
    [Chartboost startWithAppId:appId
                  appSignature:appSignature
                      delegate:sDelegateBridge];
    
}

void ChartboostHelper::cacheInterstitial(const std::string& location) {
    if(location.length() > 0) {
        [Chartboost cacheInterstitial: [NSString stringWithUTF8String:location.c_str()]];
    }
}

void ChartboostHelper::showInterstitial(const std::string& location) {
    if(location.length() > 0) {
        [Chartboost showInterstitial: [NSString stringWithUTF8String:location.c_str()]];
    }
}

bool ChartboostHelper::hasCachedInterstitial(const std::string& location) {
    if(location.length() > 0) {
        return [Chartboost hasInterstitial: [NSString stringWithUTF8String:location.c_str()]];
    }
    
    return false;
}

void ChartboostHelper::cacheMoreApps(const std::string &location) {
    if(location.length() > 0) {
        [Chartboost cacheMoreApps: [NSString stringWithUTF8String:location.c_str()]];
    }
}

void ChartboostHelper::showMoreApps(const std::string& location) {
    if(location.length() > 0) {
        [Chartboost showMoreApps: [NSString stringWithUTF8String:location.c_str()]];
    }
}

bool ChartboostHelper::hasMoreApps(const std::string &location) {
    if(location.length() > 0) {
        return [Chartboost hasMoreApps: [NSString stringWithUTF8String:location.c_str()]];
    }
    
    return false;
}

void ChartboostHelper::cacheRewardedVideo(const std::string &location) {
    if(location.length() > 0) {
        [Chartboost cacheRewardedVideo: [NSString stringWithUTF8String:location.c_str()]];
    }
    
}

void ChartboostHelper::showRewardedVideo(const std::string &location) {
    if(location.length() > 0) {
        [Chartboost showRewardedVideo: [NSString stringWithUTF8String:location.c_str()]];
    }
}

bool ChartboostHelper::hasRewardedVideo(const std::string &location) {
    if(location.length() > 0) {
        return [Chartboost hasRewardedVideo: [NSString stringWithUTF8String:location.c_str()]];
    }
    
    return false;
}

void ChartboostHelper::setShouldRequestInterstitialsInFirstSession() {
    [Chartboost setShouldDisplayLoadingViewForMoreApps:NO];
}


/**
 *
 * Delegate method
 *
 */

@implementation ChartboostDelegateBridge

// Interstitial Delegate Methods

// Called before requesting an interstitial via the Chartboost API server.
- (BOOL)shouldRequestInterstitial:(CBLocation)location {
    return ChartboostHelper::getInstance()
    ->getDelegate()
    ->shouldRequestInterstitial([self getLocation:location]);
}

// Called before an interstitial will be displayed on the screen.
- (BOOL)shouldDisplayInterstitial:(CBLocation)location {
    return ChartboostHelper::getInstance()
    ->getDelegate()
    ->shouldDisplayInterstitial([self getLocation:location]);
}

// Called after an interstitial has been displayed on the screen.
- (void)didDisplayInterstitial:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didDisplayInterstitial([self getLocation:location]);
}

// Called after an interstitial has been loaded from the Chartboost API
// servers and cached locally.
- (void)didCacheInterstitial:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didCacheInterstitial([self getLocation:location]);
}

// Called after an interstitial has attempted to load from the Chartboost API
// servers but failed.
- (void)didFailToLoadInterstitial:(CBLocation)location
withError:(CBLoadError)error {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didFailToLoadInterstitial([self getLocation:location], (int)error);
}

// Called after a click is registered, but the user is not forwarded to the App Store.
- (void)didFailToRecordClick:(CBLocation)location
withError:(CBClickError)error {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didFailToRecordClick([self getLocation:location], (int)error);
}

// Called after an interstitial has been dismissed.
- (void)didDismissInterstitial:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didDismissInterstitial([self getLocation:location]);
}

// Called after an interstitial has been closed.
- (void)didCloseInterstitial:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didCloseInterstitial([self getLocation:location]);
}

// Called after an interstitial has been clicked.
- (void)didClickInterstitial:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didClickInterstitial([self getLocation:location]);
}

// MoreApps Delegate Methods

// Called before a MoreApps page will be displayed on the screen.
- (BOOL)shouldDisplayMoreApps:(CBLocation)location {
    return (bool)ChartboostHelper::getInstance()
    ->getDelegate()
    ->shouldDisplayMoreApps([self getLocation:location]);
}

// Called after a MoreApps page has been displayed on the screen.
- (void)didDisplayMoreApps:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didDisplayMoreApps([self getLocation:location]);
}

// Called after a MoreApps page has been loaded from the Chartboost API
// servers and cached locally.
- (void)didCacheMoreApps:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didCacheMoreApps([self getLocation:location]);
}

// Called after a MoreApps page has been dismissed.
- (void)didDismissMoreApps:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didDismissMoreApps([self getLocation:location]);
}

// Called after a MoreApps page has been closed.
- (void)didCloseMoreApps:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didCloseMoreApps([self getLocation:location]);
}

// Called after a MoreApps page has been clicked.
- (void)didClickMoreApps:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didClickMoreApps([self getLocation:location]);
}

// Called after a MoreApps page attempted to load from the Chartboost API
// servers but failed.
- (void)didFailToLoadMoreApps:(CBLocation)location
                    withError:(CBLoadError)error {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didFailToLoadMoreApps([self getLocation:location], (int)error);
}

// Rewarded Video Delegate Methods

// Called before a rewarded video will be displayed on the screen.
- (BOOL)shouldDisplayRewardedVideo:(CBLocation)location {
    return (bool)ChartboostHelper::getInstance()
    ->getDelegate()
    ->shouldDisplayRewardedVideo([self getLocation:location]);
}

// Called after a rewarded video has been displayed on the screen.
- (void)didDisplayRewardedVideo:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didDisplayRewardedVideo([self getLocation:location]);
}

// Called after a rewarded video has been loaded from the Chartboost API
// servers and cached locally.
- (void)didCacheRewardedVideo:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didCacheRewardedVideo([self getLocation:location]);
}

// Called after a rewarded video has attempted to load from the Chartboost API
// servers but failed.
- (void)didFailToLoadRewardedVideo:(CBLocation)location
                         withError:(CBLoadError)error {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didFailToLoadRewardedVideo([self getLocation:location], (int)error);
}

// Called after a rewarded video has been dismissed.
- (void)didDismissRewardedVideo:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didDismissRewardedVideo([self getLocation:location]);
}

// Called after a rewarded video has been closed.
- (void)didCloseRewardedVideo:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didCloseRewardedVideo([self getLocation:location]);
}

// Called after a rewarded video has been clicked.
- (void)didClickRewardedVideo:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didClickRewardedVideo([self getLocation:location]);
}

// Called after a rewarded video has been viewed completely and user is eligible for reward.
- (void)didCompleteRewardedVideo:(CBLocation)location
                      withReward:(int)reward {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didCompleteRewardedVideo([self getLocation:location], reward);
}

// Implement to be notified of when a video will be displayed on the screen for
// a given CBLocation. You can then do things like mute effects and sounds.
- (void)willDisplayVideo:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->willDisplayVideo([self getLocation:location]);
}

// Decide if Chartboost SDK will attempt to fetch videos from Chartboost API servers.
// shouldPrefetch YES if Chartboost should prefetch video content, NO otherwise.
// Default is YES.

+ (void)setShouldPrefetchVideoContent:(BOOL)shouldPrefetch {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->setShouldPrefetchVideoContent((bool)shouldPrefetch);
}

// InPlay Delegate Methods
// Called after an InPlay object has been loaded from the Chartboost API
// servers and cached locally.
- (void)didCacheInPlay:(CBLocation)location {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didClickInterstitial([self getLocation:location]);
}

// Called after a InPlay has attempted to load from the Chartboost API
// servers but failed.
- (void)didFailToLoadInPlay:(CBLocation)location
                  withError:(CBLoadError)error {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didFailToLoadInPlay([self getLocation:location], error);
}

// Miscellaneous Delegate Methods
// Whether Chartboost should show ads in the first session
// Defaults to YES
- (BOOL)shouldRequestInterstitialsInFirstSession {
    return (bool)ChartboostHelper::getInstance()
    ->getDelegate()
    ->shouldRequestInterstitialsInFirstSession();
}

// Called after the App Store sheet is dismissed, when displaying the embedded app sheet.
- (void)didCompleteAppStoreSheetFlow {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didCompleteAppStoreSheetFlow();
}

// Called if Chartboost SDK pauses click actions awaiting confirmation from the user. Use
// to implement an age gate in your game.
- (void)didPauseClickForConfirmation {
    ChartboostHelper::getInstance()
    ->getDelegate()
    ->didPauseClickForConfirmation();
}

- (std::string)getLocation:(CBLocation)cblocation {
    if(cblocation != nil) {
        return std::string([cblocation UTF8String]);
    }
    
    return std::string([CBLocationDefault UTF8String]);
}

@end