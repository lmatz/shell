//
//  Builtin.h
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//

#ifndef __shell__Builtin__
#define __shell__Builtin__

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <deque>
#include <signal.h>
#include <cstdlib>
#include "Interpreter.h"
#include "execute.h"

using namespace std;

//extern bool debug;

//extern char * commandstring[100];




string getCurrentDic();
void builtin_cd();
void builtin_exit();
void builtin_fg();
void builtin_jobs();


#endif /* defined(__shell__Builtin__) */
