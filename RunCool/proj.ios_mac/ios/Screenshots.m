//
//  Screenshots.m
//  RunCool-mobile
//
//  Created by lx on 2019/6/14.
//

#import "Screenshots.h"

@implementation Screenshots
- (void)saveImage
{
    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    self.image = [self snapshot:window];
    
    UIAlertView * alert = [[UIAlertView alloc]initWithTitle:@"创造新纪录" message:@"是否要保存你创造记录的精彩瞬间？" delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"保存到相册", nil];
    [alert show];
    

    
}

-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    NSLog(@"clickButtonAtIndex:%ld",(long)buttonIndex);
    
    if(buttonIndex == 1){
        
        UIImageWriteToSavedPhotosAlbum(self.image, self, @selector(savingImageIsFinished:didFinishSavingWithError:contextInfo:), nil);
    }
    
}


- (UIImage *)snapshot:(UIView *)view
{
    UIGraphicsBeginImageContextWithOptions(view.bounds.size, YES, 0);
    [view drawViewHierarchyInRect:view.bounds afterScreenUpdates:YES];
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
    
}


-(void) savingImageIsFinished:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo
{
    if (error) {
        UIAlertView *alert
        = [[[UIAlertView alloc] initWithTitle:@"保存失败"
                                      message:@"请查看设置－>隐私－>照片中的APPName是否被允许存储照片。" delegate:nil
                            cancelButtonTitle:nil otherButtonTitles:@"OK", nil] autorelease];
        [alert show];
        
    } else {
        UIAlertView *alert
        = [[[UIAlertView alloc] initWithTitle:@"保存成功"
                                      message:@"请在相册中查看保存的图片。" delegate:nil
                            cancelButtonTitle:nil otherButtonTitles:@"OK", nil] autorelease];
        [alert show];
        
    }
    
    
}

@end
