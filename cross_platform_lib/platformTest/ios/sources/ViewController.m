//
//  ViewController.m
//  testSimple_old
//
//  Created by sijie.shen on 2019/12/04.
//  Copyright © 2019 djij-solution. All rights reserved.
//

#import "ViewController.h"
#import "public/ios/include/CppLibManager.h"

@interface ViewController () {
    CppLibManager *_testManager;
}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.

    _testManager = [[CppLibManager alloc] init];
    [_testManager trigerLib:3];
    
    [_testManager initWithView:self.view];
}

@end
