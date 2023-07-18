/* test_shmat2.c */
/* exemplo de utilizacao de shmat() 
* escrita num segmento de memoria compartilhada */
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define ADDKEY 123
#define MSG "Mensagem escrita na memoria comum"

int main() {
  int shmid ; /* identificador da memória comum */
  int size = 1024 ;
  char *path="nome_de_arquivo_existente" ;
  //char *path="./" ;
  char *mem ;
  int flag = 0 ;

/* recuperação do shmid */
  if (( shmid = shmget(ftok(path,ADDKEY), size,0)) == -1) {
        perror("Erro no shmget") ;
        exit(1) ; }
  printf("Sou o processo com pid: %d \n",getpid()) ;
  printf("Identificador do segmento recuperado: %d \n",shmid) ;
  printf("Este segmento e associado a chave unica: %d\n",
  ftok(path,ADDKEY)) ;
/* acoplamento do processo ao segmento de memória */
  if ((mem = shmat (shmid, 0, flag)) == (char*)-1){
       perror("acoplamento impossivel") ;
       exit (1) ;}
/* tratamento do conteúdo do segmento */
  printf("leitura do segmento de memória compartilhada:\n");
  printf("\t==>%s\n",mem) ;
  sleep(1000);
  exit(0);
}
