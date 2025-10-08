#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXALUMNOS 130
#define MRAL 174 //130/M=0,75 ---> M=130/0.75 = 173, 333... = 174
typedef struct {
    char codigo[8];
    char nombreyapellido[80];
    char correo[23];
    int nota;
    char condicion[11];
} Alumno;

int CantElemRAL=0, RAL_c=0, RAL_t_E=0, RAL_t_F=0, RAL_max_E=0, RAL_max_F=0, RAL_evocar_E=0, RAL_evocar_F=0;
float RAL_medio=0;

int hashing (char* x, int MRAL) {
 int longitud , i ;
 int contador =0;
 longitud=strlen(x);
 for ( i =0; i< longitud ; i++)
 contador +=((int)x[i]) * (i+1);
 return (contador %MRAL);
 }

 void RAL_inicializar(Alumno r[]){
 int i;
     for (i=0; i<MRAL; i++){
        strcpy(r[i].codigo, "-1");//marca de celda virgen
     }
 }

void Localizar_RAL(Alumno l[], char codigo[], int *exito, int *pos, int opcion) {
    int i = hashing(codigo, MRAL), c=0, posf, flag=0;
    if (opcion==3){
        RAL_c++;
    }
     int comp = strcasecmp(l[i].codigo, codigo);
     int virgen = strcasecmp(l[i].codigo, "-1");
     int libre = strcasecmp(l[i].codigo, "-2");
    while (c<MRAL&&virgen!=0&&comp!=0){//controlar no recorrer los M baldes, que no sea una celda virgen y que no sea el codigo que buscamos
            if (libre==0&&flag==0){ //guarda la primera celda libre
             flag=1;
             posf=i;
            }
        i=(i+1)%MRAL;
        c++;
        if (opcion==3){
        RAL_c++;
        }
        comp = strcasecmp(l[i].codigo, codigo);
     virgen = strcasecmp(l[i].codigo, "-1");
      libre = strcasecmp(l[i].codigo, "-2");
    }
    if (comp==0){ //si lo encontramos, exito
        *pos=i;
        *exito=1;
    }
        else {
            *exito=0;
            if (libre==0){ //si paramos en una celda libre, retornamos esa
            *pos=posf;
            }
                else *pos=i;
    }

}

void Alta_RAL(Alumno a[], Alumno alumno_nuevo, char codigo[], int *exito){
int exitoLocalizar, pos;
        Localizar_RAL(a, codigo, &exitoLocalizar, &pos, 0);
        if (!exitoLocalizar){
            a[pos]=alumno_nuevo;
            *exito=1;
            CantElemRAL++;

        } else *exito=2;

}

void Baja_RAL(Alumno a[], char codigo[], int *exito, Alumno e){
    int exitoLocalizar, pos;
    Localizar_RAL(a, codigo, &exitoLocalizar, &pos, 0);
    if (!exitoLocalizar){
        *exito=0; //no se encontró el elemento
    }
    else   if (sondif(a, pos, e)){
        *exito=-1; //no es el mismo elemento
    }
    else {
        strcpy(a[pos].codigo, "-2");//-2: marca de celda libre
        *exito=1;
        CantElemRAL--;
    }
}
void Evocar_RAL(Alumno a[], Alumno *e, char codigo[], int *exito){ //agregar parámetro de costo
    int exitoLocalizar, pos;
     Localizar_RAL(a, codigo, &exitoLocalizar, &pos, 3);
     if(exitoLocalizar){
        *e=a[pos];
        *exito=1;
        RAL_evocar_E++;
           if (RAL_c>RAL_max_E){
            RAL_max_E=RAL_c;
        }
        RAL_t_E+=RAL_c;
        RAL_c=0;
     }
     else {
        *exito=0;
        RAL_evocar_F++;
           if (RAL_c>RAL_max_F){
            RAL_max_F=RAL_c;
        }
        RAL_t_F+=RAL_c;
        RAL_c=0;
     }
}
int sondif(Alumno l[], int pos, Alumno elemento)
{
    return (strcasecmp(l[pos].nombreyapellido, elemento.nombreyapellido) +
            strcasecmp(l[pos].codigo, elemento.codigo) +
            strcasecmp(l[pos].condicion, elemento.condicion)+
            strcasecmp(l[pos].correo, elemento.correo)+
            l[pos].nota!=elemento.nota);
}

void MostrarEstructura_RAL(Alumno l[]) {
    system("cls");
    int i, c=0, virgen, libre;
    if (CantElemRAL == 0) {
        printf("La lista de alumnos esta vacia.\n");
        return;
    }
    for (i = 0; i < CantElemRAL; i++) {

    virgen = strcasecmp(l[i].codigo, "-1");
    libre = strcasecmp(l[i].codigo, "-2");

               printf("Celda: %d \n", i);
        if (virgen==0){
            printf("Estado: virgen \n");
        }
        if (libre==0){
            printf("Estado: Libre \n");
        }
        if (virgen!=0&&libre!=0){
        printf("Estado: Ocupada. Datos del alumno: \n");
        printf("Alumno %d:\n", i + 1);
        printf("Codigo: %s\n", l[i].codigo);
        printf("Nombre y Apellido: %s\n", l[i].nombreyapellido);
        printf("Correo: %s\n", l[i].correo);
        printf("Nota: %d\n", l[i].nota);
        printf("------------------------------------------\n");
        c++;
        if (c==5){
            getchar();
            c=0;
        }
        }
    }
}
#endif // RAL_H_INCLUDED
