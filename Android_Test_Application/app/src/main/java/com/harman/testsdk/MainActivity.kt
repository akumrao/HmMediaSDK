package com.harman.testsdk

import android.opengl.Visibility
import android.os.Bundle
import android.util.Log
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import com.harman.hmmediasdkapp.FileUploadListener
import com.harman.hmmediasdkapp.HmLibrary
import com.harman.testsdk.databinding.ActivityMainBinding
import java.io.BufferedReader
import java.io.File
import java.io.FileReader
import kotlin.random.Random

class MainActivity : AppCompatActivity() {
//    companion object {
//        init {
//            System.loadLibrary("libupload");
//        }
//    }

    private val progress: FileUploadListener = object : FileUploadListener {
        override fun uploadProgress(filePath: String?, percent: Int) {
            Log.d("HmLibrary", "filename :${File(filePath).name} percent :$percent")
            runOnUiThread {
                binding.uploadProgress.visibility = View.VISIBLE
                binding.uploadProgress.text = String.format(getString(R.string.upload_progress), File(filePath).name, percent.toString())
            }
        }

        override fun uploadSuccess(filePath: String?, msg: String?) {
            Log.d("HmLibrary", "filename :${File(filePath).name} reason :$msg")
            runOnUiThread  {
                binding.uploadSuccess.visibility = View.VISIBLE
                binding.uploadSuccess.text = String.format(getString(R.string.success_info), File(filePath).name, msg)
            }
        }

        override fun uploadFailure(filePath: String?, msg: String?, errorCode: Int) {
            Log.d("HmLibrary", "filename :${File(filePath).name} reason :$msg errorCode :$errorCode")
            runOnUiThread {
                binding.uploadFailure.visibility = View.VISIBLE
                binding.uploadFailure.text = String.format(getString(R.string.failure_info), File(filePath).name, msg, errorCode.toString())
                }
        }
    }
    lateinit var binding: ActivityMainBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.setContentView(this, R.layout.activity_main)
        //                displayView.setText("");

        binding.start.setOnClickListener {
            val metadata =
             "{filename:[1.mp4], gps-latitude:28.674109, gps-longitude:77.438009, timestamp:20200309194530, uploadmode:normal}";
//                "{\"filename\":\"1.mp4\",\"gps-latitude\":\"28.674109\",\"gps-longitude\":\"77.438009\",\"timestamp\":\"20200309194530\",\"uploadmode\":\"normal\"}"
//            val metadata =
////                "{filename:["1.mp4","2.mp4"],"gps-latitude":"28.674109","gps-longitude":"77.438009","timestamp":"20200309194530","uploadmode":"normal"}";
//                "{filename:[1.mp4, 2.mp4], gps-latitude:28.674109, gps-longitude:77.438009, timestamp:20200309194530, uploadmode:normal}";

            val ran = Random(1000)
            val path1 = getExternalFilesDir("harman")?.absolutePath + "/" + "1.mp4"
            val path2 = getExternalFilesDir("harman")?.absolutePath + "/" + "2.mp4"
            val path3 = getExternalFilesDir("harman")?.absolutePath + "/" + "3.mp4"
            val path4 = getExternalFilesDir("harman")?.absolutePath + "/" + "4.mp4"
            val f = File(path1);
            val b = f.isFile;
            try {
                val r = BufferedReader(FileReader(f));
                val s = r.readLine();
                Log.d("TAG", s)
            } catch (e: Exception) {
                e.printStackTrace();
            }
            val files = listOf(path1/*, path2, path2, path3, path4*/)
            val driverId = "Driver_${ran.nextInt()}"
            HmLibrary
                .getInstance()
                .uploadFile(driverId, metadata, files.toTypedArray(), "", progress)

            binding.stop.setOnClickListener {
                HmLibrary.getInstance().stopUpload()
            }
        }
    }
}