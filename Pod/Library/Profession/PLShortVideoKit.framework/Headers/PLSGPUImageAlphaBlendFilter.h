#import "PLSGPUImageTwoInputFilter.h"

@interface PLSGPUImageAlphaBlendFilter : PLSGPUImageTwoInputFilter
{
    GLint mixUniform;
}

// Mix ranges from 0.0 (only image 1) to 1.0 (only image 2), with 1.0 as the normal level
@property(readwrite, nonatomic) CGFloat mix; 

@end
