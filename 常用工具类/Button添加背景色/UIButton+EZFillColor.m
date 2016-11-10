//
//  UIButton+EZFillColor.m
//  MyContacts
//
//  Created by 赵 进喜 on 15/1/28.
//  Copyright (c) 2015年 everzones. All rights reserved.
//

#import "UIButton+EZFillColor.h"

@implementation UIButton (EZFillColor)
- (void)setBackgroundColor:(UIColor *)backgroundColor forState:(UIControlState)state {
    [self setBackgroundImage:[UIButton imageWithColor:backgroundColor] forState:state];
}

+ (UIImage *)imageWithColor:(UIColor *)color {
    CGRect rect = CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return image;
}

@end
