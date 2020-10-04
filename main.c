/*
 * Autor: Kaylani Bochie
 * Trabalho 1 de Sistemas Operacionais (PLE)
 *
 */

// Existe numero maximo de argumentos?
// Existe comprimento maximo de argumentos?

#include <stdio.h> // stdin
#include <stdlib.h> // strtoul

#define OK                              0
#define COMPRIMENTO_MAXIMO              15

int main ()
{
  char comando [COMPRIMENTO_MAXIMO];
  char numeroDeArgumentosAuxiliar [COMPRIMENTO_MAXIMO];
  char *strtoulDummy = NULL;
  unsigned long int numeroDeArgumentos = 0;
  // TODO: Mudar para unsigned depois de testar o cast com strtoul

  printf ("Qual comando quer executar?\n");
  fgets (comando, COMPRIMENTO_MAXIMO + 2, stdin);

  printf ("Quantos argumentos você quer digitar?\n");
  fgets (numeroDeArgumentosAuxiliar, COMPRIMENTO_MAXIMO + 2, stdin);
  numeroDeArgumentos = strtoul (numeroDeArgumentosAuxiliar, &strtoulDummy, 10);

  return OK;
}
