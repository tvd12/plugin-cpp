package com.tvd.android.plugin;

import android.app.Activity;
import android.util.Log;

import com.chartboost.sdk.CBLocation;
import com.chartboost.sdk.Chartboost;
import com.chartboost.sdk.ChartboostDelegate;
import com.chartboost.sdk.Model.CBError.CBClickError;
import com.chartboost.sdk.Model.CBError.CBImpressionError;

public class ChartboostHelper {
	
	private ChartboostHelper() {}

	public static void init(Activity activity, String appId, String appSignature) {
		Chartboost.startWithAppId(activity, appId, appSignature);
		Chartboost.setImpressionsUseActivities(true);
		Chartboost.onCreate(activity);
		Chartboost.setDelegate(new ChartboostHelperDelegate(activity));
	}
	
	public static void onCreate(Activity activity) {
		Chartboost.onCreate(activity);
	}
	
	public static void onStart(Activity activity) {
		Chartboost.onStart(activity);
	}
	
	public static void onResume(Activity activity) {
		Chartboost.onResume(activity);
	}
	
	public static void onPause(Activity activity) {
		Chartboost.onPause(activity);
	}
	
	public static void onStop(Activity activity) {
		Chartboost.onStop(activity);
	}
	
	public static void onDestroy(Activity activity) {
		Chartboost.onDestroy(activity);
	}
	
	public static boolean onBackPressed() {
		return Chartboost.onBackPressed();
	}
	
	public static void cacheInterstitial(String location) {
		if(location == null
				|| location.equals("")) {
			location = CBLocation.LOCATION_DEFAULT;
		}
		Chartboost.cacheInterstitial(location);
	}
	
	public static void showInterstitial(String location) {
		Chartboost.showInterstitial(getLocation(location));
	}
	
	public static boolean hasCachedInterstitial(String location) {
		return Chartboost.hasInterstitial(getLocation(location));
	}
	
	public static void cacheMoreApps(String location) {
		Chartboost.cacheMoreApps(getLocation(location));
	}
	
	public static void showMoreApps(String location) {
		Chartboost.showMoreApps(getLocation(location));
	}
	
	public static boolean hasMoreApps(String location) {
		return Chartboost.hasMoreApps(getLocation(location));
	}
	
	public static void cacheRewardedVideo(String location) {
		Chartboost.cacheRewardedVideo(getLocation(location));
	}
	
	public static void showRewardedVideo(String location) {
		Chartboost.showRewardedVideo(getLocation(location));
	}
	
	public static boolean hasRewardedVideo(String location) {
		return Chartboost.hasRewardedVideo(getLocation(location));
	}
	
	public static void setShouldRequestInterstitialsInFirstSession() {
		Chartboost.setShouldRequestInterstitialsInFirstSession(false);
	}
	
	private static String getLocation(String location) {
		if(location == null 
				|| location.trim().length() == 0) {
			location = CBLocation.LOCATION_DEFAULT;
		}
		
		return location;
	}
	
}

class ChartboostHelperDelegate extends ChartboostDelegate {
	
	public ChartboostHelperDelegate(Activity activity) {
		mActivity = activity;
	}
	
	@Override
    public boolean shouldRequestInterstitial(String location) {
        Log.i(LOG_TAG, "SHOULD REQUEST INTERSTITIAL '"+ (location != null ? location : "null"));
        return nativeShouldRequestInterstitial(location == null ? "" : location);
    }

    @Override
    public boolean shouldDisplayInterstitial(String location) {
        Log.i(LOG_TAG, "SHOULD DISPLAY INTERSTITIAL '"+ (location != null ? location : "null"));
        return nativeShouldDisplayInterstitial(location == null ? "" : location);
    }

    @Override
    public void didCacheInterstitial(String location) {
        Log.i(LOG_TAG, "DID CACHE INTERSTITIAL '"+ (location != null ? location : "null"));
        nativeDidCacheInterstitial((location == null) ? "" : location);
    }

    @Override
    public void didFailToLoadInterstitial(String location, CBImpressionError error) {
        Log.i(LOG_TAG, "DID FAIL TO LOAD INTERSTITIAL '"+ (location != null ? location : "null")+ " Error: " + error.name());
        nativeDidFailToLoadInterstitial(location == null ? "" : location, getError(error));
    }

    @Override
    public void didDismissInterstitial(String location) {
        Log.i(LOG_TAG, "DID DISMISS INTERSTITIAL: "+ (location != null ? location : "null"));
        nativeDidDismissInterstitial(location == null ? "" : location);
    }

    @Override
    public void didCloseInterstitial(String location) {
        Log.i(LOG_TAG, "DID CLOSE INTERSTITIAL: "+ (location != null ? location : "null"));
        nativeDidCloseInterstitial(location == null ? "" : location);
    }

    @Override
    public void didClickInterstitial(String location) {
        Log.i(LOG_TAG, "DID CLICK INTERSTITIAL: "+ (location != null ? location : "null"));
        nativeDidClickInterstitial(location == null ? "" : location);
    }

    @Override
    public void didDisplayInterstitial(String location) {
        Log.i(LOG_TAG, "DID DISPLAY INTERSTITIAL: " +  (location != null ? location : "null"));
        nativeDidDisplayInterstitial(location == null ? "" : location);
    }

    @Override
    public boolean shouldRequestMoreApps(String location) {
        Log.i(LOG_TAG, "SHOULD REQUEST MORE APPS: " +  (location != null ? location : "null"));
        return nativeShouldRequestMoreApps(location == null ? "" : location);
    }

    @Override
    public boolean shouldDisplayMoreApps(String location) {
        Log.i(LOG_TAG, "SHOULD DISPLAY MORE APPS: " +  (location != null ? location : "null"));
        return nativeShouldDisplayMoreApps(location == null ? "" : location);
    }

    @Override
    public void didFailToLoadMoreApps(String location, CBImpressionError error) {
        Log.i(LOG_TAG, "DID FAIL TO LOAD MOREAPPS " +  (location != null ? location : "null") + " Error: "+ error.name());
        nativeDidFailToLoadMoreApps(location == null ? "" : location, getError(error));
    }

    @Override
    public void didCacheMoreApps(String location) {
        Log.i(LOG_TAG, "DID CACHE MORE APPS: " +  (location != null ? location : "null"));
        nativeDidCacheMoreApps(location == null ? "" : location);
    }

    @Override
    public void didDismissMoreApps(String location) {
        Log.i(LOG_TAG, "DID DISMISS MORE APPS " +  (location != null ? location : "null"));
        nativeDidDismissMoreApps(location == null ? "" : location);
    }

    @Override
    public void didCloseMoreApps(String location) {
        Log.i(LOG_TAG, "DID CLOSE MORE APPS: "+  (location != null ? location : "null"));
        nativeDidCloseMoreApps(location == null ? "" : location);
    }

    @Override
    public void didClickMoreApps(String location) {
        Log.i(LOG_TAG, "DID CLICK MORE APPS: "+  (location != null ? location : "null"));
        nativeDidClickMoreApps(location == null ? "" : location);
    }

    @Override
    public void didDisplayMoreApps(String location) {
        Log.i(LOG_TAG, "DID DISPLAY MORE APPS: " +  (location != null ? location : "null"));
        nativeDidDisplayMoreApps(location == null ? "" : location);
    }

    @Override
    public void didFailToRecordClick(String uri, CBClickError error) {
        Log.i(LOG_TAG, "DID FAILED TO RECORD CLICK " + (uri != null ? uri : "null") + ", error: " + error.name());
        nativeDidFailToRecordClick(uri == null ? "" : uri, getError(error));
    }

    @Override
    public boolean shouldDisplayRewardedVideo(String location) {
        Log.i(LOG_TAG, String.format("SHOULD DISPLAY REWARDED VIDEO: '%s'",  (location != null ? location : "null")));
        return nativeShouldDisplayRewardedVideo(location == null ? "" : location);
    }

    @Override
    public void didCacheRewardedVideo(String location) {
        Log.i(LOG_TAG, String.format("DID CACHE REWARDED VIDEO: '%s'",  (location != null ? location : "null")));
        nativeDidCacheRewardedVideo(location == null ? "" : location);
    }

    @Override
    public void didFailToLoadRewardedVideo(String location,
            CBImpressionError error) {
        Log.i(LOG_TAG, String.format("DID FAIL TO LOAD REWARDED VIDEO: '%s', Error:  %s",  (location != null ? location : "null"), error.name()));
        nativeDidFailToLoadRewardedVideo(location == null ? "" : location, getError(error));
    }

    @Override
    public void didDismissRewardedVideo(String location) {
        Log.i(LOG_TAG, String.format("DID DISMISS REWARDED VIDEO '%s'",  (location != null ? location : "null")));
        nativeDidDismissRewardedVideo(location == null ? "" : location);
    }

    @Override
    public void didCloseRewardedVideo(String location) {
        Log.i(LOG_TAG, String.format("DID CLOSE REWARDED VIDEO '%s'",  (location != null ? location : "null")));
        nativeDidCloseRewardedVideo(location == null ? "" : location);
    }

    @Override
    public void didClickRewardedVideo(String location) {
        Log.i(LOG_TAG, String.format("DID CLICK REWARDED VIDEO '%s'",  (location != null ? location : "null")));
        nativeDidClickRewardedVideo(location == null ? "" : location);
    }

    @Override
    public void didCompleteRewardedVideo(String location, int reward) {
        Log.i(LOG_TAG, String.format("DID COMPLETE REWARDED VIDEO '%s' FOR REWARD %d",  (location != null ? location : "null"), reward));
        nativeDidCompleteRewardedVideo(location == null ? "" : location, reward);
    }
    
    @Override
    public void didDisplayRewardedVideo(String location) {
        Log.i(LOG_TAG, String.format("DID DISPLAY REWARDED VIDEO: '%s'",  (location != null ? location : "null")));
        nativeDidDisplayRewardedVideo(location == null ? "" : location);
    }

    @Override
    public void willDisplayVideo(String location) {
        Log.i(LOG_TAG, String.format("WILL DISPLAY VIDEO '%s", location));
        nativeWillDisplayVideo(location == null ? "" : location);
    }
    
    private int getError(CBClickError error) {
    	int errorint = 0;
    	switch (error) {
		case URI_INVALID:
			errorint = 0;
			break;
		case URI_UNRECOGNIZED:
			errorint = 1;
			break;
		case AGE_GATE_FAILURE:
			errorint = 2;
			break;
		case NO_HOST_ACTIVITY:
			errorint = 3;
			break;
		case INTERNAL:
			errorint = 4;
			break;
		default:
			break;
		}
    	
    	return errorint + 1000;
    }
    
    private int getError(CBImpressionError error) {
    	int errorint = 0;
        switch (error) {
		case INTERNAL:
			errorint = 0;
			break;
		case INTERNET_UNAVAILABLE:
			errorint = 1;
			break;
		case TOO_MANY_CONNECTIONS:
			errorint = 2;
			break;
		case WRONG_ORIENTATION:
			errorint = 3;
			break;
		case FIRST_SESSION_INTERSTITIALS_DISABLED:
			errorint = 4;
			break;
		case NETWORK_FAILURE:
			errorint = 5;
			break;
		case NO_AD_FOUND:
			errorint = 6;
			break;
		case SESSION_NOT_STARTED:
			errorint = 7;
			break;
		case IMPRESSION_ALREADY_VISIBLE:
			errorint = 8;
			break;
		case NO_HOST_ACTIVITY:
			errorint = 9;
			break;
		case USER_CANCELLATION:
			errorint = 10;
			break;
		case INVALID_LOCATION:
			errorint = 11;
			break;
		case VIDEO_UNAVAILABLE:
			errorint = 12;
			break;
		case VIDEO_ID_MISSING:
			errorint = 13;
			break;
		case ERROR_PLAYING_VIDEO:
			errorint = 14;
			break;
		case INVALID_RESPONSE:
			errorint = 15;
			break;
		case ASSETS_DOWNLOAD_FAILURE:
			errorint = 16;
			break;
		case ERROR_CREATING_VIEW:
			errorint = 17;
			break;
		case ERROR_DISPLAYING_VIEW:
			errorint = 18;
			break;
		case INCOMPATIBLE_API_VERSION:
			errorint = 19;
			break;
		default:
			break;
		}
        
        return errorint + 1000;
    }
    
    /**
     * native methods
     */
    private native boolean nativeShouldRequestInterstitial(String location);

    private native boolean nativeShouldDisplayInterstitial(String location);

    private native void nativeDidCacheInterstitial(String location);

    private native void nativeDidFailToLoadInterstitial(String location, int error);

    private native void nativeDidDismissInterstitial(String location);

    private native void nativeDidCloseInterstitial(String location);

    private native void nativeDidClickInterstitial(String location);

    private native void nativeDidDisplayInterstitial(String location);

    private native boolean nativeShouldRequestMoreApps(String location);

    private native boolean nativeShouldDisplayMoreApps(String location);

    private native void nativeDidFailToLoadMoreApps(String location, int error);

    private native void nativeDidCacheMoreApps(String location);

    private native void nativeDidDismissMoreApps(String location);

    private native void nativeDidCloseMoreApps(String location);

    private native void nativeDidClickMoreApps(String location);

    private native void nativeDidDisplayMoreApps(String location);

    private native void nativeDidFailToRecordClick(String uri, int error);

    private native boolean nativeShouldDisplayRewardedVideo(String location);

    private native void nativeDidCacheRewardedVideo(String location);

    private native void nativeDidFailToLoadRewardedVideo(String location,
    		int error);

    private native void nativeDidDismissRewardedVideo(String location);

    private native void nativeDidCloseRewardedVideo(String location);

    private native void nativeDidClickRewardedVideo(String location);

    private native void nativeDidCompleteRewardedVideo(String location, int reward);
    
    private native void nativeDidDisplayRewardedVideo(String location);

    private native void nativeWillDisplayVideo(String location);
    
    private Activity mActivity;
    
    private static final String LOG_TAG = 
    		ChartboostHelperDelegate.class.getSimpleName();
}

