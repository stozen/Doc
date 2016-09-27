//
//  NSString+Helper.h
//  KECallsAttribution
//
//  Created by EverZones on 16/3/30.
//  Copyright © 2016年 K.BLOCK. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSString (Helper)

/* 是否是Null */
- (BOOL)isNull ;
/* 是否为空字符(不包含任何字符,空格除外) */
- (BOOL)isEmpty ;

/* 去除空格 */
- (NSString *)trimWhitespace;
/* 包含的字符个数 */
- (NSUInteger)numberOfWords;
/* 将字符串倒序 */
- (NSString *)reverseString;


/* 是否包含某个字符串 */
- (BOOL)containsString:(NSString *)subString;
/* 是否以某个字符串开头 */
- (BOOL)isBeginsWith:(NSString *)string;
/* 是否以某个字符串结束 */
- (BOOL)isEndssWith:(NSString *)string;


/* 用新字符串替换旧的字符串 */
- (NSString *)replaceCharcter:(NSString *)olderChar withCharcter:(NSString *)newerChar;
/* 获取中间某段字符串 */
- (NSString*)getSubstringFrom:(NSInteger)begin to:(NSInteger)end;
/* 拼接字符串 */
- (NSString *)addString:(NSString *)string;
/* 移除子字符串 */
- (NSString *)removeSubString:(NSString *)subString;


/* 是否只包含字母 */
- (BOOL)containsOnlyLetters;
/* 是否只包含数字 */
- (BOOL)containsOnlyNumbers;
/* 是否只包含数字和字母 */
- (BOOL)containsOnlyNumbersAndLetters;


/* 将NSString转换成NSData,采用NSUTF8StringEncoding编码 */
- (NSData *)convertToData;
/* 将NSData转换成NSString */
+ (NSString *)getStringFromData:(NSData *)data;

/* 是否是邮箱地址 */
- (BOOL)isEmail;
/* 是否是电话号码 */
- (BOOL)isPhoneNumber;
@end
