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


int CantElemLSO = 0;


void LSO_Localizar(Alumno l[], char codigo[], int *exito, int *pos) {
    int i = 0;
    while  (i<CantElemLSO && strcasecmp(l[i].codigo, codigo) < 0) {
        i++;
    }
    *pos = i;
    if (i<CantElemLSO&&strcasecmp(l[*pos].codigo, codigo)==0) {
        *exito = 1;
    } else {
        *exito = 0;
    }
}

void LSO_Alta(Alumno l[], Alumno ElementoAlta, int *exito) {
    int pos, exitoLocalizar = 0, i;
    LSO_Localizar(l, ElementoAlta.codigo, &exitoLocalizar, &pos);


    if (!exitoLocalizar) {
        if (CantElemLSO < MAXALUMNOS) {
            // Realizamos el corrimiento para insertar en la posici�n correcta
            for (i = CantElemLSO; i > pos; i--) {
                l[i] = l[i - 1];
            }

            l[pos] = ElementoAlta;
            CantElemLSO++;
            *exito = 1;
        } else {
            *exito = -1;
        }
    } else {
        *exito = 2;

    }
}

void LSO_Baja(Alumno l[], char codigo[], int *exito){
int pos, exitoLocalizar=0, i;

LSO_Localizar(l, codigo,  &exitoLocalizar, &pos);
if(exitoLocalizar){

   if(confirma(l, pos)==1){
    for(i=pos; i < CantElemLSO-1; i++){
        l[i] = l[i+1];
    }
    CantElemLSO--;//Reducimos el numero de elementos

    *exito=1; //Se dio de baja correctamente

        } else {
            *exito = 0;

        }
    } else {
        *exito = 0;

    }
}
int confirma(Alumno l[], int pos){
    int confirmacion=0;
 printf("¿Esta seguro que quiere dar de baja al alumno con codigo %s?\n", l[pos].codigo);
    MostrarAlumno(l[pos]);
   printf("Ingrese un 1 para confirmar, o cualquier otro numero para cancelar: ");
   scanf("%d", &confirmacion);
   return confirmacion;
}




void MostrarEstructura(Alumno l[]) {
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
    LSO_Localizar(l, codigo, &exitoLocalizar, &pos);
    if(exitoLocalizar){
        *Elem = l[pos]; //Copiamos la informacion del alumno encontrado
        *exito = 1;//Evocacion exitosa
    }else{
        *exito=0;
    }

}


#endif // LSO_H_INCLUDED
