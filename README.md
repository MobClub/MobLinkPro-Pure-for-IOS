# MobLinkPro-Pure-for-IOS
MoblinkPro 无Hook版本


安装:

```
pod 'mob_linksdk_pro_pure'
```



这里是moblinkPro不hook系统方法的版本，需要开发者自己在scheme或universallink跳转时，将事件传递给MoblinkPro，来进行接下来的处理。

如果您没有适配UIScene分屏，则在Appdelegate调用以下方法


```
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url{
    [MobLink application:application handleOpenURL:url];
    return YES;;
}

- (BOOL)application:(UIApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void (^)(NSArray<id<UIUserActivityRestoring>> * _Nullable))restorationHandler{
    [MobLink application:application continueUserActivity:userActivity];
    return YES;
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation{
    [MobLink application:application handleOpenURL:url];
    return YES;
}

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options{
    [MobLink application:app handleOpenURL:url];
    return YES;
}
```

如果您适配了UIScene分屏，则在SceneDelegate调用下列方法

```
- (void)scene:(id)scene willConnectToSession:(UISceneSession *)session options:(UISceneConnectionOptions *)connectionOptions API_AVAILABLE(ios(13.0)){
   self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
   self.window.backgroundColor = [UIColor whiteColor];
   [self.window makeKeyAndVisible];
   [self.window showOnScene:scene];
    
    //在此处理是因为适配 UIScene后，冷启动App，不会走下面两个方法，需要在此处获取冷启动参数，并处理
    [MobLink application:scene continueUserActivity:connectionOptions.userActivities.anyObject];
    [MobLink application:scene handleOpenURL:connectionOptions.URLContexts.anyObject.URL];
}

- (void)scene:(UIScene *)scene openURLContexts:(NSSet<UIOpenURLContext *> *)URLContexts API_AVAILABLE(ios(13.0)){
    [MobLink application:scene handleOpenURL:URLContexts.anyObject.URL];
}


- (void)scene:(UIScene *)scene continueUserActivity:(NSUserActivity *)userActivity API_AVAILABLE(ios(13.0)){
    [MobLink application:scene continueUserActivity:userActivity];
}

```

MobLink如果有场景还原事件发生，会回调代理:

```
- (void)IMLSDKWillRestoreScene:(MLSDKScene *)scene Restore:(void (^)(BOOL, RestoreStyle))restoreHandler
{
    dispatch_async(self.guideQueue, ^{
        if (!self.isAlreadyRun)
        {
            dispatch_semaphore_wait(self.guideSemaphore, DISPATCH_TIME_FOREVER);
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            restoreHandler(YES, MLPush);
        });
    });
    // 发送场景还原记录
    if (scene.params && [scene.params isKindOfClass:[NSDictionary class]])
    {
        NSString *otherId = scene.params[@"id"];
        if (otherId)
        {
            MLDSceneType sourceType = MLDSceneTypeOthers;
            if (scene.params[@"scene"])
            {
                sourceType = [scene.params[@"scene"] integerValue];
            }
            [[MLDNetworkManager sharedManager] sendSceneLogWithCurrentUserID:[MLDUserManager sharedManager].currentUserId otherUserID:otherId sourceType:sourceType completion:^(BOOL success) {
                if (success)
                {
                    NSLog(@"上传场景记录成功");
                }
            }];
        }
    }
```

>注意，这个方法回调有可能不在主线程，如果开发者操作UI，需要自己切回主线程执行
>
>
>
>```
>- (void)IMLSDKWillRestoreScene:(MLSDKScene *)scene Restore:(void (^)(BOOL, RestoreStyle))restoreHandler
>{
>    dispatch_async(dispatch_get_main_queue(), ^{
        
>    });
> }
>```
