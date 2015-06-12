package com.tvd.android.plugin;

import android.app.Activity;
import android.content.Context;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.InterstitialAd;

public class GoogleAdmobHelper {
	
	private GoogleAdmobHelper() {}

	public static GoogleAdmobHelper getInstance() {
		if(sInstance == null) {
			synchronized (GoogleAdmobHelper.class) {
				if(sInstance == null) {
					sInstance = new GoogleAdmobHelper();
				}
			}
		}
		
		return sInstance;
	}
	
	public void initInterstitial(String unitId, Context context) {
		sContext = context;
		sInterstitialAd = new InterstitialAd(context);
		if(unitId.trim().length() > 0) {
			initInterstitial(unitId);
		}
		sInterstitialAd.setAdListener(new AdListener() {
			@Override
            public void onAdClosed() {
				nativeOnAdClosed(sInterstitialAd.getAdUnitId());
            }
			
			@Override
			public void onAdFailedToLoad(int errorCode) {
				String error = "UNKNOW";
				switch (errorCode) {
				case AdRequest.ERROR_CODE_INTERNAL_ERROR:
					error = "INTERNAL_ERROR";
					break;
				case AdRequest.ERROR_CODE_INVALID_REQUEST:
					error = "INVALID_REQUEST";
					break;
				case AdRequest.ERROR_CODE_NETWORK_ERROR:
					error = "NETWORK_ERROR";
					break;
				case AdRequest.ERROR_CODE_NO_FILL:
					error = "NO_FILL";
					break;
				default:
					break;
				}
				nativeOnAdFailedToLoad(
						sInterstitialAd.getAdUnitId(),
						error);
			}
			
			@Override
			public void onAdLoaded() {
				nativeOnAdLoaded(sInterstitialAd.getAdUnitId());
			}
			
			@Override
			public void onAdOpened() {
				nativeOnAdOpened(sInterstitialAd.getAdUnitId());
			}
			
			@Override
			public void onAdLeftApplication() {
				nativeOnAdLeftApplication(sInterstitialAd.getAdUnitId());
			}
			
		});
	}
	
	public void initInterstitial(Context context) {
		initInterstitial("", context);
	}
	
	public static void initInterstitial(String unitId) {
		sInterstitialAd.setAdUnitId(unitId);
	}
	
	public static void showInterstitial() {
		((Activity)sContext).runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				if (sInterstitialAd.isLoaded()) {
					sInterstitialAd.show();
				}
			}
		});
	}
    
    public static void requestInterstitial() {
    	((Activity)sContext).runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				AdRequest adRequest = new AdRequest.Builder()
	    		.addTestDevice(sTestDeviceId)
	    		.build();
				sInterstitialAd.loadAd(adRequest);
			}
		});
    }
    
    public static boolean isInterstitialReady() {
    	return sInterstitialAd.isLoaded();
    }
    
    public static void addTestDevices(String device) {
    	sTestDeviceId = device;
    }
    
    private native void nativeOnAdClosed(String adUnitId);
	
	private native void nativeOnAdFailedToLoad(String adUnitId,
			String error);
	
	private native void nativeOnAdLoaded(String adUnitId);
	
	private native void nativeOnAdOpened(String adUnitId);
	
	private native void nativeOnAdLeftApplication(String adUnitId);
	
	private static InterstitialAd sInterstitialAd;
	private static String sTestDeviceId = "";
	
	private static GoogleAdmobHelper sInstance;
	
	private static Context sContext;
}
