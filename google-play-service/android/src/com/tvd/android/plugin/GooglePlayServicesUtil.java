package com.tvd.android.plugin;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

public class GooglePlayServicesUtil {
	
	public static GooglePlayServicesUtil getInstance() {
		if(sInstance == null) {
			synchronized (GooglePlayServicesUtil.class) {
				if(sInstance == null) {
					sInstance = new GooglePlayServicesUtil();
				}
			}
		}
		
		return sInstance;
	}
	
	public void onCreate(Bundle savedInstanceState) {

		// Set a callback function for the C++ code to invoke after an
        // authorization event ends.
        // This should be the String name of a public, void, non-static method
        // in this class that
        // takes a single boolean as an argument.
        setAuthResultCallback("onAuthActionFinished");

        // Initialize the Google Play Games C++ SDK. This will set up the proper
        // Android platform
        // configuration and make an initial attempt to sign in without user
        // interaction.
        nativeOnActivityCreated(getActivity(), savedInstanceState);
	}
	
	public void onAuthActionFinished(boolean success) {
        Log.i(TAG, "onAuthActionFinished: " + String.valueOf(success));
        mIsSignedIn = success;

        // Need to make sure to run this on the UI thread since the C++ SDK may
        // invoke this
        // callback from a separate thread.
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
//                setButtonState();
            }
        });
    }
	
	public void onActivityResult(int requestCode, int resultCode, Intent result) {
        Log.i(TAG, "onActivityResult: " + requestCode);

        // Pass the activity result to the C++ SDK so that it can resolve any
        // errors related
        // to Google Play Games. The C++ SDK only acts on Activity results that
        // contain the
        // unique request code.
        nativeOnActivityResult(getActivity(), requestCode, resultCode, result);
    }
	
	public void setActivity(Activity activity) {
		mActivity = activity;
	}
	
	public Activity getActivity() {
		return mActivity;
	}
	
	private native void signIn();

    private native void signOut();

    private native void showAchievements();

    private native void showLeaderboards();

    private native void nativeOnActivityCreated(Activity activity,
            Bundle savedInstanceState);

    private native void nativeOnActivityResult(Activity activity,
            int request_code, int result_code, Intent result);

    private native void setAuthResultCallback(String methodName);
    
    private boolean mIsSignedIn = false;
    
    private Activity mActivity = null;
    
    private static GooglePlayServicesUtil sInstance;
    
    private static final String TAG = 
    		GooglePlayServicesUtil.class.getSimpleName();
 
}
