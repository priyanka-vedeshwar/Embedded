
/*
    Program to demostrate piping of two process 
    Example, command in form of string | grep 
*/
//refernce : https://www.rozmichelle.com/pipes-forks-dups/

#include <iostream>
#include <unistd.h>
int main(){
    int pipe1[2];
    int pid1;
    if (pipe(pipe1) < 0 ){
        std::cout<<"Error creating pipe\n";
        return 0;
    }
    pid1 = fork();
    if (pid1 == 0){
            //child process
            dup2(pipe1[0],0); //connect output end of pipe1 to the std input of child process
            close(pipe1[0]); //close output end of pipe1 to child as it's no longer required
            close(pipe1[1]); //close input to pipe1 from child
            //To grep "ea" from the string provided.
            system("grep ea");
    }else{
        //parent process
        close(pipe1[0]); //close output end of pipe1 at parent 
        char *words[]={"Zeal","Bear","Ate","Love"};
        for (auto str : words){
            dprintf(pipe1[1],"%s\n",str); //write to pipe
        }
        close(pipe1[1]); //close input to pipe1 from parent to signify end of input from parent process
    }

   return 0;
}
