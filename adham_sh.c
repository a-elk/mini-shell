#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFFER_SIZE 300

int returned;

char* lirebuff();
void exec(char*);
//void sig_handler(int);

int main(){
  char* buffer;
  while(1){
    printf("$ ");
 
    buffer = lirebuff();// fonction qui va redimensionner la taille de buffer

    if(strcmp(buffer,"echo $?") == 0)    //pour afficher la dernière valeur de retour
      printf("dernière valeur de retour :%d\n",returned); //0 si tout s'est bien passer 1 sinon 

    else{
      exec(buffer);
      free(buffer);
    }
    printf("\n");
  }
}

char* lirebuff(){
  char* buff = malloc(sizeof(char)*BUFFER_SIZE);
  fgets(buff,BUFFER_SIZE,stdin);
  char* ptr = buff;
  int i;
  for(i = 0;*ptr != '\n';++i)
    ptr++;
  *ptr = '\0';
  ptr--;
  while(*ptr == ' ')
    ptr--;
  ptr++;
  *ptr = '\0';
  return buff;
}

void  exec(char* buff){
  char* ptr = buff;
  int status = 0;
  int espace = 1;
  while(*ptr != '\0'){   // on va parser le buffer 
    if(*ptr == ' '){
      espace++;
      *ptr = '\0';
    }
    ptr++;
  }
  char** args = malloc(sizeof(char*)*espace+1);
  ptr = buff;
  for(int i = 0; i < espace;++i){            //on stock le pointeur de chaque mots du buffer
    args[i] = ptr;                           //dans un char ** 
    while(*ptr != '\0')
      ptr++;
    ptr++;
  }
  args[espace]=NULL;
  pid_t fils = fork();
  if(fils == -1){
    perror("fork");
    exit(EXIT_FAILURE);
  }
  if(fils == 0){
    if(execvp(args[0],args) == -1){
      perror("erreur commande");
      exit(EXIT_FAILURE);
    }
    free(args);
  }
  else{
    wait(&status);
    returned = WEXITSTATUS(status);
    if(!WIFEXITED(status))
      perror("erreur terminaison fils");
    free(args);
  }
}
