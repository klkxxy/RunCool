//
//  Screenshots.h
//  RunCool-mobile
//
//  Created by lx on 2019/6/14.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface Screenshots : NSObject<UIAlertViewDelegate>
{
    

}
@property (nonatomic, strong) UIImage *image;
- (void)saveImage;



@end

NS_ASSUME_NONNULL_END
