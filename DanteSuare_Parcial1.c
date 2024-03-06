#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXE 100
struct AVentas
{
    char marca[20];
    char modelo[20];
    unsigned int anio;
    char patente[8];
    int modv;
    float precio;
};
struct MVentas
{
    int modv;
    int desc;
    int garantia;
};

struct Final
{
    char marca[20];
    char modelo[20];
    int cantidad;
    int anionuevo;
    float preciopromdio;
};

struct VentasAnio
{
    unsigned int anio;
    int ventas;
};

void opera();
int retabla(struct MVentas m[], struct Final f);
void tabla(struct MVentas *m, int *cm);


int main()
{
    struct Mventas m[MAXE];
    int cm; //contador modalidades
    tabla(&m, &cm);
    opera(&m);

    return 0;
}


void opera(struct Mventas m[])
{
    FILE *autosbin, *modalidadbin;
    autosbin = fopen("AutosVenta.bin", "rb");


    struct AVentas a;
    struct Final f;
    struct VentasAnio v[MAXE];
    int c; //contador por modelo
    float cp; //acumulador precio
    int cam,i=0,j,vt =0; //Cantidad Autos de la Marca
    float preciomin;
    char modelomin[20];
    char modelomax[20];
    char marcamax[20];
    unsigned int aniomax;
    v[0].anio=1;

    if (autosbin == NULL)
    {
        printf("El archivo en opera no se abrio correctamente");
    }
    else
    {
        fread(&a, sizeof(struct AVentas), 1, autosbin);
        while(!feof(autosbin))
        {

            strcpy(f.marca,a.marca);
            printf("Marca: %-20s\n", f.marca); //Marca
            cam=0;
            while((strcmp(f.marca,a.marca))==0 && (!feof(autosbin)))
            {
                cam++;
                c=0;
                cp=0;
                strcpy(f.modelo,a.modelo);
                printf("Modelo\tCantidad autos\t A�o mas nuevo\t Precio contado promedio\n");//Modelo
                printf("%-20s\t", f.modelo);
                f.anionuevo= a.anio;
                aniomax=a.anio;
                aniomax=a.anio;
                marcamax=a.marca;
                modelomax=a.modelo;
                strcpy(modelomin, a.modelo);
                while((strcmp(f.modelo,a.modelo)==0) && (strcmp(f.marca, a.marca)) && (!feof(autosbin)))
                {

                    if (f.anionuevo<a.anio || a.anio==0)
                    {
                        f.anionuevo=a.anio;
                    }
                    if (aniomax>a.anio)
                    {
                        aniomax=a.anio;
                        marcamax=a.marca;
                        modelomax=a.modelo;
                    }
                    for(j=0; j<i ; j++)
                    {
                        if (a.anio==v[j].anio)
                        {
                            v[j].ventas++;
                            vt++;
                        }
                    }
                    if (j==i)
                    {
                        i++;
                        v[i].anio=a.anio;
                        v[i].ventas++;
                        vt++;
                    }
                    c++;
                    cp += ((a.precio*3)-((a.precio*3*m[retabla(a.modv)].desc)/100));
                    fread(&a, sizeof(struct AVentas), 1, autosbin);
                }

                printf("%d\t", c);//A�o mas nuevo del modelo
                printf("%d\t", f.anionuevo);//Cantidad del modelo
                f.preciopromdio=((float)cp/c);
                if (f.preciopromdio<preciomin)
                {
                    preciomin = f.preciopromdio
                    strcpy(modelomin, f.modelo);
                }
                printf("%.2f\n", f.preciopromdio);//Precio promedio contado por modelo
                printf("Modelo con menor precio promedio: %s \t %.2f\n", modelomin,preciomin)//Modelo con menor precio promedio
            }
            printf("Cantidad de autos de la marca: %d\n", cam);
        }
        printf("Marca y modelo del auto mas viejo: %-20s \t %-20s \t (%d)\n", marcamax, modelomax, aniomax);
        printf("Modelo \t Cantidad \t Porcentaje\n");
        for (int h = 0; h<i ; i++)
        {
            printf("%d %d %.2f\n", v[h].anio, v[h].ventas, ((float)((v[h].ventas)*100/vt)));
        }
    }

   fclose(autosbin);
}
int retabla(struct MVentas m[MAXE], struct Final f)
{
    int i=0;
    while(m[i].modv != f.modv)
    {
        i++;
    }
    return i;

}

void tabla(struct MVentas *m[MAXE], int *cm)
{
    FILE *bin;
    bin = fopen("ModalidadVentas.bin", "rb");
    cm=0;
    fread(m[0], sizeof(struct Mventas), 1, bin);
    while(!feof(bin))
    {
        cm++;
        fread(&m[cm], sizeof(struct Mventas), 1, bin);
    }

    fclose(bin);
}
