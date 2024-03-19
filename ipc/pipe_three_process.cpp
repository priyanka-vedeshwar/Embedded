
/*
    Program to demostrate piping of three process 
    i.e user input in form of string | greap ea | sort
*/
//refernce : https://www.rozmichelle.com/pipes-forks-dups/

#include <iostream>
#include <unistd.h>
int main(){
    int pipe1[2];
    int pid1;
    if (pipe(pipe1) < 0 ){
        std::cout<<"Error creating pipe";
        return 0;
    }
    pid1 = fork();
    if (pid1 == 0){
            //child process
            dup2(pipe1[0],0); //connect output of pipe1 to the std input of child#1 
            close(pipe1[0]); //close output end of pipe1 to child#1
            close(pipe1[1]); //close input to pipe1 from child#1
            int pipe2[2];
            int pid2;
            //create second pipe
            if (pipe(pipe2) < 0 ){
                std::cout<<"Error creating pipe";
                return 0;
            }
            pid2 = fork();
            //fork child at child#1
            if(pid2 == 0){
                //child of child [say child#2]
                dup2(pipe2[0],0); //connect output of pipe2 to std input of child#2
                close(pipe2[0]); //close output of pipe2 to child#2
                close(pipe2[1]); //close input to pipe#2 from child#2
                system("sort");   
            }
            //child#1
            dup2(pipe2[1],1); //connect std output of child#1 to input to pipe#2
            close(pipe2[0]); //close input to child#1 from pipe#2
            system("grep ea");
            close(pipe2[1]); //close output to pipe#2 from child#1 to indicate end of input from child#1
    }else{
        //parent process
        close(pipe1[0]); //close input to parent process from pipe#1
        char *words[]={"Zeal","Bear","Ate","Love"};
        for (auto str : words){
            dprintf(pipe1[1],"%s\n",str); //write data to pipe#1 from parent process
        }
        close(pipe1[1]); //close input to pipe#1 from parent to indicate end of input from parent process
    }

   return 0;
}
