//
//  GoogleAdmobBridgeHelper.h
//  advertising-integrations
//
//  Created by Dung Ta Van on 6/2/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface GoogleAdmobBridgeHelper : NSObject

+ (void)setViewController : (UIViewController*)viewController;
+ (UIViewController*) getViewController;

@end
