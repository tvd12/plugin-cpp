/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <GoogleMobileAds/GoogleMobileAds.h>

typedef enum {
    kSizeBanner = 1,
    kSizeFullBanner,
    kSizeLargeBanner,
    kSizeLeaderboard,
    kSizeMediumRectangle,
    kSizeSmartBanner,
    kSizeSkyscraper,
} AdmobSizeEnum;

typedef enum {
    kTypeBanner = 1,
    kTypeFullScreen,
} AdmobType;


typedef enum {
    kAdsReceived = 0,
    
    kAdsShown,
    kAdsDismissed,
    
    kPointsSpendSucceed,
    kPointsSpendFailed,
    
    kNetworkError,
    kUnknownError,
} AdsResult;

typedef enum {
    kPosCenter = 0,
    kPosTop,
    kPosTopLeft,
    kPosTopRight,
    kPosBottom,
    kPosBottomLeft,
    kPosBottomRight,
} AdsPosEnum;

@interface GoogleAdmobBanner : NSObject <GADBannerViewDelegate>
{
}

@property BOOL debug;
@property (copy, nonatomic) NSString* strPublishID;
@property (strong, nonatomic) GADBannerView* bannerView;
@property (strong, nonatomic) NSMutableArray* testDeviceIDs;

+ (id)getInstance;

/**
 interfaces from InterfaceAds
 */
- (void) configDeveloperInfo: (NSMutableDictionary*) devInfo;
- (void) showAds: (NSMutableDictionary*) info position:(int) pos;
- (void) hideAds: (NSMutableDictionary*) info;
- (void) queryPoints;
- (void) spendPoints: (int) points;
- (void) setDebugMode: (BOOL) isDebugMode;

/**
 interface for Admob SDK
 */
- (void) addTestDevice: (NSString*) deviceID;

/**
 */
- (void) onAdsResult:(id) obj withRet:(AdsResult) ret withMsg:(NSString*) msg;
- (void) onPlayerGetPoints:(id) obj withPoints: (int) points;
- (void) addAdView:(UIView*) view atPos:(AdsPosEnum) pos;
- (UIViewController *) getCurrentRootViewController;

@end
