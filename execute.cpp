/*
 * execute.cpp
 *
 *  Created on: 2014年9月21日
 *      Author: liuzhi
 */
//#include <stdio.h>
//#include <iostream>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string>
//#include <vector>
//#include <deque>
#include "execute.h"

using namespace std;



void execute() {
	string first_com=commandstring[0];
	if (first_com=="cd") {
		builtin_cd();
	}
	if (first_com=="exit") {
		builtin_exit();
	}

}





