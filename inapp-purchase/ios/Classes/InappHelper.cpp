//
//  InappHelper.cpp
//  inapp-purchase
//
//  Created by Dung Ta Van on 1/25/15.
//  Copyright (c) 2015 Dung Ta Van. All rights reserved.
//

#include "InappHelper.h"
#include "PurchaseHelper.h"
#include "InappProduct.h"

InappHelper::InappHelper() :
mDelegate(NULL),
mIsLoadPriceSuccess(false) {
    
}

InappHelper* InappHelper::getInstance() {
    static InappHelper sInstance;
    
    return &sInstance;
}

void InappHelper::buyPackage(int package) {
    PurchaseHelper::getInstance()->buyProduct(package);
}

void InappHelper::setLoadPriceSuccess(bool isSuccess) {
    mIsLoadPriceSuccess = isSuccess;
}
bool InappHelper::isLoadPriceSuccess() {
    
    return mIsLoadPriceSuccess;
}

string InappHelper::getPricesString(unsigned int indexes[], int n) {
    return "";
}
string InappHelper::getPricesString(const char* indexes) {
    return "";
}
string InappHelper::getPriceString(unsigned int index) {
    return PurchaseHelper::getInstance()->productAt(index)
    .find("IAPId")->second;
}