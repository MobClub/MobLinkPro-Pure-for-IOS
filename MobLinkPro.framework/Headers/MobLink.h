//
//  MobLink.h
//  MobLink
//
//  Created by chenjd on 16/11/14.
//  Copyright © 2016年 Mob. All rights reserved.
//  Offline

#import <Foundation/Foundation.h>
#import "IMLSDKRestoreDelegate.h"

@class MLSDKScene;
NS_ASSUME_NONNULL_BEGIN
typedef void(^MLSDKResultHandler)(NSString *_Nullable mobid, NSString *_Nullable domain, NSError *_Nullable error);

@interface MobLink : NSObject

/**
 获取MobId
 
 @param scene 当前场景信息(即传入您需要还原的场景)
 @param resultHandler 回调处理,返回mobid
 */
+ (void)getMobId:(nullable MLSDKScene *)scene result:(MLSDKResultHandler)resultHandler;

/**
 设置场景恢复委托
 
 @param delegate 委托对象
 */
+ (void)setDelegate:(id <IMLSDKRestoreDelegate>)delegate;


/**
 universallink回调
 当app由universallink拉起时调用此方法
 
 需在系统调用下列方法时调用
 
 iOS13及以下未适配UIScene ： AppDelegate
 - (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray<id<UIUserActivityRestoring>> * _Nullable))restorationHandler;
 
 适配UIScene：SceneDelegate
 - (void)scene:(id)scene willConnectToSession:(UISceneSession *)session options:(UISceneConnectionOptions *)connectionOptions
 - (void)scene:(UIScene *)scene continueUserActivity:(NSUserActivity *)userActivity;
 当app由scheme拉起时需传入此方法
 */
+ (void)application:(id)application continueUserActivity:(NSUserActivity *)userActivity;

/**
 universallink回调
 
 需在系统调用下列方法时调用
 当app由scheme拉起时需传入此方法
 
 iOS13及以下未适配UIScene ： AppDelegate
 - (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url;
 - (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;
 - (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options;
 
 适配UIScene：SceneDelegate
 - (void)scene:(id)scene willConnectToSession:(UISceneSession *)session options:(UISceneConnectionOptions *)connectionOptions
 - (void)scene:(UIScene *)scene openURLContexts:(NSSet<UIOpenURLContext *> *)URLContexts;
 
 */
+ (void)application:(id)application handleOpenURL:(NSURL *)url;


/**
 MobLink 版本号
 
 @return 当前版本号
 */
+ (NSString *)sdkVer;

@end
NS_ASSUME_NONNULL_END
