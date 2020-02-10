//
//  PLSEffectDataManager.h
//  PLShortVideoKit
//
//  Created by 李政勇 on 2019/12/16.
//  Copyright © 2019 Pili Engineering, Qiniu Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

static NSString * const PLS_EFFECT_INTERNALKEY_SHARPE = @"sharp";                                   //锐化
static NSString * const PLS_EFFECT_INTERNALKEY_SMOOTH = @"smooth";                                  //磨皮
static NSString * const PLS_EFFECT_INTERNALKEY_WHITEN = @"whiten";                                  //美白

static NSString * const PLS_EFFECT_INTERNALKEY_FACEOVERALL = @"Internal_Deform_Overall";            //瘦脸
static NSString * const PLS_EFFECT_INTERNALKEY_EYE = @"Internal_Deform_Eye";                        //大眼

/*!
 @typedef PLSEffectType:
 @abstract   特效类型
 
 @since      v1.0.0
 */
typedef NS_ENUM(NSInteger, PLSEffectType) {
    PLSEffectTypeUndefined,
    
    PLSEffectTypeFilter,
    PLSEffectTypeSticker
};

/*!
 @typedef PLSMakeUpType:
 @abstract   美妆类型
 
 @since      v1.0.0
 */
typedef NS_ENUM(NSInteger, PLSMakeUpType) {
    PLSMakeUpTypeUndefined,
    
    PLSMakeUpTypeBeauty,        //美颜
    PLSMakeUpTypeReshape,       //美型
    
    PLSMakeUpTypeEnd
};

@class PLSEffectModel, PLSMakeUpComponentModel;

/*!
 @class PLSEffectDataManager
 @abstract 管理特效资源文件的类
 
 @discussion 若使用默认的资源文件层级结构，可使用此类获取各种效果的列表。
 */
@interface PLSEffectDataManager : NSObject

/*!
 @property rootPath
 @brief 资源文件根目录
 
 @since      v1.0.0
 */
@property (nonatomic, copy, readonly) NSString *rootPath;

- (instancetype)init NS_UNAVAILABLE;

/*!
 @method initWithRootPath:
 @abstract   初始化
 
 @param root 资源文件的根目录
 
 @since      v1.0.0
 */
- (instancetype)initWithRootPath:(NSString *)root NS_DESIGNATED_INITIALIZER;

/*!
 @method fetchEffectListWithType:
 @abstract   获取贴纸、滤镜列表
 
 @param type 类型
 
 @since      v1.0.0
 */
- (NSArray<PLSEffectModel *> *)fetchEffectListWithType:(PLSEffectType)type;

/*!
 @method fetchMakeUpComponentsWithType:
 @abstract   获取makeup列表
 
 @param type 类型
 
 @since      v1.0.0
 */
- (NSArray<PLSMakeUpComponentModel *> *)fetchMakeUpComponentsWithType:(PLSMakeUpType)type;

@end

NS_ASSUME_NONNULL_END
