//
//  HmSdkWrapper.h
//  HmLibrary
//
//  Created by Nidhi Sharma on 30/03/20.
//  Copyright © 2020 Harman Connected Services. All rights reserved.
//

#import <Foundation/Foundation.h>
@class HmWrapper;
NS_ASSUME_NONNULL_BEGIN

@interface HmSdkWrapper : NSObject
@property (nonatomic, assign) NSString *oAuthToken;
@property (nonatomic, assign) NSArray *uploadfilesArray;
@property (nonatomic, assign) NSString *driverId;
@property (nonatomic, assign) HmWrapper *delegate;


- (HmSdkWrapper *) init;
- (void) upload: (NSString *) driverId metaDataJson: (NSString *)metaDataJson file:(NSString *)file;
- (void) stopUpload;
- (void) checkUploadProgress: (NSString *) file percentage: (NSInteger) percentage;
- (void) checkUploadSuccess: (NSString *) file message: (NSString *) message;
- (void) checkUploadFailure: (NSString *) file message: (NSString *) message;

@end

NS_ASSUME_NONNULL_END
