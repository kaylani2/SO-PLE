/*
 * Autor: Kaylani Bochie
 * Trabalho 2 de Sistemas Operacionais (PLE)
 * Capitulo 7.4: The Senate Bus problem
 *
 */

/*
 * Solucao em alto nivel:
 * - Uma thread para o onibus e uma thread para os passageiros
 * - Quando o onibus chega, ele avisa todas as threads de passageiros
 * - Caso algum passageiro novo chegue ele entra em uma fila separada
 * - O onibus conta quantos passageiros estao esperando, ao terminar, depart ()
 */

#include <stdio.h> // stdin
#include <stdlib.h> // strtoul ()
#include <string.h> // strcat ()
#include <signal.h> // signal ()
#include <sys/types.h> // pid_t
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define OK                              0
#define VERDADEIRO                      0
#define FALSO                           1
#define MAXIMO_VAGAS                    10
#define NUMERO_DE_REPETICOES            5
#define SLEEP_TIME                      10 // micro
#define THREAD_ARRAY_SIZE               4

pthread_mutex_t mutexFila = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t onibusChegou = PTHREAD_COND_INITIALIZER;
unsigned int fila = 0;
unsigned int segundaFila = 0;
unsigned int onibusEstaParado = FALSO;

void *bus (void *argumentos)
{
  pthread_mutex_lock (&mutexFila); // ninguem mais entra na fila
  onibusEstaParado = VERDADEIRO;
  pthread_mutex_unlock (&mutexFila);

  pthread_mutex_lock (&mutexFila);
  if (fila == 0)
  {
    printf ("Onibus saiu.\n");
    // depart ()
    pthread_mutex_unlock (&mutexFila);
    return NULL;
  }


  while (fila > 0)
    fila--;
  printf ("Onibus saiu.\n");
  fila = segundaFila;
  segundaFila = 0;
  // depart ()
  pthread_mutex_unlock (&mutexFila);
  return NULL;

  pthread_mutex_unlock (&mutexFila);

  return NULL;
}
void *rider (void *argumentos)
{
  pthread_mutex_lock (&mutexFila);
  if (onibusEstaParado == FALSO)
  {
    printf ("Entrei na fila.\n");
    fila++;
  }
  else
  {
    printf ("Esperei o proximo onibus.\n");
    segundaFila++;
  }
  pthread_mutex_unlock (&mutexFila);

  while (onibusEstaParado == FALSO);
  pthread_mutex_lock (&mutexFila);
  fila--;
  printf ("Embarquei.\n"); // boardBus ()

  pthread_mutex_unlock (&mutexFila);
  return NULL;
}


int main ()
{
  pthread_t t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;

  pthread_create (&t0, NULL, rider, NULL);
  pthread_create (&t1, NULL, rider, NULL);
  pthread_create (&t2, NULL, rider, NULL);
  pthread_create (&t3, NULL, rider, NULL);
  pthread_create (&t4, NULL, rider, NULL);
  pthread_create (&t5, NULL, rider, NULL);
  pthread_create (&t6, NULL, bus, NULL);
  pthread_create (&t7, NULL, rider, NULL);
  pthread_create (&t8, NULL, rider, NULL);
  pthread_create (&t9, NULL, rider, NULL);
  pthread_create (&t10, NULL, rider, NULL);

  pthread_join (t6, NULL);

  printf ("Nao houve deadlock!!!\n");

  return OK;
}
