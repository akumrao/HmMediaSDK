package com.harman.hmmediasdkapp;

import android.util.Log;

import androidx.annotation.Keep;

public class HmLibrary {
    // Used to load the 'native-lib' library on application startup.
    private FileUploadListener mFileUploadListener;

    static {
        System.loadLibrary("libupload");
    }

    private static final HmLibrary ourInstance = new HmLibrary();

    public static HmLibrary getInstance() {
        return ourInstance;
    }

    private HmLibrary() {
    }

    public void uploadFile(String driverId, String metadata, String[] files, String oAuthToken,
            FileUploadListener progress) {
        mFileUploadListener = progress;
        upload(driverId, metadata, files, oAuthToken);
    }

    public void stopUpload() {
        stop();
    }

    /*
     * A function calling from JNI to update current timer
     */
    @Keep
    private void uploadProgress(final String msg, final int perc) {
        mFileUploadListener.uploadProgress("", 0);
        Log.d("JniHandler1", "Native : " + msg);
    }

    /*
     * A function calling from JNI to update current timer
     */
    @Keep
    private void uploadSuccess(final String msg) {
        mFileUploadListener.uploadSuccess("", msg);
        Log.d("JniHandler1", "Native : " + msg);
    }

    /*
     * A function calling from JNI to update current timer
     */
    @Keep
    private void uploadFailure(final String msg) {
        mFileUploadListener.uploadFailure("", msg, -1);
        Log.d("JniHandler1", "Native : " + msg);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void upload(String driverid, String metadata, String[] path, String oAuthToken);

    public native void stop();
}
