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
#define BARBEARIA_CHEIA                 1
#define VERDADEIRO                      0
#define FALSO                           1
#define NUMERO_MAXIMO_DE_CADEIRAS       2 // n arbitrario
#define NUMERO_DE_REPETICOES            20
#define SLEEP_TIME                      10 // micro

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t chegouCliente = PTHREAD_COND_INITIALIZER;
pthread_cond_t barbeiroEstaLivre = PTHREAD_COND_INITIALIZER;
unsigned int barbeiroEstaOcupado = FALSO;
unsigned int cadeirasDisponiveis = NUMERO_MAXIMO_DE_CADEIRAS;

void balk ()
{
  printf ("Barbearia estava cheia.\n");
}

void cutHair ()
{
  usleep (SLEEP_TIME);
  printf ("Cortei o cabelo do cliente.\n");
}

void getHairCut ()
{
  usleep (SLEEP_TIME);
  printf ("O barbeiro cortou meu cabelo.\n");
}

void *barber (void *argumento)
{
  pthread_mutex_lock (&mutex);

  while (1 == 1)
  {
    pthread_cond_wait (&chegouCliente, &mutex);
    cutHair ();
    barbeiroEstaOcupado = 0;
    pthread_cond_signal (&barbeiroEstaLivre);
  }

  pthread_mutex_unlock (&mutex);
  return NULL;
}

void *customer (void *argumento)
{
  pthread_mutex_lock (&mutex);
  if (cadeirasDisponiveis == 0)
  {
    balk ();
    pthread_mutex_unlock (&mutex);
    return NULL;
  }

  if (barbeiroEstaOcupado)
  {
    printf ("Sentando e esperando.\n");
    cadeirasDisponiveis--;
    pthread_cond_wait (&barbeiroEstaLivre, &mutex);

    while (barbeiroEstaOcupado);

    barbeiroEstaOcupado = 1;
    cadeirasDisponiveis++;
    getHairCut ();
    pthread_cond_signal (&chegouCliente);
  }
  else // barbeiro estava livre (dormindo)
  {
    printf ("Barbearia estava vazia.\n");
    while (barbeiroEstaOcupado == VERDADEIRO);
    barbeiroEstaOcupado = VERDADEIRO;
    //getHairCut ();
    pthread_cond_signal (&chegouCliente);
  }

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

    pthread_join (t6, NULL);

    repeticoes--;
  }

  printf ("%u repeticoes.\n", NUMERO_DE_REPETICOES);
  printf ("Nao houve deadlock!!!");

  return OK;
}
