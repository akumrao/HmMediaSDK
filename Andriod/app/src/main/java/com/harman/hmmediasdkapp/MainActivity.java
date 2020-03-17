package com.harman.hmmediasdkapp;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.Keep;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button buttonStart = null;
    private Button buttonStop = null;

    private TextView displayView = null;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initViews();
    }

    private void initViews() {
        displayView = findViewById(R.id.displayId);
        buttonStart = findViewById(R.id.start);
        buttonStart.setOnClickListener(this);
        buttonStop = findViewById(R.id.stop);
        buttonStop.setOnClickListener(this);
    }


    /*
     * A function calling from JNI to update current timer
     */
    @Keep
    private void updateTimer(final String msg) {
        Log.d("JniHandler1", "Native Err: " + msg);
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Log.d("JniHandler1", "Native Err: $msg");
                String s = displayView.getText().toString();
                displayView.append(s+"\n");
            }
        });
    }

    @Override
    public void onClick(View view) {
        int id = view.getId();
        switch (id) {
            case R.id.start:
                displayView.setText("");
                String metadata =
                        "{filename:driver-1234-1232323.mp4, gps-latitude:28.674109, gps-longitude:77.438009, timestamp:20200309194530, uploadmode:normal}";
                upload(
                        "Upload", metadata,
                        "/storage/emulated/0/Android/data/com.harman.hmmediasdkapp/files/Harman/test.mp4");
                break;
            case R.id.stop:
                stop();
                break;
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void upload(String driverid, String metadata, String path);

    public native void stop();
}
