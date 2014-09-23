/*
 * Builtin.h
 *
 *  Created on: 2014年9月20日
 *      Author: liuzhi
 */

#ifndef BUILTIN_H_
#define BUILTIN_H_

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <deque>
#include "Interpreter.h"
#include "execute.h"

using namespace std;

extern char * commandstring[100];


string getCurrentDic();
void builtin_cd();
void builtin_exit();

#endif /* BUILTIN_H_ */
