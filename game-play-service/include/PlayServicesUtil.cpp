//
//  PlayServicesUtil.cpp
//  SupernaturalMemory
//
//  Created by Dung Ta Van on 1/9/15.
//
//

#include "PlayServicesUtil.h"
#include "StateManager.h"

using namespace com::tvd::plugin;

void PlayServicesUtil::sigin() {
    StateManager::beginUserInitiatedSignIn();
}

void PlayServicesUtil::signOut() {
    StateManager::signOut();
}

void PlayServicesUtil::reportAchievement(string achievementId,
		uint16_t currentStep,
		uint16_t maxstep,
		bool isPercent) {
	if(currentStep == maxstep) {
		unlockAchievement(achievementId);
	}
	else {
		StateManager::reportAchievement(achievementId.c_str(),
				currentStep,
				maxstep,
				isPercent);
	}
}

void PlayServicesUtil::unlockAchievement(string achievementId) {
    StateManager::unlockAchievement(achievementId.c_str());
}
void PlayServicesUtil::submitHighScore(string leaderboardId, uint64_t score) {
    StateManager::submitHighScore(leaderboardId.c_str(), score);
}
void PlayServicesUtil::showAchievements() {
    StateManager::showAchievements();
}
void PlayServicesUtil::showLeaderboards() {
    StateManager::showLeaderboards();
}
void PlayServicesUtil::showLeaderboard(string leaderboardId) {
    StateManager::showLeaderboard(leaderboardId.c_str());
}

bool PlayServicesUtil::isAuthInProgress() {
    return StateManager::isAuthInProgress();
}
