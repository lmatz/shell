/*
99: wrong input;
15: not determined
1 : '|'
2 : '<'
3 : '>'
4 : '>>'
5 : filename or arg or command
6 : built-in or arg or filename
7 : arg with star
8 : command
9 : built-in
10: input filename
11: output filename
12: arg without star
13: empty
filename : 5 || 6
arg      : 5 || 6 || 7
built-in : 6
command  : 5
*/
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <deque>
#include "Interpreter.h"

using namespace std;

char *commandstring[100];
int num_com=0;


// 将token类型转换为相对应的symbol。因为刚读入时无法判断具体情况，parse万之后有改动。
void type_to_symbol() {
	int _count=0;
	while (_count< num_com) {
		switch(token_type[_count]) {
		case 1:
			symbol.push_back("Pipe");
			break;
//		case 2:
//			break;
//		case 3:
//			break;
//		case 4:
//			break;
		case 5:
			symbol.push_back("Command Name");
			break;
		case 6:
			symbol.push_back("Argument");
			break;
		case 7:
			symbol.push_back("Argument");
			break;
		case 8:
			symbol.push_back("Command Name");
			break;
		case 9:
			symbol.push_back("Built-in Command");
			break;
//		case 10:
//			break;
//		case 11:
//			break;
		case 12:
			symbol.push_back("Argument");
			break;
		default:
			symbol.push_back("Not decide yet");
		}
		_count++;
	}
}



void format_print() {
	int i;
	for (i=0;i<num_com;i++) {
		printf("Token %d: \"%s\" ",i+1,commandstring[i]);
	cout<<"("<<symbol[i]<<")";
	cout<<endl;
	}
}




//将每次读入的commandstring和token_type重置。
void delete_command() {
	while(num_com) {
		commandstring[num_com--]=NULL;
	}
	for (int i=0;i<99;i++) {
		token_type[i]=-1;
	}
	symbol.clear();
	num_current=0;
	error_exception=false;
}

//prompt
void prompt() {
	delete_command();
	printf("[3150 shell:%s]$", getCurrentDic().c_str());
}

//将command line分成一个一个token放入commandstring。
void tokenize() {
	char *pch;
	pch=strtok(commandline," \n");
	while (pch!=NULL) {
		commandstring[num_com++]=pch;
		pch=strtok(NULL," \n");
	}
}

//读入commandline，调用tokennize，然后判断是否复合语法及pipe个数，输出错误信息。
bool readthisline() {
	bool flag;
	if (fgets(commandline,256,stdin)!=NULL) {
		tokenize();
	}
	checktype();
	flag=start();
	for (int i=0;i<num_com;i++) {
		printf("%d ",token_type[i]);
	}

	if ( flag && checkpipe()) {
		for (int i=0;i<num_com;i++) {
					printf("%d ",token_type[i]);
		}
		cout<<endl;
		type_to_symbol();
		format_print();
		printf("Correct!!!\n");
		return true;
	}
	else if(error_exception) {
		return false;
	}
	else {
		fprintf(stdout, "Error: invalid input command line\n");
		return false;
	}
}

//调用check_command，将token分类，并且按格式输出。
void checktype() {
	int i;
	if (num_com==0) {
		return;
	}
	for (i=0;i<num_com;i++) {
		token_type[i]=check_commandname(commandstring[i]);
	}
	for (i=0;i<num_com;i++) {
			printf("%d ",token_type[i]);
	}
	cout<<endl;
}

//检查pipe个数，不超过或等于3个。
bool checkpipe() {
	int i;
	int count=0;
	for (i=0;i<num_com;i++) {
		if (token_type[i]==1) {
			++count;
		}
	}
	if (count>=3) {
		return 0;
	}
	return 1;
}

//将token分类，但是对builtin的要另外考虑*****还没完成
int check_commandname(char * str) {
	string same_str(str);
	int len=same_str.length();
	bool star=false;
	char c;
	if (len==0) {
		return 13;
	}
	if (len==1) {
		c=str[0];
		switch(c) {
		case '|':return 1;
		case '<':return 2;
		case '>':return 3;
		case '*':return 7;
		}
	}
	if (len==2) {
		if (str[0]=='>' && str[1]=='>') return 4 ;
	}
	if (same_str=="cd" || same_str=="exit" || same_str=="fg" || same_str=="jobs") return 6 ;
	for (int i=0; i<len; i++)
	{
		c=str[i];
		if (c==9 || c==32 || c==62 || c==60 || c==124 || c==33 || c==96 ||c==39 || c==34) return 99;
		if (c==42) star=true;
	}
	if (star) return 7;
	else return 5;
}




//以下是个recursive descent parser。
bool start() {
	return ( s1() || s2() || s3() || s4() );
}


bool s1() {
	if (token_type[num_current]==-1) {
		return 1;
	}
	return 0;
}
bool s2() {
	bool cd_check=false;
	bool exit_check=false;
	int arg=0;
	int record=num_current;
	if (token_type[num_current]==6||token_type[num_current]==9) {
		string same_str(commandstring[num_current]);
		if (same_str=="cd") {
			error_exception=true;
			cd_check=true;
		}
		if (same_str=="exit") {
			error_exception=true;
			exit_check=true;
		}
		token_type[num_current]=9;
		++num_current;
		while (token_type[num_current]==5||token_type[num_current]==6||token_type[num_current]==7) {
			if (cd_check) {
				arg+=1;
			}
			if (exit_check) {
				arg+=1;
			}
			if (token_type[num_current]!=7) {
				token_type[num_current]=12;
			}
			++num_current;
		}
		if ( (cd_check) && (arg==0 || arg>=2) ) {
			fprintf(stdout,"cd: wrong number of arguments\n");
			return 0;
		}
		if ( (exit_check) && arg!=0) {
			fprintf(stdout,"exit: wrong number of arguments\n");
			return 0;
		}
		return 1;
	}
	num_current=record;
	return 0;
}
bool s3() {
	int record=num_current;
	if ( command() && recursive()) {
		++num_current;
		return 1;
	}
	num_current=record;
	return 0;
}
bool s4() {
	int record=num_current;
	if ( command() && term() ){
		return 1;
	}
	num_current=record;
	return 0;
}

bool recursive() {
	int record=num_current;
	if (token_type[num_current]==1) {
		++num_current;
		if ( command() && ( recursive() || term() )) {
			++num_current;
			return 1;
		}
	}
	num_current=record;
	return 0;
}

bool command() {
	int record=num_current;
	if (token_type[num_current]==5||token_type[num_current]==8) {
		token_type[num_current]=8;
		++num_current;
		while (token_type[num_current]==5||token_type[num_current]==6||token_type[num_current]==7||token_type[num_current]==12) {
			if (token_type[num_current]!=7) {
				token_type[num_current]=12;
			}
			++num_current;
		}
		return 1;
	}
	num_current=record;
	return 0;
}

bool term() {
	if (token_type[num_current]==-1) {
		return 1;
	}
	return 0;
}




