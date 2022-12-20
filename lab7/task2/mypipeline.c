#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    int temp;
    int debug = 0; //false
    int pipe_fd[2];
    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "-d") == 0){
            debug = 1; //true
            break;
        }
    }
    int pipe_res = pipe(pipe_fd); //1
    if (pipe_res == -1){
        perror("Error");
        exit(-1);
    }
    if(debug == 1)
        fprintf(stderr,"(parent_process>forking…)\n");

    pid_t child1 = fork(); //2

    if(debug == 1)
        fprintf(stderr,"(parent_process>created process with id: %d)\n", child1);

    switch (child1)
    {
    case -1:
        perror("Error");
        exit(-1);

    case 0:
        if(debug == 1){
            fprintf(stderr,"(child1>redirecting stdout to the write end of the pipe…)\n");
            fprintf(stderr,"(child1>going to execute cmd: …)\n");
        }
        close(1); //3.1 - close stdout
        dup(pipe_fd[1]); //3.2 - dup write end

        if(debug == 1)
            fprintf(stderr,"(parent_process>closing the write end of the pipe…)\n");

        close(pipe_fd[1]); //3.3 - close the fd that was duped
        execlp("ls", "ls", "-l", (char*) NULL); //3.4 - exec ls -l //?
        break;

    default: //parent
        if(debug == 1)
            fprintf(stderr,"(parent_process>closing the write end of the pipe…)\n");

        close(pipe_fd[1]); //4
        pid_t child2 = fork(); //5
        switch(child2)
        {
        case -1:
            perror("Error");
            exit(-1);

        case 0:
            if(debug == 1){
                fprintf(stderr,"(child2>redirecting stdout to the write end of the pipe…)\n");
                fprintf(stderr,"(child2>going to execute cmd: …)\n");
            }
            close(0); //6.1 - close stdin
            dup(pipe_fd[0]); //6.2 - dup read end
            if(debug == 1)
                fprintf(stderr,"(parent_process>closing the read end of the pipe…)\n");

            close(pipe_fd[0]); //6.3 - close the fd that was duped
            execlp("tail", "tail", "-n", "2", (char *) NULL); //6.4
            break;
        default:
            if(debug == 1)
                fprintf(stderr,"(parent_process>closing the read end of the pipe…)\n");

            close(pipe_fd[0]); //7- close read end

            if(debug == 1)
                fprintf(stderr,"(parent_process>waiting for child process to terminate…)\n");

            int return_value = waitpid(child1, &temp, WUNTRACED | WCONTINUED); //?
            if (return_value == -1){
                perror("Error");
                if(debug == 1)
                    fprintf(stderr,"(parent_process>exiting…)\n");
                exit(-1);
            }

            if(debug == 1)
                fprintf(stderr,"(parent_process>waiting for child process to terminate…)\n");

            return_value = waitpid(child2, &temp, WUNTRACED | WCONTINUED); //?
            if(return_value == -1){
                perror("Error");
                exit(-1);
            }
            if(debug == 1)
                fprintf(stderr,"(parent_process>exiting…)\n");
            break;
        }

        break;
    }
}