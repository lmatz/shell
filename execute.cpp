//
//  execute.cpp
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//

#include "execute.h"

using namespace std;




job * first_job=new job();



bool suspend=false;


void dirty_work2 () {
    pipe_pos[0]=-1;
    int temp=1;
    int i=0;
    for ( i=0;i<num_com;i++ ) {
        if (token_type[i]==1) {
            ++pipe_num;
            pipe_pos[temp]=i;
            ++temp;
        }
    }
    
    if (debug) {
        cout<<"pipe_num"<<pipe_num<<endl;
        cout<<"com_num"<<num_com<<endl;
        cout<<"pipe_pos[0]"<<pipe_pos[0]<<endl;
    }
    
    if (debug) cout<<"enter the dirt_work2"<<endl;
    
    for ( i=0;i <= pipe_num;i++) {
        if (i!=pipe_num) {
            int start=pipe_pos[i]+2;
            wild_ex[i].gl_offs=0;
//            int argument_len=pipe_pos[i+1]-(pipe_pos[i]+2);
//            wild_ex[i].gl_pathv[0]=commandstring[pipe_pos[i]+1];
            while (start<pipe_pos[i+1]) {
                wild_ex[i].gl_offs=1;
                bool flag=true;
                if (flag) {
                    if (glob(commandstring[start], GLOB_DOOFFS | GLOB_NOCHECK , NULL , &wild_ex[i])) {
                        if (debug) cout<<"glob function fails"<<endl;
                    }
                }
                else {
                    if (glob(commandstring[start], GLOB_DOOFFS | GLOB_NOCHECK | GLOB_APPEND  , NULL , &wild_ex[i])) {
                        if (debug) cout<<"glob function fails"<<endl;
                    }
                }
                flag=false;
                ++start;
            }
            if (wild_ex[i].gl_offs==0) {
                glob(commandstring[start-1], GLOB_DOOFFS | GLOB_NOCHECK , NULL , &wild_ex[i]);
            }
            else {
                wild_ex[i].gl_pathv[0]=commandstring[pipe_pos[i]+1];
            }
            if (debug) cout<<"that step:<<endl"<<endl;
        }
        else if (i==pipe_num) {
            int start=pipe_pos[i]+2;
            wild_ex[i].gl_offs=0;
            while (start<num_com) {
                wild_ex[i].gl_offs=1;
                bool flag=true;
                if (flag) {
                    if (glob(commandstring[start], GLOB_DOOFFS | GLOB_NOCHECK , NULL , &wild_ex[i])) {
                        if (debug) cout<<"glob function fails"<<endl;
                    }
                }
                else {
                    if (glob(commandstring[start], GLOB_DOOFFS | GLOB_NOCHECK | GLOB_APPEND  , NULL , &wild_ex[i])) {
                        if (debug) cout<<"glob function fails"<<endl;
                    }
                }
                flag=false;
                ++start;
            }
            if (wild_ex[i].gl_offs==0) {
                glob(commandstring[start-1], GLOB_DOOFFS | GLOB_NOCHECK , NULL , &wild_ex[i]);
            }
            else {
                wild_ex[i].gl_pathv[0]=commandstring[pipe_pos[i]+1];
            }
            if (debug) cout<<"that step:<<endl"<<endl;
        }
    }
}











// 将pipe的位置弄出来，才能将argument弄出来。
void dirty_work() {
    pipe_pos[0]=-1;
    int temp=1;
    int i=0;
    for ( i=0;i<num_com;i++ ) {
        if (token_type[i]==1) {
//            if (debug) cout<<"find a pipe at  "<<i<<endl;
            ++pipe_num;
            pipe_pos[temp]=i;
            ++temp;
        }
    }
//    if (debug) {
//        for (int i=1;i<=pipe_num;i++) {
//            cout<<"pipe position at "<<pipe_pos[i]<<endl;
//        }
//    }
    
    
    for ( i=0;i <= pipe_num;i++) {
        
//        if (debug) cout<<"fuck the shit!!!"<<endl;
        argument[i][0]=commandstring[pipe_pos[i]+1];
        temp=1;
        if (i!=pipe_num) {
            for (int j= pipe_pos[i]+2;j<pipe_pos[i+1];j++) {
                argument[i][temp]=commandstring[j];
                if (debug) cout<<argument[i][temp]<<"   "<<endl;
                ++temp;
            }
            argument[i][temp]=NULL;
            arg_len[i]=temp;
        }
        if (i==pipe_num) {
            for (int j=pipe_pos[pipe_num]+2;j<num_com;j++) {
                argument[i][temp]=commandstring[j];
                if (debug) cout<<argument[i][temp]<<"   "<<endl;
                ++temp;
            }
            argument[i][temp]=NULL;
            arg_len[i]=temp;
        }
        
    }
    
}



void execute() {
//    dirty_work();
    dirty_work2();
    string first_com=commandstring[0];
    if (first_com=="cd") {
        builtin_cd();
    }
    else if (first_com=="exit") {
        builtin_exit();
    }
    else if (first_com=="fg") {
        builtin_fg();
    }
    else if (first_com=="jobs") {
        builtin_jobs();
    }
    else if (token_type[0]==8){
        if (debug) cout<<commandline;
        Pipe_line all_pipe(pipe_num);
        int loop=0;
        int fd[2][2];
        pid_t all_pid[3];
        
        
        memset(all_pid,-1,sizeof(all_pid));
        
        if (debug) {
            for (int i=0;i<3;i++) {
                cout<<all_pid[i]<<endl;
            }
        }
        
        if (debug) cout<<"pipe_num"<<pipe_num<<endl;
        
        while (loop<=pipe_num) {
            
            if (debug) cout<<"enter the execute normal command"<<endl;
            

            char path[]="PATH=/bin:/usr/bin:./";
            putenv(path);
            pid_t new_pgid;
            all_pid[loop]=fork();
            
            if (all_pid[loop]==-1) {
                cout<<"Fork Failed"<<endl;
            }
            
            else if (all_pid[loop]==0) {
                all_pipe.set_pipe(loop);
                new_pgid=getpid();
                
                signal(SIGINT,SIG_DFL);
                signal(SIGTERM,SIG_DFL);
                signal(SIGQUIT,SIG_DFL);
                signal(SIGTSTP,SIG_DFL);
//              signal (SIGCHLD, SIG_DFL);
                
                if (debug) cout<<"child process's group id"<<getpgrp()<<endl;
                if (debug) cout<<"enter the child"<<endl;
                
//                for (int i=0;i<arg_len[loop];i++) {
//                    cout<<"argument["<<loop<<"]["<<i<<"]: "<<argument[loop][i]<<"**"<<endl;
//                }
                if (debug) cout<<"child process's id"<<getpid()<<endl;
                if (execvp(commandstring[pipe_pos[loop]+1],/*argument[loop]*/wild_ex[loop].gl_pathv)==-1) {
                    cout<<"no opeartion"<<endl;
                    if(errno==ENOENT)
                    {
                        cout<<"["<<commandstring[0]<<"]"<<": command not found\n";
                    }
                    else
                    {
                        cout<<commandstring[0]<<": unknown error\n";
                    }
                    exit(-1);
                }
            }
            else if (all_pid[loop]!=0) {
                if (debug) cout<<"parent process's group id"<<getpgrp()<<endl;
                if (debug) cout<<"parent process id"<<getpid()<<endl;
                if (debug) cout<<"child process id"<<all_pid[loop]<<endl;

                if (debug) cout<<"This is father process"<<endl;
                ++loop;
            }
            
            
            if (debug) cout<<"****the "<<loop<<" command has been run***"<<endl;
        }
        
        if (pipe_num==2) {
            fd[0][0]=all_pipe.pipefd[0][0];
            fd[0][1]=all_pipe.pipefd[0][1];
            fd[1][0]=all_pipe.pipefd[1][0];
            fd[1][1]=all_pipe.pipefd[1][1];
        }
        else if (pipe_num==1) {
            fd[0][0]=all_pipe.pipefd[0][0];
            fd[0][1]=all_pipe.pipefd[0][1];
            fd[1][0]=-1;
            fd[1][1]=-1;
//            cout<<"fd[0][0]"<<fd[0][0]<<endl;
//            cout<<"fd[0][1]"<<fd[0][1]<<endl;
        }
        else if (pipe_num==0) {
            fd[0][0]=-1;
            fd[0][1]=-1;
            fd[1][0]=-1;
            fd[1][1]=-1;
        }
        
        if (debug) cout<<"ready to wait child"<<endl;
        wait_child(all_pid,fd,save_commandline);
        
    }
    if (debug) cout<<"The execute part is over!!!"<<endl;
}


void store_child(int pid[],int fd[][2],char * command_) {
    job * temp=first_job;
    job * store_one=new job();
    
        for (;temp->next!=NULL;temp=temp->next) {
        }
    
        for (int i=0;i<3;i++) {
            store_one->pids[i]=pid[i];
        }
        for (int i=0;i<2;i++) {
            for (int j=0;j<2;j++) {
                store_one->fd[i][j]=fd[i][j];
            }
        }
        strcpy(store_one->command,command_);
        if (debug) cout<<command_;
        store_one->next=NULL;
        temp->next=store_one;
}


void wait_child(int all_pid[],int fd[][2],char * command_) {
    int status;
    int store_all_pid[3];
    for (int i=0;i<3;i++) {
        store_all_pid[i]=all_pid[i];
        if (debug) {
            cout<<"pid["<<i<<"]: "<<store_all_pid[i]<<endl;
        }
    }
    int store_fd[2][2];
    for (int i=0;i<2;i++) {
        for (int j=0;j<2;j++) {
            store_fd[i][j]=fd[i][j];
            if (debug) {
                cout<<"fd["<<i<<"]["<<j<<"]: "<<fd[i][j]<<endl;
            }
        }
    }
    for (int i=0;i<3;i++) {
        if (all_pid[i]!=-1) {  
            if (waitpid(all_pid[i], &status, WUNTRACED)!=all_pid[i]) {
                    if (debug) cout<<"DAD doesn't get his CHILD!"<<endl;
            }
            else {
                if (WIFSTOPPED(status)) {
                    //子进程被suspend了
                    store_child(store_all_pid,store_fd,command_);
                    if (debug) {
                        cout<<"has suspended"<<endl;
                    }
//                    fflush(stdin);
//                    fflush(stdout);
                    cout<<endl;
                    return ;
                }
                else if (WIFEXITED(status)) {
//                    cout<<endl;
                }
                else {
                    switch(i) {
                        case 0:
                            if (fd[0][1]!=-1) {
                                close(fd[0][1]);
                            }
                            break;
                        case 1:
                            if (fd[0][0]!=-1) {
                                close(fd[0][0]);
                            }
                            if (fd[1][1]!=-1) {
                                close(fd[1][1]);
                            }
                            break;
                        case 2:
                            if (fd[1][0]!=-1) {
                                close(fd[1][0]);
                            }
                            break;
                    }
                }
            }
        }
    }
}







//************************************************************************

Pipe_line::Pipe_line(int num) {
    pipe_number=num;
    for(int i=0; i<num; i++) {
        if(pipe(pipefd[i])!=0)
        {
            cout<<"Pipe failed\n";
            exit(0);
        }
    }
}


bool Pipe_line::set_pipe(int num) {
    if (pipe_number==0)
        return true;
    if (num==0) {
        //这是第一个pipe
        if (dup2(pipefd[num][1],STDOUT_FILENO)==-1) {
            cout<<"Set The Fisrst Pipe Fail\n";
            return false;
        }
        close(pipefd[num][1]);
    }
    else if (num==pipe_number) {
        //这是最后一个pipe
        for (int i=0;i<num-1;i++) {
            close(pipefd[i][0]);
            close(pipefd[i][1]);
        }
        close(pipefd[num-1][1]);
        if (dup2(pipefd[num-1][0],STDIN_FILENO==-1)) {
            cout<<"Set The Last Pipe Fail\n";
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
            cout<<"Set Middle Pipe Fail\n";
            return false;
        }
        close(pipefd[num-1][0]);
        if (dup2(pipefd[num][1],STDIN_FILENO)==-1){
            cout<<"Set Middle Pipe Fail\n";
            return false;
        }
        close(pipefd[num][1]);
    }
    return true;
}


void Pipe_line::close_all() {
    for (int i=0;i<pipe_number;i++) {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }
}



//job::job(int pid[3], int fd[][2]) {
//    
//}





