//
//  Builtin.cpp
//  shell
//
//  Created by 刘智 on 14-10-12.
//  Copyright (c) 2014年 刘智. All rights reserved.
//

#include "Builtin.h"


using namespace std;


string getCurrentDic() {
    char cwd[1000];
    if(!getcwd(cwd,1000)){
        perror("Error: Cannot obtain current working directory");
        exit(EXIT_FAILURE);
    }
    return string(cwd);
}


void builtin_cd() {
    if (num_com==2) {
        string path=commandstring[1];
        string path_f;
        if (path[0]=='/') {
            path_f=path;
        }
        else if ( ( path.length()>1 && path[0]=='.' && path[1]=='/' ) || ( path[0]=='.' && path.length()==1 ) ) {
            path_f=getCurrentDic();
            string temp=path.substr(1,path.length());
            path_f.append(temp);
        }
        else if ( ( path.length()>2 && path[0]=='.' && path[1]=='.' && path[2]=='/' ) || ( path[0]=='.' && path[1]=='.' && path.length()==2 ) ) {
            path_f=getCurrentDic();
            unsigned long upper=path_f.find_last_of("/");
            path_f=path_f.substr(0,upper);
            path_f.append(path.substr(2,path.length()));
        }
        else {
            path_f=getCurrentDic();
            path_f.append("/").append(path);
        }
        const char * path_change=path_f.c_str();
        //		printf("%d",chdir(path_change));
        //		printf("Using cd Command!");
        if (chdir(path_change)) {
            cout<<"["<<path<<"]: cannot change directory\n";
        }
    }
}

void builtin_exit() {
    job *temp=first_job;
    if (temp->next==NULL) {
        fprintf(stdout,"[ Shell Terminated ]\n");
        exit(0);
    }
    else {
        fprintf(stdout,"There is at least one suspended job\n");
    }
}


void builtin_fg() {
    int i=1;
    int job_number=atoi(commandstring[1]);
    job * temp=first_job;
    if (first_job->next==NULL) {
        cout<<"fg: no such job"<<endl;
        return;
    }
    for (;i<job_number;i++) {
        temp=temp->next;
    }
    if (i==job_number) {

//        temp->next=temp->next->next;
        cout<<"ready to resume jobs"<<endl;
//准备resume suspended job
        cout<<"Job wake up: "<<temp->next->command<<endl;
        
        for (int pid_th=0;pid_th<3;pid_th++) {
            if (temp->next->pids[pid_th]!=-1) {
                if ( kill(temp->next->pids[i],SIGCONT) == -1) {
                    if (errno==EPERM) {
                        cout<<"does not have permission"<<endl;
                    }
                }
            }
        }
//维护job list
//        temp->next=temp->next->next;
        
        wait_child(temp->next->pids,temp->next->fd,temp->next->command);
        
        temp->next=temp->next->next;
    }
    else {
        cout<<"fg: no such job"<<endl;
    }
    cout<<"job_number"<<job_number<<endl;
}


void builtin_jobs() {
    job * temp=first_job;
    if (first_job->next==NULL) {
        cout<<"No suspended jobs"<<endl;
        return;
    }
    else {
        temp=temp->next;
        for (int i=1;temp!=NULL;temp=temp->next,i++) {
            cout<<"["<<i<<"] "<<temp->command;
        }
    }
}
