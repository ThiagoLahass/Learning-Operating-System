#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
// Neste exemplo, supõe-se que o segmento de memória compartilhada tem a chave de acesso 123 utilizada no Exemplo 1.


#define ADDKEY 123

struct shmid_ds buf ;

int main() {
 	char *path="nome_de_arquivo_existente" ;
	//char *path="./" ;
	int shmid ;
	int size = 1024 ;
	/* recuperação do identificador do segmento associado à chave 123 */
	if (( shmid = shmget(ftok(path,(key_t)ADDKEY),size,0)) == -1 ) {
		perror ("Erro shmget()") ;
		exit(1) ; }
	/* recuperação das informações relativas ao segmento */
	if ( shmctl(shmid,IPC_STAT,&buf) == -1){ perror("Erro shmctl()") ;
		exit(1) ;}
	printf("ESTADO DO SEGMENTO DE MEMORIA COMPARTILHADA %d\n",shmid) ;
	printf("ID do usuario proprietario: %d\n",buf.shm_perm.uid) ;
	printf("ID do grupo do proprietario: %d\n",buf.shm_perm.gid) ;
	printf("ID do usuario criador: %d\n",buf.shm_perm.cuid) ;
	printf("ID do grupo criador: %d\n",buf.shm_perm.cgid) ;
	printf("Modo de acesso: %d\n",buf.shm_perm.mode) ;
	printf("Tamanho da zona de memoria: %ld\n",buf.shm_segsz) ;
	printf("pid do criador: %d\n",buf.shm_cpid) ;
	printf("pid (ultima operacao): %d\n",buf.shm_lpid) ;
	/* destruicao do segmento */
	if ((shmctl(shmid, IPC_RMID, NULL)) == -1){ perror("Erro shmctl()") ;
		exit(1) ; }
	exit(0);
}

