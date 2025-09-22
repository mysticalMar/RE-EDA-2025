#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include <string.h>
#define MAXALUMNOS 130

typedef struct {
    char codigo[8];
    char nombreyapellido[80];
    char correo[23];
    int nota;
    char condicion[11];
} Alumno;
 //variables para costos
int LSO_Altas=0, LSO_total_Alta, LSO_corr_Alta=0, LSO_max_Alta=0,
    LSO_Bajas=0, LSO_total_Baja=0, LSO_corr_Baja=0, LSO_max_Baja=0,
    LSO_celdas_consultadas=0, LSO_total_celdas=0, LSO_max_celdas=0, LSO_Evocaciones=0;
float LSO_medio_Alta=0, LSO_medio_Baja=0, LSO_medio_Evocar=0;

int CantElemLSO = 0;


void LSO_Localizar(Alumno l[], char codigo[], int *exito, int *pos, int costo) {
    int i = 0;
    while  (i<CantElemLSO && strcasecmp(l[i].codigo, codigo) < 0) {
        i++;
        if (costo==1){
            LSO_celdas_consultadas++;
        }
    }
    *pos = i;
    if (i<CantElemLSO&&strcasecmp(l[*pos].codigo, codigo)==0) {
        *exito = 1;
    } else {
        *exito = 0;
    }
    //calculos de costos en caso de evocacion
    if (costo==1){
            //chequear el maximo
        if (LSO_celdas_consultadas>LSO_max_celdas){
            LSO_max_celdas=LSO_celdas_consultadas;
        }
        //actualizar la cantidad total de celdas consultadas
        LSO_total_celdas+=LSO_celdas_consultadas;
        //resetear el contador temporal de celdas
        LSO_celdas_consultadas=0;
    }
}

void LSO_Alta(Alumno l[], Alumno ElementoAlta, int *exito) {
    int pos, exitoLocalizar = 0, i;
    LSO_Localizar(l, ElementoAlta.codigo, &exitoLocalizar, &pos, 0);


    if (!exitoLocalizar) {
        if (CantElemLSO < MAXALUMNOS) {
            // Realizamos el corrimiento para insertar en la posici�n correcta
            for (i = CantElemLSO; i > pos; i--) {
                l[i] = l[i - 1];
                LSO_corr_Alta++;
            }
            l[pos] = ElementoAlta;
            CantElemLSO++;
            LSO_Altas++;
            *exito = 1;
        } else {
            *exito = -1;
        }
    } else {
        *exito = 2;

    }
     //Calculos de costos
    if (LSO_corr_Alta>LSO_max_Alta)
    {
        LSO_max_Alta=LSO_corr_Alta;
    }
    LSO_total_Alta+=LSO_corr_Alta;
    LSO_corr_Alta=0;
}

void LSO_Baja(Alumno l[], char codigo[], int *exito){
int pos, exitoLocalizar=0, i;

LSO_Localizar(l, codigo,  &exitoLocalizar, &pos, 0);
if(exitoLocalizar){


    for(i=pos; i < CantElemLSO-1; i++){
        l[i] = l[i+1];
        LSO_corr_Baja++;
    }
    CantElemLSO--;//Reducimos el numero de elementos
    LSO_Bajas++;

    *exito=1; //Se dio de baja correctamente

    } else {
        *exito = 0;

    }
          //Calculos de costos
        if (LSO_corr_Baja>LSO_max_Baja)
        {
            LSO_max_Baja=LSO_corr_Baja;
        }
        LSO_total_Baja+=LSO_corr_Baja;
        LSO_corr_Baja=0;

}




void LSO_MostrarEstructura(Alumno l[]) {
    system("cls");
    int i, c=0;

    if (CantElemLSO == 0) {
        printf("La lista de alumnos esta vacia. \n");
        return;
    }
    for (i = 0; i < CantElemLSO; i++) {
        printf("--------- Listado de Alumnos ---------\n");
        printf("Alumno %d:\n", i + 1);
        MostrarAlumno(l[i]);
        printf("------------------------------------------\n");
        c++;
        if (c==5){
            getchar();
            c=0;
        }
    }
}

void MostrarAlumno(Alumno a){
            printf("Codigo: %s\n", a.codigo);
            printf("Nombre: %s\n", a.nombreyapellido);
            printf("Correo: %s\n", a.correo);
            printf("Nota: %d\n", a.nota);
            printf("Condicion: %s\n", a.condicion);
}

void LSO_Evocar(Alumno l[], Alumno *Elem, char codigo[], int *exito){
    int pos, exitoLocalizar;
    LSO_Localizar(l, codigo, &exitoLocalizar, &pos, 1);
    if(exitoLocalizar){
        *Elem = l[pos]; //Copiamos la informacion del alumno encontrado
        *exito = 1;//Evocacion exitosa
        LSO_Evocaciones++;
    }else{
        *exito=0;
    }

}


#endif // LSO_H_INCLUDED
