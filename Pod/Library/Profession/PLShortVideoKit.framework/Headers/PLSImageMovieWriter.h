
// 参考 THImageMovieWriter

// GPUImage Video Merge: Fix Movie Writer
// http://tuohuang.info/gpuimage-video-merge-fix-movie-writer#.WkoFWSO75n4

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "PLSRenderEngine.h"

extern NSString *const kPLSImageColorSwizzlingFragmentShaderString;

@class PLSImageMovieWriter;
@protocol PLSImageMovieWriterDelegate <NSObject>

@optional
- (void)movieRecordingCompleted;
- (void)movieRecordingFailedWithError:(NSError*)error;
- (CVPixelBufferRef)imageMovieWriter:(PLSImageMovieWriter *)movieWriter willWritePixelBuffer:(CVPixelBufferRef)pixelBuffer timeStamp:(CMTime)timeStamp;

@end

@interface PLSImageMovieWriter: NSObject <PLSGPUImageInput>
{
    BOOL alreadyFinishedRecording;
    
    NSURL *movieURL;
    NSString *fileType;
	AVAssetWriter *assetWriter;
	AVAssetWriterInput *assetWriterAudioInput;
	AVAssetWriterInput *assetWriterVideoInput;

    
    PLSGPUImageContext *_movieWriterContext;
    CVPixelBufferRef renderTarget;
    CVOpenGLESTextureRef renderTexture;

    CGSize videoSize;
    PLSGPUImageRotationMode inputRotation;
}

@property (assign, nonatomic) AVMutableAudioMix *audioMix; // by suntongmian, 2018-01-01
@property(readwrite, nonatomic) BOOL hasAudioTrack;
@property(readwrite, nonatomic) BOOL shouldPassthroughAudio;
@property(readwrite, nonatomic) BOOL shouldInvalidateAudioSampleWhenDone;
@property(nonatomic, copy) void(^completionBlock)(void);
@property(nonatomic, copy) void(^failureBlock)(NSError*);
@property(nonatomic, assign) id<PLSImageMovieWriterDelegate> delegate;
@property(readwrite, nonatomic) BOOL encodingLiveVideo;
@property(nonatomic, copy) BOOL(^videoInputReadyCallback)(void);
@property(nonatomic, copy) BOOL(^audioInputReadyCallback)(void);
@property(nonatomic, copy) void(^audioProcessingCallback)(SInt16 **samplesRef, CMItemCount numSamplesInBuffer);
@property(nonatomic) BOOL enabled;
@property(nonatomic, readonly) AVAssetWriter *assetWriter;
@property(nonatomic, readonly) CMTime duration;
@property(nonatomic, assign) CGAffineTransform transform;
@property(nonatomic, copy) NSArray *metaData;
@property(nonatomic, assign, getter = isPaused) BOOL paused;
@property(nonatomic, retain) PLSGPUImageContext *movieWriterContext;

// add by hxiongan 2018-10-29
@property(nonatomic, assign) double sampleRate;
@property(nonatomic, assign) int audioBitrate;
@property(nonatomic, assign) int outputChannel;
@property(nonatomic, assign) AudioChannelLayoutTag outputChannelLayout;

// Initialization and teardown
- (id)initWithMovieURL:(NSURL *)newMovieURL size:(CGSize)newSize movies:(NSArray *)movies;// 不传 outputSettings 则默认 iOS 11.0 及以上系统使用 H265，iOS 11.0 以下使用 H264
- (id)initWithMovieURL:(NSURL *)newMovieURL size:(CGSize)newSize fileType:(NSString *)newFileType outputSettings:(NSDictionary *)outputSettings movies:(NSArray *)movies;

- (void)setHasAudioTrack:(BOOL)hasAudioTrack audioSettings:(NSDictionary *)audioOutputSettings;

// Movie recording
- (void)startRecording;
- (void)startRecordingInOrientation:(CGAffineTransform)orientationTransform;
- (void)finishRecording;
- (void)finishRecordingWithCompletionHandler:(void (^)(void))handler;
- (void)cancelRecording;
- (void)processAudioBuffer:(CMSampleBufferRef)audioBuffer;
- (void)enableSynchronizationCallbacks;

//===
@property(nonatomic) CGFloat audioWroteDuration, videoWroteDuration;
@property(nonatomic) CGFloat firstVideoFrameTime;

@property(nonatomic, retain) AVAssetWriterInputPixelBufferAdaptor *assetWriterPixelBufferInput;

@end
