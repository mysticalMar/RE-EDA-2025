//Grupo 55: Romano Mariana, Fiona Masucci

#include <stdio.h>
#include <stdlib.h>
#include "ABB.h"
#include "LSO.h"
#include "LIBB.h"

 int lectura_operaciones(Alumno LSO[], Alumno* LIBT[], Arbol *arbol) {
    init_ABB(arbol);  // Inicializa el árbol
    int opcion = 0, exitoLSO = 0, exitoLIBT = 0, exitoABB=0, exito = 0, duplicados = 0, codigoduplicado;
    int prestadorescargadosLSO = 0, prestadorescargadosLSOBB = 0;
    char codigo[7];
    FILE *fp;
    Alumno aux_LSO;
    Alumno* aux_LIBT;
    AlumnoABB aux_ABB;
    char nombre_completo[160];

    if ((fp = fopen("OperacionesAlumnos.txt", "r")) == NULL) {
    printf("No se pudo abrir el archivo 'OperacionesAlumnos.txt'.\n");
    return 0;
} else {

    while (fscanf(fp, "%d", &opcion) == 1) {
        aux_LIBT = (Alumno*)malloc(sizeof(Alumno));
        if (aux_LIBT == NULL) {
            printf("Error en la asignaci�n de memoria\n");
            break;
        }

        if (opcion == 1 || opcion == 2) {
           fscanf(fp, "%8s\n", aux_LIBT->codigo);
           fgets(nombre_completo, sizeof(nombre_completo), fp);
                        fscanf(fp, "%s\n", aux_LIBT->correo);
                        fscanf(fp, "%d\n", &aux_LIBT->nota);
                        fscanf(fp, "%s\n", aux_LIBT->condicion);
                        nombre_completo[strcspn(nombre_completo, "\n")] = '\0';
                        char coma = strchr(nombre_completo, ',');
                        if (coma != NULL) {
                            coma = '\0';
                            strcpy(aux_LIBT->nombreyapellido, nombre_completo);
            }


            aux_LSO=*aux_LIBT;

             aux_ABB.nota= aux_LSO.nota;
            strcpy(aux_ABB.apellidoynombre, aux_LSO.nombreyapellido);
            strcpy(aux_ABB.condicion, aux_LSO.condicion);
            strcpy(aux_ABB.codigo, aux_LSO.codigo);
            strcpy(aux_ABB.correo, aux_LSO.correo);
        }
                 else
                fscanf(fp, "%s", codigo);


            switch (opcion) {
                case 1: if (LIBT_elementos<MAXALUMNOS){
                LIBT_Alta(LIBT, aux_LIBT, &exitoLIBT);
                }
                if (CantElemLSO<MAXALUMNOS){
                LSO_Alta(LSO, aux_LSO, &exitoLSO);
                }
                Alta_ABB(arbol, aux_ABB, &exitoABB);
                break;
                case 2:
                LIBT_MostrarAlumno(aux_LIBT);
                MostrarAlumno(aux_LSO);
                exitoLIBT=LIBT_Baja(LIBT, codigo, aux_LIBT);
                exitoLSO=LSO_Baja(LSO, codigo, aux_LSO);
                printf("exito LIBT_ %d \n", exitoLIBT);
                printf("exito lso %d \n", exitoLSO);
                Baja_ABB(arbol, aux_ABB);

                break;

                case 3:
                LIBT_Evocar(LIBT, aux_LIBT, codigo, &exitoLIBT);
                LSO_Evocar(LSO,  &aux_LSO, codigo, &exitoLSO);
                Evocar_ABB(arbol, codigo, &exitoABB, &aux_ABB);
                break;
            }
    }


    }

    fclose(fp);
    return 1;
 }


int main()
{
    int opcion;
    Alumno* LIBT[130], nuevo_alumno;
    int i;

    for (i = 0; i < MAXALUMNOS; i++) {
    LIBT[i] = NULL;
}
    Alumno LSO[130];
    Arbol arbol;
    init_ABB(&arbol);
   do {
    printf("1: Comparacion de Estructuras \n");
    printf("2: Mostrar: ABB \n");
    printf("3: Mostrar: LIBT\n");
    printf("4: Mostrar: LSO \n");
    printf("5: Salir \n");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1:
            if (LIBT_elementos>0||CantElemLSO>0||cantAltas>0){
                printf("Las estructuras deben estar vacias. \n");
                break;
            }
            lectura_operaciones(&LSO, LIBT, &arbol);
            printf("________________Costos Obtenidos________________ \n");
            printf("--------Lista Invertida con busqueda por Triseccion-------- \n");
            printf("Costos de Altas \n");
            if (LIBT_Altas==0){
                printf("No se realizaron altas. \n");
            }
            else {
            printf("Cantidad total de altas: %d \n", LIBT_Altas);
            printf("Coste maximo de corrimientos: %f \n", LIBT_max_Alta);
            printf("Coste medio de corrimientos: %f \n", LIBT_total_Alta/LIBT_Altas);
            }
            printf("---------------------------------------------------------- \n");
            printf("Costos de Bajas \n");
            if (LIBT_Bajas==0){
                printf("No se realizaron bajas. \n");
            }
                else {
                    printf("Cantidad total de bajas: %d \n", LIBT_Bajas);
                    printf("Coste maximo de corrimientos: %f \n", LIBT_max_Baja);
                    printf("Coste medio de corrimientos: %f \n", LIBT_total_Baja/LIBT_Bajas);
                }
             printf("---------------------------------------------------------- \n");

           printf("Costos de Evocaciones Exitosas\n");
            if (LIBT_Evocaciones_Exitosas==0){
                printf("No se realizaron evocaciones exitosas. \n");
            }
                else {
                printf("Cantidad total de evocaciones exitosas: %d \n", LIBT_Evocaciones_Exitosas);
                  printf("Coste maximo de celdas consultadas: %d \n", LIBT_max_celdas_Exito);
                    printf("Coste medio de celdas consultadas: %f \n", LIBT_total_celdas_Exito/LIBT_Evocaciones_Exitosas);
                }

                printf("Costos de Evocaciones No Exitosas\n");
            if (LIBT_Evocaciones_NoExitosas==0){
                printf("No se realizaron evocaciones no exitosas. \n");
            }
                else {
                printf("Cantidad total de evocaciones no exitosas: %d \n", LIBT_Evocaciones_NoExitosas);
                  printf("Coste maximo de celdas consultadas: %d \n", LIBT_max_celdas_NoExitosa);
                    printf("Coste medio de celdas consultadas: %f \n", LIBT_total_celdas_NoExitosa/LIBT_Evocaciones_NoExitosas);
            }


            printf("--------Lista Secuencial Ordenada con examinacion secuencial-------- \n");
            if (LSO_Altas==0){
                printf("No se realizaron altas. \n");
            }
            else {
                printf("Cantidad total de altas: %d \n", LSO_Altas);
                  printf("Coste maximo de corrimientos: %d \n", LSO_max_Alta);
            printf("Coste medio de corrimientos: %f \n", LSO_total_Alta/LSO_Altas);
            }
             printf("---------------------------------------------------------- \n");
            printf("Costos de Bajas \n");
            if (LSO_Bajas==0){
                printf("No se realizaron bajas. \n");
            }
                else {
                    printf("Cantidad total de bajas: %d \n", LSO_Bajas);
                    printf("Coste maximo de corrimientos: %d \n", LSO_max_Baja);
                    printf("Coste medio de corrimientos: %f \n", LSO_total_Baja/LSO_Bajas);
                }
             printf("---------------------------------------------------------- \n");

           printf("Costos de Evocaciones Exitosas\n");
            if (LSO_Evocaciones_Exitosas==0){
                printf("No se realizaron evocaciones exitosas. \n");
            }
                else {
                printf("Cantidad total de evocaciones exitosas: %d \n", LSO_Evocaciones_Exitosas);
                  printf("Coste maximo de celdas consultadas: %d \n", LSO_max_celdas_Exito);
                    printf("Coste medio de celdas consultadas: %f \n", LSO_total_celdas_Exito/LSO_Evocaciones_Exitosas);
                }

                printf("Costos de Evocaciones No Exitosas\n");
            if (LSO_Evocaciones_NoExitosas==0){
                printf("No se realizaron evocaciones no exitosas. \n");
            }
                else {
                printf("Cantidad total de evocaciones no exitosas: %d \n", LSO_Evocaciones_NoExitosas);
                  printf("Coste maximo de celdas consultadas: %d \n", LSO_max_celdas_NoExitosa);
                    printf("Coste medio de celdas consultadas: %f \n", LSO_total_celdas_NoExitosa/LSO_Evocaciones_NoExitosas);
            }


           printf("--------Arbol Binario de Busqueda-------- \n");
            printf("Costos de Alta en ABB \n");
            if (cantAltas > 0) {
                printf("Costo medio de Alta en ABB: %.2f\n", cantActPtrosAlta * 0.5 / cantAltas);
                printf("Costo maximo de Alta en ABB: %d\n", MaxAlta);
            } else {
                printf("No se realizaron altas. \n");
            }
         printf("---------------------------------------------------------- \n");
            printf("Costos de Baja en ABB \n");
            if (cantBajas > 0) {
                printf("Costo medio de Baja en ABB: %.2f\n", cantActPtrosBaja * 0.5 / cantBajas);
                printf("Costo maximo de Baja en ABB: %d\n", MaxBaja);
            } else {
                printf("No se realizaron bajas. \n");
            }
         printf("---------------------------------------------------------- \n");
            printf("Costos de Evocacion en ABB \n");
            if (cantEvocaciones > 0) {
                printf("Costo medio de Evocacion en ABB: %.2f\n", (float)comparacionesEvocar / cantEvocaciones);
                printf("Maximo de comparaciones en una Evocacion en ABB: %d\n", MaxComparaciones);
            } else {
                printf("No se realizaron evocaciones. \n");
            }
             printf("---------------------------------------------------------- \n");
            break;

        case 2:
            MostrarEstructura_ABB(&arbol);
            break;
        case 3:
            LIBT_MostrarEstructura(LIBT);
            break;
        case 4:
            LSO_MostrarEstructura(LSO);
            break;
        case 5:
            printf("Saliendo...\n");
            break;

        default:
            printf("Opci�n no v�lida\n");
            break;

}

} while (opcion != 5);

return 0;
}

