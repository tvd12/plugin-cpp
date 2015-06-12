//
//  InappHelper.h
//  SupernaturalMemory
//
//  Created by Dung Ta Van on 12/15/14.
//
//

#ifndef __SupernaturalMemory__InappHelper__
#define __SupernaturalMemory__InappHelper__

#include <string>

using namespace std;

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

class InappHelperDelegate {
    
public:
    virtual void onInappSuccess(const string &package,
                                const string &productId,
                                const string &purchaseToken) = 0;
    
    virtual void onLoadPriceSuccess(bool isSuccess) {}
    
    virtual void onInappFail() {}
    
};


class InappHelper {
public:
    static InappHelper* getInstance();
    
    void buyPackage(int package);
    
    void setLoadPriceSuccess(bool isSuccess);
    bool isLoadPriceSuccess();
    
    string getPricesString(unsigned int indexes[], int n);
    string getPricesString(const char* indexes);
    string getPriceString(unsigned int index);
    
    SYNTHESIZE(InappHelperDelegate*, mDelegate, Delegate);
    
protected:
    bool mIsLoadPriceSuccess;
    
private:
    InappHelper();
    InappHelper(const InappHelper &);
    void operator = (const InappHelper &);
};

#endif /* defined(__SupernaturalMemory__InappHelper__) */
