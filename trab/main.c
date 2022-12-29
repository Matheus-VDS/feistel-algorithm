/* Para compilar: gcc -Wall -pedantic -std=c99  -o feistel feistel.c feistel.h main.c
   Para executar: ./feistel
*/
#include <stdio.h>
#include <stdlib.h>
#include "feistel.h"
int main(){
    int bloco_cifra[MAX_BYTES];
    int bloco_decifra[MAX_BYTES];
    int chave[MAX_BYTES];
    int tam_chave, num_rodadas;
    int *vetor_cifrado = (int*)malloc(MAX_BYTES*(sizeof(int)));
    int *vetor_decifrado = (int*)malloc(MAX_BYTES*(sizeof(int)));
    char comando;
    printf("Digite I para inicializar, C para cifrar e D para decifrar\n");
    printf("Para sair basta digitar qualquer outro caractere\n");
    do{ 
        printf("Insira um comando: ");
        scanf(" %c", &comando);
        if(comando == 'I'){ 
            scanf("%d", &num_rodadas); 
            scanf("%d", &tam_chave);
            for(int i = 0; i < tam_chave; i++)
                scanf("%d", &chave[i]);
            if(!(num_rodadas >= 2 && num_rodadas <= 32)){
                printf("O numero de rodadas deve ser um inteiro entre 2 e 32\n");
                return 0;        
            }  
            if(!(tam_chave >= 8 && tam_chave <= 32)){
                printf("A chave deve ser um inteiro entre 8 e 32\n");
                return 0;        
            }
        }
        else if(comando == 'C'){
            if(num_rodadas < 2 || num_rodadas > 32 ){
                printf("A rede nao foi inicializada\n");
                return 0; 
            }
            else{
                for(int i=0; i< MAX_BYTES;i++)
                    scanf("%d", &bloco_cifra[i]);
                cifra(bloco_cifra, chave, tam_chave);
                /*vetor_cifrado = cifra(bloco_cifra, chave, tam_chave);
                printf("C ");
                for(int i =0; i< MAX_BYTES;i++){
                    printf("%d ", vetor_cifrado[i]);
                }*/
                printf("\n"); 
            }
        }
        else if(comando == 'D'){
            if(num_rodadas < 2 || num_rodadas > 32 ){
                printf("A rede nao foi inicializada\n");
                return 0; 
            }
            else{
                for(int i=0; i< MAX_BYTES;i++)
                    scanf("%d", &bloco_decifra[i]);
                /*for(int i=0; i< MAX_BYTES;i++)
                    printf("%d ", bloco_decifra[i]);*/
                vetor_decifrado = decifra(bloco_decifra, vetor_cifrado, tam_chave);
                printf("C ");
                for(int i =0; i< MAX_BYTES;i++){
                    printf("%d ", vetor_decifrado[i]);
                }
                printf("\n");
            }  
        }
    }while(comando == 'I' || comando== 'C' || comando == 'D');
    return 0;
}