package com.harman.hmmediasdkapp;

import android.util.Log;

import androidx.annotation.Keep;

public class HmLibrary {
    // Used to load the 'native-lib' library on application startup.
    private UploadProgress uploadProgress;

    static {
        System.loadLibrary("libupload");
    }

    private static final HmLibrary ourInstance = new HmLibrary();

    public static HmLibrary getInstance() {
        return ourInstance;
    }

    private HmLibrary() {
    }

    public void uploadFile(String driverId, String metadata, String[] files, UploadProgress progress, String oAuthToken ) {
        uploadProgress = progress;
        upload(driverId, metadata, files,oAuthToken);
    }

    public void stopUpload() {
        stop();
    }

    /*
     * A function calling from JNI to update current timer
     */
    @Keep
    private void uploadProcess(final String msg) {
        uploadProgress.progress(msg);
        Log.d("JniHandler1", "Native : " + msg);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void upload(String driverid, String metadata, String[] path, String oAuthToken);

    public native void stop();
}
