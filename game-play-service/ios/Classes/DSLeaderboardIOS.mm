//
//  DSFacebookNativeIOS.m
//  Dreamsake
//
//  Created by Dreamsake Studios on 2/27/2014.
//  Copyright (c) 2014 Dreamsake Studios.
//

#import "DSLeaderboardIOS.h"

@implementation DSLeaderboardIOS

static DSLeaderboardIOS* sharedSingleton;

+ (void) initialize
{
    static BOOL initialized = NO;
    if (!initialized)
    {
        initialized = YES;
        sharedSingleton = [[DSLeaderboardIOS alloc] init];
        sharedSingleton->mainViewController = nil;
        
        NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
        [notificationCenter addObserver:sharedSingleton
                               selector:@selector(authenticationChanged)
                                   name:GKPlayerAuthenticationDidChangeNotificationName
                                 object:nil];
    }
}

+ (DSLeaderboardIOS*) sharedSingleton
{
    return sharedSingleton;
}

- (void) setViewController:(UIViewController*)viewController
{
    mainViewController = viewController;
}

- (void) authenticateUser
{
    GKLocalPlayer* _localPlayer = [GKLocalPlayer localPlayer];
    __weak GKLocalPlayer* localPlayer = _localPlayer;
    localPlayer.authenticateHandler = ^(UIViewController *viewController, NSError *error)
    {
        if (viewController != nil)
        {
            if (!localPlayer.isAuthenticated)
            {
                [mainViewController presentViewController:viewController animated:YES completion:nil];
            }
        }
        else{
            if ([GKLocalPlayer localPlayer].authenticated) {
                // Get the default leaderboard identifier.
                [[GKLocalPlayer localPlayer] loadDefaultLeaderboardIdentifierWithCompletionHandler:^(NSString *leaderboardIdentifier, NSError *error) {
                    
                    if (error != nil) {
                        NSLog(@"%@", [error localizedDescription]);
                    }
                }];
                
                // Load achievements
                [self reportCachedAchievements];
            }
        }
    };
}

- (void) authenticationChanged
{
    if ([GKLocalPlayer localPlayer].isAuthenticated && !isAuthenticated)
    {
        isAuthenticated = YES;
    }
    else if (![GKLocalPlayer localPlayer].isAuthenticated && isAuthenticated)
    {
        isAuthenticated = NO;
    }
}

- (void) submitScore:(int64_t)score forLeaderboard:(NSString*)leaderboard
{
    GKScore* scoreReporter = [[GKScore alloc] initWithLeaderboardIdentifier:leaderboard];
    scoreReporter.value = score;
    scoreReporter.context = 0;
    
    NSArray *scores = @[scoreReporter];
    [GKScore reportScores:scores withCompletionHandler:^(NSError *error) {
        if (error != nil) {
            NSLog(@"%@", [error localizedDescription]);
        }
    }];
}

- (void) openLeaderboard:(NSString*)leaderboard
{
    GKGameCenterViewController* gcView = [[GKGameCenterViewController alloc] init];
    if (gcView && mainViewController)
    {
        gcView.gameCenterDelegate = self;
        gcView.viewState = GKGameCenterViewControllerStateLeaderboards;
        gcView.leaderboardTimeScope = GKLeaderboardTimeScopeAllTime;
        gcView.leaderboardIdentifier = leaderboard;
        //gcView.leaderboardCategory = leaderboard;
        [mainViewController presentViewController:gcView animated:YES completion:nil];
    }
}

- (void) openLeaderboards
{
    if ([GKLocalPlayer localPlayer].isAuthenticated && isAuthenticated) {
        GKGameCenterViewController* gcView = [[GKGameCenterViewController alloc] init];
        if (gcView && mainViewController)
        {
            gcView.gameCenterDelegate = self;
            gcView.viewState = GKGameCenterViewControllerStateLeaderboards;
            gcView.leaderboardTimeScope = GKLeaderboardTimeScopeAllTime;
            [mainViewController presentViewController:gcView animated:YES completion:nil];
        }
    }
    else {
        [self authenticateUser];
    }
}


- (void) gameCenterViewControllerDidFinish:(GKGameCenterViewController*)gameCenterViewController
{
    [mainViewController dismissViewControllerAnimated:YES completion:nil];
}

- (void) leaderboardViewControllerDidFinish:(GKLeaderboardViewController*)viewController
{
    [mainViewController dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark Achievements

- (void) loadAchievements
{
    [GKAchievement loadAchievementsWithCompletionHandler:^(NSArray* loadedAchievements, NSError* error)
     {
         if (achievements == nil)
         {
             achievements = [[NSMutableDictionary alloc] init];
         }
         else
         {
             [achievements removeAllObjects];
         }
         
         for (GKAchievement* achievement in loadedAchievements)
         {
             [achievements setObject:achievement forKey:achievement.identifier];
         }
     }];
}

- (void) openAchievements
{
    if ([GKLocalPlayer localPlayer].isAuthenticated && isAuthenticated) {
        GKAchievementViewController* achievementsVC = [[GKAchievementViewController alloc] init];
        if (achievementsVC && mainViewController)
        {
            achievementsVC.achievementDelegate = self;
            [mainViewController presentViewController:achievementsVC animated:YES completion:nil];
        }
    }
    else{
        [self authenticateUser];
    }
}

- (void) reportAchievementWithID:(NSString*)identifier percentComplete:(float)percent
{
    GKAchievement* achievement = [self getAchievementByID:identifier];
    if (achievement != nil && achievement.percentComplete < percent)
    {
        achievement.percentComplete = percent;
        [achievement reportAchievementWithCompletionHandler:^(NSError* error)
         {
             BOOL success = (error == nil);
             if (success == NO)
             {
                 // Keep achievement to try to submit it later
                 [self cacheAchievement:achievement];
             }
         }];
    }
}

- (GKAchievement*) getAchievementByID:(NSString*)identifier
{
    // Try to get an existing achievement with this identifier
    GKAchievement* achievement = [achievements objectForKey:identifier];
    
    if (achievement == nil)
    {
        // Create a new achievement object
        achievement = [[GKAchievement alloc] initWithIdentifier:identifier];
        [achievements setObject:achievement forKey:achievement.identifier];
    }
    
    return achievement;
}

- (void) resetAchievements
{
    [achievements removeAllObjects];
    [cachedAchievements removeAllObjects];
    
    [GKAchievement resetAchievementsWithCompletionHandler:^(NSError* error)
     {
     }];
}

- (void) reportCachedAchievements
{
    if ([cachedAchievements count] == 0)
        return;
    
    for (GKAchievement* achievement in [cachedAchievements allValues])
    {
        [achievement reportAchievementWithCompletionHandler:^(NSError* error)
         {
             BOOL success = (error == nil);
             if (success == YES)
             {
                 [self uncacheAchievement:achievement];
             }
         }];
    }
}

- (void) initCachedAchievements
{
    NSString* file = [NSHomeDirectory() stringByAppendingPathComponent:kCachedAchievementsFile];
    id object = [NSKeyedUnarchiver unarchiveObjectWithFile:file];
    
    if ([object isKindOfClass:[NSMutableDictionary class]])
    {
        NSMutableDictionary* loadedAchievements = (NSMutableDictionary*)object;
        cachedAchievements = [[NSMutableDictionary alloc] initWithDictionary:loadedAchievements];
    }
    else
    {
        cachedAchievements = [[NSMutableDictionary alloc] init];
    }
}

- (void) saveCachedAchievements
{
    NSString* file = [NSHomeDirectory() stringByAppendingPathComponent:kCachedAchievementsFile];
    [NSKeyedArchiver archiveRootObject:cachedAchievements toFile:file];
}

- (void) cacheAchievement:(GKAchievement*)achievement
{
    [cachedAchievements setObject:achievement forKey:achievement.identifier];
    
    // Save to disk immediately, to keep achievements around even if the game crashes.
    [self saveCachedAchievements];
}

- (void) uncacheAchievement:(GKAchievement*)achievement
{
    [cachedAchievements removeObjectForKey:achievement.identifier];
    
    // Save to disk immediately, to keep the removed cached achievement from being loaded again
    [self saveCachedAchievements];
}

- (void) achievementViewControllerDidFinish:(GKAchievementViewController *)viewController {
    
}


@end
