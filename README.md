*Android Build* 


To build source code git clone --recursive https://github.com/akumrao/HmMediaSDK.git

for git 2.3 later git clone --recurse-submoduleshttps://github.com/akumrao/HmMediaSDK.git

git submodule update --init

cd HmMediaSDK/Andriod/app/src/main/cpp/mediaserver
git checkout master
git pull

open project  Andriod at Android studio

Manifest changes

<uses-permission android:name="android.permission.INTERNET" />

<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE"/>

 
      Please put .mp4 videos at sdcard in this path and test it.
 
   Path : /storage/emulated/0/Android/data/com.harman
   
connect mobile phone to usb or run emulator

adb devices

List of devices attached

emulator-5554 device

run app from Android Studio



*IOS Build*

brew install cmake

To build source code git clone --recursive https://github.com/akumrao/HmMediaSDK.git

for git 2.3 later git clone --recurse-submoduleshttps://github.com/akumrao/HmMediaSDK.git

git submodule update --init

cd IOS/mediaserver

cd IOS/

git checkout master
git pull

mkdir build

cd build

cmake ..

cd ..

cp test.mp4 from any location

make

run ./runUpload

*Logs*


Android Log logcats search for jnilog

Remote and Console logging is possible.

Right now AWS logging is not supported.


