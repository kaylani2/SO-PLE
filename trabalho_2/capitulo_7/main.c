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
#define MAXIMO_VAGAS                   10 
#define NUMERO_DE_REPETICOES            5
#define SLEEP_TIME                      10 // micro
#define THREAD_ARRAY_SIZE               4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t onibusChegou = PTHREAD_COND_INITIALIZER;
unsigned int onibusEstaParado = FALSO;
unsigned int primeiraFila = 0;
unsigned int segundaFila = 0;
unsigned int vagas;

void depart ()
{
  printf ("Onibus saiu.\n");
}

void boardBus ()
{
  primeiraFila--;
  printf ("Embarquei.\n");
}

void *bus (void *argumentos)
{
  pthread_mutex_lock (&mutex);
  vagas = MAXIMO_VAGAS;
  onibusEstaParado = VERDADEIRO;
  printf ("Onibus chegou!\n");
  pthread_cond_signal (&onibusChegou);


  while (1)
  {
    pthread_mutex_lock (&mutex);
    if (vagas == 0)
    {
      depart ();
      primeiraFila = segundaFila;
      segundaFila = 0;
      return OK;
    }
    while (primeiraFila != 0); // tem gente pra embarcar
    depart ();
    primeiraFila = segundaFila;
    segundaFila = 0;
    return OK;

    pthread_mutex_unlock (&mutex);
  }
}


void *rider (void *argumentos)
{
  pthread_mutex_lock (&mutex);
  if (onibusEstaParado == FALSO) // fila unica
  {
    primeiraFila++;
    pthread_cond_wait (&onibusChegou, &mutex);
    boardBus (); // decrementa fila
  }
  else
  {
    segundaFila++;
    pthread_cond_wait (&onibusChegou, &mutex);
    //boardBus (); // decrementa fila
  }
  pthread_mutex_unlock (&mutex);
  return OK;
}

int main ()
{
  pthread_t t0, t1, t2, t3, t4, t5, t6;
  unsigned int repeticoes = NUMERO_DE_REPETICOES;
  // 4 search (), 2 insert (), 1 delete ()

  repeticoes = 10;
  while (repeticoes != 0)
  {
    printf ("repeticoes %d\n", repeticoes);
    pthread_create (&t0, NULL, rider, NULL);
    pthread_create (&t1, NULL, rider, NULL);
    pthread_create (&t2, NULL, rider, NULL);
    pthread_create (&t3, NULL, rider, NULL);
    pthread_create (&t4, NULL, rider, NULL);
    pthread_create (&t5, NULL, rider, NULL);
    pthread_create (&t6, NULL, bus, NULL);

    repeticoes--;
  }

  printf ("%u repeticoes.\n", NUMERO_DE_REPETICOES);
  printf ("Nao houve deadlock!!!");

  return OK;
}
