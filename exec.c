int main(){
  char* buffer;
  printf(">");
  buffer = readbuff();
  printf("buffer :%s\n",buffer);
  exec(buffer);
  //printf("buffer :%s\n",buffer);
  free(buffer);
}

char* readbuff(){
  char* buff = malloc(sizeof(char)*BUFFER_SIZE);
  char* ptr = buff;
  fgets(buff,BUFFER_SIZE,stdin);
  int i;
  for(i = 0;*ptr != '\0' && *ptr != '\n';++i){
    ptr++;
  }
  memset(ptr,'\0',1);
  return buff;
}

void exec(char* buff){
  char* ptr = buff;
  char command[30];
  int i = 0,j = 0;
  for(i=0;*ptr != ' ';++i){
    ptr++;
  }
  strncpy(commande,buff,i);
  command[i] = '\0';
  ptr++;
  char* ptr2 = ptr;
  while(*ptr2 != '\0'){  //j will contain the number of arguments 
    if(*ptr2 == ' ')
      j++;
    ptr2++;
  }
  char** args = malloc(sizeof(char*)*j);
  char** ptrarg = args;
  for(int i = 0;i < j;i++){
    *ptrarg = ptr;
    while(*ptr !=  ' ')
      ptr++;
    ptr++;
    ptrarg ++;
  }

  pid_t son = fork();
  if(son == 0){ //son
    execvp(command,args);
    free(buff);
    free(args);
  }
  free(args);
}
