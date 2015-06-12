package com.tvd.android.plugin;

/* Copyright (c) 2012 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use context file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Date;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

import com.android.util.IabHelper;
import com.android.util.IabResult;
import com.android.util.Inventory;
import com.android.util.Purchase;
import com.android.util.SkuDetails;
import com.tvd.android.inapp.model.GameSku;

public class GameInappHelper {

	private native void nativeOnLoadPriceSuccess(boolean isSuccess);
    private native void nativeOnInappFail();
    private native void nativeOnInappSuccess(String packageName, 
    		String productId, String purchaseToken);

    private GameInappHelper() {
    	sIsLoadPriceSuccess = false;
    }
    
    public static GameInappHelper getInstance() {
    	if(GameInappHelper.sInstance == null) {
    		synchronized (GameInappHelper.class) {
				if(GameInappHelper.sInstance == null) {
					GameInappHelper.sInstance = new GameInappHelper();
				}
			}
    	}
    	
    	return GameInappHelper.sInstance;
    }
    

    public static void prepareProducts() {
        // load game data
        loadData();

        // Create the helper, passing it our context and the public key 
        // to verify signatures with
        Log.d(LOG_TAG, "Creating IAB helper.");
//        sInAppHelper = new IabHelper(context, Constants.BASE64_ENCODE_PUBLIC_KEY);
        sInappHelper = new IabHelper(GameInappHelper.sContext, 
        		sBase64EncodeKey);

        // enable debug logging (for a production application, you should set context to false).
        sInappHelper.enableDebugLogging(true);

        // Start setup. This is asynchronous and the specified listener
        // will be called once setup completes.
        Log.d(LOG_TAG, "Starting setup.");
        sInappHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
            public void onIabSetupFinished(IabResult result) {
                Log.d(LOG_TAG, "Setup finished.");
                if (!result.isSuccess()) {
                    // Oh noes, there was a problem.
                    return;
                }
                
                // Have we been disposed of in the meantime? If so, quit.
                if (sInappHelper == null) return;

                // IAB is fully set up. Now, let's get an inventory of stuff we own.
                Log.d(LOG_TAG, "Setup successful. Querying inventory.");
                ArrayList<String> moreSkus = new ArrayList<String>();
                moreSkus.addAll(Arrays.asList(sProductIds));
                sInappHelper.queryInventoryAsync(true, moreSkus, mGotInventoryListener);
            }
        });
    }

    // Listener that's called when we finish querying the items and subscriptions we own
    private static IabHelper.QueryInventoryFinishedListener mGotInventoryListener = 
    		new IabHelper.QueryInventoryFinishedListener() {
        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
            Log.d(LOG_TAG, "Query inventory finished.");

            // Have we been disposed of in the meantime? If so, quit.
            if (sInappHelper == null) return;

            // Is it a failure?
            if (result.isFailure()) {
                //complain("Failed to query inventory: " + result);
                return;
            }

            Log.d(LOG_TAG, "Query inventory was successful.");
            
            sGetSkuPriceList();

            /*
             * Check for items we own. Notice that for each purchase, we check
             * the developer payload to see if it's correct! See
             * verifyDeveloperPayload().
             */
            // get prices
            for(int i = 0 ; i < sProductIds.length ; i++) {
            	SkuDetails skuDetails = inventory.getSkuDetails(sProductIds[i]);
            	if(skuDetails != null) {
                    Log.d(LOG_TAG, sProductIds[i] + " Price: " + skuDetails.getPrice());
            	}
            }

            // consume 
            for(int i = 0 ; i < sProductIds.length ; i++) {
            	Purchase chipPurchase = inventory.getPurchase(sProductIds[i]);
            	if(chipPurchase != null) {
            		sInappHelper.consumeAsync(inventory.getPurchase(sProductIds[i]), 
                    		mConsumeFinishedListener);
            	}
            }

            Log.d(LOG_TAG, "Initial inventory query finished; enabling main UI.");
        }
    };

    // User clicked the "Buy Gas" button
    private static void sOnBuyButtonClicked(int index) {
        Log.d(LOG_TAG, "Buy gold button clicked.");

        sDeveloperPayload = new Date().toString();

        sInappHelper.launchPurchaseFlow((Activity)sContext, sProductIds[index], 
        		RC_REQUEST, mPurchaseFinishedListener, sDeveloperPayload);
    }

    public static void sBuyPackage(int index) {
        sDeveloperPayload = new Date().toString();

        sInappHelper.launchPurchaseFlow((Activity)sContext, sProductIds[index], 
        		RC_REQUEST, mPurchaseFinishedListener, sDeveloperPayload);
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        Log.d(LOG_TAG, "onActivityResult(" + requestCode + "," + resultCode + "," + data);
        if (sInappHelper == null) {
        	return;
        } else {
        }
    }

    /** Verifies the developer payload of a purchase. */
    private static boolean verifyDeveloperPayload(Purchase p) {
        /*
         * verify that the developer payload of the purchase is correct. It will be
         * the same one that you sent when initiating the purchase.
         *
         * WARNING: Locally generating a random string when starting a purchase and
         * verifying it here might seem like a good approach, but context will fail in the
         * case where the user purchases an item on one device and then uses your app on
         * a different device, because on the other device you will not have access to the
         * random string you originally generated.
         *
         * So a good developer payload has these characteristics:
         *
         * 1. If two different users purchase an item, the payload is different between them,
         *    so that one user's purchase can't be replayed to another user.
         *
         * 2. The payload must be such that you can verify it even when the app wasn't the
         *    one who initiated the purchase flow (so that items purchased by the user on
         *    one device work on other devices owned by the user).
         *
         * Using your own server to store and verify developer payloads across app
         * installations is recommended.
         */
    	String payload = p.getDeveloperPayload();
        return (payload.equals(sDeveloperPayload));
    }

    // Callback for when a purchase is finished
    private static IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = 
    		new IabHelper.OnIabPurchaseFinishedListener() {
        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
            Log.d(LOG_TAG, "Purchase finished: " + result + ", purchase: " + purchase);
            
            // if we were disposed of in the meantime, quit.
            if (sInappHelper == null) return;

            if (result.isFailure() || purchase == null) {
            	// update to game
    			GameInappHelper.getInstance().nativeOnInappFail();
                return;
            }

            // purchase success
            Log.d(LOG_TAG, "Purchase getPackageName: " + purchase.getPackageName() +
            		", getSku: " + purchase.getSku() + ", getToken: " + purchase.getToken());
            GameInappHelper.getInstance().nativeOnInappSuccess(
            		purchase.getPackageName(), 
            		purchase.getSku(),
            		purchase.getToken());

            Log.d(LOG_TAG, "Purchase successful.");

            for(int i = 0 ; i < sProductIds.length ; i++) {
            	if (purchase.getSku().equals(sProductIds[i])) {
            		sInappHelper.consumeAsync(purchase, mConsumeFinishedListener);
            	}
            }
        }
    };

    // Called when consumption is complete
    private static IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = 
    		new IabHelper.OnConsumeFinishedListener() {
        public void onConsumeFinished(Purchase purchase, IabResult result) {
            Log.d(LOG_TAG, "Consumption finished. Purchase: " 
            		+ purchase + ", result: " + result);

            // if we were disposed of in the meantime, quit.
            if (sInappHelper == null) return;

            // We know context is the "gas" sku because it's the only one we consume,
            // so we don't check which sku was consumed. If you have more than one
            // sku, you probably should check...
            if (result.isSuccess()) {
                // successfully consumed, so we apply the effects of the item in our
                // game world's logic, which in our case means filling the gas tank a bit
                Log.d(LOG_TAG, "Consumption successful. Provisioning.");
                saveData();
            }
            else {
                complain("Error while consuming: " + result);
            }
            Log.d(LOG_TAG, "End consumption flow.");
        }
    };

    // We're being destroyed. It's important to dispose of the helper here!
    public void onDestroy() {
        // very important:
        Log.d(LOG_TAG, "Destroying helper.");
        if (sInappHelper != null) {
            sInappHelper.dispose();
            sInappHelper = null;
        }
    }

    static void complain(String message) {
        Log.e(LOG_TAG, "**** TrivialDrive Error: " + message);
        alert("Error: " + message);
    }

    public static void alert(String message) {
        AlertDialog.Builder bld = new AlertDialog.Builder(sContext);
        bld.setMessage(message);
        bld.setNeutralButton("OK", null);
        Log.d(LOG_TAG, "Showing alert dialog: " + message);
        bld.create().show();
    }

    static void saveData() {

    }

    static void loadData() {
    }
    
    public static void sSendTransacIdToServer(List<NameValuePair> params) {
    	HttpClient client = new DefaultHttpClient();
    	HttpPost post = new HttpPost(URI_SERVER_VERIFY);
    	try {
	    	post.setEntity(new UrlEncodedFormEntity(params));
	    	HttpResponse response = client.execute(post);
	    	InputStream content = response.getEntity().getContent();
	    	BufferedReader reader = new BufferedReader(new InputStreamReader(content));
		    StringBuffer buffer = new StringBuffer();
		    for (String line = reader.readLine(); line != null; line = reader.readLine()) {
		    	buffer.append(line);
		    }
		    if(buffer.toString().equals("")) {
	    		alert("verify failed");
	    	}
		    System.out.println(buffer.toString());
    	} catch(UnsupportedEncodingException e) {
    		Log.e(LOG_TAG, e.toString());
    	} catch (ClientProtocolException e) {
    		Log.e(LOG_TAG, e.toString());
		} catch (IOException e) {
			Log.e(LOG_TAG, e.toString());
		} catch(NullPointerException e) {
			alert("verify failed");
			Log.e(LOG_TAG, e.toString());
		}
    }
        
	private static List<GameSku> sGetSkuDetailsList() {
    	ArrayList<String> skuList = new ArrayList<String>();
        skuList.addAll(Arrays.asList(sProductIds));
        List<String> skuDetailsList = sInappHelper.getSkuDetailsList(skuList);
        List<GameSku> result = new ArrayList<GameSku>();
        for (String skuDetails : skuDetailsList) {
	        JSONObject object;
			try {
				object = new JSONObject(skuDetails);
				String skuId = object.getString("productId");
			    String price = object.getString("price");
			    result.add(new GameSku(skuId, price));
			} catch (JSONException e) {
				Log.e(LOG_TAG, e.toString());
			}
    	}
        return result;
    }
    
    public static boolean sGetSkuPriceList() {
    	//progressDialog = ProgressDialog.show(context, " Working...", 
    			//"Retrieving prices", true, false);
    	new Thread() {
    		@Override
    		public void run() {
    			sGameSkus = sGetSkuDetailsList();
    			Collections.sort(sGameSkus);
    			handler.sendEmptyMessage(0);
    		}
    	}.start();
    	return sIsLoadPriceSuccess;
    }
    
    public static String sGetPricesString(String indexes) {
    	String[] temp = indexes.split(",");
    	int[] someSku = new int[temp.length];
    	for(int i = 0 ; i < someSku.length ; i++) {
    		someSku[i] = Integer.parseInt(temp[i]);
    	}
    	return sGetPricesString(someSku);
    }
    
    public static String sGetPricesString(int[] someSku) {
    	String result = "";
    	if(sIsLoadPriceSuccess) {
    		for(int i = 0 ; i < someSku.length ; i++) {
    			//alert(" i = " + someSku[i]);
    			Log.v(LOG_TAG, " some[i] = " + someSku[i]);
    			result += sGameSkus.get(someSku[i]).getPrice();
    			if(i < someSku.length - 1) {
    				result += ";";
    			}
    		}
    	}
    	//alert(result);
    	return result.replace("₫", "đ");
    }
    
    public static String sGetPricesString(int index) {
    	return sGetPricesString(new int[]{index});
    }
    
    public static void toastComplain(String str) {
    	Toast.makeText(sContext, str, Toast.LENGTH_LONG).show();
    }
    
    public static IabHelper getIabHelper() {
    	return sInappHelper;
    }
    
    public static void setBase64EncodeKey(String base64EncodeKey) {
    	sBase64EncodeKey = base64EncodeKey;
    }
    
    public static void setProductIds(String productIds[]) {
    	sProductIds = productIds;
    }
    
    // (arbitrary) request code for the purchase flow
    static final int RC_REQUEST = 10001;
    
    public static Context sContext = null;
    public static IabHelper sInappHelper = null;
    private static GameInappHelper sInstance = null;
    
    private static String sDeveloperPayload = "tvd";
    private static List<GameSku> sGameSkus;
    private static boolean sIsLoadPriceSuccess = false;
    private static String sBase64EncodeKey;
    private static String[] sProductIds;
    private static String LOG_TAG = GameInappHelper.class.getSimpleName();
    
    private static Handler handler = new Handler() {
		@Override
		public void handleMessage(final Message msg) {
			//progressDialog.dismiss();
			sIsLoadPriceSuccess = true;
			
			// inform to client
			GameInappHelper.getInstance().nativeOnLoadPriceSuccess(true);
			//alert(pokerSkus.toString());
		}
	};
    
    protected static final String URI_SERVER_VERIFY = "http://192.168.1.102:8080/IAppBilling/InAppServlet";
}