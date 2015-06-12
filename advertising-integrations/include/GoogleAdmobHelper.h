//
//  GoogleAdmobHelper.h
//  advertising-integrations
//
//  Created by Dung Ta Van on 5/28/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#ifndef advertising_integrations_GoogleAdmobHelper_h
#define advertising_integrations_GoogleAdmobHelper_h

#include <string>
#include <map>
#include <vector>

namespace com { namespace tvd { namespace plugin {

class InterstitialDelegate;
    
class GoogleAdmobHelper {
public:
    static GoogleAdmobHelper* getInstance() {
        static GoogleAdmobHelper sInstance;
        
        return &sInstance;
    }
    
    void addTestDevices(const std::vector<std::string> &devices);
    
    void initInterstitial(const std::string &admobId,
                          bool debug = true);
    
    void showInterstitial();
    
    void requestInterstitial();
    
    bool isInterstitialReady();
    
    void setInterstitialDelegate(InterstitialDelegate* delegate) {
        mInterstitialDelegate = delegate;
    }
    
    inline InterstitialDelegate* getInterstitialDelegate() {return mInterstitialDelegate;}
    
    void setAdUnitId(const std::string &adUnitId) {
        mAdUnitId = adUnitId;
    }
    
    inline std::string getAdUnitId() {return mAdUnitId;}
    
//    void showAds(const std::map<std::string, std::string> &info);
//    void hideAds(const std::map<std::string, std::string> &info);
    
private:
    std::vector<std::string> mTestDevices;
    std::string mAdUnitId;
    
    InterstitialDelegate *mInterstitialDelegate;
    
private:
    GoogleAdmobHelper();
    GoogleAdmobHelper(const GoogleAdmobHelper &);
    void operator = (const GoogleAdmobHelper &);
};
    
/**
 * Interstitial delegate
 */
class InterstitialDelegate {
public:
    virtual void interstitialDidReceiveAd(const std::string& adUnitId) {};
    virtual void interstitial(const std::string& adUnitId,
                              const std::string& error) {};
    virtual void interstitialWillPresentScreen(const std::string& adUnitId) {};
    virtual void interstitialWillDismissScreen(const std::string& adUnitId) {};
    virtual void interstitialDidDismissScreen(const std::string& adUnitId) {};
    virtual void interstitialWillLeaveApplication(const std::string& adUnitId) {};
    
};
    
}}}

#endif
