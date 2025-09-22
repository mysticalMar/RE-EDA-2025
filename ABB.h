#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAUSA_ALUMNOS 5
#define MAXALUMNOS 130
typedef struct {
    char codigo [8];
    char apellidoynombre[80];
    char correo[23];
    int nota;
    char condicion[11];
} AlumnoABB;
//Variables de costo
int maxAltaExitosa = 0, cantActPtrosAltaExitosa = 0, cantAltasExitosas = 0;
int maxBajaExitosa = 0, cantActPtrosBajaExitosa = 0, cantBajasExitosas = 0;
int maxEvocExitosa = 0, cantComparacionesEvocExitosa = 0, cantEvocacionesExitosas = 0;
int maxEvocNoExitosa = 0, cantComparacionesEvocNoExitosa = 0, cantEvocacionesNoExitosas = 0;


typedef struct nodoA {
    AlumnoABB datos;
    struct nodoA *izq;
    struct nodoA *der;
} NodoA;

typedef struct {
    NodoA *raiz;
    NodoA *cur;
    NodoA *padre;
} Arbol;

void init_ABB(Arbol *a) {
    a->raiz = NULL;
    a->cur = NULL;
    a->padre = NULL;
}


void Localizar_ABB(Arbol *a, char codigo [], int *exito, int *comparaciones) {
    *comparaciones = 0;
    a->cur = a->raiz;
    a->padre = NULL;

    while (a->cur != NULL) {
        (*comparaciones)++;  // Costo por comparaci�n
        if (strcasecmp(a->cur->datos.codigo,codigo)==0) {
            *exito = 1;
            return;  // codigo encontrado
        }
        a->padre = a->cur;
        if (strcasecmp(a->cur->datos.codigo,codigo)<0) {//no se si es < o >
            a->cur = a->cur->izq;
        } else {
            a->cur = a->cur->der;
        }
    }
    *exito = 0;  // No se encontr� el codigo
}

void Alta_ABB(Arbol *a, AlumnoABB nuevoAlumno, int *exito) {
    int exitoLocalizar = 0, comparaciones = 0;
    int actualizacionestemp = 0;
    Localizar_ABB(a, nuevoAlumno.codigo, &exitoLocalizar, &comparaciones);

    NodoA *nuevoNodo = (NodoA *)malloc(sizeof(NodoA));
    if (nuevoNodo == NULL) {
        *exito = 0;  // Error en la asignaci�n de memoria
        return;
    }
    nuevoNodo->datos = nuevoAlumno;
    nuevoNodo->der = NULL;
    nuevoNodo->izq = NULL;

    if (a->raiz == NULL) {
        a->raiz = nuevoNodo;  // El �rbol estaba vac�o
        actualizacionestemp++;  // Actualizaci�n de puntero
        *exito = 1;
    } else if (exitoLocalizar) {
        *exito = 2;  // codigo duplicado
        free((void *)nuevoNodo);  // Liberar el nodo asignado si es duplicado
    } else {
        if (strcasecmp(nuevoAlumno.codigo, a->padre->datos.codigo)<0) {
            a->padre->izq = nuevoNodo;
        } else {
            a->padre->der = nuevoNodo;
        }
        actualizacionestemp++;  // Actualizaci�n de puntero
        *exito = 1;
    }

    if (*exito == 1) {
        cantAltasExitosas++;  // Incrementar el n�mero de altas exitosas
        cantActPtrosAltaExitosa += actualizacionestemp * 0.5;  // Sumar costo por actualizaciones de punteros
        if (actualizacionestemp > maxAltaExitosa) {
            maxAltaExitosa = actualizacionestemp;  // Actualizar el m�ximo de actualizaciones
        }
    }
}

int Baja_ABB(Arbol *a, AlumnoABB alumno) {
    int exitoLocalizar = 0;
    int comparaciones = 0;
    int actualizacionestemp = 0;

    // Localizar el nodo a eliminar
    Localizar_ABB(a, alumno.codigo, &exitoLocalizar, &comparaciones);

    if (!exitoLocalizar) {
        return 0;  // alumno no encontrado
    }

    NodoA *nodoeliminar = a->cur;


    if (strcasecmp(nodoeliminar->datos.codigo, alumno.codigo) !=0 ||
        strcmp(nodoeliminar->datos.apellidoynombre, alumno.apellidoynombre) != 0 ||
        strcmp(nodoeliminar->datos.correo, alumno.correo) != 0 ||
        nodoeliminar->datos.nota != alumno.nota ||
        strcmp(nodoeliminar->datos.condicion, alumno.condicion) != 0) {
        return 0;
    }

    // Caso 1: Nodo hoja (sin hijos)
    if (nodoeliminar->izq == NULL && nodoeliminar->der == NULL) {
        if (a->padre == NULL) {
            a->raiz = NULL;
        } else if (a->padre->izq == nodoeliminar) {
            a->padre->izq = NULL;
        } else {
            a->padre->der = NULL;
        }
        free(nodoeliminar);
        actualizacionestemp++;
    }
    // Caso 2: Nodo con un solo hijo
    else if (nodoeliminar->izq == NULL || nodoeliminar->der == NULL) {
        NodoA *hijo = (nodoeliminar->izq != NULL) ? nodoeliminar->izq : nodoeliminar->der;

        if (a->padre == NULL) {
            a->raiz = hijo;
        } else if (a->padre->izq == nodoeliminar) {
            a->padre->izq = hijo;
        } else {
            a->padre->der = hijo;
        }
        free(nodoeliminar);
        actualizacionestemp++;
    }
    // Caso 3: Nodo con dos hijos � usar menor de los mayores
    else {
        NodoA *padreMenorMayor = nodoeliminar;
        NodoA *menorMayor = nodoeliminar->der;

        // Buscar el menor del sub�rbol derecho
        while (menorMayor->izq != NULL) {
            padreMenorMayor = menorMayor;
            menorMayor = menorMayor->izq;
        }

        // Copiar datos al nodo a eliminar
        nodoeliminar->datos = menorMayor->datos;

        // Eliminar el nodo del menor de los mayores
        if (padreMenorMayor == nodoeliminar) {
            padreMenorMayor->der = menorMayor->der;
        } else {
            padreMenorMayor->izq = menorMayor->der;
        }

        free(menorMayor);
        actualizacionestemp += 2;  // Copia + ajuste punteros
    }

    // Costos de baja
    cantBajasExitosas++;
    cantActPtrosBajaExitosa += actualizacionestemp * 0.5;
    if (actualizacionestemp > maxBajaExitosa) {
        maxBajaExitosa = actualizacionestemp;
    }

    return 1;
}






void MostrarEstructura_ABB(Arbol *a) {
    if (a->raiz == NULL) {
        printf("El arbol esta vacio.\n");
        return;
    }

    NodoA *pila[MAXALUMNOS];  // Pila para manejar hasta 130 alumnos
    int tope = -1;
    int contador = 0;

    // Iniciar con la ra�z del �rbol
    pila[++tope] = a->raiz;

    // Mientras haya nodos en la pila
    while (tope != -1 && contador < MAXALUMNOS) {
        NodoA *actual = pila[tope--];  // Pop de la pila

        // Mostrar la informaci�n del alumno
        printf("Alumno %d:\n", contador + 1);
        printf("Codigo: %s\n", actual->datos.codigo);
        printf("Apellido y Nombre: %s\n", actual->datos.apellidoynombre);
        printf("Correo: %s\n", actual->datos.correo);
        printf("Nota: %d\n", actual->datos.nota);
        printf("Condicion: %s\n", actual->datos.condicion);

        if (actual->izq != NULL) {
            printf("Codigo del Hijo izquierdo: %s\n", actual->izq->datos.codigo);
        } else {
            printf("Codigo del Hijo izquierdo: NULL\n");
        }
        if (actual->der != NULL) {
            printf("Codigo del Hijo derecho: %s\n", actual->der->datos.codigo);
        } else {
            printf("Codigo del Hijo derecho: NULL\n");
        }

        printf("----------------------\n");
        contador++;

        if (contador % PAUSA_ALUMNOS == 0) {
            printf("Presione Enter para continuar...\n");
            getchar();
        }
        /// Primero empujamos el hijo derecho, luego el izquierdo para procesarlos en orden preorden
        if (actual->der != NULL) {
            pila[++tope] = actual->der;
        }
        if (actual->izq != NULL) {
            pila[++tope] = actual->izq;
        }
    }
}

 int Evocar_ABB(Arbol *a, char codigo [], int *exito, AlumnoABB *alumnoEncontrado) {
    int comparacionestemp = 0;

    // Localizar el nodo por DNI
    Localizar_ABB(a, codigo, exito, &comparacionestemp);

    if (*exito) {
        *alumnoEncontrado = a->cur->datos;

        // Actualizar costos de evocaci�n exitosa
        cantComparacionesEvocExitosa += comparacionestemp;
        if (comparacionestemp > maxEvocExitosa) {
            maxEvocExitosa = comparacionestemp;
        }
        cantEvocacionesExitosas++;

        return 1;  // Evocaci�n exitosa
    } else {
        cantComparacionesEvocNoExitosa += comparacionestemp;
        if (comparacionestemp > maxEvocNoExitosa) {
            maxEvocNoExitosa = comparacionestemp;
        }
        cantEvocacionesNoExitosas++;

        return 0;  // Evocaci�n no exitosa
    }
}

//Funcion para que no sea sensible a mayuscula y minuscula
//la dejo por las dudas. Fiona
int confirma_ABB(AlumnoABB alumno1, AlumnoABB alumno2) {
    int c = 1;

    if (strcasecmp(alumno1.apellidoynombre, alumno2.apellidoynombre) != 0) {
        c = 0;
    }
    if (strcasecmp(alumno1.correo, alumno2.correo) != 0) {
        c = 0;
    }
    if (strcasecmp(alumno1.condicion, alumno2.condicion) != 0) {
        c = 0;
    }

    }

#endif // ABB_H_INCLUDED
