//
//  AdColonyHelper.m
//  advertising-integrations
//
//  Created by Dung Ta Van on 4/24/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AdColony/AdColony.h>

#include "AdColonyHelper.h"

using namespace std;
using namespace com::tvd::plugin;

@interface AdColonyDelegateBridge : NSObject<AdColonyDelegate, AdColonyAdDelegate>

@end
static AdColonyDelegateBridge *sDelegateBridge = nil;

AdColonyHelper::AdColonyHelper() :
mDelegate(NULL) {
    sDelegateBridge = [[AdColonyDelegateBridge alloc] init];
}

void AdColonyHelper::init(const std::string &appId,
                          std::vector<std::string> &zoneIds,
                          bool logging) {
    NSMutableArray *zoneIdArray = [NSMutableArray array];
    for(int i = 0 ; i < zoneIds.size() ; i++) {
        NSString *nsstring = [NSString stringWithUTF8String:zoneIds.at(i).c_str()];
        [zoneIdArray addObject:nsstring];
    }
    NSString *nappId = [NSString stringWithUTF8String:appId.c_str()];
    [AdColony configureWithAppID: nappId
                         zoneIDs: zoneIdArray
                        delegate: sDelegateBridge
                         logging: (BOOL)logging];
}

void AdColonyHelper::checkeExistenceVideoAd(const std::string &zoneId) {
    
}

void AdColonyHelper::playVideoAdForZone(const std::string &zoneId) {
    [AdColony playVideoAdForZone:[NSString stringWithUTF8String:zoneId.c_str()]
                    withDelegate:sDelegateBridge];
    
}

void AdColonyHelper::playVideoAdForZone(const std::string &zoneId,
                                        bool showPrePopup,
                                        bool showPostPopup) {
    [AdColony playVideoAdForZone:[NSString stringWithUTF8String:zoneId.c_str()]
                    withDelegate: sDelegateBridge
                withV4VCPrePopup:(BOOL)showPrePopup
                andV4VCPostPopup:(BOOL)showPostPopup];
}

int AdColonyHelper::zoneStatusForZone(const std::string &zoneId) {
    ADCOLONY_ZONE_STATUS status = [AdColony zoneStatusForZone:
                                   [NSString stringWithUTF8String:zoneId.c_str()]];
    if(status == ADCOLONY_ZONE_STATUS_NO_ZONE) {
        return 0;
    }
    else if(status == ADCOLONY_ZONE_STATUS_OFF) {
        return 1;
    }
    else if(status == ADCOLONY_ZONE_STATUS_LOADING) {
        return 2;
    }
    else if(status == ADCOLONY_ZONE_STATUS_ACTIVE) {
        return 3;
    }
    else if(status == ADCOLONY_ZONE_STATUS_UNKNOWN) {
        return 4;
    }
    
    return 4;
}

void AdColonyHelper::setCustomId(const std::string &customId) {
    [AdColony setCustomID:[NSString stringWithUTF8String:customId.c_str()]];
}

std::string AdColonyHelper::getCustomId() {
    NSString* nsstring = [AdColony getCustomID];
    
    return (nsstring != nil) ? string([nsstring UTF8String]) : "";
}

std::string AdColonyHelper::getOpenUDID() {
    NSString* nsstring = [AdColony getOpenUDID];
    
    return (nsstring != nil) ? string([nsstring UTF8String]) : "";
}

std::string AdColonyHelper::getUniqueDeviceId() {
    NSString* nsstring = [AdColony getUniqueDeviceID];
    
    return (nsstring != nil) ? string([nsstring UTF8String]) : "";
}

std::string AdColonyHelper::getODIN1() {
    NSString *nsstring = [AdColony getODIN1];
    
    return (nsstring != nil) ? string([nsstring UTF8String]) : "";
}

std::string AdColonyHelper::getAdvertisingIdentifier() {
    NSString *nsstring = [AdColony getAdvertisingIdentifier];
    
    return (nsstring != nil) ? string([nsstring UTF8String]) : "";
}

std::string AdColonyHelper::getVendorIdentifier() {
    NSString *nsstring = [AdColony getVendorIdentifier];
    
    return (nsstring != nil) ? string([nsstring UTF8String]) : "";
}

bool AdColonyHelper::isVirtualCurrencyRewardAvailableForZone(const std::string &zoneId) {
    BOOL result = [AdColony isVirtualCurrencyRewardAvailableForZone:
                   [NSString stringWithUTF8String:zoneId.c_str()]];
    
    return (bool)result;
}

int AdColonyHelper::getVirtualCurrencyRewardsAvailableTodayForZone(const std::string &zoneId) {
    return [AdColony getVirtualCurrencyRewardsAvailableTodayForZone:
            [NSString stringWithUTF8String:zoneId.c_str()]];
}

std::string AdColonyHelper::getVirtualCurrencyNameForZone(const std::string &zoneId) {
    NSString *nsstring = [AdColony getVirtualCurrencyNameForZone:
                          [NSString stringWithUTF8String:zoneId.c_str()]];
    
    return (nsstring != nil) ? string([nsstring UTF8String]) : "";
}

int AdColonyHelper::getVirtualCurrencyRewardAmountForZone(const std::string &zoneId) {
    return [AdColony getVirtualCurrencyRewardAmountForZone:
            [NSString stringWithUTF8String:zoneId.c_str()]];
}

int AdColonyHelper::getVideosPerReward(const std::string &currencyName) {
    return [AdColony getVideosPerReward:
            [NSString stringWithUTF8String:currencyName.c_str()]];
}

int AdColonyHelper::getVideoCreditBalance(const std::string &currencyName) {
    return [AdColony getVideoCreditBalance:
            [NSString stringWithUTF8String:currencyName.c_str()]];
}

void AdColonyHelper::setOptions(const std::map<std::string, std::string> &options) {
    std::map<std::string, std::string> temp = options;
    NSDictionary* nsdict = [NSDictionary dictionary];
    std::map<std::string, std::string>::iterator it;
    for(it = temp.begin() ; it != temp.end() ; it ++) {
        NSString *key = [NSString stringWithUTF8String:it->first.c_str()];
        NSString *value = [NSString stringWithUTF8String:it->second.c_str()];
        [nsdict setValue:value forKey:key];
    }
}

void AdColonyHelper::cancelAd() {
    [AdColony cancelAd];
}

bool AdColonyHelper::isVideoReady() {
    return true;
}

bool AdColonyHelper::videoAdCurrentlyRunning() {
    BOOL result = [AdColony videoAdCurrentlyRunning];
    
    return (bool)result;
}

void AdColonyHelper::turnAllAdsOff() {
    [AdColony turnAllAdsOff];
}

void AdColonyHelper::setUserMetadata(const std::string &metadataType,
                                     const std::string &value) {
    [AdColony setUserMetadata:[NSString stringWithUTF8String:metadataType.c_str()]
                    withValue:[NSString stringWithUTF8String:value.c_str()]];
}

void AdColonyHelper::userInterestedIn(const std::string &topic) {
    [AdColony userInterestedIn:[NSString stringWithUTF8String:topic.c_str()]];
}

void AdColonyHelper::notifyIAPComplete(const std::string &transactionId,
                                       const std::string &productId,
                                       int quantity,
                                       int price,
                                       const std::string &currencyCode) {
    [AdColony notifyIAPComplete:[NSString stringWithUTF8String:transactionId.c_str()]
                      productID:[NSString stringWithUTF8String:productId.c_str()]
                       quantity:quantity
                          price:[NSNumber numberWithInt:quantity]
                   currencyCode:[NSString stringWithUTF8String:currencyCode.c_str()]];
}

/**
 *
 * Delegate method
 *
 */

@implementation AdColonyDelegateBridge

- (void) onAdColonyAdAvailabilityChange:(BOOL)available
                                 inZone:(NSString *)zoneID {
    AdColonyHelper::getInstance()->getDelegate()
    ->onAdColonyAdAvailabilityChange((bool)available,
                                     string([zoneID UTF8String]));
}

- (void) onAdColonyV4VCReward:(BOOL)success
                 currencyName:(NSString *)currencyName
               currencyAmount:(int)amount
                       inZone:(NSString *)zoneID {
    AdColonyHelper::getInstance()->getDelegate()
    ->onAdColonyV4VCReward((bool)success,
                           string([currencyName UTF8String]),
                           amount,
                           string([zoneID UTF8String]));
}

- (void) onAdColonyAdStartedInZone:(NSString *)zoneID {
    AdColonyHelper::getInstance()->getDelegate()
    ->onAdColonyAdStartedInZone(string([zoneID UTF8String]));
}

- (void) onAdColonyAdAttemptFinished:(BOOL)shown
                              inZone:(NSString *)zoneID {
    AdColonyHelper::getInstance()->getDelegate()
    ->onAdColonyAdAttemptFinished((bool)shown,
                                  string([zoneID UTF8String]));
}

- (void) onAdColonyAdFinishedWithInfo:(AdColonyAdInfo *)info {
    AdColonyHelperAdInfo* helperInfor =
    new AdColonyHelperAdInfo((bool)[info shown],
                             (bool)[info iapEnabled],
                             [info iapQuantity],
                             [info iapEngagementType],
                             string([[info zoneID] UTF8String]),
                             string([[info iapProductID] UTF8String]));
    AdColonyHelper::getInstance()->getDelegate()
    ->onAdColonyAdAttemptFinishedWithInfo(helperInfor);
    
    delete helperInfor;
    helperInfor = 0;
}
@end

/**
 *
 */
//void AdColonyHelperNativeAdView::pause() {
//
//}
//
//void AdColonyHelperNativeAdView::resume() {
//
//}
//
//float AdColonyHelperNativeAdView::recommendedHeightForWidth(float width) {
//    return width;
//}
