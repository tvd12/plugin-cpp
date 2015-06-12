//
//  TapjoyBridgeHelper.h
//  advertising-integrations
//
//  Created by Dung Ta Van on 4/28/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#ifndef advertising_integrations_TapjoyBridgeHelper_h
#define advertising_integrations_TapjoyBridgeHelper_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface TapjoyBridgeHelper : NSObject

+ (void)setViewController : (UIViewController*)viewController;
+ (UIViewController*) getViewController;

@end

#endif
