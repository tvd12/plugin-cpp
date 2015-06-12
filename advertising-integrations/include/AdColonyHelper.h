//
//  AdColonyHelper.h
//  advertising-integrations
//
//  Created by Dung Ta Van on 4/24/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#ifndef advertising_integrations_AdColonyHelper_h
#define advertising_integrations_AdColonyHelper_h

#include <vector>
#include <string>
#include <map>

namespace com { namespace tvd { namespace plugin {
    
class AdColonyHelperDelegate;
class AdColonyHelperAdInfo;
class AdColonyHelperNativeAdView;
class AdColonyHelperNativeAdViewDelegate;

class AdColonyHelper {
    
public:
    
    static AdColonyHelper* getInstance() {
        static AdColonyHelper sInstance;
        
        return &sInstance;
    }
    
    void init(const std::string& appId,
              std::vector<std::string> &zoneIds,
              bool logging = false);
    
    void checkeExistenceVideoAd(const std::string &zoneId);
    
    void playVideoAdForZone(const std::string &zoneId);
    
    void playVideoAdForZone(const std::string &zoneId,
                            bool showPrePopup,
                            bool showPostPopup);
    
    int zoneStatusForZone(const std::string &zoneId);
    
    void setCustomId(const std::string &customId);
    
    std::string getCustomId();
    
    std::string getOpenUDID();
    
    std::string getUniqueDeviceId();
    
    std::string getODIN1();
    
    std::string getAdvertisingIdentifier();
    
    std::string getVendorIdentifier();
    
    bool isVirtualCurrencyRewardAvailableForZone(const std::string &zoneId);
    
    int getVirtualCurrencyRewardsAvailableTodayForZone(const std::string &zoneId);
    
    std::string getVirtualCurrencyNameForZone(const std::string &zoneId);
    
    int getVirtualCurrencyRewardAmountForZone(const std::string &zoneId);
    
    int getVideosPerReward(const std::string &currencyName);
    
    int getVideoCreditBalance(const std::string &currencyName);
    
    void setOptions(const std::map<std::string, std::string> &options);
    
    void cancelAd();
    
    bool isVideoReady();
    
    bool videoAdCurrentlyRunning();
    
    void turnAllAdsOff();
    
    void setUserMetadata(const std::string& metadataType,
                         const std::string& value);
    
    void userInterestedIn(const std::string& topic);
    
    void notifyIAPComplete(const std::string &transactionId,
                           const std::string &productId,
                           int quantity,
                           int price,
                           const std::string &currencyCode);
    
//    + ( AdColonyNativeAdView * ) getNativeAdForZone:( NSString * )zoneID presentingViewController:( UIViewController * )viewController
    
    void setDelegate(AdColonyHelperDelegate* delegate) {
        mDelegate = delegate;
    }

    inline AdColonyHelperDelegate* getDelegate() {return mDelegate;}
    
private:
    AdColonyHelperDelegate* mDelegate;
    
private:
    
    AdColonyHelper();
    AdColonyHelper(const AdColonyHelper&);
    void operator = (const AdColonyHelper&);
    
};

class AdColonyHelperDelegate {
public:
    virtual void onAdColonyAdAvailabilityChange(bool available,
                                                const std::string &zoneId) {}
    virtual void onAdColonyV4VCReward(bool success,
                                      const std::string &currencyName,
                                      int currencyAmount,
                                      const std::string &zoneID) {}
    
    virtual void onAdColonyAdStartedInZone(const std::string &zoneId) {}
    
    virtual void onAdColonyAdAttemptFinished(bool shown,
                                             const std::string &zoneId) {}
    
    virtual void onAdColonyAdAttemptFinishedWithInfo(AdColonyHelperAdInfo* info) {}
    
    
};
    
class AdColonyHelperAdInfo {
public:
    AdColonyHelperAdInfo(bool shown,
                         bool iapEnabled,
                         int iapQuantity,
                         int iapEngagement,
                         const std::string& zoneId,
                         const std::string& iapProductId) {
        mIsShown = shown;
        mIsIapEnabled = iapEnabled;
        
        mIapQuantity = iapQuantity;
        mIapEngagement = iapEngagement;
        
        mZoneId = zoneId;
        mIapProductId = iapProductId;
    }
    
    inline bool isShown() { return mIsShown; }
    inline bool isIapEnabled() { return mIsIapEnabled; }
    inline int getIapQuantity() { return mIapQuantity; }
    inline int getIapEngagement() { return mIapEngagement; }
    inline std::string getZoneId() { return mZoneId; }
    inline std::string getIapProductId() { return mIapProductId; }
    
    std::string toString() {
        std::string builder = std::string();
        builder.append("shown = ").append(std::to_string(isShown()));
        builder.append("\niap enabled = ").append(std::to_string(isIapEnabled()));
        builder.append("\niap quantity = ").append(std::to_string(getIapQuantity()));
        builder.append("\niap engagement = ").append(std::to_string(getIapEngagement()));
        builder.append("\nzone id = ").append(getZoneId());
        builder.append("\niap product id = ").append(getIapProductId());
        
        return builder;
    }
    
private:
    bool mIsShown;
    bool mIsIapEnabled;
    
    int mIapQuantity;
    int mIapEngagement;
    
    std::string mZoneId;
    std::string mIapProductId;
    
};
    
//class AdColonyHelperNativeAdView {
//public:
//    void pause();
//    void resume();
//    float recommendedHeightForWidth(float width);
//    
//    void setDelegate(AdColonyHelperNativeAdViewDelegate* delegate) {
//        mDelegate = delegate;
//    }
//    
//    inline AdColonyHelperNativeAdViewDelegate* getDelegate() {
//        return mDelegate;
//    }
//    
//    void setAdvertiserName(const std::string &advertiserName) {
//        mAdvertiserName = advertiserName;
//    }
//    void setAdvertiserIcon(const std::string &advertiserIcon) {
//        mAdvertiserIcon = advertiserIcon;
//    }
//    void setAdTitle(const std::string &adTitle) {
//        mAdTitle = adTitle;
//    }
//    void setAdDescription(const std::string &adDescription) {
//        mAdDescription = adDescription;
//    }
//    void setEngagementButton(const std::string engagementButton) {
//        mEngagementButton = engagementButton;
//    }
//    
//    void setVolumn(float volume) {
//        mVolume = volume;
//    }
//    void setMuted(bool muted) {
//        mIsMuted = muted;
//    }
//    
//    inline std::string getAdvertiserName() { return mAdvertiserName; }
//    inline std::string getAdvertiserIcon() { return mAdvertiserIcon; }
//    inline std::string getAdTitle() {return mAdTitle; }
//    inline std::string getAdDescription() {return mAdDescription; }
//    inline std::string getEngagementButton() { return mEngagementButton; }
//    
//    inline float getVolume() { return mVolume; }
//    inline bool isMuted() { return mIsMuted; }
//    
//private:
//    std::string mAdvertiserName;
//    std::string mAdvertiserIcon;
//    std::string mAdTitle;
//    std::string mAdDescription;
//    std::string mEngagementButton;
//    
//    float mVolume;
//    bool mIsMuted;
//    
//    AdColonyHelperNativeAdViewDelegate* mDelegate;
//    
//};
//    
//class AdColonyHelperNativeAdViewDelegate {
//public:
//    virtual void onAdColonyNativeAdStarted(AdColonyHelperNativeAdView *ad) {}
//    virtual void onAdColonyNativeAdExpanded(AdColonyHelperNativeAdView *ad) {}
//    virtual void onAdColonyNativeAdFinished(AdColonyHelperNativeAdView* ad,
//                                                     bool expanded) {}
//    virtual void onAdColonyNativeAd(AdColonyHelperNativeAdView *ad,
//                                    bool muted) {};
//};

}}}

#endif
