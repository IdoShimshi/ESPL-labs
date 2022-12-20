#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int fd[2];
    pipe(fd); //turn fd to a pipe. fd[0] -> read end, fd[1] -> write end.
    pid_t pid = fork();
    
    if (pid == 0){ //child 
        char* message = "hello\n";
        close(fd[0]); 
        close(1); //close stdout
        dup(fd[1]); // open fd[1] instead of the stdout
        write(1, message, 7); //write the msg to the "stdout" (actually wrties to fd[1])
    }
    else if (pid > 0){ // parent
        wait(NULL); //wait for the child to die
        close(0);
        close(fd[1]);
        dup(fd[0]);
        char incoming_msg[7];
        int n = read(0, incoming_msg, 7); //read the child msg from the pipe
        for(int i =0; i < n; i++){
            printf("%c", incoming_msg[i]);
        }
        exit(0);

    }
    else{ //basa
        perror("Bad PID. basa");
    }









}