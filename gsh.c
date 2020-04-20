#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BUFF_S 1024
#define DELIM " \t\n\r"



char **split_line(char *line){
	int buffsize = BUFF_S , position = 0;
	char **args = malloc(sizeof(buffsize) * sizeof(char *));
	char *arg;
	if(!args){
		perror("args");
		exit(EXIT_FAILURE);}
	
	arg = strtok(line,DELIM);
	while(arg != NULL){
		args[position] = arg;
		position++;

		if(position >= buffsize){
			buffsize += BUFF_S;
			args = realloc(args,buffsize*sizeof(char*));
			if(!args){
				perror("args");
				exit(EXIT_FAILURE);}}
		arg = strtok(NULL,DELIM);
	}
	args[position] = NULL;
	return args;
}

void cd(char *path){
	int stat;
	if(path == NULL){
		 stat = chdir(getenv("HOME"));}
	else{ stat = chdir(path);}

	if(stat == -1){
		perror("cd");
	}
}

void gexit(){
	exit(EXIT_SUCCESS);
}

int main(){
	char *line,*prompt=" => ";
	while(1){
		char * pwd = getcwd(0,0);
		strcat(pwd,prompt);
		line = readline(pwd);
		if(strcmp(line,"")==0){free(line) ; continue;}
		if(strcmp(line,"exit")==0){free(line); gexit();}
		add_history(line);
		char **args=split_line(line);

			if(strcmp(args[0],"cd")==0){
				cd(args[1]);
				free(line);
				continue;}


			pid_t cpid = fork();
			if(cpid == 0){
				if((execvp(args[0],args)) < 0){
					perror("gsh");}
			}if(cpid > 0){wait(NULL);}


		free(line);
		free(args);
		}
	}
