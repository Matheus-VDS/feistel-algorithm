#include <sdtio.h>
#include <stdlib.h>
#include "feistel.h"
void troca(int *A, int *B){
    int aux = *A;
    *A = *B;
    *B = aux;
}
int* permutacao_inicial(/*int tam_chave ,int *chave_K*/ ){ //criação de PA
    int *vetor_PA = (int*)malloc(MAX_BITS*(sizeof(int))); 
    int par =0;
    for(int i = 0; i< MAX_BITS; i++){
        if(par>MAX_BITS){
            par = 0;
            vetor_PA[i] = par;
            par=par+2;
        }
        else{
            vetor_PA[i] = par;
            par=par+2;
        }
    }
    return vetor_PA;
}
int* permutacao_2(){ //criação de PB
    int *vetor_PB = (int*)malloc(MAX_BITS*(sizeof(int))); 
    int impar = 1;
    for(int i = 0; i< MAX_BITS; i++){
        if(impar>MAX_BITS){
            impar = 1;
            vetor_PB[i] = impar;
            impar=impar+2;
        }
        else{
            vetor_PB[i] = impar;
            impar=impar+2;
        }
    }
    return vetor_PB;
}
int* F_substituicao(int *bloco_metade, int *chave /*chave que o usuario entrar de 2 à 32 bytes*/, int tam_chave, int rodada){
    int *vetor_S = (int*)malloc(MAX_BITS*(sizeof(int)));
    if(rodada == 0)
        vetor_S = permutacao_inicial();
    else
        vetor_S = permutacao_2();
    int *vetor_T = (int*)malloc(MAX_BITS*(sizeof(int))); 
    //int *vetor_AUX = (int*)malloc(MAX_BITS*(sizeof(int)));
    int j = 0;
    for(int i = 0; i < MAX_BITS; i++)
        vetor_T[i] = chave[i % tam_chave];

    for(int i = 0; i < MAX_BITS; i++){
        j = (j + vetor_S[i] + vetor_T[i]) % MAX_BITS;
        troca(&vetor_S[i], &vetor_S[j]);
        /*
        vetor_AUX[i] = vetor_S[i];
        vetor_S[i] = vetor_S[j];
        vetor_S[j] = vetor_AUX[i];*/
        //printf("%d ", vetor_S[j]);
    }
    //printf("\n");
    return vetor_S;
}
int* cifra(int *bloco, int *chave, int tam_chave){
    int metade = MAX_BYTES/2;
    int *bloco_E;  //Metade esquerda do bloco
    int *bloco_D;  //Metade direita da bloco
    bloco_E = (int*)malloc(MAX_BYTES*(sizeof(int)));
    bloco_D = (int*)malloc(MAX_BYTES*(sizeof(int)));
    int j = 0;
    for(int i =0; i< MAX_BYTES; i++){
        if(i < metade)
            bloco_E[i] = bloco[i];
        else{
            bloco_D[j] = bloco[i];
            j++;
        }
    }

    /********CÁLCULO DE F[0]********/
    int *novo_E, *novo_D, *vetor_substituicao;
    novo_E = (int*)malloc(MAX_BITS*(sizeof(int)));
    novo_D = (int*)malloc(MAX_BITS*(sizeof(int)));
    vetor_substituicao = (int*)malloc(MAX_BITS*(sizeof(int)));
    vetor_substituicao = F_substituicao(bloco_D, chave, tam_chave, 0);
    int *vetor_cifrado = (int*)malloc(MAX_BITS*(sizeof(int)));
    
    //nova esquerda
    for(int i =0; i < metade; i++){
        novo_E[i] = bloco_D[i];
        novo_D[i] = bloco_E[i] ^ vetor_substituicao[i];
        //vetor_cifrado[i] = novo_E[i];
    }
    printf("\nF[0]: ");
    for(int i = 0; i< MAX_BITS;i++)
        printf("%d ", vetor_substituicao[i]);
    printf("\n");
    printf("\nnova metade esquerda: ");
    for(int i =0; i < metade; i++)
        printf("%d ", novo_D[i]);
    printf("\n");


    /********CÁLCULO DE F[1]********/  
    int *novo_E2 = (int*)malloc(MAX_BITS*(sizeof(int)));
    int *novo_D2 = (int*)malloc(MAX_BITS*(sizeof(int)));
    int *vetor_substituicao2 = (int*)malloc(MAX_BITS*(sizeof(int)));
    vetor_substituicao2 = F_substituicao(novo_D, chave, tam_chave, 1);
    
    
    //nova direita
    for(int i =0; i < metade; i++){
        novo_E2[i] = novo_D[i];
        novo_D2[i] = novo_E[i] ^ vetor_substituicao2[i];
        vetor_cifrado[i] = novo_E2[i];
        vetor_cifrado[metade+i] = novo_D2[i];
    }
    
    printf("\nF[1]: ");
    for(int i = 0; i< MAX_BITS;i++)
        printf("%d ", vetor_substituicao2[i]);
    printf("\n");
    printf("\nnova metade direita: ");
    for(int i =0; i < metade; i++)
        printf("%d ", novo_D[i]);
    printf("\n");
    printf("\nVetor cifrado: ");
    for(int i =0; i< MAX_BYTES;i++){
        printf("%d ", vetor_cifrado[i]);
    printf("\n");
    }
    return vetor_cifrado;
}
int* decifra(int *bloco, int *chave, int tam_chave){
    int metade = MAX_BYTES/2;
    int *bloco_E;  //Metade esquerda do bloco
    int *bloco_D;  //Metade direita da bloco
    bloco_E = (int*)malloc(MAX_BYTES*(sizeof(int)));
    bloco_D = (int*)malloc(MAX_BYTES*(sizeof(int)));
    int j = 16;
    for(int i = MAX_BYTES; i > 0; i--){
        if(i > metade)
            bloco_E[i] = bloco[i];
        else{
            bloco_D[j] = bloco[i];
            j--;
        }
    } 
    int *vetor_cifrado = (int*)malloc(MAX_BYTES*(sizeof(int)));
    int *vetor_decifrado = (int*)malloc(MAX_BITS*(sizeof(int)));
    vetor_cifrado = cifra(bloco, chave, tam_chave);
    vetor_decifrado = vetor_cifrado;
    /*int *novo_E, *novo_D, *vetor_substituicao;
    novo_E = (int*)malloc(MAX_BITS*(sizeof(int)));
    novo_D = (int*)malloc(MAX_BITS*(sizeof(int)));
    vetor_substituicao = (int*)malloc(MAX_BITS*(sizeof(int)));
    vetor_substituicao = F_substituicao(bloco_D, vetor_cifrado, tam_chave, 0);*/
    
    return vetor_decifrado;
}