package com.reactnativecryptopp;

import android.util.Log;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContext;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;

public class CryptoppBridge {
  private native void installNativeJsi(long jsContextNativePointer, CallInvokerHolderImpl jsCallInvokerHolder);
  public static final CryptoppBridge instance = new CryptoppBridge();

  public void install(ReactContext context) {
      long jsContextPointer = context.getJavaScriptContextHolder().get();
      CallInvokerHolderImpl jsCallInvokerHolder = (CallInvokerHolderImpl)context.getCatalystInstance().getJSCallInvokerHolder();
      
      installNativeJsi(
        jsContextPointer,
        jsCallInvokerHolder
      );
  }
}