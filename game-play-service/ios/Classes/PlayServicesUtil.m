//
//  PlayServicesUtil.m
//  google-play-services
//
//  Created by Dung Ta Van on 4/20/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#include "PlayServicesUtil.h"
#include "DSLeaderboardIOS.h"
#include "DSLeaderboard.h"

using namespace com::tvd::plugin;

void PlayServicesUtil::sigin() {
    [[DSLeaderboardIOS sharedSingleton] authenticateUser];
}

void PlayServicesUtil::signOut() {
    
}

void PlayServicesUtil::reportAchievement(string achievementId,
                                         uint16_t currentStep,
                                         uint16_t maxstep,
                                         bool isPercent) {
    DSLeaderboard::sharedManager()
    ->reportAchievement(achievementId.c_str(),
                        ((1.0f * currentStep)/maxstep) * 100);
}

void PlayServicesUtil::unlockAchievement(string achievementId) {
    reportAchievement(achievementId, 1, 1);
}
void PlayServicesUtil::submitHighScore(string leaderboardId, uint64_t score) {
    DSLeaderboard::sharedManager()->submitScore(leaderboardId.c_str(), score);
}
void PlayServicesUtil::showAchievements() {
    DSLeaderboard::sharedManager()->openAchievements();
}
void PlayServicesUtil::showLeaderboards() {
    DSLeaderboard::sharedManager()->openLeaderboards();
}
void PlayServicesUtil::showLeaderboard(string leaderboardId) {
    DSLeaderboard::sharedManager()->openLeaderboard(leaderboardId.c_str());
}

bool PlayServicesUtil::isAuthInProgress() {

    
    return true;
}