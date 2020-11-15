/*
 * Autor: Kaylani Bochie
 * Trabalho 2 de Sistemas Operacionais (PLE)
 * Capitulo 6.1: The search-insert-delete problem
 *
 */

/*
 * Solucao em alto nivel:
 * - Todos pegam o lock do delete
 * - insert () e delete () pegam a lock do insert
 * - Garantir que os locks sejam pegos sempre em ordem
 */

#include <stdio.h> // stdin
#include <unistd.h> // usleep ()
#include <sys/wait.h>
#include <pthread.h>

#define OK                              0
#define NUMERO_DE_REPETICOES            5000
#define SLEEP_TIME                      10 // micro

pthread_mutex_t mutexDelete = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexInsert = PTHREAD_MUTEX_INITIALIZER;

void *search (void *listaEncadeada)
{
  /*
   * Podem executar com outros search
   * Podem executar com um insert
   * Nao podem executar com um delete
   */
  pthread_mutex_lock (&mutexDelete);
  printf ("Estou buscando...\n");
  usleep (SLEEP_TIME);
  pthread_mutex_unlock (&mutexDelete);
  return OK;
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
  printf ("Estou inserindo...\n");
  usleep (SLEEP_TIME);
  pthread_mutex_unlock (&mutexInsert);
  pthread_mutex_unlock (&mutexDelete);
  return OK;
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
  printf ("Estou apagando...\n");
  usleep (SLEEP_TIME);
  pthread_mutex_unlock (&mutexInsert);
  pthread_mutex_unlock (&mutexDelete);
  return OK;
}


int main ()
{
  pthread_t t0, t1, t2, t3, t4, t5, t6;
  unsigned int repeticoes = NUMERO_DE_REPETICOES;
  // 4 search (), 2 insert (), 1 delete ()

  while (repeticoes != 0)
  {
    pthread_create (&t0, NULL, search, NULL);
    pthread_create (&t1, NULL, search, NULL);
    pthread_create (&t2, NULL, search, NULL);
    pthread_create (&t3, NULL, search, NULL);
    pthread_create (&t4, NULL, insert, NULL);
    pthread_create (&t5, NULL, insert, NULL);
    pthread_create (&t6, NULL, delete, NULL);

    pthread_join (t0, NULL);
    pthread_join (t1, NULL);
    pthread_join (t2, NULL);
    pthread_join (t3, NULL);
    pthread_join (t4, NULL);
    pthread_join (t5, NULL);
    pthread_join (t6, NULL);

    repeticoes--;
  }

  printf ("%u repeticoes.\n", NUMERO_DE_REPETICOES);
  printf ("Nao houve deadlock!!!");

  return OK;
}
