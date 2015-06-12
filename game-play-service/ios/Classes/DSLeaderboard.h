//
//  DSLeaderboard.h
//  Dreamsake Studios
//
//  Created by Dreamsake Studios.
//  Copyright (c) 2014 Dreamsake Studios.
//

#ifndef DSLeaderboard_h
#define DSLeaderboard_h

/*!
 * @class DSLeaderboard
 * @abstract An engine level singleton that delegates to platform level leaderboard singletons.
 */
class DSLeaderboard
{
private:
    static DSLeaderboard* m_sharedManager;
    
	DSLeaderboard() {}
	DSLeaderboard(const DSLeaderboard&) {}
    
public:
    inline static DSLeaderboard* sharedManager()
	{
		if (!m_sharedManager)
		{
			m_sharedManager = new DSLeaderboard();
		}
        
		return m_sharedManager;
	}
    
    /*!
     * @abstract Initializes the leaderboard.
     */
    void initLeaderboard();
    
    /*!
     * @abstract Submits a score to the leaderboard.
     * @param leaderboardIdentifier The leaderboard identifier.
     * @param score The score to submit.
     */
    void submitScore(const char* leaderboardIdentifier, long long score);
    
    /*!
     * @abstract Opens a leaderboard.
     * @param leaderboardIdentifier The leaderboard identifier.
     */
    void openLeaderboard(const char* leaderboardIdentifier);
    
    void openLeaderboards();

    void openAchievements();
    void reportAchievement(const char* identifier, float percent);
};

#endif
