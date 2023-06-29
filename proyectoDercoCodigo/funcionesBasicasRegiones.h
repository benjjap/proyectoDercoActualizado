//
// Created by gerar on 5/31/2023.
//
#include "structs.h"
#include "stdio.h"
#define cantRegiones 16

#ifndef PROYECTODERCO_FUNCIONESBASICASREGIONES_H
#define PROYECTODERCO_FUNCIONESBASICASREGIONES_H

/*
 mostrarRegiones recibe el arreglo de regiones, esta función recorre e imprime todas las regiones ubicadas en el arreglo
 de forma enumerada.
 */

void mostrarRegiones(struct Regiones **regiones){
    int i, j=1;
    for (i = 0;  i<cantRegiones ;i++) {
        if(regiones[i] != NULL){
            printf("%d. Nombre: %s\n",regiones[i]->sigla,regiones[i]->Nombre);
        }
    }
}

/*
 crearRegiones sirve para crear y agregar las regiones en el arreglo del sistema Derco. Se crea el arreglo, se asigna
 memoria al arreglo, y se pregunta por los datos de la region (nombre de la region y asignación de la lista de sucursales)
 y se retorna el arreglo.
 */

struct Regiones **crearRegiones(){
    struct Regiones**regiones=NULL;
    int i;
    char buffer[500];
    regiones=(struct Regiones **) malloc(cantRegiones * sizeof(struct Regiones *));
    for ( i = 0; i <cantRegiones ; ++i) {
        regiones[i]=(struct Regiones *) malloc(sizeof(struct Regiones));
        regiones[i]->sigla=i+1;
        printf("\nIngrese el nombre de la %d region: ",i+1);
        scanf("%[^\n]s ",buffer);
        getchar();
        regiones[i]->Nombre=(char *) malloc((strlen(buffer)+1) * sizeof(char));
        strcpy(regiones[i]->Nombre,buffer);
        regiones[i]->sucursales=NULL;
    }
    return regiones;
}

void eliminarRegion(struct SistemaDerco *derco, int siglaRegion){
    int i;

    if(derco == NULL) return;
    if(derco->regiones == NULL){
        printf("No existen regiones!");
        return;
    }
    for(i=0;i<cantRegiones;i++){
        if(derco->regiones[i]!=NULL){
            if(derco->regiones[i]->sigla == siglaRegion){
                derco->regiones[i] = NULL;
                printf("Region eliminada con exito\n");
            }
        }
    }
    if(!eliminado){
        printf("No se encontro la region a eliminar\n");
    }
}

void cambiarNombreRegion(struct SistemaDerco *derco, int siglaRegion){
    int i;
    char buffer[500];

    if(derco == NULL) return;
    if(derco->regiones == NULL){
        printf("No existen regiones!");
        return;
    }
    for(i=0;i<cantRegiones;i++){
        if(derco->regiones[i] != NULL){
            if(derco->regiones[i]->sigla == siglaRegion){
                printf("Ingrese el nuevo nombre de la %d region: ", derco->regiones[i]->sigla);
                getchar();
                scanf("%[^\n]s ",buffer);
                getchar();
                strcpy(derco->regiones[i]->Nombre,buffer);
                printf("Nombre de la region modificado con exito!");
            }
        }
    }
}


#endif //PROYECTODERCO_FUNCIONESBASICASREGIONES_H
