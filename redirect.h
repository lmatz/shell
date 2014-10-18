//
//  redirect.h
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//

#ifndef __shell__redirect__
#define __shell__redirect__

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

using namespace std;



class Pipe {
public:
    Pipe(int num);
    bool set_pipe(int num);
    //	bool creatPipe(int);
    //	bool setPipe(int num);
private:
    int pipefd[3][2];
    int pipe_num;
};






#endif /* defined(__shell__redirect__) */
