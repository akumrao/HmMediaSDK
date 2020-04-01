//
//  ViewController.swift
//  SampleApp_HmLibrary
//
//  Created by Nidhi Sharma on 24/03/20.
//  Copyright © 2020 Harman Connected Services. All rights reserved.
//

import UIKit
import HmLibrary

class ViewController: UIViewController {

    @IBOutlet weak var uploadProgressLabel: UILabel!
    @IBOutlet weak var uploadSuccessLabel: UILabel!
    @IBOutlet weak var uploadFailureLabel: UILabel!
    var hmWrapper: HmWrapper?
    let videosArray = ["AppIntro_1", "AppIntro_2", "AppIntro_3", "AppIntro_4"]
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        hmWrapper = HmWrapper.init()
        hmWrapper?.delegate = self
    }

    @IBAction func startUpload(_ sender: Any) {
//        let resourcePath = Bundle.main.resourcePath
//        let subdir = URL(fileURLWithPath:resourcePath!).appendingPathComponent("MP4Files").path
        let randomElement = videosArray.randomElement()
        //let randomElement = videosArray[0]

        let mp4VideoPath = Bundle.main.path(forResource: randomElement, ofType: ".mp4")
        
        let mp4VideoPath1 = Bundle.main.path(forResource: videosArray[0], ofType: ".mp4") ?? ""
        let mp4VideoPath2 = Bundle.main.path(forResource: videosArray[1], ofType: ".mp4") ?? ""
        let mp4VideoPath3 = Bundle.main.path(forResource: videosArray[2], ofType: ".mp4") ?? ""
        let mp4VideoPath4 = Bundle.main.path(forResource: videosArray[3], ofType: ".mp4") ?? ""
        
        let pathsArr = [mp4VideoPath1, mp4VideoPath2, mp4VideoPath3, mp4VideoPath4]

        print("Random file: \(String(describing: mp4VideoPath))")
        if let videoFile = mp4VideoPath {
            hmWrapper?.uploadfilesArray = [videoFile]
        }
        //hmWrapper?.uploadfilesArray = pathsArr
//        hmWrapper?.stopUpload()
        hmWrapper?.startUpload(file: mp4VideoPath ?? "")
    }
    
    @IBAction func stopUpload(_ sender: Any) {
        hmWrapper?.stopUpload()
    }
}

extension ViewController: HmUploadDelegate {
    func uploadProgress(file: String, percentage: Int) {
        self.uploadProgressLabel.text = String("\(percentage) %")
    }
    
    func uploadSuccess(file: String, message: String) {
        self.uploadSuccessLabel.text = message
    }
    
    func uploadFailure(file: String, message: String) {
        self.uploadFailureLabel.text = message

    }
    
    
}

