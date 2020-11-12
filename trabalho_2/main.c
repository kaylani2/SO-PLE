/*
 * Autor: Kaylani Bochie
 * Trabalho 2 de Sistemas Operacionais (PLE)
 * Capitulo 6: The search-insert-delete problem
 *
 */

/*
 * Solucao em alto nivel:
 * - Todos pegam o lock do delete
 * - insert () e delete () pegam a lock do insert
 */

#include <stdio.h> // stdin
#include <stdlib.h> // strtoul ()
#include <string.h> // strcat ()
#include <signal.h> // signal ()
#include <sys/types.h> // pid_t
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
const int sleepTime = 10; // micro
pthread_mutex_t mutexDelete = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexInsert = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condDelete = PTHREAD_COND_INITIALIZER;

void *search (void *listaEncadeada)
{
  /*
   * Podem executar com outros search
   * Podem executar com um insert
   * Nao podem executar com um delete
   */
  pthread_mutex_lock (&mutexDelete);
  printf ("Estou buscando...");
  usleep (sleepTime);
  pthread_mutex_unlock (&mutexDelete);
}

void *insert (void *listaEncadeada)
{
  /*
   * Podem executar com multiplos search
   * Nao podem executar com outro insert
   * Nao podem executar com um delete
   */
  pthread_mutex_lock (&mutexDelete);
  pthread_mutex_lock (&mutexInsert);
  printf ("Estou inserindo...");
  usleep (sleepTime);
  pthread_mutex_unlock (&mutexInsert);
  pthread_mutex_unlock (&mutexDelete);
}

void *delete (void *listaEncadeada)
{
  /*
   * Nao podem executar com um search
   * Nao podem executar com um insert
   * Nao podem executar com outro delete
   */
  pthread_mutex_lock (&mutexDelete);
  pthread_mutex_lock (&mutexInsert);
  printf ("Estou apagando...");
  usleep (sleepTime);
  pthread_mutex_unlock (&mutexInsert);
  pthread_mutex_unlock (&mutexDelete);
}


#define OK                              0
int main ()
{
  return OK;
}
