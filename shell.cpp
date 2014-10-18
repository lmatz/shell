//
//  main.cpp
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Interpreter.h"
#include "Builtin.h"
#include "execute.h"

bool debug=true;


int main() {
//    	signal(SIGINT,SIG_IGN);
    	signal(SIGTERM,SIG_IGN);
    	signal(SIGQUIT,SIG_IGN);
    	signal(SIGTSTP,SIG_IGN);
    printf("-----------------------shell start------------------------\n");
    while (1) {
        prompt();
        if (readthisline()){
            execute();
        }
    }
    return 0;
}
