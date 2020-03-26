package com.harman.testsdk

import android.Manifest
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.databinding.DataBindingUtil
import com.harman.hmmediasdkapp.FileUploadListener
import com.harman.hmmediasdkapp.HmLibrary
import com.harman.testsdk.databinding.ActivityMainBinding
import java.io.BufferedReader
import java.io.File
import java.io.FileReader
import kotlin.properties.Delegates


class MainActivity : AppCompatActivity() {
    private val RECORD_REQUEST_CODE = 101
    var startTime : Long = 0L
    var endTime : Long = 0L
    private val progress: FileUploadListener = object : FileUploadListener {
        override fun uploadProgress(filePath: String?, percent: Int) {
            Log.d("HmLibrary", "filename :${File(filePath).name} percent :$percent")
            runOnUiThread {
                binding.uploadProgress.visibility = View.VISIBLE
                binding.uploadProgress.text = String.format(
                    getString(R.string.upload_progress),
                    File(filePath).name,
                    percent.toString()
                )
            }
        }

        override fun uploadSuccess(filePath: String?, msg: String?) {
            Log.d("HmLibrary", "filename :${File(filePath).name} reason :$msg")
            runOnUiThread {
                binding.uploadSuccess.visibility = View.VISIBLE
                binding.uploadSuccess.text =
                    String.format(getString(R.string.success_info), File(filePath).name, msg)
                endTime = System.currentTimeMillis()
                Log.d("HmLibrary", "upload time: ${(endTime - startTime) / 1000}")
            }
        }

        override fun uploadFailure(filePath: String?, msg: String?, errorCode: Int) {
            Log.d(
                "HmLibrary",
                "filename :${File(filePath).name} reason :$msg errorCode :$errorCode"
            )
            runOnUiThread {
                binding.uploadFailure.visibility = View.VISIBLE
                binding.uploadFailure.text = String.format(
                    getString(R.string.failure_info),
                    File(filePath).name,
                    msg,
                    errorCode.toString()
                )
            }
        }
    }
    lateinit var binding: ActivityMainBinding
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = DataBindingUtil.setContentView(this, R.layout.activity_main)
        setupPermissions()

        binding.browse.setOnClickListener {
            val intent = Intent()
                .setType("video/*")
                .setAction(Intent.ACTION_GET_CONTENT)

            startActivityForResult(Intent.createChooser(intent, "Select a file"), 111)
        }

        binding.stop.setOnClickListener {
            HmLibrary.getInstance().stopUpload()
        }
    }

    private fun uploadFile(
        driverId: String,
        metadata: String,
        files: List<String>,
        authToken: String
    ) {
        startTime = System.currentTimeMillis()
        HmLibrary
            .getInstance()
            .uploadFile(driverId, metadata, files.toTypedArray(), authToken, progress)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)

        if (requestCode == 111 && resultCode == RESULT_OK) {
            val selectedFile = data?.data //The uri with the location of the file
            val path: String = RealPathUtil.getRealPath(this, selectedFile!!)!!
            Log.d(
                "HmLibrary",
                "selected file :$selectedFile path :$path"
            )
            val currenttime = System.currentTimeMillis()
            val file = (1..4).random()
            val name = File(path).name
            val fileSize = File(path).length()

            val sizeInMb = fileSize / (1024.0 * 1024)

            val sizeInMbStr = "%.2f".format(sizeInMb)

            Log.d("HmLibrary", "Size=${sizeInMbStr}MB")

            val metadata =
                "{\"filename\":[\"$name\"],\"gps-latitude\":\"28.674109\",\"gps-longitude\":\"77.438009\",\"timestamp\":\"$currenttime\",\"uploadmode\":\"normal\"}"
            val ran = (0..1000).random()
            val files = listOf(path)//, path4/*, path2, path2, path3, path4*/)
            val driverId = "driver_$ran"
            Log.d("HmLibrary", "driverId : $driverId filename: $path")
            val authToken = ""
            uploadFile(driverId, metadata, files, authToken)
        }
    }

    private fun setupPermissions() {
        val permission = ContextCompat.checkSelfPermission(this,
            Manifest.permission.READ_EXTERNAL_STORAGE)

        if (permission != PackageManager.PERMISSION_GRANTED) {
            Log.i("HmLibrary", "Permission denied")
            makeRequest()
        }
    }

    private fun makeRequest() {
        ActivityCompat.requestPermissions(this,
            arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE),
            RECORD_REQUEST_CODE)
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        when (requestCode) {
            RECORD_REQUEST_CODE -> {

                if (grantResults.isEmpty() || grantResults[0] != PackageManager.PERMISSION_GRANTED) {

                    Log.i("HmLibrary", "Permission has been denied by user")
                } else {
                    Log.i("HmLibrary", "Permission has been granted by user")
                }
            }
        }
    }
}