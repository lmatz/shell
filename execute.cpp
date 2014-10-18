//
//  execute.cpp
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//

#include "execute.h"

using namespace std;



job_list * first_job=new job_list();

extern job_list * first_job;

bool suspend=false;

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
    dirty_work();
    string first_com=commandstring[0];
    if (first_com=="cd") {
        builtin_cd();
    }
    else if (first_com=="exit") {
        builtin_exit();
    }
    else if (first_com=="fg") {
        builtin_exit();
    }
    else if (first_com=="jobs") {
        builtin_jobs();
    }
    else if (token_type[0]==8){
        int loop=0;
        while (loop<=pipe_num) {
            if (debug) cout<<"enter the execute normal command"<<endl;
            pid_t test_p;
            char path[]="PATH=/bin:/usr/bin:./";
            putenv(path);
            test_p=fork();
            if (test_p==-1) {
                cout<<"Fork Failed"<<endl;
            }
            else if (test_p==0) {
//                signal(SIGINT,SIG_DFL);
                signal(SIGTSTP,SIG_DFL);
                if (debug) cout<<"child process's group id"<<getpgrp()<<endl;
//                if (debug) cout<<"enter the child"<<endl;
                for (int i=0;i<arg_len[loop];i++) {
                    cout<<"argument["<<loop<<"]["<<i<<"]: "<<argument[loop][i]<<"**"<<endl;
                }
                cout<<getpid()<<endl;
                if (execvp(commandstring[pipe_pos[loop]+1],argument[loop])==-1) {
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
            else if (test_p!=0) {
                int status;
                if (debug) cout<<"parent process's group id"<<getpgrp()<<endl;
                if (debug) cout<<"parent process id"<<getpid()<<endl;
                if (debug) cout<<"child process id"<<test_p<<endl;
                if (waitpid(test_p, &status, WUNTRACED)!=test_p) {
                    if (debug) cout<<"DAD doesn't get his CHILD!"<<endl;
                }
                else {
                    if (WIFSTOPPED(status)) {
                        //子进程被suspend了
                        job_list *temp=first_job;
                        for (;temp->next_job!=NULL;temp=temp->next_job) {
                        }
                        temp->next_job=new job_list(test_p, commandstring[pipe_pos[loop]+1]);
                        if (debug) {
                        cout<<temp->next_job->job_name<<endl;
                        cout<<temp->next_job->job_pid<<endl;
                        cout<<first_job->next_job->job_name<<endl;
                        cout<<first_job->next_job->job_pid<<endl;
                        }   
                        
                        if (debug) cout<<"put in the suspended job"<<endl;

                    }
                    else {
                        
                    }
                }
                if (debug) cout<<"This is father process"<<endl;
                ++loop;
            }
            if (debug) cout<<"****the "<<loop<<" command has been run***"<<endl;
        }
        
        job_list *tmp=first_job;
        

//    if (first_job->next_job!=NULL) {
//            tmp=first_job->next_job;
//        }
        
        for (int i=1;tmp->next_job!=NULL;tmp=tmp->next_job,i++) {
            cout<<i<<"  "<<tmp->next_job->job_pid<<endl;
        }
        if (debug) cout<<"listed job list"<<endl;
    }
    
    if (debug) cout<<"The execute part is over!!!"<<endl;
}





job_list::job_list() {
    job_name=NULL;
    job_pid=0;
    next_job=NULL;
}

job_list::job_list(pid_t pid, char * s) {
    job_name=new char[strlen(s)+1];
    strcpy(job_name,s);
    job_pid=pid;
    next_job=NULL;
}

job_list::~job_list(){
    free(job_name);
}






