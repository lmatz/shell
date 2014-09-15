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
#include <io.h>
#include <string.h>
#include <string>
#include < direct.h.>
#include "Interpreter.h"

using namespace std;

void delete_command() {
	while(num_com) {
		commandstring[num_com]=NULL;
		token_type[num_com--]=-1;
	}
	num_current=0;
}


void prompt() {
	delete_command();
	printf("[3150 shell:%s]$", getcwd(current,256));
}

void tokenize() {
	char *pch;
	pch=strtok(commandline," \n");
	while (pch!=NULL) {
		commandstring[num_com++]=pch;
		pch=strtok(NULL," \n");
	}
}

void readthisline() {
	if (fgets(commandline,256,stdin)!=NULL) {
		tokenize();
	}
	parse_command();
	checktype();
	if (start()) {
		printf("valid!\n");
	}
	else {
		printf("invalid\n");
	}
}

void parse_command() {
	int i=0;
	int _count=num_com;
	while (_count--) {
		printf("%d : %s ",i,commandstring[i]);
		i++;
	}
	if (num_com!=0) {
		printf("\n");
	}
}

void checktype() {
	int i;
	for (i=0;i<num_com;i++) {
		token_type[i]=check_commandname(commandstring[i]);
	}
	for (i=0;i<num_com;i++) {
		printf("%d  ",token_type[i]);
	}
	if (num_com!=0) {
		printf("\n");
	}
}



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


bool start() {
	return (s1()||s2()||s3()||s4());
}


bool s1() {
	if (token_type[num_current]==-1) {
		return 1;
	}
	return 0;
}
bool s2() {
	if (token_type[num_current]==6||token_type[num_current]==9) {
		token_type[num_current]=9;
		++num_current;
		if ( token_type[num_current]==5) {
			++num_current;
			return 1;
		}
	}
	return 0;
}
bool s3() {
	if (command()) {
		if ( recursive()||term() ) {
			
		}
	}
	return 0;
}
bool s4() {
	return 0;
}

bool recursive() {
	return 0;
}

bool command() {
	if (token_type[num_current]==5||token_type[num_current]==8) {
		token_type[num_current]==8;
		++num_current;
		if (token_type[num_current]==5||token_type[num_current]==6||token_type[num_current]==7) {
			++num_current;
			return 1;
		}
	}
	return 0;
}

bool term() {
	return 0;
}
