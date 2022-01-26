package com.reactnativecryptopp;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;

public class CryptoppModule extends ReactContextBaseJavaModule {
  public static final String NAME = "Cryptopp";
  private static native void initialize(long jsiPtr, String docDir);

  public CryptoppModule(ReactApplicationContext reactContext) {
    super(reactContext);
  }

  @NonNull
  @Override
  public String getName() {
    return "Cryptopp";
  }

  @ReactMethod(isBlockingSynchronousMethod = true)
  public boolean install() {
    try {
      System.loadLibrary("cryptopp");

      ReactApplicationContext context = getReactApplicationContext();
      initialize(
        context.getJavaScriptContextHolder().get(),
        context.getFilesDir().getAbsolutePath()
      );
      return true;
    } catch (Exception exception) {
      return false;
    }
  }
}
