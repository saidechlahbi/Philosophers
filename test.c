#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    
    // close(fd);
    // int f = fork();
    // if (f == 0)
    // {
     
        
        // }else
        // {
            //     waitpid(f, NULL, 0);
            // }
            
            // int fd = open("file", O_CREAT | O_RDWR, 0777);
            // int a = dup(fd);
            // write (fd,"hello", 5);
            // char str[6];
            // read(a, str, 6);
            // printf("%s\n",str);

            int fd = open("file", O_CREAT | O_RDWR, 0777);
            int a = open("file", O_CREAT | O_RDWR, 0777);
            write (fd,"hello", 5);
            char str[6];
            read(a, str, 6);
            printf("%s\n",str);

}