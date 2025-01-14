//
//  NTOneKeyCutoutTool.h
//  GTRPImageCoreEngine
//
//  Created by Jormungande World Serpent on 28/4/2021.
//  Copyright © 2021 Jormungande World Serpent. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@interface NTEYPoint : NSObject
/// 坐标点类型
@property (nonatomic, assign) CGPathElementType type;
/// X轴坐标
@property (nonatomic, assign) CGFloat x;
/// Y轴坐标
@property (nonatomic, assign) CGFloat y;

+ (instancetype)pointWithX:(CGFloat)x y:(CGFloat)y type:(CGPathElementType)type;

@end


@interface NTEYDrawStepModel : NSObject
/// 起点
@property (nonatomic, assign) CGPoint startPoint;
/// 终点
@property (nonatomic, assign) CGPoint endPoint;
@end

@interface NTOneKeyCutoutTool : NSObject
/// 初始化实例对象
/// @param image 图像
/// @param maskMaxWidth [mask遮罩画布]宽度最大值(数值越大绘制越精细,内核负担也越大,一般设置1000px即可)
+ (instancetype)initWithImage:(UIImage*)image maskMaxWidth:(CGFloat)maskMaxWidth;
/// 整体画布大小
@property (nonatomic, assign, readonly) CGSize layerSize;
/// [mask遮罩画布]的尺寸
@property (nonatomic, assign, readonly) CGSize maskSize;

/// 自动获取物体轮廓图(通过热力算法)
/// @param inputImage 输入图像
/// @param success 处理成功的回调函数
/// @param failure 处理失败的回调函数
- (void)autoObjectContour:(UIImage *)inputImage success:(void (^__nullable)(UIImage *resultImage))success failure:(void (^__nullable)(NSError* error))failure;

/// 自动获取物体轮廓图(通过热力算法)
/// @param inputImage 输入图像
/// @param success 处理成功的回调函数
/// @param failure 处理失败的回调函数
- (void)autoObjectContourWithInputImage:(UIImage *)inputImage success:(void (^__nullable)(UIImage *resultImage))success failure:(void (^__nullable)(NSError* error))failure;


- (void)adjustBorderWithWidth:(CGFloat)width density:(CGFloat)density completion:(void (^__nullable)(UIImage *resultImage))completion;

- (void)adjustBorderWithWidth:(CGFloat)width density:(CGFloat)density
                     minAlpha:(CGFloat)minAlpha maxAlpha:(CGFloat)maxAlpha hardness:(CGFloat)hardness
                   completion:(void (^__nullable)(UIImage *resultImage))completion;

/// 设置 背景图像
/// @param image 背景图像
- (void)setBackgroundImage:(UIImage*)image;
/// 设置 叠加效果图
/// @param image 效果图
- (void)setEffectImage:(UIImage*)image;
/// 设置 叠加效果图(不刷新Mask)
/// @param effectImage 效果图
- (void)setEffectImageWithOutRefreshMask:(UIImage*)effectImage;
/// 设置 mask遮罩图
/// @param image mask遮罩图
- (void)setMaskImage:(UIImage*)image;

/// 画笔大小(1~550 备注:不能超过550)
@property (nonatomic, assign) CGFloat brushWidth;
/// 画笔硬度(范围 : 0.0 ~ 1.0)
@property (nonatomic, assign) CGFloat hardness;
/// 画笔透明度最小值(默认0.2)
@property (nonatomic, assign) CGFloat minAlpha;
/// 画笔透明度最大值(默认1.0)
@property (nonatomic, assign) CGFloat maxAlpha;
/// 画笔类型的枚举
typedef NS_ENUM(NSInteger, NTDWBrushType) {
    NTDWBrushType_Paint = 1001,///<[绘画笔]模式
    NTDWBrushType_Eraser = 1002,///<[橡皮擦]模式
};
/// 画笔类型
@property (nonatomic, assign) NTDWBrushType brushType;

/// 初始化 [混合画布](背景+叠加效果)的纹理Texture对象
- (void)initCombineTexture;

/// 更新 [叠加效果]的纹理Texture对象
- (void)overlayTextureRender;
/// 更新[混合画布](背景+绘画画板)的纹理Texture对象
- (void)combineTextureRender;
/// 更新 [临时缓存]combineTexture[混合画布]的纹理Texture对象
- (void)cacheTextureRender;
/// 清空mask遮罩纹理的所有内容
- (void)clearMaskTexture;
/// 画线方法
/// @param start 开始点
/// @param end 结束点
/// @param vertexCount 绘点平均数量
-(void)renderLineFromPoint:(CGPoint)start toPoint:(CGPoint)end vertexCount:(CGFloat)vertexCount;
/// 预备绘画
/// @param start 开始点
/// @param end 结束点
/// @param vertexCount 绘点数量
- (void)prepareFromPoint:(CGPoint)start toPoint:(CGPoint)end vertexCount:(CGFloat)vertexCount;
/// 通过缓存点集渲染图像
- (void)renderByCachePoints;

/// 获取渲染缓存区的纹理对象
- (GLuint)getTextureID;
/// 获取OpenGLES遮罩图
- (UIImage*)getMaskImageOfRender;
/// 获取最终mask遮罩图
/// @desc (该方法将释放OpenGLES所有内存用于最终mask遮罩图渲染,即OpenGLES需要重新初始化才能对图像进行再次渲染)
/// @param maskSize mask遮罩图尺寸(CGSizeZero即为图像原尺寸)
- (UIImage*)getLastMaskImage:(CGSize)maskSize;
/// 获取OpenGLES渲染图像
- (UIImage*)getImageOfRender;
/// 获取最终结果图
/// @desc (该方法将释放OpenGLES所有内存用于最终结果图渲染,即OpenGLES需要重新初始化才能对图像进行再次渲染)
/// @param imageSize 图像尺寸(CGSizeZero即为图像原尺寸)
- (UIImage*)getLastResultImage:(CGSize)imageSize;
@end

NS_ASSUME_NONNULL_END
