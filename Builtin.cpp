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
    fprintf(stdout,"[ Shell Terminated ]\n");
    exit(0);
}


void builtin_fg() {
    
    

}


void builtin_jobs() {
    job_list *tmp=first_job;
    if (first_job->next_job!=NULL) {
        tmp=first_job->next_job;
    }
    for (int i=1;tmp->next_job!=NULL;tmp=tmp->next_job,i++) {
        cout<<"["<<i<<"]  "<<tmp->job_name;
    }
}
