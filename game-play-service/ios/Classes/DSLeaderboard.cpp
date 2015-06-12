///
//  DSLeaderboard.cpp
//  Chill Casino
//
//  Created by Dreamsake Studios on 13-08-01.
//  Copyright (c) 2014 Dreamsake Studios.
//

#include "DSLeaderboard.h"
#import "DSLeaderboardIOS.h"

DSLeaderboard* DSLeaderboard::m_sharedManager = NULL;

void DSLeaderboard::initLeaderboard()
{
    [[DSLeaderboardIOS sharedSingleton] authenticateUser];
}

void DSLeaderboard::submitScore(const char* leaderboardIdentifier, long long score)
{
    NSString* convertedString = [NSString stringWithUTF8String:leaderboardIdentifier];
    [[DSLeaderboardIOS sharedSingleton] submitScore:score forLeaderboard:convertedString];
}

void DSLeaderboard::openLeaderboard(const char* leaderboardIdentifier)
{
    [[DSLeaderboardIOS sharedSingleton] openLeaderboard:[NSString stringWithUTF8String:leaderboardIdentifier]];
}

void DSLeaderboard::openLeaderboards()
{
    [[DSLeaderboardIOS sharedSingleton] openLeaderboards];
}

void DSLeaderboard::openAchievements()
{
    [[DSLeaderboardIOS sharedSingleton] openAchievements];
}

void DSLeaderboard::reportAchievement(const char* identifier, float percent)
{
    [[DSLeaderboardIOS sharedSingleton] reportAchievementWithID:[NSString stringWithUTF8String:identifier]
                                                percentComplete:percent];
}
