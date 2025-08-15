#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFSIZE 512

void ping_pong(int fd) 
{
   //char *pong = "pong";
   char buffer[BUFSIZE]; 
   int count = 0;
   char temp[517]; // this is to handle the breaks in input when a new buffer i loaded
   while(1){
	int bytes_read = read(fd, buffer, BUFSIZE);
	if(bytes_read == 0){
		break;
	}
	for(int j=5; j<517; j++){
		temp[j] = buffer[j-5];    // store the buffer in temp array from 6th index. the first 6 will be loaded from the previous buffer
	} 
	for(int i=0; i<bytes_read; i++){
		while(temp[i] != 'p' && i<bytes_read){
			i++;
		}
		if(temp[i-1] == ' ' || temp[i-1] == '.'){
			if(temp[i+1]=='i' && temp[i+2]=='n'&& temp[i+3]=='g'){
				printf(1, "%s\n", "pong");
				i +=3 ;
				count += 1;
		}
			/*	i++;
			if(buffer[i] == 'i'){
				i++;
				if(buffer[i]=='n'){
					i++;
					if(buffer[i]=='g'){
						if(buffer[i+1]==' '){
							printf(1, "%s\n", pong);
						}
					}
				}
			}*/
		}
	}
	// store the last 6 characters so that if input is broken in between, it can be handled
	temp[4] = buffer[511];temp[3] = buffer[510]; temp[2]=buffer[509]; temp[1]=buffer[508];temp[0]=buffer[507];
   }
//    printf(1, "%d\n", count);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf(1, "Usage: %s <input_file>\n", argv[0]);
        exit();
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf(1, "Error opening file %s\n", argv[1]);
        exit();
    }

    ping_pong(fd);
    close(fd);

    exit();
}
