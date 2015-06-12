package com.tvd.android.plugin;

import android.app.Activity;

import com.jirbo.adcolony.AdColony;
import com.jirbo.adcolony.AdColonyAd;
import com.jirbo.adcolony.AdColonyAdAvailabilityListener;
import com.jirbo.adcolony.AdColonyAdListener;
import com.jirbo.adcolony.AdColonyIAPEngagement;
import com.jirbo.adcolony.AdColonyV4VCAd;
import com.jirbo.adcolony.AdColonyV4VCListener;
import com.jirbo.adcolony.AdColonyV4VCReward;

public class AdColonyHelper {

	public static void init(Activity activity,
			String clientOptions,
			String app_id,
			String... zonesIds) {
		AdColony.configure(activity, 
				clientOptions, 
				app_id, 
				zonesIds);
		AdColony.addAdAvailabilityListener(new AdColonyHelperListener());
		AdColony.addV4VCListener(new AdColonyHelperListener());
		sActivity = activity;
	}
	
	public static void resume(Activity activity) {
		AdColony.resume(activity);
	}
	
	public static void pause() {
		AdColony.pause();
	}
	
	public static void setCustomId(String customId) {
		System.out.println("ad::setCustomId");
		AdColony.setCustomID(customId);
	}
	
	public static void newFunction(String zoneId, boolean withPreConfirm,
			boolean withPostConfirm) {
		System.out.println("ad::new function, a = " + withPostConfirm);
	}
	
	public static String getDeviceId() {
		return AdColony.getDeviceID();
	}
	
	public static String getCustomId() {
		return AdColony.getCustomID();
	}
	
	public static int statusForZone(String zoneId) {
		System.out.println("ad::statusForZone");
		
		String status = AdColony.statusForZone(zoneId);
		if(status.equals("invalid")) {
			return 0;
		}
		else if(status.equals("off")) {
			return 1;
		}
		else if(status.equals("loading")) {
			return 2;
		}
		else if(status.equals("active")) {
			return 3;
		}
		else if(status.equals("unknown")) {
			return 4;
		}
		return 4;
	}
	
	public static void cancelVideo() {
		AdColony.cancelVideo();
	}
	
	public static int getRemainingV4VCForZone(String zoneId) {
		return AdColony.getRemainingV4VCForZone(zoneId);
	}
	
	public static void notifyIAPComplete( String productId, 
			String transationId, 
			String currencyCode, 
			double price) {
		AdColony.notifyIAPComplete(productId, 
				transationId,
				currencyCode,
				price);
	}
	
	public static void showVideoAd(String zoneId) {
		mV4VCAd.show();
	}
	
	public static void showVideoAd(String zoneId,
			boolean withPreConfirm,
			boolean withPostConfirm) {
		System.out.println("Ad::showVideoAd2");
		if(withPostConfirm) {
			mV4VCAd.withConfirmationDialog();
		}
		if(withPreConfirm) {
			mV4VCAd.withResultsDialog();
		}
		sActivity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				mV4VCAd.show();
			}
		});
	}
	
	public static void checkeExistenceVideoAd(String zoneId) {
		mV4VCAd = new AdColonyV4VCAd(zoneId)
		.withListener(new AdColonyHelperListener());
		
		System.out.println("Ad::checkeExistenceVideoAd");
	}
	
	public static boolean isVideoReady() {
		return mV4VCAd.isReady();
	}

	public static String getRewardName() {
		return mV4VCAd.getRewardName();
	}
	
	public static int getRewardAmount() {
		return mV4VCAd.getRewardAmount();
	}
	
	public int getViewsPerReward() {
		return mV4VCAd.getViewsPerReward();
	}
	
	public int getRemainingViewsUntilReward() {
		return mV4VCAd.getRemainingViewsUntilReward();
	}
	
	
	
	private static AdColonyV4VCAd mV4VCAd;
	private static Activity sActivity;
}

class AdColonyHelperListener implements AdColonyAdListener,
		AdColonyAdAvailabilityListener,
		AdColonyV4VCListener {

	@Override
	public void onAdColonyV4VCReward(AdColonyV4VCReward reward) {
		System.out.println("Ad::onAdColonyV4VCReward");
		nativeOnAdColonyV4VCReward(reward.success(), 
				reward.name(), reward.amount(),
				"UNKNOWN");
	}

	@Override
	public void onAdColonyAdAvailabilityChange(boolean available, 
			String zoneId) {
		System.out.println("Ad::onAdColonyAdAvailabilityChange");
		nativeOnAdColonyAdAvailabilityChange(available, zoneId);
	}

	@Override
	public void onAdColonyAdAttemptFinished(AdColonyAd ad) {
		System.out.println("Ad::onAdColonyAdAttemptFinished");
		nativeOnAdColonyAdAttemptFinished(
				ad.shown(), 
				ad.iapEnabled(), 
				ad.getAvailableViews(),
				getIapEngagementType(ad.iapEngagementType()),
				"UNKNOWN",
				ad.iapProductID());
	}

	@Override
	public void onAdColonyAdStarted(AdColonyAd ad) {
		System.out.println("Ad::onAdColonyAdStarted");
		nativeOnAdColonyAdStarted("UNKNOWN");
	}
	
	private int getIapEngagementType(AdColonyIAPEngagement ement) {
		if(ement.equals(AdColonyIAPEngagement.NONE)) {
			return 0;
		}
		else if(ement.equals(AdColonyIAPEngagement.AUTOMATIC)) {
			return 1;
		}
		else if(ement.equals(AdColonyIAPEngagement.END_CARD)) {
			return 2;
		}
		else if(ement.equals(AdColonyIAPEngagement.OVERLAY)) {
			return 3;
		}
		
		return 0;
	}
	
	private native void nativeOnAdColonyV4VCReward(
			boolean success,
			String currencyName, 
			int currencyAmount,
			String zoneId
			);
	private native void nativeOnAdColonyAdAvailabilityChange(
			boolean available, String zoneId);
	private native void nativeOnAdColonyAdAttemptFinished(
			boolean shown,
            boolean iapEnabled,
            int iapQuantity,
            int iapEngagement,
            String zoneId,
            String iapProductId);
	
	private native void nativeOnAdColonyAdStarted(
            String zoneId);
}
