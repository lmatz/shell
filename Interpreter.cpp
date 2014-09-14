/*
0: wrong input;
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

filename : 5 || 6
arg      : 5 || 6 || 7
built-in : 6
command  : 5

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Interpreter.h"


void delete_command() {
	while(num_com) {
		commandstring[num_com--]=NULL;
	}
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
	parse_command();
}

void readthisline() {
	if (fgets(commandline,256,stdin)!=NULL) {
		tokenize();
	}
}

void parse_command() {
	int i=0;
	int _count=num_com;
	while (_count--) {
		printf("%d : %s ",i,commandstring[i]);
		i++;
	}
	printf("\n");
}

bool term(char *string) {
	if (strcmp(commandstring[num_current++],string)==0) {
		return 1;
	}
	else {
		return 0;
	}
}


bool start() {
	token=commandstring[num_current];
	return (s1()||s2()||s3()||s4());
}

bool s1() {
	return 1;
}
bool s2() {
	return 1;
}
bool s3() {
	return 1;
}
bool s4() {
	return 1;
}

int check_commandname(char * str) {
	int len=strlen(str);
	bool star=false;
	char c;
	if (len==1) {
		c=str[0];
		switch(c) {
		case '|':return 1;
		case '<':return 2;
		case '>':return 3;
		}
	}
	if (len==2) {
		if (str[0]=='>' && str[1]=='>') return 4;
	}
}
