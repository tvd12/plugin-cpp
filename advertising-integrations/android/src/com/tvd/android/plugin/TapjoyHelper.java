package com.tvd.android.plugin;

import java.util.Hashtable;

import com.tapjoy.TJActionRequest;
import com.tapjoy.TJConnectListener;
import com.tapjoy.TJError;
import com.tapjoy.TJPlacement;
import com.tapjoy.TJPlacementListener;
import com.tapjoy.Tapjoy;
import com.tapjoy.TapjoyConnectFlag;

import android.app.Activity;
import android.content.Context;

public class TapjoyHelper {
	
	private TapjoyHelper() {}
	
	public static void init(Context context,
			Hashtable<String, Object> connectFlags) {
		sContext = context;
		if(connectFlags == null) {
			connectFlags = new Hashtable<String, Object>();
			connectFlags.put(TapjoyConnectFlag.ENABLE_LOGGING, "true");
		}
		sConnectFlags = connectFlags;
	}
	
	public static void connect(String sdkKey, boolean debug) {
		Tapjoy.connect(sContext, sdkKey, sConnectFlags, new TJConnectListener() {
			
			@Override
			public void onConnectSuccess() {
				nativeOnConnectSuccess();
			}
			
			@Override
			public void onConnectFailure() {
				nativeOnConnectFailure();
			}
		});
		Tapjoy.setDebugEnabled(debug);
		
		System.out.println("Tapjoy::connect");
	}
	
	public static void requestOfferwall(String offerwallUnit) {
		sOfferwallPlacement = new TJPlacement(sContext, offerwallUnit, new TJPlacementListener() {
			
			@Override
			public void onRewardRequest(TJPlacement placement, 
					TJActionRequest request,
					String itemId, 
					int quantity) {
				
			}
			
			@Override
			public void onRequestSuccess(TJPlacement placement) {
				nativeOfferwallOnRequestSuccess(placement.getName(),
						placement.isContentReady(),
						placement.isContentAvailable());
			}
			
			@Override
			public void onRequestFailure(TJPlacement placement, 
					TJError error) {
				nativeOfferwallOnRequestFailure(placement.getName(), 
						error.message);
			}
			
			@Override
			public void onPurchaseRequest(TJPlacement placement,
					TJActionRequest request,
					String productId) {
				
			}
			
			@Override
			public void onContentShow(TJPlacement placement) {
				nativeOfferwallOnContentShow(placement.getName());
			}
			
			@Override
			public void onContentReady(TJPlacement placement) {
				nativeOfferwallOnContentReady(placement.getName(),
						placement.isContentAvailable());
			}
			
			@Override
			public void onContentDismiss(TJPlacement placement) {
				nativeOfferwallOnContentDismiss(placement.getName());
			}
		});
	}
	
	public static void onActivityStart(Activity activity) {
		Tapjoy.onActivityStart(activity);
	}
	
	public static void onActivityStop(Activity activity) {
		Tapjoy.onActivityStop(activity);
	}
	
	/**
	 * Common native
	 */
	private native static void nativeOnConnectSuccess();
	private native static void nativeOnConnectFailure();
	
	/**
	 * Offerwall native
	 */
	
	private native static void nativeOfferwallOnRequestSuccess(
			String placementName,
			boolean isContentReady,
			boolean isContentAvailable);
	private native static void nativeOfferwallOnRequestFailure(
			String placementName,
			String error);
	private native static boolean nativeOfferwallOnContentReady(
			String placementName,
			boolean isContentAvailable);
	private native static void nativeOfferwallOnContentShow(
			String placementName);
	private native static void nativeOfferwallOnContentDismiss(
			String placementName);
	
	private static Context sContext;
	private static Hashtable<String, Object> sConnectFlags;
	
	private static TJPlacement sOfferwallPlacement;
	
}
