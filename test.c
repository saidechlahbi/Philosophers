#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int ac, char **av, char **env)
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
            // close(0);
            int fd = open("file", O_CREAT | O_RDWR, 0777);
            // int a = open("file", O_CREAT | O_RDWR, 0777);
            // write (fd,"hello", 5);
            // char str[6];
            // read(a, str, 6);
            // write(1, "hello", 5);
            // dup2(fd, 1);
            // write(1, "hello", 5);
            // printf("%d\n",fd);
            // int ff = fork();
            // int fd[2];
            // pipe(fd);
            // printf("%d %d \n", fd[0], fd[1]);
            // if (ff == 0)
            // {
            dup2(fd, 1);
                char *str[] = {"l",  NULL};
                
                char *s = "/usr/bin/ls";
                
                execve(s,str , env);
            // }else
            // {
            //     printf("hello\n");
            //     waitpid(ff, NULL, 0);
            // }
            
        // waitpid(fd, &c, 0);
}