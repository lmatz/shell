//
//  redirect.cpp
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//
#include "redirect.h"



Pipe::Pipe(int num) {
    pipe_num=num;
    //	pipePos=0;
    //	comPos=0;
    for(int i=0; i<num; i++) {
        if(pipe(pipefd[i])!=0)
        {
            cout<<"Pipe failed\n";
            exit(0);
        }
    }
}


bool Pipe::set_pipe(int num) {
    
    if (pipe_num==0)
        return true;
    if (num==0) {
        //这是第一个pipe
        if (dup2(pipefd[num][1],STDOUT_FILENO)==-1) {
            cout<<"Set Pipe Fail\n";
            return false;
        }
        close(pipefd[num][1]);
    }
    else if (num==pipe_num) {
        //这是最后一个pipe
        for (int i=0;i<num-1;i++) {
            close(pipefd[i][0]);
            close(pipefd[i][1]);
        }
        close(pipefd[num-1][1]);
        if (dup2(pipefd[num-1][0],STDIN_FILENO==-1)) {
            cout<<"Set Pipe Fail\n";
            return false;
        }
        //最后一个pipe弄好了。
        close(pipefd[num-1][0]);
    }
    else {
        for (int i=0;i<num-1;i++) {
            close(pipefd[i][0]);
            close(pipefd[i][1]);
        }
        close(pipefd[num-1][1]);
        if (dup2(pipefd[num-1][0],STDIN_FILENO)==-1){
            cout<<"Set Pipe Fail\n";
            return false;
        }
        close(pipefd[num-1][0]);
        if (dup2(pipefd[num][1],STDIN_FILENO)==-1){
            cout<<"Set Pipe Fail\n";
            return false;
        }
        close(pipefd[num][1]);
    }
    return true;
}





