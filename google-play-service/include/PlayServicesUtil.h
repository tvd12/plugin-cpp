//
//  PlayServicesUtil.h
//  SupernaturalMemory
//
//  Created by Dung Ta Van on 1/9/15.
//
//

#ifndef __SupernaturalMemory__PlayServicesUtil__
#define __SupernaturalMemory__PlayServicesUtil__

#include <string>

using namespace std;

namespace com { namespace tvd { namespace plugin {

class PlayServicesUtil {
public:
    static void sigin();
    static void signOut();
    static void unlockAchievement(string achievementId);
    static void submitHighScore(string leaderboardId, uint64_t score);
    static void showAchievements();
    static void showLeaderboards();
    static void showLeaderboard(string leaderboardId);
    
    static bool isAuthInProgress();
private:
    PlayServicesUtil() {};
    PlayServicesUtil(const PlayServicesUtil &);
    void operator = (const PlayServicesUtil &);
};

}}}
#endif /* defined(__SupernaturalMemory__PlayServicesUtil__) */
