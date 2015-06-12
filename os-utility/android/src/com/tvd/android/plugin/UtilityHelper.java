package com.tvd.android.plugin;

/**
 * 
*/

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.pm.Signature;
import android.net.Uri;
import android.os.Build;
import android.os.Vibrator;
import android.telephony.TelephonyManager;
import android.util.Base64;
import android.util.Log;

public class UtilityHelper {
	
	public void setRegId(String regId) {
		this.mRegId = regId;
	}

	static {
		
	}
	
	public static UtilityHelper getInstance() {
		if(UtilityHelper.sInstance == null) {
			synchronized (UtilityHelper.class) {
				if(UtilityHelper.sInstance == null) {
					UtilityHelper.sInstance = new UtilityHelper();
				}
			}
		}
		
		return UtilityHelper.sInstance;
	}
	
	public static String sGenerateFbKeyHash() {
		String keyHash = null;
		try {
			Log.v(LOG_TAG, "KeyHash:for: " + sActivity.getClass().getPackage().getName());
            PackageInfo info = sContext.getPackageManager().getPackageInfo(
            		sActivity.getClass().getPackage().getName(), 
                    PackageManager.GET_SIGNATURES);
            for (Signature signature : info.signatures) {
                MessageDigest md = MessageDigest.getInstance("SHA");
                md.update(signature.toByteArray());
                keyHash = Base64.encodeToString(md.digest(), Base64.DEFAULT);
                Log.v("KeyHash: ", keyHash);
                }
        } catch (NameNotFoundException e) {
        	Log.v(LOG_TAG, "KeyHash:" + e.toString());
        }
        catch (NoSuchAlgorithmException e) {
        	Log.v(LOG_TAG, "KeyHash:" + e.toString());
        }
		return keyHash;
	}
	
	public static String sGetPhoneId() {
		TelephonyManager telephonyManager = 
				(TelephonyManager)sContext.getSystemService(Context.TELEPHONY_SERVICE);
		
		return telephonyManager.getDeviceId();
	}
	
	protected static String md5(String s) {
	    MessageDigest md = null;
	    StringBuffer result = new StringBuffer();
		try {
			md = MessageDigest.getInstance("MD5");
			md.update(s.getBytes());
		    byte digest[] = md.digest();
		    for (int i = 0; i < digest.length; i++) {
		    	result.append(Integer.toString((digest[i] & 0xff) + 0x100, 16).substring(1));
		    }
		} catch (NoSuchAlgorithmException e) {
			Log.e(LOG_TAG, e.toString());
			return s;
		}
	    return (result.toString());
	}
	
	public static void sVibrate() {
		Vibrator vibrator = (Vibrator) sContext.getSystemService(Context.VIBRATOR_SERVICE);
		vibrator.vibrate(100);
	}
	
	public static String sGetPushId() {
		return UtilityHelper.getInstance().getRegId();
	}
	
	public static String sGetAppVersion() {
    	String app_ver;
        try {
			app_ver = sContext.getPackageManager().getPackageInfo(
					sContext.getPackageName(), 0).versionName;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			app_ver = "unknown";
		}
        
        return app_ver;
	}

	public static String sGetSystemVersion() {
        return Build.VERSION.RELEASE;
	}

	public static String sGetDeviceModel() {
        return Build.MODEL;
	}

	public static void sRateUs() {
		Intent i = new Intent(Intent.ACTION_VIEW);
		i.setData(Uri.parse("market://details?id=" + sContext.getPackageName()));
		sContext.startActivity(i);
	}

    public static void sOpenUrl(String url) { 
        Intent i = new Intent(Intent.ACTION_VIEW);  
        i.setData(Uri.parse(url));
        sContext.startActivity(i);
    }

    public static void sSendFeedback(final String email,
    		final String subject, 
    		final String mailbody) {
        
        Intent i = new Intent(Intent.ACTION_SEND);
        i.setType("message/rfc822");
        i.putExtra(Intent.EXTRA_EMAIL, new String[] {email});
        i.putExtra(Intent.EXTRA_SUBJECT, subject);
        i.putExtra(Intent.EXTRA_TEXT, mailbody);
        sContext.startActivity(Intent.createChooser(i, "Select application"));  
    }
    
    public void setContext(Context context) {
    	sContext = context;
    }
    
    public void setActivity(Activity activity) {
    	sActivity = activity;
    }
    
    private static UtilityHelper sInstance = null;
	
	private static Context sContext;
	
	private static Activity sActivity;
	
    private String mRegId;
    
	public String getRegId() {
		return mRegId;
	}

    private static final String LOG_TAG = 
    		UtilityHelper.class.getSimpleName();
}
