/*
 * Autor: Kaylani Bochie
 * Trabalho 2 de Sistemas Operacionais (PLE)
 * Capitulo 5.2: The barbershop problem
 *
 */

/*
 * Solucao em alto nivel:
 */

#include <stdio.h> // stdin
#include <signal.h> // signal ()
#include <unistd.h> // usleep ()
#include <pthread.h>

#define OK                              0
#define VERDADEIRO                      0
#define FALSO                           1
#define NUMERO_DE_REPETICOES            20
#define SLEEP_TIME                      10 // micro

unsigned int numeroDeOxigenios = 0;
unsigned int numeroDeHidrogenios = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *oxygen (void *argumento)
{
  pthread_mutex_lock (&mutex);


  pthread_mutex_unlock (&mutex);
  return OK;
}






int main ()
{
  pthread_t t0, t1, t2, t3, t4, t5, t6;
  unsigned int repeticoes = NUMERO_DE_REPETICOES;
  // 1 barber (), 6 customer ()

  while (repeticoes != 0)
  {
    pthread_create (&t0, NULL, barber, NULL);
    pthread_create (&t1, NULL, customer, NULL);
    pthread_create (&t2, NULL, customer, NULL);
    pthread_create (&t3, NULL, customer, NULL);
    pthread_create (&t4, NULL, customer, NULL);
    pthread_create (&t5, NULL, customer, NULL);
    pthread_create (&t6, NULL, customer, NULL);

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
