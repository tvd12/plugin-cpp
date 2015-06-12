//
//  UtilityHelper.cpp
//  os-utility
//
//  Created by Dung Ta Van on 4/14/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#include "UtilityHelper.h"
#include <string>
#import <AudioToolbox/AudioServices.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <sys/utsname.h> // import it in your header or implementation file.

using namespace com::tvd::plugin;

void UtilityHelper::vibrate() {
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

void UtilityHelper::rateUs() {
    
    [NSURL URLWithString:[NSString stringWithFormat:
                          ([[UIDevice currentDevice].systemVersion floatValue] >= 7.0f)
                          ? @"itms-apps://itunes.apple.com/app/id%s"
                                                   : @"itms-apps://itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%s", getAppStoreId().c_str()]]; // Would contain the right link
}

std::string UtilityHelper::getOSName() {
    return "IOS";
}

std::string UtilityHelper::getAppVersion() {
    NSString* appVersion = [[NSBundle mainBundle]
                            objectForInfoDictionaryKey: (NSString *)kCFBundleVersionKey];
    return string([appVersion UTF8String]);
}

std::string UtilityHelper::getDeviceModel() {
    struct utsname systemInfo;
    uname(&systemInfo);
    
    return string(systemInfo.machine);
}

std::string UtilityHelper::getDeviceName() {
    string deviceModel = getDeviceModel();
    if(!deviceModel.compare("i386"      )) { return "32-bit Simulator"; }
    if(!deviceModel.compare("x86_64"    )) { return "64-bit Simulator"; }
    if(!deviceModel.compare("iPod1,1"   )) { return "iPod Touch"; }
    if(!deviceModel.compare("iPod2,1"   )) { return "iPod Touch Second Generation"; }
    if(!deviceModel.compare("iPod3,1"   )) { return "iPod Touch Third Generation"; }
    if(!deviceModel.compare("iPod4,1"   )) { return "iPod Touch Fourth Generation"; }
    if(!deviceModel.compare("iPhone1,1" )) { return "iPhone"; }
    if(!deviceModel.compare("iPhone1,2" )) { return "iPhone 3G"; }
    if(!deviceModel.compare("iPhone2,1" )) { return "iPhone 3GS"; }
    if(!deviceModel.compare("iPad1,1"   )) { return "iPad"; }
    if(!deviceModel.compare("iPad2,1"   )) { return "iPad 2"; }
    if(!deviceModel.compare("iPad3,1"   )) { return "3rd Generation iPad"; }
    if(!deviceModel.compare("iPhone3,1" )) { return "iPhone 4 (GSM)"; }
    if(!deviceModel.compare("iPhone3,3" )) { return "iPhone 4 (CDMA/Verizon/Sprint)"; }
    if(!deviceModel.compare("iPhone4,1" )) { return "iPhone 4S"; }
    if(!deviceModel.compare("iPhone5,1" )) { return "iPhone 5 (model A1428, AT&T/Canada)"; }
    if(!deviceModel.compare("iPhone5,2" )) { return "iPhone 5 (model A1429, everything else)"; }
    if(!deviceModel.compare("iPad3,4"   )) { return "4th Generation iPad"; }
    if(!deviceModel.compare("iPad2,5"   )) { return "iPad Mini"; }
    if(!deviceModel.compare("iPhone5,3" )) { return "iPhone 5c (model A1456, A1532 | GSM)"; }
    if(!deviceModel.compare("iPhone5,4" )) { return "iPhone 5c (model A1507, A1516, A1526 (China), A1529 | Global)"; }
    if(!deviceModel.compare("iPhone6,1" )) { return "iPhone 5s (model A1433, A1533 | GSM)"; }
    if(!deviceModel.compare("iPhone6,2" )) { return "iPhone 5s (model A1457, A1518, A1528 (China), A1530 | Global)"; }
    if(!deviceModel.compare("iPad4,1"   )) { return "5th Generation iPad (iPad Air) - Wifi"; }
    if(!deviceModel.compare("iPad4,2"   )) { return "5th Generation iPad (iPad Air) - Cellular"; }
    if(!deviceModel.compare("iPad4,4"   )) { return "2nd Generation iPad Mini - Wifi"; }
    if(!deviceModel.compare("iPad4,5"   )) { return "2nd Generation iPad Mini - Cellular"; }
    if(!deviceModel.compare("iPhone7,1" )) { return "iPhone 6 Plus"; }
    if(!deviceModel.compare("iPhone7,2" )) { return "iPhone 6"; }
    
    return "unknown";
}

std::string UtilityHelper::getSystemVersion() {
    NSString *systemVersion = [[UIDevice currentDevice] systemVersion];
    
    return string([systemVersion UTF8String]);
}

void UtilityHelper::sendFeedback(const std::string &email,
                                 const std::string &emailSubject,
                                 const std::string &mailbody) {
    
    
    NSString *content = [NSString stringWithFormat:@"mailto:%s?subject=%s&body=%s",
                         email.c_str(),
                         emailSubject.c_str(),
                         mailbody.c_str()];
    NSURL *emailURL = [NSURL URLWithString:
                       [content stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
    
    [[UIApplication sharedApplication] openURL:emailURL];
}