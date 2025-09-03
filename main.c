//Grupo 55 Fiona Masucci y Mariana Romano

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LSO.h"



int Modificar(Alumno LSO[], Alumno *Elem, int codigo, int *exito){
      int pos, exitoLocalizar = 0;

    Alumno ElemBusqueda;
    strcpy(ElemBusqueda.codigo, codigo);
    LSO_Localizar(LSO, codigo, &exitoLocalizar, &pos);

    if (!exitoLocalizar) {
        *exito = 0;
        return 0;
    } else {
        int decision;
        int seguir = 1;
        do {
            system("cls");
            printf("Este es el alumno encontrado:\n");
            MostrarAlumno(LSO[pos]);

            printf("\nIndique que campo desea modificar:\n");
            printf("<1> Nombre y Apellido\n<2>Nota\n<3> Condicion\n");
            printf("<4> Correo\n<5> Salir de modificaciones\n");
            scanf("%d", &decision);

            if (decision >= 1 && decision <= 6) {
                system("cls");
                switch (decision) {
                    case 1:
                        printf("Ingrese el nuevo Nombre y Apellido: \n");
                        scanf(" %[^\n]", LSO[pos].nombreyapellido);
                        break;
                    case 2:
                        printf("Ingrese la nueva nota: \n");
                        scanf("%d", & LSO[pos].nota);
                        break;
                    case 3:
                        printf("Ingrese la nueva condicion \n");
                        scanf(" %[^\n]", LSO[pos].condicion);
                        break;
                    case 4:
                        printf("Ingrese el nuevo correo: \n");
                        scanf(" %[^\n]", LSO[pos].correo);
                        break;
                    case 5:
                        seguir = 0;
                        break;
                }
            } else {
                printf("Error! Ingrese una opcion valida\n.");
                system("pause");
            }

            if (seguir) {
                printf("¿Desea modificar otro campo? (1: Si, 0: No)\n");
                scanf("%d", &seguir);
            }

        } while (seguir == 1);

        *exito = 1;
        return 1;
    }
}



int MemorizacionPrevia(Alumno LSO[]){
   FILE *fp;
    Alumno aux;
    int exito = 0, duplicados = 0;
    int codigoduplicado;
    char nombre_completo[160];
printf("cant elemen: %d \n", CantElemLSO);

    if ((fp = fopen("Alumnos.txt", "r")) == NULL) {
        printf("No se pudo abrir el archivo 'Alumnos.txt'.\n");
        return 0;
    }else{
           while (!(feof(fp))&&(CantElemLSO<MAXALUMNOS)) {
                        fscanf(fp, "%8s\n", aux.codigo);
                        fgets(nombre_completo, sizeof(nombre_completo), fp);
                        fscanf(fp, "%s\n", aux.correo);
                        fscanf(fp, "%d\n", &aux.nota);
                        fscanf(fp, "%s\n", aux.condicion);
                        nombre_completo[strcspn(nombre_completo, "\n")] = '\0';
                        char coma = strchr(nombre_completo, ',');
                        if (coma != NULL) {
                            coma = '\0';
                            strcpy(aux.nombreyapellido, nombre_completo);
                        }

            LSO_Alta(LSO, aux, &exito);
            if (exito){
                CantElemLSO++;
            }
            }
    }



    // Cerrar el archivo
    fclose(fp);
    printf("cant elemen: %d \n", CantElemLSO);
    return 1;
}


void carga(Alumno *nuevoAlumno){

             printf("Ingrese el codigo del nuevo alumno (7 digitos): \n");
             scanf("%s", &nuevoAlumno->codigo);
             printf("Ingrese el nombre y apellido: \n");
             scanf(" %[^\n]", &nuevoAlumno->nombreyapellido);
             printf("Ingrese el correo: \n");
             scanf(" %[^\n]", &nuevoAlumno->correo);
             printf("Ingrese la nota: \n");
             scanf(" %d", &nuevoAlumno->nota);
             if (nuevoAlumno->nota==0){
                char condicion[11]="Ausente";
               strcpy(nuevoAlumno->condicion, condicion);
             }
             else {
             printf("Ingrese la condicion: \n");
             scanf(" %[^\n]", &nuevoAlumno->condicion);
             }
}
int main()
{
        int opcion, exito;
        char codigo[7];
        Alumno LSO[MAXALUMNOS];
        Alumno e, AlumnoEvocado, nuevoAlumno;

        do {
       printf("----- MENU PRINCIPAL -----\n");
       printf("1. Ingresar un alumno\n");
       printf("2. Eliminar alumnos existentes\n");
       printf("3. Modificar datos de un alumno\n");
       printf("4. Consultar la informacion completa asociada a un alumno\n");
       printf("5. Cargar alumnos desde un archivo\n");
       printf("6. Mostrar todos los alumnos\n");
       printf("7. Salir\n");
       printf("---------------------------\n");
       printf("Ingrese una opcion: ");
       scanf(" %d", &opcion);
        system("cls");
        switch(opcion){
     case 1:
            if(CantElemLSO >=MAXALUMNOS){
            printf("Error: la lista de alumnos esta llena. \n");
            system("pause");
            break;
         }
         system("cls");


             carga(&nuevoAlumno);

             LSO_Alta(LSO, nuevoAlumno, &exito);

             if (exito == 1) {
                 printf("Alumno dado de alta con exito.\n");
             } else if (exito == 2) {
                     printf("Error: el codigo de alumno ya existe en la lista.\n");
                     int decision;
                     printf("¿Desea intentar con otro codigo  o salir al menu principal?\n");
                     printf("Ingrese 1 para intentar con otro codigo o 0 para salir al menu principal: ");
                     scanf("%d", &decision);
                     if (decision == 0) {
                         break;
                     }
             } else {
                 printf("Error: no se pudo dar de alta al alumno.\n");
             }
         system("pause");
         break;
     case 2:

        if (CantElemLSO==0){
            printf("Error: lista vacia \n");
            break;
            }
         do {
            system("cls");
            printf("Ingrese el codigo del alumno a dar de baja: \n");
            scanf("%s", codigo);
            LSO_Baja(LSO, codigo, &exito);
            if (exito == 1) {
            printf("Alumno dado de baja con exito.\n");
              break;  // Salimos del bucle si la baja es exitosa
            } else {
                    printf("No se pudo dar de baja al alumno con codigo %s.\n", codigo);
                    int opcionReintento;
                    printf("¿Desea intentar con otro codigo? (Cualquier numero: Si , 0: No): ");
                    scanf(" %d", &opcionReintento);
                    if (opcionReintento == 0) {
                            break;  // Salimos del bucle si el usuario no quiere intentar de nuevo
                        }
                    }
                } while (1);

                system("pause");
                break;
     case 3:
          if (CantElemLSO==0){
            printf("Error: lista vacia \n");
            break;
        }
        system("cls");
        printf("Ingrese el codigo del alumno a modificar: ");
        scanf("%s", codigo);
        Modificar(LSO, &e, codigo, &exito);
        if(exito){
            printf("Alumno modificado con exito. \n");
        }else{
            printf("Error: No se encontro el alumno. \n");
        }
        system("pause");
        break;
     case 4:
          if (CantElemLSO==0){
            printf("Error: lista vacia \n");
            break;
        }
        system("cls");
        printf("Ingrese el codigo del alumno a evocar: \n");
        scanf("%s", codigo);
        LSO_Evocar(LSO, &AlumnoEvocado, codigo, &exito);
        if(exito){
        printf("Alumno encontrado: \n");
        MostrarAlumno(AlumnoEvocado);
        }else{
            printf("Error: alumno no encontrado. \n");
        }
         break;
     case 5:
         system("cls");
         MemorizacionPrevia(LSO);
         system("pause");
         break;
     case 6:
          if (CantElemLSO==0){
            printf("Error: lista vacia \n");
            break;
        }
         system("cls");
         MostrarEstructura(LSO);
         system("pause");
         break;
     case 7:
          printf("Saliendo del programa. . . \n");
          break;
     default:
        printf("Opcion invalida intente nuevamente \n");
        system("pause");
        break;

       }
    }while(opcion != 7);


         }
