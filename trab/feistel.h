#include<sdtio.h>
#define MAX_BITS 256
#define MAX_BYTES 32
int* permuta();
void troca(int *A, int *B);
int* F_substituicao(int *bloco_metade, int *chave, int tam_chave, int rodada);
int* permutacao_inicial();
int* permutacao_2();
int* cifra(int *bloco, int *chave, int tam_chave);
int* decifra(int *bloco, int *chave, int tam_chave);
int* feistel(int tam_bloco, int *bloco, int *chave);
