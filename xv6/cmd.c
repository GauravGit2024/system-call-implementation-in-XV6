#include "types.h"

#include "stat.h"

#include "user.h"

 

int main(int argc, char *argv[])

{

    if (argc < 2)

    {

        printf(1, "Usage: %s <program> [arguments...]\n", argv[0]);

        exit();

    }
	int n = argc;
    int pid = fork();
    if(pid == 0){
	char *args[n];
	for(int i=1; i<n; i++){
		//printf(1,"%s\n", argv[i]);
		args[i-1] = argv[i];
		// strcpy(args[i-1], argv[i]);
		// printf(1, "%s\n", args[i-1]);
	}
	// printf(1, "args: %s\n", args[0]);
	args[n-1] = 0;
	exec(args[0], args);
    }else {
	wait();
    }
	exit();

}
