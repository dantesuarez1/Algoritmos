#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tdacola.h"

typedef struct nodito{
    char materia[5];
    struct nodito *sig;
}NODITO;
typedef NODITO* TSUBLISTA;

typedef struct nodo{
    char matricula[5];
    TSUBLISTA sub;
    struct nodo *sig;
}NODO;
typedef NODO *TLISTA;

void carga(TLISTA *pl);
void muestr(TLISTA lista);
void cargacola(TCOLA *c);

int main()
{
    TLISTA lista;
    TCOLA c;
    TELEMENTOC e;

    carga(&lista);
    //muestr(lista);
    cargacola(&c);

    TLISTA aux, ant;
    TSUBLISTA auxs, ants;

    while(!vaciac(c)){
        sacac(&c, &e);
        aux=lista;
        ant=NULL;
        while(aux!=NULL && strcmp(aux->matricula, e.matricula)){
            ant=aux;
            aux=aux->sig;
        }
        if(aux!=NULL && !strcmp(aux->matricula, e.matricula)){
            auxs=aux->sub;
            ants=NULL;
            if(auxs->sig==NULL){//SUBLISTA CON UN SOLO ELEMENTO
                if(!strcmp(e.materia, auxs->materia)){// EL UNICO ELEMENETO ES LA MATERIA
                    free(auxs);
                    aux->sub=NULL;
                    if(ant==NULL){//ES EL PRIMER NODO
                        lista=lista->sig;
                        free(aux);
                        aux=lista;
                    }
                    else{//
                        ant->sig=aux->sig;
                        free(aux);
                        aux=ant->sig;
                    }

                }
                else{
                    printf("La materia no existe en la matricula1.\n");
                }

            }
            else{ //SUBLISTA CON MAS DE UN ELEMENTO
                while(auxs!=NULL && strcmp(e.materia, auxs->materia)){
                    ants=auxs;
                    auxs=auxs->sig;
                }
                if(!strcmp(e.materia, auxs->materia)){//ENCOTRO ELEMENTO
                    if(ants==NULL){//PRIMER NODITO
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
                    printf("La materia no existe en la matricula2.\n");
                }

            }

        }
        else{
            printf("La matricula no existe en la lista3.\n");
        }
    }
    muestr(lista);
    return 0;
}

void carga(TLISTA *pl){
    FILE *arch=fopen("datos.txt", "r");
    TSUBLISTA auxs;
    TLISTA ult;
    int x;
    char mat[5];

    if(arch==NULL)
        perror("El archivo no se abrio correctamente.\n");
    else{

        (*pl)=NULL;
        ult=(*pl);
        while(fscanf(arch, "%s %d", mat, &x)==2){
            if(ult==NULL){
                (*pl)=(TLISTA)malloc(sizeof(NODO));
                ult=(*pl);

            }
            else{
                ult->sig=(TLISTA)malloc(sizeof(NODO));
                ult=ult->sig;
            }
            strcpy(ult->matricula, mat);
            //printf("\n%s\n", mat);
            ult->sub=NULL;
            auxs=ult->sub;
            for(int i=0; i<x ; i++){
                fscanf(arch, "%s", mat);
                //printf("%s -", mat);
                if(ult->sub==NULL){
                    ult->sub=(TSUBLISTA)malloc(sizeof(NODITO));
                    auxs=ult->sub;
                }
                else{
                    auxs->sig=(TSUBLISTA)malloc(sizeof(NODITO));
                    auxs=auxs->sig;
                }

                strcpy(auxs->materia, mat);
                auxs->sig=NULL;
            }
            ult->sig=NULL;
        }
    }
}


void muestr(TLISTA lista){
    TSUBLISTA sub;
    while(lista!=NULL){
        printf("\nMatricuala: %s\n", lista->matricula);
        sub=lista->sub;
        while(sub!=NULL){
            printf(" %s -", sub->materia);
            sub=sub->sig;
        }
        lista=lista->sig;
    }
}

void cargacola(TCOLA *c){
    iniciac(c);
    TELEMENTOC x;
    strcpy(x.matricula,"4567");
    strcpy(x.materia, "ALGE");
    ponec(c, x);

    strcpy(x.matricula,"2345");
    strcpy(x.materia, "FISI");
    ponec(c, x);

    strcpy(x.matricula,"4567");
    strcpy(x.materia, "INIF");
    ponec(c, x);

}
