#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXE 100

typedef struct{
    char pat[8];
    unsigned int mod;
    unsigned int cser;
    unsigned int kmus;
    float precio;
}AutoHisto;

typedef struct{
    char pat[8];
    unsigned int mod;
    unsigned int km;
}Services;

typedef struct{
    unsigned int mod;
    unsigned int km1;
    unsigned int km2;
    float precio;
}Tarifas;

typedef struct{
    unsigned int mod;
    float imp;
    int cc;
}Modelos;

void bin();
void opera();
void creatabla();
void creatablamodelos(Tarifas t[], int n, int *x, Modelos m[]);
int buscamodelos(Modelos m[], int x, int mod);
int buscatabla(Services s, Tarifas t[], int n);

int main(){
    bin();
    printf("\n--------------------------------------------------\n");
    opera();

    return 0;
}

void bin(){
    FILE *a1, *a2, *a3, *b1, *b2, *b3;
    a1=fopen("AutoHisto.txt", "r");
    a2=fopen("Services.txt", "r");
    a3=fopen("Tarifas.txt", "r");
    b1=fopen("AutoHisto.bin", "wb");
    b2=fopen("Services.bin", "wb");
    b3=fopen("Tarifas.bin", "wb");

    AutoHisto a;
    Services s;
    Tarifas t;

    if(a1==NULL||a2==NULL||a3==NULL||b1==NULL||b2==NULL||b3==NULL)
        perror("Un archivo de bin no se abrio correctamente.\n");
    else{
        while(fscanf(a1, "%s %u %u %u %f", a.pat, &a.mod, &a.cser, &a.kmus, &a.precio)==5){
            fwrite(&a, sizeof(AutoHisto), 1, b1);
            //printf("bin1: %s %u %u %u %f\n", a.pat, a.mod, a.cser, a.kmus, a.precio);
            }
        while(fscanf(a2, "%s %u %u", s.pat, &s.mod, &s.km)==3){
            fwrite(&s, sizeof(Services), 1, b2);
            //printf("bin2: %s %u %u\n", s.pat, s.mod, s.km);
            }
        while(fscanf(a3, "%u %u %u %f", &t.mod, &t.km1, &t.km2, &t.precio)==4){
            fwrite(&t, sizeof(Tarifas), 1, b3);
            //printf("bin3: %u %u %u %f\n", t.mod, t.km1, t.km2, t.precio);
            }
    }

    fclose(a1);fclose(a2);fclose(a3);fclose(b1);fclose(b2);fclose(b3);
}

void creatabla(Tarifas t[], int *n){
    FILE *bin=fopen("Tarifas.bin", "rb");
    (*n)=0;

    if(bin!=NULL){
        while(fread(&t[(*n)], sizeof(Tarifas), 1 ,bin))
            (*n)++;
    }
    else
        perror("El archivo de creatabla no se abrio correctamente.\n");
    fclose(bin);
}

void creatablamodelos(Tarifas t[], int n, int *x, Modelos m[]){
    (*x)=0;
    for (int i=0;i<n; i++){
        if(t[i].mod!=t[i+1].mod){
            m[(*x)].mod=t[i].mod;
            m[(*x)].cc=0;
            m[(*x)].imp=0;
            //printf("mod %d: %u\n", (*x), m[(*x)].mod);
            (*x)++;
        }
    }
    printf("\n %d \n", (*x));
}

int buscamodelos(Modelos m[], int x, int mod){
    int i=0;
    while(i<x && (mod!=m[i].mod))
        i++;
    if(i<x)
        return i;
    else{
        perror("Eror en buscamodelo.\n");
        return -1;
    }
}


int buscatabla(Services s, Tarifas t[], int n){
    int i=0;
    while(i<n && (s.mod!=t[i].mod) && ((s.km<t[i].km1) && (s.km>t[i].km2)))
        i++;

    if(i<n)
        return i;
    else{
        perror("Error en buscatabla.\n");
        return -1;
    }
}

void opera(){
    FILE *autos, *service, *actualizado;
    autos=fopen("AutoHisto.bin", "rb");
    service=fopen("Services.bin", "rb");
    actualizado=fopen("Actualizado.bin", "wb");
    //Tabla
    Tarifas t[MAXE];
    int n;
    creatabla(t, &n);
    //Tabla 2
    Modelos m[MAXE];
    int x;
    creatablamodelos(t, n, &x, m);

    AutoHisto a, act;
    Services s;
    float total=0;

    if(autos==NULL || service==NULL || actualizado==NULL)
        perror("Un archivo de opera no se abrio correctamente.\n");
    else{
        fread(&a, sizeof(AutoHisto), 1, autos);
        fread(&s, sizeof(Services), 1, service);
        while(!feof(autos) && !feof(service)){

            if(!strcmp(a.pat, s.pat)){ // Se actualiza ultimo service
                act=a;
                while(!feof(service) && !strcmp(a.pat, s.pat)){
                    act.cser++;
                    act.kmus=a.kmus;
                    act.precio=t[buscatabla(s, t, n)].precio;
                    fread(&s, sizeof(Services), 1, service);

                }
                if(strcmp(act.pat, "ZZZZZZZ")){
                    m[buscamodelos(m, x, act.mod)].cc++;
                    m[buscamodelos(m, x, act.mod)].imp+=act.precio;
                    total+=act.precio;
                    fwrite(&act, sizeof(AutoHisto), 1, actualizado);
                }
                printf("1: %s %u %u %u %f\n", act.pat, act.mod, act.cser, act.kmus, act.precio);
                fread(&a, sizeof(AutoHisto), 1, autos);
            }

            else if(strcmp(a.pat, s.pat)>0){ //Auto nuevo
                act.cser=0;
                strcpy(act.pat,s.pat);
                act.mod=s.mod;
                while(!feof(service) && strcmp(a.pat, s.pat)>0){
                    act.cser++;
                    act.kmus=s.km;
                    act.precio=t[buscatabla(s, t, n)].precio;
                    m[buscamodelos(m, x, act.mod)].imp+=act.precio;
                    total+=act.precio;
                    fread(&s, sizeof(Services), 1, service);
                }
                m[buscamodelos(m, x, act.mod)].cc++;

                printf("2: %s %u %u %u %f\n", act.pat, act.mod, act.cser, act.kmus, act.precio);
                fwrite(&act, sizeof(AutoHisto), 1, actualizado);
            }

            else{ //No se modifica |No hubo service|

                m[buscamodelos(m, x, a.mod)].cc++;
                m[buscamodelos(m, x, a.mod)].imp+=a.precio;
                total+=a.precio;
                fwrite(&a, sizeof(AutoHisto), 1, actualizado);
                printf("3: %s %u %u %u %f\n", a.pat, a.mod, a.cser, a.kmus, a.precio);
                fread(&a, sizeof(AutoHisto), 1, autos);
            }

        }

    }
    printf("Modelo\tImporte\tPorcentaje del total\n");
    for (int i=0; i<x-1; i++){
        printf("%u \t %.2f \t %.2f\n", m[i].mod, m[i].imp, (m[i].imp*100/total));
    }

    fclose(autos);fclose(service);
}

