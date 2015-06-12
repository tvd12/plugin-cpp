//
//  UtilityHelper.h
//  os-utility
//
//  Created by Dung Ta Van on 1/26/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#ifndef __os_utility__UtilityHelper__
#define __os_utility__UtilityHelper__

#include <string>

using namespace std;

namespace com { namespace tvd { namespace plugin {

class UtilityHelper {
public:
    
    static UtilityHelper* getInstance() {
        static UtilityHelper sInstance;
        
        return &sInstance;
    }
    
    void rateUs();
    void vibrate();
    
    void sendFeedback(const std::string &email,
                      const std::string &emailSubject,
                      const std::string &mailbody);
    
    std::string getOSName();
    
    std::string getAppVersion();
    
    std::string getSystemVersion();
    
    std::string getDeviceModel();
    
    std::string getDeviceName();
    
    void setAppStoryId(const string& appStoreId) {
        mAppStoreId = appStoreId;
    }
    
    std::string getAppStoreId() {
        return mAppStoreId;
    }
    
private:
    
    std::string mAppStoreId;
    
private:
    UtilityHelper() {};
    UtilityHelper(const UtilityHelper &);
    void operator = (const UtilityHelper &);
};
    
}}}

#endif /* defined(__os_utility__UtilityHelper__) */
