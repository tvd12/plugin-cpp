/* Copyright (c) 2014 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "PlayServicesHeaders.h"

class StateManager {
public:
    static void initServices(gpg::PlatformConfiguration const &pc,
                             gpg::GameServices::Builder::OnAuthActionStartedCallback
                             started_callback,
                             gpg::GameServices::Builder::OnAuthActionFinishedCallback
                             finished_callback);
    
    static gpg::GameServices *getGameServices();
    
    static void beginUserInitiatedSignIn();
    static void signOut();
    static void unlockAchievement(const char *achievementId);
    static void submitHighScore(const char *leaderboardId, uint64_t score);
    static void showAchievements();
    static void showLeaderboards();
    static void showLeaderboard(const char *leaderboardId);
   
    static bool isAuthInProgress() {
        return sIsAuthInProgress;
    }
    
private:
    static bool sIsAuthInProgress;
    static std::unique_ptr<gpg::GameServices> sGameServices;
};

#endif  // STATE_MANAGER_H
