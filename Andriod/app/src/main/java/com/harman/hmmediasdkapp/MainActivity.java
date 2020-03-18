package com.harman.hmmediasdkapp;

import androidx.annotation.Keep;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("libupload");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String metadata = "{filename:driver-1234-1232323.mp4, gps-latitude:28.674109, gps-longitude:77.438009, timestamp:20200309194530, uploadmode:normal}";

        //socket.upload( filename, , metadata);

        //String[] files = {"/storage/emulated/0/Android/data/com.harman.hmmediasdkapp/files/Harman/test.mp4", "/storage/emulated/0/Android/data/com.harman.hmmediasdkapp/files/Harman/test.mp4"};

        String[] files = {"/storage/emulated/0/Android/data/com.harman.hmmediasdkapp/files/Harman/test.mp4"};

        upload("Driver123", metadata,files );

        TextView tv = findViewById(R.id.sample_text);
        tv.setText("arvind");
    }


    /*
     * A function calling from JNI to update current timer
     */
    @Keep
    private void uploadProcess(final String msg ) {

        Log.e("JniHandler1", "Native Err: " + msg);


        runOnUiThread(new Runnable() {
            @Override
            public void run() {

                //MainActivity.this.tickView.setText(msg + " " );
                TextView tv = findViewById(R.id.sample_text);
                tv.setText(msg);
            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
   // public native String stringFromJNI();

    public native void upload(String driverid, String metadata, String[] path);

    public native void stop();
}
