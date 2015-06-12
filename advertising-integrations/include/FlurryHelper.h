//
//  FlurryHelper.h
//  advertising-integrations
//
//  Created by Dung Ta Van on 4/27/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#ifndef advertising_integrations_FlurryHelper_h
#define advertising_integrations_FlurryHelper_h

#include <string>

namespace com { namespace tvd { namespace plugin {

    class FlurryHelperDelegate;

class FlurryHelper {
public:
    
    static FlurryHelper* getInstance() {
        static FlurryHelper sInstance;
        
        return &sInstance;
    }
    
    void init(const std::string &apiKey);
    
    void initAdInterstitial(const std::string &adSpaceName);
    
    void fetchAdInterstitial();
    
    void showAdInterstitial();
    
    void setDelegate(FlurryHelperDelegate* delegate) {
        mDelegate = delegate;
    }
    
    inline FlurryHelperDelegate* getDelegate() { return mDelegate; }
    
private:
    
    FlurryHelperDelegate* mDelegate;
    
private:
    FlurryHelper();
    FlurryHelper(const FlurryHelper &);
    void operator = (const FlurryHelper &);
};
    
class FlurryHelperDelegate {
public:
    virtual void adInterstitialDidFetchAd() {
        FlurryHelper::getInstance()->showAdInterstitial();
    }
    
    virtual void onAdInterstitialDidRender() {}
    
    virtual void onAdInterstitialVideoDidFinish() {}
    
    virtual void onAdInterstitial(int error) {}
};
    
}}}

#endif
