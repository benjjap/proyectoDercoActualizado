//
// Created by gerar on 5/31/2023.
//

#include "structs.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "funcionesBasicasSucursales.h"
#include "funcionesBasicasMarcas.h"
#include "funcionesBasicasProductos.h"

#ifndef PROYECTODERCO_INTERFAZMARCA_H
#define PROYECTODERCO_INTERFAZMARCA_H

/*
    "interfazAgregadoMarcaSucursal" esta funcion esta destinada para que el usuario tenga un medio visual
    que le ayudara a la hora crear una marca y agregarla a la sucursal correspondiente.

    *Utilizando la biblioteca "time.h" y "stdlib.h" se generara un numero pseudo aleatorio para poder
    asignarle un ID a la nueva Marca a crear, para esto llamara a la funciones "agregarMarcaASucursal" Y
    "crearMarca"
*/
int interfazAgregadoMarcaSucursal(struct NodoSucursales*sucursales, int idScucursal)
{
    srand(time(NULL));
    int id=0;
    struct NodoSucursales *rec=sucursales;
    do
    {
        if(rec->datosSucursal->id==idScucursal) break;
        rec=rec->sig;
    }while(rec!=sucursales);


    do{
        id=rand();
    }while(buscarSucursal(sucursales,id)==1);

    agregarMarcaASucursal(&(rec->datosSucursal->marcasAutos), crearMarca(id));

    return 1;
}

/*
    "interfazActualizarMarcaSucursal" esta funcoón esta destinada para que el usuario tenga un medio visual
    que le ayudara a la hora de actualizar una marca, primero mostrando las sucursales disponibles para esto

    *La actualización consiste en cambiar el nombre de la sucursal para después llamar a la función "actualizarMarca".
*/

int interfazActualizarMarcaSucursal(struct NodoSucursales *sucursales, int idSucursal)
{

    int id;
    char NuevoNombre[50];
    struct NodoSucursales *rec=sucursales;

    struct Marca *actualizacion=NULL;

    do
    {
        if(rec->datosSucursal->id==idSucursal) break;
        rec=rec->sig;
    }while(rec!=sucursales);
    if(rec->datosSucursal->marcasAutos!=NULL){
        printf("Marcas disponibles para actualizar\n");
        mostrarMarcasEnumeradas(rec->datosSucursal->marcasAutos);
        do
        {
            printf("Ingrese  id de la marca que desea actualizar, asegurese que sea valido\n");
            scanf("%d",&id);
            actualizacion= RetornarMarcaPorId(rec->datosSucursal->marcasAutos,id);
        }while(actualizacion==NULL);


        printf("Ingrese el nuevo nombre para la marca %s\n",actualizacion->nombre);
        getchar();
        scanf("%[^\n]s ",NuevoNombre);
        getchar();

        actualizacion->nombre=NULL;

        actualizacion->nombre=(char *)malloc(sizeof(char)*strlen(NuevoNombre));
        strcpy(actualizacion->nombre,NuevoNombre);

        actualizarMarca(&(rec->datosSucursal->marcasAutos),actualizacion);
        return 1;
    }
    printf("No hay registros de marcas en esta sucursal\n");
    return 0;
}
/*
    "interfazEliminarMarcaSucursal" esta función esta destinada para que el usuario tenga un medio visual
    que le ayudara a la hora  de eliminar una marca, primero mostrando las sucursales disponibles para esto

    *La elimación se efectua llamando a la funcion "eliminarMarca".
*/

int interfazEliminarMarcaSucursal(struct NodoSucursales *sucursales, int  idSucursal)
{
    int id;
    struct NodoSucursales *rec=sucursales;
    struct Marca *aEliminar=NULL;
    do
    {
        if(rec->datosSucursal->id==idSucursal) break;
        rec=rec->sig;
    }while(rec!=sucursales);

    if(rec->datosSucursal->marcasAutos!=NULL){
        printf("Marcas disponibles para eliminar\n");
        mostrarMarcasEnumeradas(rec->datosSucursal->marcasAutos);
        do
        {
            printf("Ingrese id de la marca que desea eliminar, asegurese que sea valido\n");
            scanf("%d",&id);
            aEliminar= RetornarMarcaPorId(rec->datosSucursal->marcasAutos,id);
        }while(aEliminar==NULL);

        eliminarMarca(&(rec->datosSucursal->marcasAutos),id);
        printf("La marca %s ha sido eliminada exitosamente\n",aEliminar->nombre);

        return 1;
    }
    printf("No hay registros de marcas en esta sucursal\n");
        return 0;
}
#endif //PROYECTODERCO_INTERFAZMARCA_H
