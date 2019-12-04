//
//  ViewController.m
//  testSimple_old
//
//  Created by sijie.shen on 2019/12/04.
//  Copyright © 2019 djij-solution. All rights reserved.
//

#import "ViewController.h"
 #import "public/ios/include/CppLibManager.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.

     CppLibManager *testManager = [[CppLibManager alloc] init];
     [testManager trigerLib:-1];
}

@end
