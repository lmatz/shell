#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Interpreter.h"



int main() {
//	signal(SIGINT,SIG_IGN);
//	signal(SIGTERM,SIG_IGN);
//	signal(SIGQUIT,SIG_IGN);
//	signal(SIGTSTP,SIG_IGN);
	printf("-----------------------shell start------------------------\n");
	while (1) {
		prompt();
		readthisline();
	}
}
