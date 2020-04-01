package com.harman.hmmediasdkapp;

public interface FileUploadListener {
    void uploadProgress(String file, int percent);

    void uploadSuccess(String file, String msg);

    void uploadFailure(String file, String msg, int errorCode);
}
