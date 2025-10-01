

#ifndef LIBT_H_INCLUDED
#define LIBT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LSO.h"


//variables de costos
int LIBT_Altas=0,
    LIBT_Bajas=0,
    LIBT_Evocaciones=0;
    LIBT_celdas_consultadas=0, LIBT_total_celdas=0, LIBT_max_celdas=0;
float LIBT_medio_Alta=0, LIBT_medio_Baja=0, LIBT_medio_Evocar=0,
LIBT_total_Alta, LIBT_corr_Alta=0, LIBT_max_Alta=0,
LIBT_total_Baja=0, LIBT_corr_Baja=0, LIBT_max_Baja=0;
//Explicacion de variables:
//LIBB_Altas: total de altas exitosas en la lista
//LIBB_total_Alta: son todos los corrimientos en la lista
//LIBB_corr_Alta: son los corrimientos en cada ejecucion. Auxiliar para el m�ximo.
//LIBB_max_Alta: cantidad de corrimientos m�s alto en el alta.
//LIBB_medio_Alta: coste medio del alta.
int LIBT_elementos=0;

void LIBT_Localizar(Alumno* l[], char codigo[], int *exito, int *pos, int costo)   //li inclusivo ls inclusivo, testigo y segmento mas grande a izquierda
{

        if (LIBT_elementos==0)
        {
            *exito=0;
            *pos=0;
        }
        else
        {
            int li = 0;
    int ls = LIBT_elementos - 1;
    int m;
    *exito = 0;

    while (li <= ls) {

    m = (li+ls+1) / 2;

    if (costo == 1) {
        LIBT_celdas_consultadas++;
    }

    int comp = strcasecmp(l[m]->codigo, codigo);

    if (comp == 0) { //encontró el elemento
        *exito = 1;
        *pos = m;
        break;
    } else if (comp > 0) { //el elemento es menor al x en la posicion m
        ls = m - 1;
    } else {
       //el elemento es mayor al x en la posicion m
        li = m + 1;
    }
}

if (*exito == 0) {
    *pos = li;
}
    }
    //calculos de costos en caso de evocacion
    if (costo==1){
            //chequear el maximo
        if (LIBT_celdas_consultadas>LIBT_max_celdas){
            LIBT_max_celdas=LIBT_celdas_consultadas;
        }
        //actualizar la cantidad total de celdas consultadas
        LIBT_total_celdas+=LIBT_celdas_consultadas;
        //resetear el contador temporal de celdas
        LIBT_celdas_consultadas=0;
    }
}




void LIBT_Alta(Alumno* l[], Alumno* ElementoAlta, int *exito)
{
    int pos, exitoLocalizar = 0, i;
    LIBT_Localizar(l, ElementoAlta->codigo, &exitoLocalizar, &pos, 0);
    if (!exitoLocalizar)
    {
        if (LIBT_elementos < MAXALUMNOS)
        {
            // Realizamos el corrimiento para insertar en la posici�n correcta
            for (i = LIBT_elementos; i > pos; i--)
            {
                l[i] = l[i - 1];
                LIBT_corr_Alta=LIBT_corr_Alta+0.5;
            }
            // Insertamos el elemento en la posici�n encontrada
            l[pos]=ElementoAlta;

            LIBT_elementos++;

            *exito = 1;  // Alta exitosa
            LIBT_Altas++;

                     //Calculos de costos
            if (LIBT_corr_Alta>LIBT_max_Alta)
            {
                LIBT_max_Alta=LIBT_corr_Alta;
            }
            LIBT_total_Alta+=LIBT_corr_Alta;
            LIBT_corr_Alta=0;

        }
        else
        {
            *exito = -1;  // Alta no exitosa, lista llena o DNI inv�lido

        }
    }
    else
    {
        *exito = 2;  // Alta no exitosa, DNI repetido

    }

}

int LIBT_Baja(Alumno* l[], char codigo[], Alumno* e)
{
        int pos, exitoLocalizar=0, i, c=0;
        LIBT_Localizar(l, codigo,  &exitoLocalizar, &pos, 0);
        if(!exitoLocalizar)
        {
            return 0; //no se encontró el elemento
        }
            else
            {

                if (sondif(l, pos, e)) return 3; //no es el mismo elemento

                else
                {
                  free(l[pos]);
                    for(i=pos; i<LIBT_elementos-1; i++)
                    {
                        l[i] = l[i+1];
                        LIBT_corr_Baja+=0.5;
                    }
                    LIBT_elementos--;//Reducimos el numero de elementos
                    LIBT_Bajas++;
                    return 1;
                }
            }


        //Calculos de costos
        if (LIBT_corr_Baja>LIBT_max_Baja)
        {
            LIBT_max_Baja=LIBT_corr_Baja;
        }
        LIBT_total_Baja+=LIBT_corr_Baja;
        LIBT_corr_Baja=0;
}



void LIBT_MostrarAlumno(Alumno* a){

            printf("Codigo: %s\n", a->codigo);
            printf("Nombre: %s\n", a->nombreyapellido);
            printf("Correo: %s\n", a->correo);
            printf("Nota: %d\n", a->nota);
            printf("Condicion: %s\n", a->condicion);
}


void LIBT_Evocar(Alumno* LIBB[], Alumno** Elem, char codigo[], int *exito)
{
    int pos, exitoLocalizar;
    LIBT_Localizar(LIBB, codigo, &exitoLocalizar, &pos, 1);
    if (exitoLocalizar)
    {
        *Elem = LIBB[pos];
        *exito = 1;
        LIBT_Evocaciones++;
    }
    else
    {
        *Elem = NULL;
        *exito = 0;
    }
}



void LIBT_MostrarEstructura(Alumno* l[]) {
    system("cls");
    int i, c=0;

    if (LIBT_elementos == 0) {
        printf("La lista de alumnos esta vacia. \n");
        return;
    }
    for (i = 0; i < LIBT_elementos; i++) {
        printf("--------- Listado de Alumnos ---------\n");
        printf("Alumno %d:\n", i + 1);
        LIBT_MostrarAlumno(l[i]);
        printf("------------------------------------------\n");
        c++;
        if (c==5){
            getchar();
            c=0;
        }
    }
}

int sondif(Alumno* l[], int pos, Alumno* elemento)
{
    return (strcasecmp(l[pos]->nombreyapellido, elemento->nombreyapellido) +
            strcasecmp(l[pos]->codigo, elemento->codigo) +
            strcasecmp(l[pos]->condicion, elemento->condicion)+
            strcasecmp(l[pos]->correo, elemento->correo)+
            l[pos]->nota==elemento->nota);
}



#endif // LIBT_H_INCLUDED
