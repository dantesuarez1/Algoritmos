#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdapilad.h"

typedef struct nodito{
    float precio;
    struct nodito *sig;
}NODITO;
typedef NODITO* TSUBLISTA;

typedef struct nodo{
    char nombre[11];
    float precio;
    TSUBLISTA sub;
    struct nodo* sig;
}NODO;
typedef NODO* TLISTA;



void inicialista(TLISTA *lista);
void cargalista(TLISTA *lista);
void muestralista(TLISTA lista);

int main()
{
    TLISTA lista;
    inicialista(&lista);
    cargalista(&lista);
    //muestralista(lista);


    TPILA p;
    TELEMENTOP ep;
    iniciap(&p);

    TLISTA act;
    TSUBLISTA ants, auxs;

    while(lista!=NULL){
        ants=NULL;
        auxs=lista->sub;
        //printf("%s\n", lista->nombre);
        while(auxs!=NULL){
            //printf("%.2f ", auxs->precio);
            if(auxs->precio > lista->precio){
                if(ants==NULL){
                  lista->sub=auxs->sig;
                  free(auxs);
                  auxs=lista->sub;
                }
                else{
                    ants->sig=auxs->sig;
                    free(auxs);
                    auxs=ants->sig;
                }

            }
            else{
                ants=auxs;
                auxs=auxs->sig;
            }
        }

        if(lista->sub==NULL){
            ponep(&p, (lista->nombre));
        }
        lista=lista->sig;
    }

    while(!vaciap(p)){
        sacap(&p, &ep);
        printf("%s\n", ep);
    }
    return 0;
}

void inicialista(TLISTA *lista){
    *lista = NULL;
}

void cargalista(TLISTA *lista){

    TLISTA ult;
    TSUBLISTA auxs;
    char nombre[11];
    float precio;

    *lista=(TLISTA)malloc(sizeof(NODO));
    printf("Ingrese el nombre: ");
    fgets((*lista)->nombre, 11, stdin);
    printf("\nIngrese el precio referencia: ");
    scanf("%f", &precio);
    (*lista)->precio=precio;
    (*lista)->sub=NULL;
    printf("\nIngrese precios(* para finalizar): \n");
    while(scanf("%f", &precio)==1){
        auxs=(TSUBLISTA)malloc(sizeof(NODITO));
        auxs->precio=precio;
        auxs->sig= (*lista)->sub;
        (*lista)->sub=auxs;
        printf("\nIngrese precios(* para finalizar): \n");
    }
    ult=(*lista);
    fflush(stdin);
    printf("Ingrese el nombre: ");
    while(gets(nombre) != NULL){
        ult->sig=(TLISTA)malloc(sizeof(NODO));
        ult=ult->sig;
        strcpy(ult->nombre, nombre);
        printf("Ingrese el precio referencia: ");
        scanf("%f", &precio);
        ult->precio=precio;
        ult->sub=NULL;
        printf("\nIngrese precios(* para finalizar): \n");
        while(scanf("%f", &precio)==1){
            auxs=(TSUBLISTA)malloc(sizeof(NODITO));
            auxs->precio=precio;
            auxs->sig= ult->sub;
            ult->sub=auxs;
            printf("\nIngrese precios(* para finalizar): \n");
        }
        printf("Ingrese el nombre: ");
        fflush(stdin);
    }
    ult->sig=NULL;
}


void muestralista(TLISTA lista){
    TSUBLISTA auxs;
    while(lista!=NULL){
        printf("\n%s %.2f \n", lista->nombre, lista->precio);
        auxs=lista->sub;
        while(auxs!=NULL){
            printf("%f ", auxs->precio);
            auxs=auxs->sig;
        }
        lista=lista->sig;
    }
    printf("\n-----------------------------------------------\n");
}
