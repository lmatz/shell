//
//  execute.h
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//

#ifndef __shell__execute__
#define __shell__execute__

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <glob.h>
#include "Interpreter.h"
#include "Builtin.h"

using namespace std;

//extern pid_t shell_pgid;
//extern struct termios shell_tmodes;
//extern int shell_terminal;
//extern int shell_is_interactive;

class job;



extern bool debug;

extern job * first_job;


extern glob_t wild_ex[3];

//extern char *commandstring[100];
//extern int num_com;
//extern int token_type[100];
//extern int pipe_num;
//extern char * argument[3][100];
//extern std::vector<std::string> symbol;
//extern char *current;
//extern char commandline[256];
//extern char * token;
//extern char * next;
//extern int num_current;
//extern int cd_arg;
//extern bool error_exception;
//
//
//
//extern int pipe_pos[3];
//extern int arg_len[3];
//extern bool suspend;

void execute() ;
void dirty_work();
void wait_child(int pid[],int fd[][2],char * command_);
void store_child(int pid[],int fd[][2], char * command_);



class Pipe_line {
public:
    Pipe_line(int num);
    bool set_pipe(int num);
    //	bool creatPipe(int);
    //	bool setPipe(int num);
    void close_all();
    int pipefd[3][2];
    int pipe_number;
};


class job{
public:
//    job(int pid[],int fd[][2]);
    job* next;
    int pids[3];
    int fd[2][2];
    char command[256];
//    job();
//    int getPid(int index);
//    string getCommand();
};











#endif /* defined(__shell__execute__) */
