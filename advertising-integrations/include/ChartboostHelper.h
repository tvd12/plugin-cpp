//
//  ChartboostHelper.h
//  chartboost-integrations
//
//  Created by Dung Ta Van on 4/16/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#ifndef chartboost_integrations_ChartboostHelper_h
#define chartboost_integrations_ChartboostHelper_h

#include <string>

namespace com { namespace tvd { namespace plugin {

class ChartboostHelperDelegate;

class ChartboostHelper {
public:
    static ChartboostHelper* getInstance() {
        static ChartboostHelper sInstance;
        
        return &sInstance;
    }
    
    /**
     * Cache an interstitial, optionally takes a location argument
     */
    void cacheInterstitial(const std::string& location);

    /** 
     * Show an interstitial, optionally takes a location argument
     */
    void showInterstitial(const std::string& location);
    
    /** 
     * Check if an interstitial is stored in cache for a default location, or a specific location
     * Only valid in iOS
     * In Android, it will always return false, if the interstitial has cached when call this method,
     * ChartboostHelper::didCacheInterstitial(const char* location) will be call-back.
     */
    bool hasCachedInterstitial(const std::string& location);
    
    /** 
     * Cache the More Apps page
     */
    void cacheMoreApps(const std::string& location);
    
    /** 
     * Show the More Apps page
     */
    void showMoreApps(const std::string& location);
    
    bool hasMoreApps(const std::string& location);
    
    void cacheRewardedVideo(const std::string &location);
    
    void showRewardedVideo(const std::string &location);
    
    bool hasRewardedVideo(const std::string &location);
    
    void setShouldRequestInterstitialsInFirstSession();
    
    void init(const std::string appId,
              const std::string appSignature);
    
    void setAppId(const std::string appId) {
        mAppId = appId;
    }
    
    void setAppSignature(const std::string appSignature) {
        mAppSignature = appSignature;
    }
    
    void setDelegate(ChartboostHelperDelegate* delegate) {
        mDelegate = delegate;
    }
    
    inline std::string getAppId() { return mAppId; }
    
    inline std::string getAppSignature() {return mAppSignature; }
    
    inline ChartboostHelperDelegate* getDelegate() { return mDelegate; }
    
    static const int STATUS_NO_ZONE       = 0;
    static const int STATUS_OFF           = 1;
    static const int STATUS_LOADING       = 2;
    static const int STATUS_ACTIVE        = 3;
    static const int STATUS_UNKNOWN       = 4;
    
private:
    
    std::string mAppId;
    std::string mAppSignature;
    
    ChartboostHelperDelegate* mDelegate;
    
private:
    ChartboostHelper();
    ChartboostHelper(const ChartboostHelper &);
    void operator = (const ChartboostHelper &);
};

class ChartboostHelperDelegate {
public:
    
    //Interstitial Delegate Methods
    // Called before requesting an interstitial via the Chartboost API server.
    virtual bool shouldRequestInterstitial(const std::string &location) {return true;};
    
    // Called before an interstitial will be displayed on the screen.
    virtual bool shouldDisplayInterstitial(const std::string &location) {return true;};
    
    // Called after an interstitial has been displayed on the screen.
    virtual void didDisplayInterstitial(const std::string &location) {};
    
    // Called after an interstitial has been loaded from the Chartboost API
    // servers and cached locally.
    virtual void didCacheInterstitial(const std::string &location) {};
    
    // Called after an interstitial has attempted to load from the Chartboost API
    // servers but failed.
    virtual void didFailToLoadInterstitial(const std::string &location,
                                   int error) {}
    
    // Called after a click is registered, but the user is not forwarded to the App Store.
    virtual void didFailToRecordClick(const std::string &location,
                              int error) {}
    
    // Called after an interstitial has been dismissed.
    virtual void didDismissInterstitial(const std::string &location) {};
    
    // Called after an interstitial has been closed.
    virtual void didCloseInterstitial(const std::string &location) {};
    
    // Called after an interstitial has been clicked.
    virtual void didClickInterstitial(const std::string &location) {};
    
    //MoreApps Delegate Methods

    virtual bool shouldRequestMoreApps(const std::string &location) {return true;};

    // Called before a MoreApps page will be displayed on the screen.
    virtual bool shouldDisplayMoreApps(const std::string &location) {return true;};
    
    // Called after a MoreApps page has been displayed on the screen.
    virtual void didDisplayMoreApps(const std::string &location) {};
    
    // Called after a MoreApps page has been loaded from the Chartboost API
    // servers and cached locally.
    virtual void didCacheMoreApps(const std::string &location) {};
    
    // Called after a MoreApps page has been dismissed.
    virtual void didDismissMoreApps(const std::string &location) {};
    
    // Called after a MoreApps page has been closed.
    virtual void didCloseMoreApps(const std::string &location) {};
    
    // Called after a MoreApps page has been clicked.
    virtual void didClickMoreApps(const std::string &location) {};
    
    // Called after a MoreApps page attempted to load from the Chartboost API
    // servers but failed.
    virtual void didFailToLoadMoreApps(const std::string &location,
                               int error) {};
    
    //Rewarded Video Delegate Methods
    // Called before a rewarded video will be displayed on the screen.
    virtual bool shouldDisplayRewardedVideo(const std::string &location) {return true;};
    
    // Called after a rewarded video has been displayed on the screen.
    virtual void didDisplayRewardedVideo(const std::string &location) {};
    
    // Called after a rewarded video has been loaded from the Chartboost API
    // servers and cached locally.
    virtual void didCacheRewardedVideo(const std::string &location) {};
    
    // Called after a rewarded video has attempted to load from the Chartboost API
    // servers but failed.
    virtual void didFailToLoadRewardedVideo(const std::string &location,
                                    int error) {};
    
    // Called after a rewarded video has been dismissed.
    virtual void didDismissRewardedVideo(const std::string &location) {};
    
    // Called after a rewarded video has been closed.
    virtual void didCloseRewardedVideo(const std::string &location) {};
    
    // Called after a rewarded video has been clicked.
    virtual void didClickRewardedVideo(const std::string &location) {};
    
    // Called after a rewarded video has been viewed completely and user is eligible for reward.
    virtual void didCompleteRewardedVideo(const std::string &location,
                                  int reward) {}
    
    // Implement to be notified of when a video will be displayed on the screen for
    // a given CBLocation. You can then do things like mute effects and sounds.
    virtual void willDisplayVideo(const std::string &location) {};
    
    // Decide if Chartboost SDK will attempt to fetch videos from Chartboost API servers.
    // shouldPrefetch YES if Chartboost should prefetch video content, NO otherwise.
    // Default is YES.
    
    virtual void setShouldPrefetchVideoContent(bool shouldPrefetch) {};
    
    //InPlay Delegate Methods
    // Called after an InPlay object has been loaded from the Chartboost API
    // servers and cached locally.
    virtual void didCacheInPlay(const std::string &location) {};
    
    // Called after a InPlay has attempted to load from the Chartboost API
    // servers but failed.
    virtual void didFailToLoadInPlay(const std::string &location,
                             int error) {};
    
    //Miscellaneous Delegate Methods
    // Whether Chartboost should show ads in the first session
    // Defaults to YES
    virtual bool shouldRequestInterstitialsInFirstSession() {return true;}
    
    // Use the following if you're seeing the Apple keyboard covering Chartboost interstitials
    virtual bool shouldDisplayInterstitial(const char* &location) {return true;};
    
    // Called after the App Store sheet is dismissed, when displaying the embedded app sheet.
    virtual void didCompleteAppStoreSheetFlow() {};
    
    // Called if Chartboost SDK pauses click actions awaiting confirmation from the user. Use
    // to implement an age gate in your game.
    virtual void didPauseClickForConfirmation() {};
};
    
}}}

#endif
