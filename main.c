/*
 * Autor: Kaylani Bochie
 * Trabalho 1 de Sistemas Operacionais (PLE)
 *
 */

// Existe numero maximo de argumentos?
// Existe comprimento maximo de argumentos?
// Existe comprimento maximo para os comandos?

#include <stdio.h> // stdin
#include <stdlib.h> // strtoul ()
#include <string.h> // strcat ()
#include <sys/types.h> // pid_t
#include <unistd.h>
#include <sys/wait.h>

#define OK                              0
#define COMPRIMENTO_MAXIMO              50
#define NUMERO_MAXIMO_ARGUMENTOS        20
#define EOS                             '\0'

int main ()
{
  char comando [COMPRIMENTO_MAXIMO];
  char comandoComCaminho [COMPRIMENTO_MAXIMO] = "/bin/";
  char numeroDeArgumentosAuxiliar [COMPRIMENTO_MAXIMO];
  char buffer [COMPRIMENTO_MAXIMO];
  unsigned long int numeroDeArgumentos = 0;
  // TODO: /\ Mudar para unsigned depois de testar o cast com strtoul
  unsigned int indiceArgumentos;
  char *argumentos [NUMERO_MAXIMO_ARGUMENTOS];

  pid_t child_pid = 0;
  // TODO: /\ Mudar o nome, apenas um teste

  // Entrada
  printf ("Qual comando quer executar?\n");
  fgets (comando, COMPRIMENTO_MAXIMO + 2, stdin);
  comando [strlen (comando) - 1] = EOS;
  strcat (comandoComCaminho, comando);
  printf ("Quantos argumentos você quer digitar?\n");
  fgets (numeroDeArgumentosAuxiliar, COMPRIMENTO_MAXIMO + 2, stdin);
  numeroDeArgumentos = strtoul (numeroDeArgumentosAuxiliar, NULL, 10);
  // TODO: Tratar numero invalido
  //printf ("Numero de argumentos: %lu\n", numeroDeArgumentos); // DEBUG

  // Construir vetor de argumentos
  for (indiceArgumentos = 0; indiceArgumentos < numeroDeArgumentos;
       indiceArgumentos++)
  {
    argumentos [indiceArgumentos] = malloc (COMPRIMENTO_MAXIMO * sizeof (char));
    printf ("Digite o argumento %u.\n", (indiceArgumentos + 1));
    fgets (buffer, COMPRIMENTO_MAXIMO + 2, stdin);
    buffer [strlen (buffer) - 1] = EOS;
    strncpy (argumentos [indiceArgumentos], buffer, COMPRIMENTO_MAXIMO);
  }
  argumentos [indiceArgumentos] = NULL;


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
  child_pid = fork ();
  if (child_pid == 0) // fork OK
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
