
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

            if (opcion == 1) {
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
                //LIBT_MostrarAlumno(aux_LIBT);

                aux_LSO=*aux_LIBT;

                //MostrarAlumno(aux_LSO);

                 aux_ABB.nota= aux_LSO.nota;
                strcpy(aux_ABB.apellidoynombre, aux_LSO.nombreyapellido);
                strcpy(aux_ABB.condicion, aux_LSO.condicion);
                strcpy(aux_ABB.codigo, aux_LSO.codigo);
                strcpy(aux_ABB.correo, aux_LSO.correo);
                if (LIBT_elementos<MAXALUMNOS){
                LIBT_Alta(LIBT, aux_LIBT, &exitoLIBT);
                }
                LSO_Alta(LSO, aux_LSO, &exitoLSO);
                Alta_ABB(arbol, aux_ABB, &exitoABB);
            }

            else if (opcion == 2) {
                fscanf(fp, "%s", aux_LIBT->codigo);
                LIBT_Baja(LIBT, aux_LIBT->codigo, aux_LIBT, 0);
                LSO_Baja(LSO, aux_LSO.codigo, &exitoLSO);
                Baja_ABB(arbol, aux_ABB);
            }

            else if (opcion == 3) {
                fscanf(fp, "%s", codigo);
                LIBT_Evocar(LIBT, aux_LIBT, codigo, &exitoLIBT);
                LSO_Evocar(LSO,  &aux_LSO, codigo, &exitoLSO);
                Evocar_ABB(arbol, codigo, &exitoABB, &aux_ABB);
            }

            free(aux_LIBT);
        }

        fclose(fp);
        return 1;
     }

    }



   int main()
{
        int opcion, opcion2, opcion3;
        Alumno* LIBT[130], nuevo_alumno;
        Alumno LSO[130];
        Arbol arbol;
        init_ABB(&arbol);
       do {
        printf("1: Comparacion de Estructuras \n");
        printf("3: Mostrar: ABB \n");
        printf("4: Mostrar: LIBT\n");
        printf("5: Mostrar: LSO \n");
        printf("6: Salir \n");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                lectura_operaciones(LIBT, &LSO, &arbol);
                printf("bajas libt: %d", LIBT_Bajas);

                //printf("bajas lvo: %d", LSO_Bajas);
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

    } while (opcion != 6);

    return 0;
}

