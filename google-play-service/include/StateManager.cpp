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

#include "StateManager.h"

bool StateManager::sIsAuthInProgress = false;
std::unique_ptr<gpg::GameServices> StateManager::sGameServices;

gpg::GameServices *StateManager::getGameServices() {
  return sGameServices.get();
}

void StateManager::beginUserInitiatedSignIn() {
  if (!sGameServices->IsAuthorized()) {
    LOGI("StartAuthorizationUI");
    sGameServices->StartAuthorizationUI();
  }
}

void StateManager::signOut() {
  if (sGameServices->IsAuthorized()) {
    LOGI("SignOut");
    sGameServices->SignOut();
  }
}

void StateManager::unlockAchievement(char const *achievement_id) {
  if (sGameServices->IsAuthorized()) {
    LOGI("Achievement unlocked");
    sGameServices->Achievements().Unlock(achievement_id);
  }
}

void StateManager::submitHighScore(char const *leaderboard_id, uint64_t score) {
  if (sGameServices->IsAuthorized()) {
    LOGI("High score submitted");
    sGameServices->Leaderboards().SubmitScore(leaderboard_id, score);
  }
}

void StateManager::showAchievements() {
  if (sGameServices->IsAuthorized()) {
    LOGI("Show achievements");
    sGameServices->Achievements().ShowAllUI([](gpg::UIStatus const &status) {
        if (gpg::IsSuccess(status)) {
            LOGI("Achievements Result: success.");
        } else {
            LOGI("Achievements Result: failure.");
        }
    });
  }
}

void StateManager::showLeaderboards() {
  if (sGameServices->IsAuthorized()) {
    LOGI("Show leaderboards");
    sGameServices->Leaderboards().ShowAllUI([](gpg::UIStatus const &status) {
        if (gpg::IsSuccess(status)) {
            LOGI("Leaderboards Result: success.");
        } else {
            LOGI("Leaderboards Result: failure.");
        }
    });
  }
}

void StateManager::showLeaderboard(const char *leaderboardId) {
    if(sGameServices->IsAuthorized()) {
        LOGI("Show leaderboard: %s", leaderboardId);
        sGameServices->Leaderboards().ShowUI(leaderboardId,
                                             [](gpg::UIStatus const &status) {
                                                 if (gpg::IsSuccess(status)) {
                                                     LOGI("Leaderboard Result: success.");
                                                 } else {
                                                     LOGI("Leaderboard Result: failure.");
                                                 }
                                             });
    }
    else {
    	beginUserInitiatedSignIn();
    }
}

void StateManager::initServices(gpg::PlatformConfiguration const &pc,
    gpg::GameServices::Builder::OnAuthActionStartedCallback started_callback,
    gpg::GameServices::Builder::OnAuthActionFinishedCallback
        finished_callback) {

  LOGI("Initializing Services");
  if (!sGameServices) {
    LOGI("Uninitialized services, so creating");
    sGameServices = gpg::GameServices::Builder()
        .SetOnAuthActionStarted([started_callback](gpg::AuthOperation op) {
          sIsAuthInProgress = true;
          if (started_callback != nullptr) {
            started_callback(op);
          }
        })
        .SetOnAuthActionFinished([finished_callback](gpg::AuthOperation op,
                                                     gpg::AuthStatus status) {
          LOGI("Sign in finished with a result of %d", status);
          sIsAuthInProgress = false;
          if (finished_callback != nullptr) {
            finished_callback(op, status);
          }
        })
        .Create(pc);
  }
  LOGI("Created");
}
