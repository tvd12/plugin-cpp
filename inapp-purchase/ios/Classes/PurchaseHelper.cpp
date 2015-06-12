//
//  PurchaseHelper.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 1/20/15.
//
//

#include "PurchaseHelper.h"
#include "PluginManager.h"
#include "cocos2d.h"
#include "InappHelper.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::plugin;

PurchaseHelper::PurchaseHelper() :
mInapp(NULL),
mListener(NULL),
mProducts(vector<TProductInfo>()) {
    
}

PurchaseHelper* PurchaseHelper::getInstance() {
    static PurchaseHelper sInstance;
    
    return &sInstance;
}

void PurchaseHelper::init() {
    mInapp = new ProtocolIAP();
}

void PurchaseHelper::purgePurchase() {
    PluginManager::end();
}

void PurchaseHelper::loadInappPlugin() {
    if(!mListener) {
        mListener = new PurchaseListener;
    }
    
    mInapp = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()
                                        ->loadPlugin("IOSIAP"));
    mInapp->setResultListener(mListener);
    mInapp->setDebugMode(true);
}

void PurchaseHelper::unloadInappPlugin() {
    if(mInapp) {
        PluginManager::getInstance()->unloadPlugin("IOSIAP");
        mInapp = NULL;
    }
}

void PurchaseHelper::buyProduct(plugin::TProductInfo info) {
    mInapp->payForProduct(info);
}

void PurchaseHelper::buyProduct(int index) {
    buyProduct(productAt(index));
}

void PurchaseHelper::addProduct(plugin::TProductInfo product) {
    mProducts.push_back(product);
}

TProductInfo PurchaseHelper::productAt(int index) {
    if(index < mProducts.size()) {
        return mProducts.at(index);
    }
    return TProductInfo();
}

PurchaseHelper::~PurchaseHelper() {
    
    unloadInappPlugin();
    
    CC_SAFE_DELETE(mListener);
}

// Listener
void PurchaseListener::onPayResult(plugin::PayResultCode resultCode,
                                   const char *msg,
                                   plugin::TProductInfo info) {
    char inappInfo[1024] = { 0 };
    sprintf(inappInfo, "ProductID:%s\nName:%s\nPrice:%s\nDesc:%s",
            info.find("productId")->second.c_str(),
            info.find("productName")->second.c_str(),
            info.find("productPrice")->second.c_str(),
            info.find("productDesc")->second.c_str());
//    MessageBox(inappInfo , msg);
    CCLOG("PurchaseListener::onPayResult::inappInfor = %s\n, message = %s",
          inappInfo,
          msg);
    InappHelperDelegate* delegate = InappHelper::getInstance()->getDelegate();
    if(delegate) {
        delegate->onInappSuccess("",
                                 info.find("productId")->second.c_str(),
                                 "");
    }
    
}

void PurchaseListener::onRequestProductsResult(plugin::IAPProductRequest ret,
                                               plugin::TProductList info) {
    int size = info.size();
    
    cocos2d::log("PurchaseListener::number of products: %d", size);
    for(int i = 0 ; i < size ; i++) {
        string productId = info.at(i)["IAPId"];
        cocos2d::log("PurchaseListener::product[%d]: %s", i, productId.c_str());
        PurchaseHelper::getInstance()->addProduct(info.at(i));
    }
    
    InappHelper::getInstance()->setLoadPriceSuccess(true);
    InappHelperDelegate* delegate = InappHelper::getInstance()->getDelegate();
    if(delegate) {
        delegate->onLoadPriceSuccess(true);
    }
}










