/* 
 * File:   main.c
 * Author: Vitor
 *
 * Created on 16 de Julho de 2021, 11:55
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int anbn(char input[200], int max, int init){
    int inputPointer = 0; //"ponteiro" do input
    int state = 1; //estado atual
    char stack[200] = {}; //pilha inicializada
    int stackPointer = -1; //"ponteiro" da pilha, funciona como 'máximo + 1' da pilha também
    
//    read   read goto  stack  stack
//    state  char state remove write
//    q1 =    ,   q2;     ->   $
//    q2 =   a,     ;     ->   0
//           b,   q3;   0 -> 
//    q3 =   b,     ;   0 -> 
//           EOF, q4;   $ -> 
//    q4 =   nada
    
    printf("\nVetor pilha: {"); //printa pilha
    for(int i=0; i<=stackPointer; i++){
        printf(" %c ", stack[i]);
    }
    printf("}\nState: %i\n", state); //printa estado
    
    if (state == 1 && inputPointer < max){ //inicializa automato de q1 para q2 caso tenha algo no input
        stackPointer++;
        stack[stackPointer] = '$';
        state = 2;
    }
    printf("$ imbutido na pilha\n|\n|\nV\n");
    
    
    
    while(inputPointer < max){ //laço repetição para os estados q2 e q3
        
        printf("\nVetor pilha: {"); //printa pilha
        for(int i=0; i<=stackPointer; i++){ 
            printf(" %c ", stack[i]);
        }
        printf("}\nState: %i\n", state);
        if (inputPointer != max)
            printf("Analizando char: %c\n", input[inputPointer]);
        else
            printf("Input lido!\n");
        
        if (state == 2){ //q2
            if (input[inputPointer] == 'a'){ //se input é A, entao adiciona na pilha
                stackPointer++;
                stack[stackPointer] = '0';
            }
            else if (input[inputPointer] == 'b'){ //se for B, tira da pilha e vai pra q3
                if (stack[stackPointer] == '0')
                    state = 3;
                    stackPointer--;
            }
        }
        else if (state == 3){ //q3
            if (input[inputPointer] == 'b'){ //se for B, tira da pilha
                if (stack[stackPointer] == '0')
                    stackPointer--;
                else { 
                    stackPointer++; //se não ter 0 na pilha, adiciona um valor na pilha pois não está balanceado
                    stack[stackPointer] = 'x';
                }
            }
        }
        
        printf("|\n|\nV\n"); //"seta" no print para visualização
        
        inputPointer++; //avança a casa no input
    }
    
    //verifica se foi lido tudo e a pilha está com último valor com $
    if (stack[stackPointer] == '$' && state == 3){ 
        stackPointer--;
        state = 4;
        printf("$ retirado da pilha\n");
    }
    
    
    printf("\n\nPilha FINAL: {"); //printa pilha uma ultima vez
    for(int i = 0; i <= stackPointer; i++)
        printf(" %c ", stack[i]);
    printf("}\nState: %i\n\n", state);
    
    if (state == 4 || state == 1) //se cair em q1 ou q4
        return 1; //retorna verdadeiro
    else //se nao
        return 0; //retorna falso
}

/*
 * 
 */
int main(int argc, char** argv) {
    char input[200]; //string para ser recebido como input
    
    printf("digite input: ");
    scanf("%s", &input);
    
    int max; //máximo de iterações, que é a quantidade de símbolos no input
    max = strlen(input);
    printf("\nTamanho de input: %i\n", max);
    
    if (anbn(input, max, 0) == 1) //executa o AFD de a^n b^n | n >= 1
        printf("\n\nINPUT ACEITO\n");
    else
        printf("\n\nINPUT NAO ACEITO: FIM NAO EH q1 OU q4\n");

    
    printf("\n\nFim do codigo\n");
    system("pause"); //problema de janela windows
    return (EXIT_SUCCESS);
}

