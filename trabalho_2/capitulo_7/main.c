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

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t onibusChegou = PTHREAD_COND_INITIALIZER;
unsigned int onibusEstaParado = FALSO;
unsigned int primeiraFila = 0;
unsigned int segundaFila = 0;
unsigned int vagas;

void depart ()
{
  onibusEstaParado = FALSO;
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
    if (vagas == 0)
    {
      depart ();
      primeiraFila = segundaFila;
      segundaFila = 0;
      pthread_mutex_unlock (&mutex);
      return NULL;
    }
    while (primeiraFila != 0); // tem gente pra embarcar
    depart ();
    primeiraFila = segundaFila;
    segundaFila = 0;
    pthread_mutex_unlock (&mutex);
    return NULL;
  }

  return NULL;
}


void *rider (void *argumentos)
{
  pthread_mutex_lock (&mutex);
  if (onibusEstaParado == FALSO) // fila unica
  {
    printf ("Entrei na primeira fila.\n");
    primeiraFila++;
    pthread_cond_wait (&onibusChegou, &mutex);
    printf ("antes do boar dbus");
    boardBus (); // decrementa fila
  }
  else
  {
    printf ("Entrei na segunda fila.\n");
    segundaFila++;
    pthread_cond_wait (&onibusChegou, &mutex);
    //boardBus (); // decrementa fila
  }

  pthread_mutex_unlock (&mutex);

  return NULL;
}

int main ()
{
  pthread_t t0, t1, t2, t3, t4, t5, t6;
  unsigned int repeticoes = NUMERO_DE_REPETICOES;

  repeticoes = 10;
  {
    printf ("repeticoes %d\n", repeticoes);
    pthread_create (&t0, NULL, rider, NULL);
    pthread_create (&t1, NULL, rider, NULL);
    pthread_create (&t2, NULL, rider, NULL);
    pthread_create (&t3, NULL, rider, NULL);
    pthread_create (&t4, NULL, rider, NULL);
    pthread_create (&t5, NULL, rider, NULL);
    pthread_create (&t6, NULL, bus, NULL);

    pthread_join (t6, NULL);
    repeticoes--;
  }

  printf ("%u repeticoes.\n", NUMERO_DE_REPETICOES);
  printf ("Nao houve deadlock!!!");

  return OK;
}
