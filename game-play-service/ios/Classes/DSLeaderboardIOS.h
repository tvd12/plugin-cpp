//
//  DSLeaderboardIOS.h
//  Dreamsake Studios
//
//  Created by Dreamsake Studios.
//  Copyright (c) 2014 Dreamsake Studios.
//

#import <GameKit/GameKit.h>
static NSString* kCachedAchievementsFile = @"CachedAchievements.archive";

/*!
 * @class DSAdColonyIOS
 * @abstract A singleton that communicates with GameCenter on iOS.
 */
@interface DSLeaderboardIOS : NSObject
    <GKGameCenterControllerDelegate, GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate>
{
    UIViewController* mainViewController;
    BOOL isAuthenticated;
    
@protected
    NSMutableDictionary* achievements;
    NSMutableDictionary* cachedAchievements;
}

+ (DSLeaderboardIOS*) sharedSingleton;

/*!
 * @abstract Sets the view controller used when authenticating the user or viewing the leaderboard.
 * @param viewController The view controller to set to.
 */
- (void) setViewController:(UIViewController*)viewController;

/*!
 * @abstract Authenticates the user to GameCenter.
 */
- (void) authenticateUser;

/*!
 * @abstract Submits a score to the leaderboard.
 * @param score The score to submit.
 * @param leaderboard The leaderboard identifier from iTunes Connect.
 */
- (void) submitScore:(int64_t)score forLeaderboard:(NSString*)leaderboard;

/*!
 * @abstract Opens a leaderboard for viewing.
 * @param leaderboard The leaderboard identifier from iTunes Connect.
 */
- (void) openLeaderboard:(NSString*)leaderboard;

- (void) openLeaderboards;

/*
 * Below methods are callbacks from GameCenter.
 */
- (void) gameCenterViewControllerDidFinish:(GKGameCenterViewController*)gameCenterViewController;
- (void) leaderboardViewControllerDidFinish:(GKLeaderboardViewController*)viewController;

// achievements
- (void) openAchievements;
- (void) reportAchievementWithID:(NSString*)identifier percentComplete:(float)percent;

- (GKAchievement*) getAchievementByID:(NSString*)identifier;
- (void) resetAchievements;
- (void) reportCachedAchievements;
- (void) saveCachedAchievements;
- (void) loadAchievements;


@end
