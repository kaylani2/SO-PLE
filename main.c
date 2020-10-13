/*
 * Autor: Kaylani Bochie
 * Trabalho 1 de Sistemas Operacionais (PLE)
 *
 */

#include <stdio.h> // stdin
#include <stdlib.h> // strtoul ()
#include <string.h> // strcat ()
#include <signal.h> // signal ()
#include <sys/types.h> // pid_t
#include <unistd.h>
#include <sys/wait.h>

#define OK                              0
#define ERRO_SINAL_DESCONHECIDO         1
#define COMPRIMENTO_MAXIMO              50
#define NUMERO_MAXIMO_ARGUMENTOS        20
#define EOS                             '\0'

void signalHandler (int inputSignal)
{
  if (inputSignal == SIGUSR1)
    printf ("Received SIGUSR1\n");
  else
    printf ("Sinal desconhecido.\n");
}


int main ()
{
  char comando [COMPRIMENTO_MAXIMO] = "";
  char comandoComCaminho [COMPRIMENTO_MAXIMO] = "/bin/";
  char numeroDeArgumentosAuxiliar [COMPRIMENTO_MAXIMO] = "";
  char buffer [COMPRIMENTO_MAXIMO] = "";
  unsigned long int numeroDeArgumentos = 0; // long para usar strtoul ()
  unsigned char indiceArgumentos = 0;
  char *argumentos [NUMERO_MAXIMO_ARGUMENTOS];
  pid_t pidFilho = 0;

  if (signal (SIGUSR1, signalHandler) == SIG_ERR)
  {
    printf("Sinal desconhecido, encerrando.\n");
    return ERRO_SINAL_DESCONHECIDO;
  }


  // Entrada
  printf ("Qual comando quer executar?\n");
  // INICIO DO ESCOPO DE RECEBIMENTO DO SINAL SIGUSR1
  fgets (comando, COMPRIMENTO_MAXIMO + 2, stdin);
  comando [strlen (comando) - 1] = EOS;
  strcat (comandoComCaminho, comando);
  printf ("Quantos argumentos você quer digitar?\n");
  fgets (numeroDeArgumentosAuxiliar, COMPRIMENTO_MAXIMO + 2, stdin);
  numeroDeArgumentos = strtoul (numeroDeArgumentosAuxiliar, NULL, 10);
  // TODO: Tratar numero invalido
  //printf ("Numero de argumentos: %lu\n", numeroDeArgumentos); // DEBUG

  // Construir vetor de argumentos
  strncpy (argumentos [0], comando, COMPRIMENTO_MAXIMO);
  for (indiceArgumentos = 1; indiceArgumentos < numeroDeArgumentos + 1;
       indiceArgumentos++)
  {
    argumentos [indiceArgumentos] = malloc (COMPRIMENTO_MAXIMO * sizeof (char));
    printf ("Digite o argumento %u: ", (indiceArgumentos));
    fgets (buffer, COMPRIMENTO_MAXIMO + 2, stdin);
    buffer [strlen (buffer) - 1] = EOS;
    strncpy (argumentos [indiceArgumentos], buffer, COMPRIMENTO_MAXIMO);
  }
  argumentos [indiceArgumentos] = NULL;
  // FIM DO ESCOPO DE RECEBIMENTO DO SINAL SIGUSR1


  // DEBUG
  printf ("Argumentos:\n");
  for (indiceArgumentos = 0; indiceArgumentos < numeroDeArgumentos;
       indiceArgumentos++)
  {
    printf ("%s\n", argumentos [indiceArgumentos]);
  }
  printf ("Comando com caminho: %s\n", comandoComCaminho);
  printf ("Comando sem caminho: %s\n", comando);


  // Executar processo
  pidFilho = fork ();
  if (pidFilho == 0) // fork OK
  {
    execv (comandoComCaminho, argumentos);
  }
  else
  {
    wait (NULL);
    printf ("Comando executado com sucesso!\n");
  }


  return OK;
}
