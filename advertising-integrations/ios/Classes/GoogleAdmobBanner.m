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

#import "GoogleAdmobBanner.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation GoogleAdmobBanner

@synthesize debug = __debug;
@synthesize strPublishID = __PublishID;
@synthesize testDeviceIDs = __TestDeviceIDs;

- (void) dealloc
{
    if (self.bannerView != nil) {
//        [self.bannerView release];
        self.bannerView = nil;
    }
    
    if (self.testDeviceIDs != nil) {
//        [self.testDeviceIDs release];
        self.testDeviceIDs = nil;
    }
//    [super dealloc];
}

#pragma mark InterfaceAds impl

+ (id) getInstance
{
    // structure used to test whether the block has completed or not
    static dispatch_once_t p = 0;
    
    // initialize sharedObject as nil (first call only)
    __strong static id _sharedObject = nil;
    
    // executes a block object once and only once for the lifetime of an application
    dispatch_once(&p, ^{
        _sharedObject = [[self alloc] init];
    });
    
    // returns the same object each time
    return _sharedObject;
}

- (void) configDeveloperInfo: (NSMutableDictionary*) devInfo
{
    self.strPublishID = (NSString*) [devInfo objectForKey:@"AdmobID"];
}

- (void) showAds: (NSMutableDictionary*) info position:(int) pos
{
    if (self.strPublishID == nil ||
        [self.strPublishID length] == 0) {
        OUTPUT_LOG(@"configDeveloperInfo() not correctly invoked in Admob!");
        return;
    }
    
    NSString* strType = [info objectForKey:@"AdmobType"];
    int type = [strType intValue];
    switch (type) {
        case kTypeBanner:
        {
            NSString* strSize = [info objectForKey:@"AdmobSizeEnum"];
            int sizeEnum = [strSize intValue];
            [self showBanner:sizeEnum atPos:pos];
            break;
        }
        case kTypeFullScreen:
            OUTPUT_LOG(@"Now not support full screen view in Admob");
            break;
        default:
            OUTPUT_LOG(@"The value of 'AdmobType' is wrong (should be 1 or 2)");
            break;
    }
}

- (void) hideAds: (NSMutableDictionary*) info
{
    NSString* strType = [info objectForKey:@"AdmobType"];
    int type = [strType intValue];
    switch (type) {
        case kTypeBanner:
        {
            if (nil != self.bannerView) {
                [self.bannerView removeFromSuperview];
//                [self.bannerView release];
                self.bannerView = nil;
            }
            break;
        }
        case kTypeFullScreen:
            OUTPUT_LOG(@"Now not support full screen view in Admob");
            break;
        default:
            OUTPUT_LOG(@"The value of 'AdmobType' is wrong (should be 1 or 2)");
            break;
    }
}

- (void) queryPoints
{
    OUTPUT_LOG(@"Admob not support query points!");
}

- (void) spendPoints: (int) points
{
    OUTPUT_LOG(@"Admob not support spend points!");
}

- (void) setDebugMode: (BOOL) isDebugMode
{
    self.debug = isDebugMode;
}

- (NSString*) getSDKVersion
{
    return @"6.12.2";
}

- (NSString*) getPluginVersion
{
    return @"0.2.0";
}

- (void) showBanner: (int) sizeEnum atPos:(int) pos
{
    GADAdSize size = kGADAdSizeBanner;
    switch (sizeEnum) {
        case kSizeBanner:
            size = kGADAdSizeBanner;
            break;
        case kSizeFullBanner:
            size = kGADAdSizeFullBanner;
            break;
        case kSizeLargeBanner:
            size = kGADAdSizeLargeBanner;
            break;
        case kSizeLeaderboard:
            size = kGADAdSizeLeaderboard;
            break;
        case kSizeMediumRectangle:
            size = kGADAdSizeMediumRectangle;
            break;
        case kSizeSmartBanner:
            // check game orientation
            if (UIInterfaceOrientationIsPortrait([[UIApplication sharedApplication] statusBarOrientation]))
            {
                size = kGADAdSizeSmartBannerPortrait;
                NSLog(@"kGADAdSizeSmartBannerPortrait");
            }
            else
            {
                size = kGADAdSizeSmartBannerLandscape;
                NSLog(@"kGADAdSizeSmartBannerLandscape");
            }
            break;
        case kSizeSkyscraper:
            size = kGADAdSizeSkyscraper;
            break;
        default:
            break;
    }
    if (nil != self.bannerView) {
        [self.bannerView removeFromSuperview];
//        [self.bannerView release];
        self.bannerView = nil;
    }
    
    self.bannerView = [[GADBannerView alloc] initWithAdSize:size];
    self.bannerView.adUnitID = self.strPublishID;
    self.bannerView.delegate = self;
    [self.bannerView setRootViewController:[self getCurrentRootViewController]];
    [self addAdView:self.bannerView atPos:pos];
    
    GADRequest* request = [GADRequest request];
    request.testDevices = [NSArray arrayWithArray:self.testDeviceIDs];
    [self.bannerView loadRequest:request];
}

#pragma mark interface for Admob SDK

- (void) addTestDevice: (NSString*) deviceID
{
    if (nil == self.testDeviceIDs) {
        self.testDeviceIDs = [[NSMutableArray alloc] init];
        [self.testDeviceIDs addObject:kGADSimulatorID];
    }
    [self.testDeviceIDs addObject:deviceID];
}

#pragma mark GADBannerViewDelegate impl

// Since we've received an ad, let's go ahead and set the frame to display it.
- (void)adViewDidReceiveAd:(GADBannerView *)adView {
    NSLog(@"Received ad");
    [self onAdsResult:self withRet:kAdsReceived withMsg:@"Ads request received success!"];
}

- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"Failed to receive ad with error: %@", [error localizedFailureReason]);
    int errorNo = kUnknownError;
    switch ([error code]) {
        case kGADErrorNetworkError:
            errorNo = kNetworkError;
            break;
        default:
            break;
    }
    [self onAdsResult:self withRet:errorNo withMsg:[error localizedDescription]];
}

/*
 *
 */
- (void) onAdsResult:(id) obj withRet:(AdsResult) ret withMsg:(NSString*) msg
{
}

- (void) onPlayerGetPoints:(id) obj withPoints: (int) points
{

}

- (NSString*)buildVersion
{
    NSString *SDKPlatformVersion = [[NSBundle mainBundle] infoDictionary][@"DTPlatformVersion"];
    
    if (SDKPlatformVersion) {
        return SDKPlatformVersion;
    }
    
    // adapted from http://stackoverflow.com/questions/25540140/can-one-determine-the-ios-sdk-version-used-to-build-a-binary-programmatically
    // form character set of digits and punctuation
    NSMutableCharacterSet *characterSet = [[NSCharacterSet decimalDigitCharacterSet] mutableCopy];
    
    [characterSet formUnionWithCharacterSet: [NSCharacterSet punctuationCharacterSet]];
    
    // get only those things in characterSet from the SDK name
    NSString *SDKName = [[NSBundle mainBundle] infoDictionary][@"DTSDKName"];
    NSArray *components = [[SDKName componentsSeparatedByCharactersInSet: [characterSet invertedSet]]
                           filteredArrayUsingPredicate: [NSPredicate predicateWithFormat:@"length != 0"]];
    
    if([components count])  {
        return components[0];
    }
    
    return nil;
}

- (BOOL)wasBuiltForiOS8orLater
{
    return [[self buildVersion] compare:@"8.0"] != NSOrderedAscending;
}

- (BOOL)requireRotation
{
    return ![self wasBuiltForiOS8orLater] || ([[[UIDevice currentDevice] systemVersion] floatValue] < 8.0);
}

- (void) addAdView:(UIView*) view atPos:(AdsPosEnum) pos
{
    UIViewController* controller = [self getCurrentRootViewController];
    
    if (nil == controller) {
        NSLog(@"Can't get the UIViewController object");
        return;
    }
    
    CGSize rootSize = controller.view.frame.size;
    CGSize viewSize = view.frame.size;
    CGPoint viewOrigin;
    
    if ([self requireRotation] && UIInterfaceOrientationIsLandscape(controller.interfaceOrientation)){
        CGFloat temp = rootSize.width;
        rootSize.width = rootSize.height;
        rootSize.height = temp;
    }
    
    switch (pos) {
        case kPosTop:
            viewOrigin.x = (rootSize.width - viewSize.width) / 2;
            viewOrigin.y = 0.0f;
            break;
        case kPosTopLeft:
            viewOrigin.x = 0.0f;
            viewOrigin.y = 0.0f;
            break;
        case kPosTopRight:
            viewOrigin.x = rootSize.width - viewSize.width;
            viewOrigin.y = 0.0f;
            break;
        case kPosBottom:
            viewOrigin.x = (rootSize.width - viewSize.width) / 2;
            viewOrigin.y = rootSize.height - viewSize.height;
            break;
        case kPosBottomLeft:
            viewOrigin.x = 0.0f;
            viewOrigin.y = rootSize.height - viewSize.height;
            break;
        case kPosBottomRight:
            viewOrigin.x = rootSize.width - viewSize.width;
            viewOrigin.y = rootSize.height - viewSize.height;
            break;
        case kPosCenter:
        default:
            viewOrigin.x = (rootSize.width - viewSize.width) / 2;
            viewOrigin.y = (rootSize.height - viewSize.height) / 2;
            break;
    }
    
    CGRect rect = CGRectMake(viewOrigin.x, viewOrigin.y, viewSize.width, viewSize.height);
    view.frame = rect;
    [controller.view addSubview:view];
}

- (UIViewController *)getCurrentRootViewController {
    
    UIViewController *result = nil;
    
    // Try to find the root view controller programmically
    
    // Find the top window (that is not an alert view or other window)
    UIWindow *topWindow = [[UIApplication sharedApplication] keyWindow];
    if (topWindow.windowLevel != UIWindowLevelNormal)
    {
        NSArray *windows = [[UIApplication sharedApplication] windows];
        for(topWindow in windows)
        {
            if (topWindow.windowLevel == UIWindowLevelNormal)
                break;
        }
    }
    
    UIView *rootView = [[topWindow subviews] objectAtIndex:0];
    id nextResponder = [rootView nextResponder];
    
    if ([nextResponder isKindOfClass:[UIViewController class]])
        result = nextResponder;
    else if ([topWindow respondsToSelector:@selector(rootViewController)] && topWindow.rootViewController != nil)
        result = topWindow.rootViewController;
    else
        NSAssert(NO, @"Could not find a root view controller.");
    
    return result;
}

@end
