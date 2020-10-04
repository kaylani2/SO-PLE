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
  char comandoComCaminho [COMPRIMENTO_MAXIMO];
  char numeroDeArgumentosAuxiliar [COMPRIMENTO_MAXIMO];
  char *strtoulDummy = NULL;
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
  printf ("Comando sem caminho: %s\n", comando); // DEBUG
  strcpy (comandoComCaminho, "/bin/");
  strcat (comandoComCaminho, comando);
  printf ("Comando com caminho: %s\n", comandoComCaminho); // DEBUG
  // TODO: Verificar se o comando existe

  printf ("Quantos argumentos você quer digitar?\n");
  fgets (numeroDeArgumentosAuxiliar, COMPRIMENTO_MAXIMO + 2, stdin);
  numeroDeArgumentos = strtoul (numeroDeArgumentosAuxiliar, &strtoulDummy, 10);

  printf ("1");
  for (indiceArgumentos = 0; indiceArgumentos < numeroDeArgumentos; indiceArgumentos++)
  {
    printf ("Digite o argumento %u.\n", (indiceArgumentos + 1));
    fgets (argumentos [indiceArgumentos], COMPRIMENTO_MAXIMO + 2, stdin);
  }

  printf ("akos2\n");
  printf ("Argumentos:\n");
  for (indiceArgumentos = 0; indiceArgumentos < numeroDeArgumentos; indiceArgumentos++)
    printf ("%s", argumentos [indiceArgumentos]);


  printf ("2");
  // Execução
  child_pid = fork ();
  if (child_pid == 0) // fork OK
  {
    printf ("Comando com caminho: %s\n", comandoComCaminho);
    printf ("Comando sem caminho: %s\n", comando);
    //execlp ("/bin/ping", "ping", "8.8.8.8", NULL);
    execlp (comandoComCaminho, comando, argumentos [0], NULL);
  }
  else
  {
    wait (NULL);
    printf ("Comando executado com sucesso!\n");
  }


  return OK;
}
