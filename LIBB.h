

#ifndef LIBB_H_INCLUDED
#define LIBB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LSO.h"


//variables de costos
int LIBT_Altas=0, LIBT_total_Alta, LIBT_corr_Alta=0, LIBT_max_Alta=0,
    LIBT_Bajas=0, LIBT_total_Baja=0, LIBT_corr_Baja=0, LIBT_max_Baja=0;
float LIBT_medio_Alta=0, LIBT_medio_Baja=0;
//Explicacion de variables:
//LIBB_Altas: total de altas exitosas en la lista
//LIBB_total_Alta: son todos los corrimientos en la lista
//LIBB_corr_Alta: son los corrimientos en cada ejecucion. Auxiliar para el m�ximo.
//LIBB_max_Alta: cantidad de corrimientos m�s alto en el alta.
//LIBB_medio_Alta: coste medio del alta.
int LIBT_elementos=0;

LIBT_Localizar(Alumno* l[], char codigo[], int *exito, int *pos)   //li inclusivo ls inclusivo, testigo y segmento mas grande a izquierda
{
        int control_celdas[LIBT_elementos];
        if (LIBT_elementos==0)
        {
            *exito=0;
            *pos=0;
        }
        else
        {
            int li,ls,m;
            li=0;
            ls=LIBT_elementos-1;

            while (li<=ls&&(strcasecmp(l[m]->codigo, codigo) != 0)){
            {
                m =(li+ls+1)/2;

                if (strcasecmp(l[m]->codigo, codigo) > 0)
                {
                    ls = m-1;
                }
                else
                {
                    li = m+1;
                }

            }
            if ((strcasecmp(l[m]->codigo, codigo)==0))
            {
                *exito= 1; //localizaci�n exitosa
                *pos=li;
            }
            else
            {
                *exito=0; //localizacion no exitosa
                *pos=li;
                if (l[li]->codigo<codigo)
                {
                *pos=*pos+1;
                }
            }
        }
    }
}




void LIBT_Alta(Alumno* l[], Alumno* ElementoAlta, int *exito)
{
    int pos, exitoLocalizar = 0, i;
    LIBT_Localizar(l, ElementoAlta->codigo, &exitoLocalizar, &pos);
    if (!exitoLocalizar)
    {
        if (LIBT_elementos < MAXALUMNOS)
        {
            // Realizamos el corrimiento para insertar en la posici�n correcta
            for (i = LIBT_elementos; i > pos; i--)
            {
                l[i] = l[i - 1];
                LIBT_corr_Alta++;
            }
            // Insertamos el elemento en la posici�n encontrada
            l[pos]=ElementoAlta;

            LIBT_elementos++;

            *exito = 1;  // Alta exitosa
            LIBT_Altas++;

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
    //Calculos de costos
    if (LIBT_corr_Alta>LIBT_max_Alta)
    {
        LIBT_max_Alta=LIBT_corr_Alta;
    }
    LIBT_total_Alta+=LIBT_corr_Alta;
    LIBT_corr_Alta=0;
}

int LIBT_Baja(Alumno* l[], char codigo[], Alumno* e, int modouser)
{
        int pos, exitoLocalizar=0, i, c=0;

        LIBT_Localizar(l, codigo,  &exitoLocalizar, &pos);
        if(!exitoLocalizar)
        {
            return 0;
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
                        LIBT_corr_Baja++;
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
    LIBT_Localizar(LIBB, codigo, &exitoLocalizar, &pos);
    if (exitoLocalizar)
    {
        *Elem = LIBB[pos];
        *exito = 1;
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
         printf("Codigo: %s\n", l[i]->codigo);
            printf("Nombre: %s\n", l[i]->nombreyapellido);
            printf("Correo: %s\n", l[i]->correo);
            printf("Nota: %d\n", l[i]->nota);
            printf("Condicion: %s\n", l[i]->condicion);
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



#endif // LIBB_H_INCLUDED
