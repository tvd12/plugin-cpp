//
//  TapjoyHelper.h
//  advertising-integrations
//
//  Created by Dung Ta Van on 4/28/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#ifndef advertising_integrations_TapjoyHelper_h
#define advertising_integrations_TapjoyHelper_h

#include <string>

#define SYNTHESIZE_DELEGATE(__class_name__, __func_name__) \
protected: \
    __class_name__* m##__func_name__; \
public: \
    void set##__func_name__(__class_name__* delegate) { \
        m##__func_name__ = delegate; \
    } \
    inline __class_name__* get##__func_name__() { return m##__func_name__; }

namespace com { namespace tvd { namespace plugin {

class TapjoyHelperDelegate;
class TapjoyHelperViewDelegate;
class TapjoyHelperVideoDelegate;
class TapjoyHelperPlacementDelegate;
class TapjoyHelperDirectPlayPlacementDelegate;
class TapjoyHelperOfferwallPlacementDelegate;

class TapjoyHelper {
public:
    
    static TapjoyHelper* getInstance() {
        static TapjoyHelper sInstance;
        
        return &sInstance;
    }
    
    void init(const std::string &sdkKey,
              const std::string &userId = "",
              bool debug = false);
    
    void initViewController();
    
    void addCurrencyEarnedListener();
    
    void removeCurrencyEarnedListener();
    
    void requestOfferwall(const std::string &offerwallUnit = "offerwall_unit");
    void showOfferwall();
    
    void requestDirectPlayVideo(const std::string &videoUnit = "video_unit");
    void showDirectPlayVideo();
    bool hasDirectPlayVideo();
    bool isDirectPlayVideoReady();
    
    std::string getCurrentBalance();
    
    std::string spendCurrency(int value);
    
    std::string awardCurrecy(int value);
    
    bool requestContent(const std::string &placementName);
    
    bool showContent();
    
    void setVideoUnit(const std::string &videoUnit) {
        mVideoUnit = videoUnit;
    }
    
    inline std::string getVideoUnit() { return mVideoUnit; }
    
    void setOfferwallUnit(const std::string &offerwallUnit) {
        mOfferwallUnit = offerwallUnit;
    }
    
    inline std::string getOfferwallUnit() { return mOfferwallUnit; }
    
    SYNTHESIZE_DELEGATE(TapjoyHelperDelegate, CommonDelegate);
    SYNTHESIZE_DELEGATE(TapjoyHelperViewDelegate, ViewDelegate);
    SYNTHESIZE_DELEGATE(TapjoyHelperVideoDelegate, VideoDelegate);
    SYNTHESIZE_DELEGATE(TapjoyHelperPlacementDelegate, PlacementDelegate);
    SYNTHESIZE_DELEGATE(TapjoyHelperDirectPlayPlacementDelegate, DirectPlayDelegate);
    SYNTHESIZE_DELEGATE(TapjoyHelperOfferwallPlacementDelegate, OfferwallDelegate);
    
protected:
    
    std::string mVideoUnit;
    std::string mOfferwallUnit;
    
private:
    TapjoyHelper();
    TapjoyHelper(const TapjoyHelper&);
    void operator = (TapjoyHelper &);
};

class TapjoyHelperDelegate {
public:
    virtual void onConnectSuccess() {}
    virtual void onConnectFail() {} 
    virtual void showEarnedCurrencyAlert() {}
};

class TapjoyHelperViewDelegate {
public:
    virtual void viewWillAppearWithType(int type) {}
    virtual void viewWillDisappearWithType(int type) {}
    virtual void viewDidDisappearWithType(int type) {}
};

class TapjoyHelperVideoDelegate {
public:
    virtual void videoAdBegan() {}
    virtual void videoAdClosed() {}
    virtual void videoAdCompleted() {}
    virtual void videoAdError(const std::string &error) {}
};

class TapjoyHelperPlacementDelegate {
public:
    virtual void requestDidSucceed(const std::string &placementName,
                                   bool contentReady,
                                   bool contentAvailable) {}
    virtual void contentIsReady(const std::string &placementName,
                                bool contentAvailable) {}
    virtual void requestDidFail(const std::string &placementName,
                                const std::string &error) {}
    virtual void contentDidAppear(const std::string &placementName) {}
    virtual void contentDidDisappear(const std::string &placementName) {}
    
    virtual void placementWithProduct(const std::string &placementName,
                           bool contentReady,
                           bool contentAvailable,
                           int requestType,
                           const std::string &requestId,
                           const std::string &requestToken,
                                      const std::string &productId) {}
    virtual void placementWithItem(const std::string &placementName,
                           bool contentReady,
                           bool contentAvailable,
                           int requestType,
                           const std::string &requestId,
                           const std::string &requestToken,
                           const std::string &itemId,
                                   int quantity) {}
    virtual void placementWithCurrency(const std::string &placementName,
                           bool contentReady,
                           bool contentAvailable,
                           int requestType,
                           const std::string &requestId,
                           const std::string &requestToken,
                           const std::string &currency,
                                       int amount) {}
    
    virtual void placementWithLocation(const std::string &placementName,
                                       bool contentReady,
                                       bool contentAvailable,
                                       int requestType,
                                       const std::string &requestId,
                                       const std::string &requestToken,
                                       const std::string &location) {}
    
};

class TapjoyHelperDirectPlayPlacementDelegate {
public:
    virtual void requestDidSucceed(const std::string &placementName,
                                   bool contentReady,
                                   bool contentAvailable) {}
    
    virtual bool contentIsReady(const std::string &placementName,
                                bool contentAvailable) { return true; }
    
    virtual void requestDidFail(const std::string &placementName,
                                const std::string &error) {}
    
    virtual void contentDidAppear(const std::string &placementName) {}
    
    void contentDidDisappear(const std::string &placementName) {}
    
};

class TapjoyHelperOfferwallPlacementDelegate {
public:
    virtual void requestDidSucceed(const std::string &placementName,
                                   bool contentReady,
                                   bool contentAvailable) {}
    
    virtual bool contentIsReady(const std::string &placementName,
                                bool contentAvailable) {return true;}
    
    virtual void requestDidFail(const std::string &placementName,
                                const std::string &error) {}
    
    virtual void contentDidAppear(const std::string &placementName) {}
    
    void contentDidDisappear(const std::string &placementName) {}
    
};
    
}}}

#endif
