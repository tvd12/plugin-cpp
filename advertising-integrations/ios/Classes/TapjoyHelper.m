//
//  TapjoyHelper.m
//  advertising-integrations
//
//  Created by Dung Ta Van on 4/28/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#import "TapjoyBridgeHelper.h"
#import <Tapjoy/Tapjoy.h>
#import <Tapjoy/TJPlacement.h>

#include "TapjoyHelper.h"

using namespace std;
using namespace com::tvd::plugin;

@interface TJMainViewController : NSObject
-(void)config;
-(void) requestOfferwall:(NSString*) placementUnit;
-(void) showOfferwall;
-(void) requestDirectPlayVideo:(NSString*) videoUnit;
-(BOOL) hasDirectPlayVideo;
-(BOOL) isDirectPlayVideoReady;
-(void) showDirectPlayVideo;
-(NSString*)getCurrencyBalance;
-(NSString*)spendCurrency:(int)value;
-(NSString*)awardCurrency:(int)value;
-(BOOL)requestContent:(NSString*)placementName;
-(BOOL)showContent;

@end

@interface TJDirectPlayPlacementDelegate : NSObject<TJPlacementDelegate>
@property (nonatomic, strong) TJMainViewController *tjViewController;
@end

@interface TJOfferwallPlacementDelegate : NSObject<TJPlacementDelegate>
@property (nonatomic, strong) TJMainViewController *tjViewController;
@end

@interface TJMainViewController () <TJCViewDelegate, TJPlacementDelegate, TJCVideoAdDelegate>

@property (strong, nonatomic) TJPlacement *testPlacement;
@property (strong, nonatomic) TJPlacement *directPlayPlacement;
@property (strong, nonatomic) TJPlacement *offerwallPlacement;
@property (nonatomic, strong) TJDirectPlayPlacementDelegate *dpDelegate;
@property (nonatomic, strong) TJOfferwallPlacementDelegate *offerwallDelegate;

@end

@interface TapjoyHelperBridgeDelegate : UIResponder<UIApplicationDelegate>
- (void)config;
- (void)addCurrencyEarnedListener;
- (void)removeCurrencyEarnedListener;
@end

static TapjoyHelperBridgeDelegate *sBridgeDelegate;
static TJMainViewController* sMainViewController;

TapjoyHelper::TapjoyHelper() :
mCommonDelegate(NULL),
mViewDelegate(NULL),
mVideoDelegate(NULL),
mDirectPlayDelegate(NULL),
mOfferwallDelegate(NULL),
mVideoUnit("video_unit"),
mOfferwallUnit("offerwall_unit") {
    sBridgeDelegate = [[TapjoyHelperBridgeDelegate alloc] init];
    [sBridgeDelegate config];
}

void TapjoyHelper::init(const std::string &sdkKey,
                        const std::string &userId,
                        bool debug) {
    if(userId.length() == 0) {
        [Tapjoy connect:[NSString stringWithUTF8String:sdkKey.c_str()]];
    }
    else {
        [Tapjoy connect:[NSString stringWithUTF8String:sdkKey.c_str()]
                options:@{TJC_OPTION_USER_ID:[NSString stringWithUTF8String:userId.c_str()],
                          TJC_OPTION_ENABLE_LOGGING : @((BOOL)debug)} ];
    }
    
}

void TapjoyHelper::initViewController() {
    sMainViewController = [[TJMainViewController alloc] init];
    [sMainViewController config];
}

void TapjoyHelper::addCurrencyEarnedListener() {
    [sBridgeDelegate addCurrencyEarnedListener];
}

void TapjoyHelper::removeCurrencyEarnedListener() {
    [sBridgeDelegate removeCurrencyEarnedListener];
}

void TapjoyHelper::requestOfferwall(const std::string &offerwallUnit) {
    setOfferwallUnit(offerwallUnit);
    [sMainViewController requestOfferwall:[NSString stringWithUTF8String:offerwallUnit.c_str()]];
}

void TapjoyHelper::showOfferwall() {
    [sMainViewController showOfferwall];
}

void TapjoyHelper::requestDirectPlayVideo(const std::string &videoUnit) {
    setVideoUnit(videoUnit);
    [sMainViewController requestDirectPlayVideo:[NSString stringWithUTF8String:videoUnit.c_str()]];
}

bool TapjoyHelper::hasDirectPlayVideo() {
    return (bool)[sMainViewController hasDirectPlayVideo];
}

bool TapjoyHelper::isDirectPlayVideoReady() {
    return (bool)[sMainViewController isDirectPlayVideoReady];
}

void TapjoyHelper::showDirectPlayVideo() {
    [sMainViewController showDirectPlayVideo];
}

string TapjoyHelper::getCurrentBalance() {
    return [[sMainViewController getCurrencyBalance] UTF8String];
}

string TapjoyHelper::spendCurrency(int value) {
    return [[sMainViewController spendCurrency:value] UTF8String];
}

string TapjoyHelper::awardCurrecy(int value) {
    return [[sMainViewController awardCurrency:value] UTF8String];
}

bool TapjoyHelper::requestContent(const std::string &placementName) {
    return (bool)[sMainViewController requestContent:
                  [NSString stringWithUTF8String:placementName.c_str()]];
}

bool TapjoyHelper::showContent() {
    return (bool)[sMainViewController showContent];
}

@implementation TapjoyHelperBridgeDelegate

-(void)config {
    // Tapjoy Connect Notifications
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(tjcConnectSuccess:)
                                                 name:TJC_CONNECT_SUCCESS
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(tjcConnectFail:)
                                                 name:TJC_CONNECT_FAILED
                                               object:nil];
}

-(void)addCurrencyEarnedListener {
    // Add an observer for when a user has successfully earned currency.
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(showEarnedCurrencyAlert:)
                                                 name:TJC_CURRENCY_EARNED_NOTIFICATION
                                               object:nil];
    
    // Best Practice: We recommend calling getCurrencyBalance as often as possible so the user’s balance is always up-to-date.
//    [Tapjoy getCurrencyBalance];
}
-(void)removeCurrencyEarnedListener {
    // Remove this to prevent the possibility of multiple redundant notifications.
    [[NSNotificationCenter defaultCenter] removeObserver:self name:TJC_CURRENCY_EARNED_NOTIFICATION object:nil];
}

-(void)tjcConnectSuccess:(NSNotification*)notifyObj {
    NSLog(@"Tapjoy connect Succeeded");
    
    [Tapjoy getCurrencyBalance];
    TapjoyHelper::getInstance()->getCommonDelegate()->onConnectSuccess();
}


- (void)tjcConnectFail:(NSNotification*)notifyObj {
    NSLog(@"Tapjoy connect Failed");
    TapjoyHelper::getInstance()->getCommonDelegate()->onConnectFail();
}

- (void)showEarnedCurrencyAlert:(NSNotification*)notifyObj
{
    NSNumber *currencyEarned = notifyObj.object;
    int earnedNum = [currencyEarned intValue];
    
    NSLog(@"Currency earned: %d", earnedNum);
    
    // Pops up a UIAlert notifying the user that they have successfully earned some currency.
    // This is the default alert, so you may place a custom alert here if you choose to do so.
    [Tapjoy showDefaultEarnedCurrencyAlert];
    
    TapjoyHelper::getInstance()->getCommonDelegate()->showEarnedCurrencyAlert();
}

@end

/**
 *
 */

@implementation TJMainViewController

-(void)config {
    [Tapjoy setViewDelegate:self];
    [Tapjoy setVideoAdDelegate:self];
    
    _dpDelegate = [[TJDirectPlayPlacementDelegate alloc] init];
    _dpDelegate.tjViewController = self;
    
    _offerwallDelegate = [[TJOfferwallPlacementDelegate alloc] init];
    _offerwallDelegate.tjViewController = self;
}

-(void)requestOfferwall:(NSString*) placementUnit {
    _offerwallPlacement = [TJPlacement placementWithName:placementUnit
                                                delegate:_offerwallDelegate];
    _offerwallPlacement.presentationViewController = [TapjoyBridgeHelper getViewController];
    [_offerwallPlacement requestContent];
}

-(void)showOfferwall {
    _offerwallPlacement.presentationViewController =
    [TapjoyBridgeHelper getViewController];
}

-(void)requestDirectPlayVideo:(NSString *)videoUnit {
    _directPlayPlacement = [TJPlacement placementWithName:videoUnit delegate:_dpDelegate];
    [_directPlayPlacement requestContent];
}

-(BOOL)hasDirectPlayVideo {
    return [_directPlayPlacement isContentAvailable];
}

-(BOOL)isDirectPlayVideoReady {
    return [_directPlayPlacement isContentAvailable]
    && [_directPlayPlacement isContentReady];
}

-(void)showDirectPlayVideo {
    [_directPlayPlacement showContentWithViewController:
                                     [TapjoyBridgeHelper getViewController]];
}

-(NSString*)getCurrencyBalance {
    __block NSString* result = nil;
    [Tapjoy getCurrencyBalanceWithCompletion:^(NSDictionary *parameters, NSError *error) {
        
        if(error) {
            result = [NSString stringWithFormat:@"{\"error\":\"%@\"}",
                                [error localizedDescription]];
        }
        else {
            result = [NSString stringWithFormat:@"{\"currencyName\":\"%@\", \"amount\":%d}",
                      parameters[@"currencyName"],
                      [parameters[@"amount"] intValue]];
        }
        
    }];
    
    return result;
}

-(NSString*)spendCurrency:(int)value {
    __block NSString* result = nil;
    [Tapjoy spendCurrency:value completion:^(NSDictionary *parameters, NSError *error) {
        if(error) {
            result = [NSString stringWithFormat:@"{\"error\":\"%@\"}",
                      [error localizedDescription]];
        }
        else {
            result = [NSString stringWithFormat:@"{\"currencyName\":\"%@\", \"amount\":%d}",
                      parameters[@"currencyName"],
                      [parameters[@"amount"] intValue]];
        }
    }];
    
    return result;
}

-(NSString*)awardCurrency:(int)value {
    __block NSString* result = nil;
    [Tapjoy awardCurrency:value completion:^(NSDictionary *parameters, NSError *error) {
        if(error) {
            result = [NSString stringWithFormat:@"{\"error\":\"%@\"}",
                      [error localizedDescription]];
        }
        else {
            result = [NSString stringWithFormat:@"{\"currencyName\":\"%@\", \"amount\":%d}",
                      parameters[@"currencyName"],
                      [parameters[@"amount"] intValue]];
        }
    }];
    
    return result;
}

-(BOOL)requestContent:(NSString *)placementName {
    if(placementName != nil && placementName.length > 0) {
        _testPlacement = [TJPlacement placementWithName:placementName delegate:self];
        [_testPlacement requestContent];
        
        return true;
    }
    
    return false;
}

-(BOOL)showContent {
    if(_testPlacement.isContentAvailable) {
        [_testPlacement showContentWithViewController:
                                   [TapjoyBridgeHelper getViewController]];
        return true;
    }
    
    return false;
}

#pragma mark - Tapjoy Related Methods

- (void)viewWillAppearWithType:(int)viewType
{
    NSLog(@"Tapjoy view is about to be shown. %d", viewType);
    TapjoyHelper::getInstance()->getViewDelegate()
    ->viewWillAppearWithType(viewType);
}

- (void)viewDidAppearWithType:(int)viewType
{
    NSLog(@"Tapjoy view has been shown. %d", viewType);
    TapjoyHelper::getInstance()->getViewDelegate()
    ->viewDidDisappearWithType(viewType);
    // Best Practice: We recommend calling getCurrencyBalance as often as possible so the user’s balance is always up-to-date.
    [Tapjoy getCurrencyBalance];
}

- (void)viewWillDisappearWithType:(int)viewType
{
    NSLog(@"Tapjoy view is about to go away. %d", viewType);
    TapjoyHelper::getInstance()->getViewDelegate()
    ->viewWillDisappearWithType(viewType);
}

- (void)viewDidDisappearWithType:(int)viewType
{
    NSLog(@"Tapjoy view has been closed. %d", viewType);
    TapjoyHelper::getInstance()->getViewDelegate()
    ->viewDidDisappearWithType(viewType);
    // Best Practice: We recommend calling getCurrencyBalance as often as possible so the user’s balance is always up-to-date.
    [Tapjoy getCurrencyBalance];
}

#pragma mark Tapjoy Video

- (void)videoAdBegan {
    NSLog(@"videoAdBegan");
    TapjoyHelper::getInstance()->getVideoDelegate()
    ->videoAdBegan();
}

- (void)videoAdClosed {
    NSLog(@"videoAdClosed");
    TapjoyHelper::getInstance()->getVideoDelegate()
    ->videoAdClosed();
}

- (void)videoAdCompleted {
    NSLog(@"videoAdCompleted");
    TapjoyHelper::getInstance()->getVideoDelegate()
    ->videoAdCompleted();
}

- (void)videoAdError:(NSString*)errorMsg {
    NSLog(@"videoAdError");
    TapjoyHelper::getInstance()->getVideoDelegate()
    ->videoAdError([errorMsg UTF8String]);
}

#pragma mark TJPlacementDelegate methods

- (void)requestDidSucceed:(TJPlacement*)placement
{
    NSLog(@"Tapjoy request content complete, isContentAvailable:%d",
          placement.isContentAvailable);
    TapjoyHelper::getInstance()->getPlacementDelegate()
    ->requestDidSucceed([[placement placementName] UTF8String],
                        (bool)[placement isContentReady],
                        (bool)[placement isContentAvailable]);
}

- (void)contentIsReady:(TJPlacement*)placement
{
    NSLog(@"Tapjoy placement content is ready to display");
    TapjoyHelper::getInstance()->getPlacementDelegate()
    ->contentIsReady([[placement placementName] UTF8String],
                        (bool)[placement isContentAvailable]);
}

- (void)requestDidFail:(TJPlacement*)placement error:(NSError *)error
{
    NSLog(@"Tapjoy request content failed with error: %@", [error localizedDescription]);
    TapjoyHelper::getInstance()->getPlacementDelegate()
    ->requestDidFail([[placement placementName] UTF8String],
                     [[error localizedDescription] UTF8String]);

}

- (void)contentDidAppear:(TJPlacement*)placement
{
    NSLog(@"Content did appear for %@ placement", [placement placementName]);
    TapjoyHelper::getInstance()->getPlacementDelegate()
    ->contentDidAppear([[placement placementName] UTF8String]);
}

- (void)contentDidDisappear:(TJPlacement*)placement
{
    NSLog(@"Content did disappear for %@ placement", [placement placementName]);
    TapjoyHelper::getInstance()->getPlacementDelegate()
    ->contentDidDisappear([[placement placementName] UTF8String]);
}

- (void)placement:(TJPlacement*)placement didRequestPurchase:(TJActionRequest*)request productId:(NSString*)productId
{
    NSString *message = [NSString stringWithFormat: @"didRequestPurchase -- productId: %@, token: %@, requestId: %@", productId, request.token, request.requestId];
    NSLog(@"%@", message);
    
    TapjoyHelper::getInstance()->getPlacementDelegate()
    ->placementWithProduct([[placement placementName] UTF8String],
                           (bool)[placement isContentReady],
                           (bool)[placement isContentAvailable],
                           [request type],
                           [[request requestId] UTF8String],
                           [[request token] UTF8String],
                           [productId UTF8String]);
    
    // Your app must call either completed or cancelled to complete the lifecycle of the request
    [request completed];
}


- (void)placement:(TJPlacement*)placement didRequestReward:(TJActionRequest*)request itemId:(NSString*)itemId quantity:(int)quantity
{
    NSString *message = [NSString stringWithFormat: @"didRequestReward -- itemId: %@, quantity: %d, token: %@, requestId: %@", itemId, quantity, request.token, request.requestId];
    NSLog(@"%@", message);
    
    TapjoyHelper::getInstance()->getPlacementDelegate()
    ->placementWithItem([[placement placementName] UTF8String],
                        (bool)[placement isContentReady],
                        (bool)[placement isContentAvailable],
                        [request type],
                        [[request requestId] UTF8String],
                        [[request token] UTF8String],
                        [itemId UTF8String],
                        quantity);
    
    // Your app must call either completed or cancelled to complete the lifecycle of the request
    [request completed];
}


- (void)placement:(TJPlacement*)placement didRequestCurrency:(TJActionRequest*)request currency:(NSString*)currency amount:(int)amount
{
    NSString *message = [NSString stringWithFormat: @"didRequestCurrency -- currency: %@, amount: %d, token: %@, requestId: %@", currency, amount, request.token, request.requestId];
    NSLog(@"%@", message);
    
    TapjoyHelper::getInstance()->getPlacementDelegate()
    ->placementWithCurrency([[placement placementName] UTF8String],
                            (bool)[placement isContentReady],
                            (bool)[placement isContentAvailable],
                            [request type],
                            [[request requestId] UTF8String],
                            [[request token] UTF8String],
                            [currency UTF8String],
                            amount);
    
    // Your app must call either completed or cancelled to complete the lifecycle of the request
    [request completed];
}


- (void)placement:(TJPlacement*)placement didRequestNavigation:(TJActionRequest*)request location:(NSString *)location
{
    NSString *message = [NSString stringWithFormat: @"didRequestNavigation -- location: %@, token: %@, requestId: %@", location, request.token, request.requestId];
    NSLog(@"%@", message);
    
    TapjoyHelper::getInstance()->getPlacementDelegate()
    ->placementWithLocation([[placement placementName] UTF8String],
                            (bool)[placement isContentReady],
                            (bool)[placement isContentAvailable],
                            [request type],
                            [[request requestId] UTF8String],
                            [[request token] UTF8String],
                            [location UTF8String]);
    
    // Your app must call either completed or cancelled to complete the lifecycle of the request
    [request completed];
}

@end

/**
 * TJDirectPlayPlacementDelegate
 */

@interface TJDirectPlayPlacementDelegate ()

@end

@implementation TJDirectPlayPlacementDelegate
-(id)init
{
    self = [super init];
    
    if (self)
    {}
    
    return self;
}

- (void)requestDidSucceed:(TJPlacement*)placement
{
    NSLog(@"Tapjoy request did succeed, contentIsAvailable:%d", placement.isContentAvailable);
    TapjoyHelper::getInstance()->getDirectPlayDelegate()
    ->requestDidSucceed([[placement placementName] UTF8String],
                        (bool)[placement isContentReady],
                        (bool)[placement isContentAvailable]);
}

- (void)contentIsReady:(TJPlacement*)placement
{
    NSLog(@"Tapjoy placement content is ready to display");
    bool isShow = TapjoyHelper::getInstance()->getDirectPlayDelegate()
    ->contentIsReady([[placement placementName] UTF8String],
                        (bool)[placement isContentAvailable]);
    if(isShow) {
        [placement showContentWithViewController:placement.presentationViewController];
    }
}

- (void)requestDidFail:(TJPlacement*)placement error:(NSError *)error
{
    NSLog(@"Tapjoy request failed with error: %@", [error localizedDescription]);
    TapjoyHelper::getInstance()->getDirectPlayDelegate()
    ->requestDidFail([[placement placementName] UTF8String],
                     [[error localizedDescription] UTF8String]);
}

- (void)contentDidAppear:(TJPlacement*)placement
{
    NSLog(@"Content did appear for %@ placement", [placement placementName]);
    TapjoyHelper::getInstance()->getDirectPlayDelegate()
    ->contentDidAppear([[placement placementName] UTF8String]);
}

- (void)contentDidDisappear:(TJPlacement*)placement
{
    TapjoyHelper::getInstance()->getDirectPlayDelegate()
    ->contentDidDisappear([[placement placementName] UTF8String]);
    
    // Request next placement after the previous one is dismissed
    _tjViewController.directPlayPlacement =
    [TJPlacement placementWithName:[NSString stringWithUTF8String:TapjoyHelper::getInstance()
                                    ->getVideoUnit().c_str()]
                          delegate:self];
    [_tjViewController.directPlayPlacement requestContent];
    
    // Best Practice: We recommend calling getCurrencyBalance as often as possible so the user’s balance is always up-to-date.
    [Tapjoy getCurrencyBalance];
    
    NSLog(@"Content did disappear for %@ placement", [placement placementName]);
}
@end

@interface TJOfferwallPlacementDelegate ()

@end

@implementation TJOfferwallPlacementDelegate
-(id)init
{
    self = [super init];
    
    if (self)
    {}
    
    return self;
}

- (void)requestDidSucceed:(TJPlacement*)placement
{
    NSLog(@"Tapjoy request did succeed, contentIsAvailable:%d", placement.isContentAvailable);
    
    TapjoyHelper::getInstance()->getOfferwallDelegate()
    ->requestDidSucceed([[placement placementName] UTF8String],
                        (bool)[placement isContentReady],
                        (bool)[placement isContentAvailable]);
}

- (void)contentIsReady:(TJPlacement*)placement
{
    NSLog(@"Tapjoy placement content is ready to display");
    bool isShow = TapjoyHelper::getInstance()->getOfferwallDelegate()
    ->contentIsReady([[placement placementName] UTF8String],
                        (bool)[placement isContentAvailable]);
    if(isShow) {
        [placement showContentWithViewController:placement.presentationViewController];
    }
}

- (void)requestDidFail:(TJPlacement*)placement error:(NSError *)error
{
    NSLog(@"Tapjoy request failed with error: %@", [error localizedDescription]);
    TapjoyHelper::getInstance()->getOfferwallDelegate()
    ->requestDidFail([[placement placementName] UTF8String],
                     [[error localizedDescription] UTF8String]);
}

- (void)contentDidAppear:(TJPlacement*)placement
{
    NSLog(@"Content did appear for %@ placement", [placement placementName]);
    TapjoyHelper::getInstance()->getOfferwallDelegate()
    ->contentDidAppear([[placement placementName] UTF8String]);
}

- (void)contentDidDisappear:(TJPlacement*)placement
{
    NSLog(@"Content did disappear for %@ placement", [placement placementName]);
    TapjoyHelper::getInstance()->getOfferwallDelegate()
    ->contentDidDisappear([[placement placementName] UTF8String]);
    
    // Request next placement after the previous one is dismissed
    _tjViewController.directPlayPlacement =
    [TJPlacement placementWithName:[NSString stringWithUTF8String:TapjoyHelper::getInstance()
                                    ->getOfferwallUnit().c_str()]
                          delegate:self];
    [_tjViewController.directPlayPlacement requestContent];
    
    // Best Practice: We recommend calling getCurrencyBalance as often as possible so the user’s balance is always up-to-date.
    [Tapjoy getCurrencyBalance];
}
@end

/**
 * Bridge to set view controller
 */
@implementation TapjoyBridgeHelper

static UIViewController* sViewController;

+ (void)setViewController:(UIViewController *)uiViewController {
    sViewController = uiViewController;
}

+ (UIViewController*)getViewController {
    return sViewController;
}

@end
