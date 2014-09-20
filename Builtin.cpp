#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <deque>
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
			int upper=path_f.find_last_of("/");
			path_f=path_f.substr(0,upper);
			path_f.append(path.substr(2,path.length()));
		}
		else {
			path_f=getCurrentDic();
			path_f.append("/").append(path);
		}
		const char * path_change=path_f.c_str();
		if (chdir(path_change)) {
			cout<<"["<<path<<"]: cannot change directory";
		}
	}

}
