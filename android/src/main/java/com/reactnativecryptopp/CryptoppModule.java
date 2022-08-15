package com.reactnativecryptopp;

import androidx.annotation.NonNull;
import android.util.Log;

import com.facebook.jni.HybridData;
import com.facebook.jni.annotations.DoNotStrip;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;

class CryptoppModule extends ReactContextBaseJavaModule {
  public CryptoppModule(ReactApplicationContext context) {
    super(context);
  }

  @NonNull
  @Override
  public String getName() {
    return "Cryptopp";
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  public boolean install() {
    try {
      System.loadLibrary("rncryptopp");
      CryptoppBridge.instance.install(getReactApplicationContext());
      return true;
    } catch (Exception exception) {
      Log.e("RNCryptopp", "Failed to install JSI Bindings!", exception);
      return false;
    }
  }
}
