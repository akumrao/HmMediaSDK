package com.harman.hmmediasdkapp;

import android.os.Bundle;
import android.util.Log;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;

import com.harman.hmmediasdkapp.databinding.ActivityHmLibraryBinding;

import java.io.File;

public class HmLibraryActivity extends AppCompatActivity {

    ActivityHmLibraryBinding binding = null;

    FileUploadListener progress = new FileUploadListener() {
        @Override
        public void uploadProgress(final String filePath, final int percent) {
            Log.d("HmLibrary", "filename :${File(filePath).name} percent :$percent");
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    binding.uploadProgress.setVisibility(View.VISIBLE);
                    binding.uploadProgress.setText(String.format(getString(R.string.upload_progress), new File(filePath).getName(), String.valueOf(percent)));
                }
            });
        }

        @Override
        public void uploadSuccess(final String filePath, final String msg) {
            Log.d("HmLibrary", "filename :${File(filePath).name} reason :$msg");
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    binding.uploadSuccess.setVisibility(View.VISIBLE);
                    binding.uploadSuccess.setText(String.format(getString(R.string.success_info), new File(filePath).getName(), msg));
                }
            });
        }

        @Override
        public void uploadFailure(final String filePath, final String msg, final int errorCode) {
            Log.d("HmLibrary", "filename :${File(filePath).name} reason :$msg errorCode :$errorCode");
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    binding.uploadFailure.setVisibility(View.VISIBLE);
                    binding.uploadFailure.setText(String.format(getString(R.string.failure_info), new File(filePath).getName(), msg, String.valueOf(errorCode)));
                }
            });
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = DataBindingUtil.setContentView(this, R.layout.activity_hm_library);
        final String metadata =
//             "{filename:1.mp4, gps-latitude:28.674109, gps-longitude:77.438009, timestamp:20200309194530, uploadmode:normal}";/**/
                "{\"filename\":[\"1.mp4\"],\"gps-latitude\":\"28.674109\",\"gps-longitude\":\"77.438009\",\"timestamp\":\"20200309194530\",\"uploadmode\":\"normal\"}";

        String path1 = getExternalFilesDir("harman").getAbsolutePath() + "/" + "1.mp4";
        final String[] files = new String[]{path1};
        final String driverId = "Driver_1234";
        binding.start.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HmLibrary.getInstance().uploadFile(driverId, metadata, files, "", progress);
            }
        });

        binding.stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HmLibrary.getInstance().stopUpload();
            }
        });
    }
}
