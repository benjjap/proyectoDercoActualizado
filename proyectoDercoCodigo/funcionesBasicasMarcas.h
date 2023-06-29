//
// Created by gerar on 5/28/2023.
//
#define cantRegiones 16
#include "structs.h"
#include <stdlib.h>
#include "funcionesBasicasSucursales.h"
#ifndef PROYECTODERCO_FUNCIONESBASICASMARCAS_H
#define PROYECTODERCO_FUNCIONESBASICASMARCAS_H

/*
 Esta función recibe la lista de marcas a partir del head y el id de la marca que se desea eliminar.
 Aquí se recorre la lista de marcas para eliminar la marca buscada, donde se revisa en que posición está el nodo y se elimina

 */

int eliminarMarca(struct NodoMarcas **head, int idMarca)
{
    struct NodoMarcas *rec;
    if((*head)->ant==NULL && (*head)->sig==NULL) {
        (*head)=NULL;
        return 1;
    }
    rec = (*head);
    while(rec != NULL)
    {
        if(rec->datosMarca->id == idMarca)
        {
            if(rec==*head) {
                (*head)=(*head)->sig;
                (*head)->ant=NULL;
            }else if(rec->sig == NULL)
            {
                rec->ant->sig = NULL;
            }
            else
            {
                rec->ant->sig = rec->sig;
                rec->sig->ant=rec->ant;
            }
            return 1;
        }
        rec = rec->sig;
    }
    return 0;
}

/*
 Esta función recibe la lista de Marcas y la marca que se va a actualizar. Dentro recorremos la lista buscando la marca,
 una vez encontramos la marca, se realizaran los cambios de la marca, retornando 1.
 */

int actualizarMarca(struct NodoMarcas **head, struct Marca *marca)
{
    struct NodoMarcas *rec;
    if((*head) != NULL)
    {
        rec = (*head);
        while(rec != NULL)
        {
            if(rec->datosMarca->id == marca->id)
            {
                rec->datosMarca = marca;
                return 1;
            }
            rec = rec->sig;
        }
    }
    return 0;
}

/*
 Se recibe la lista de marcas y la marca que se desea agregar. Si la lista está vacía se agrega la marca en la primera
 posición (head), si no se recorre la lista hasta la última posición para agregar la marca.

 */

int agregarMarcaASucursal(struct NodoMarcas **head, struct Marca *marca)
{
    struct NodoMarcas *nuevo, *rec;
    if((*head) == NULL)
    {
        (*head) = (struct NodoMarcas *) malloc (sizeof (struct NodoMarcas));
        (*head)->datosMarca = marca;
        (*head)->ant = (*head)->sig = NULL;
        return 1;
    }
    else
    {
        nuevo = (struct NodoMarcas *) malloc (sizeof (struct NodoMarcas));
        rec = (*head);
        while(rec != NULL)
        {
            if(rec->sig == NULL)
            {
                rec->sig = nuevo;
                nuevo->ant=rec;
                nuevo->sig=NULL;
                nuevo->datosMarca=marca;
                return 1;
            }
            rec = rec->sig;
        }
    }
    return 0;
}

/*
 hayProductosAutosEnMarcas buscara si existen productos para autos en alguna marca de la sucursal retornando 1 si encuentra
 por lo menos una marca con productos y retornara 0 si no encuentra ningun producto
 */

int hayProductosAutosEnMarcas(struct NodoMarcas *marcas){
    struct NodoMarcas *rec=marcas;
    while(rec!=NULL){
        if(rec->datosMarca->productosAutos!=NULL) return 1;
        rec=rec->sig;
    }
    return 0;
}

/*
 hayModelosEnMarcas buscara si existen modelos de autos en alguna marca de la sucursal retornando 1 si encuentra
 por lo menos una marca con modelos y retornara 0 si no encuentra ningun modelo
 */

int hayModelosEnMarcas(struct NodoMarcas *marcas){
    struct NodoMarcas *rec=marcas;
    while(rec!=NULL){
        if(rec->datosMarca->autos!=NULL) return 1;
        rec=rec->sig;
    }
    return 0;
}


/*
 buscarMarcaporId recibe la lista de marcas y el id de la marca buscada. Se recorre la lista y se pregunta si el id de
 la marca en la posición en la estamos es la que buscamos, si se encontró retorna 1 y si no se retorna 0.

 */

int buscarMarcaporId(struct NodoMarcas *marcas,int idMarcaBuscada){
    struct NodoMarcas *rec=marcas;
    while(rec!=NULL){
        if(rec->datosMarca->id==idMarcaBuscada) return 1;
        rec=rec->sig;
    }
    return 0;
}

/*
 RetornarMarcaPorId recibe la lista de marcas y el id de la marca buscada. Se recorre la lista de marcas y se pregunta
 si el id de la marca es igual al de la marca buscada, si se encontró se retorna el struct de marca, si no se encontró,
 se retorna NULL.
 */

struct Marca *RetornarMarcaPorId(struct NodoMarcas *marcas, int idMarcaBuscada)
{
    struct NodoMarcas *rec=marcas;
    while(rec!=NULL){
        if(rec->datosMarca->id==idMarcaBuscada) return rec->datosMarca;
        rec=rec->sig;
    }
    return NULL;
}

/*
 mostrarMarcasEnumeradas recibe la lista de marcas. Esta función imprime la lista de marcas de forma enumerada, su nombre
 e ID.

 */

void mostrarMarcasEnumeradas(struct NodoMarcas *marcas){
    int i=1;
    struct NodoMarcas *rec=marcas;
    while(rec!=NULL){
        printf("-%d. Nombre: %s -ID: %d \n",i,rec->datosMarca->nombre,rec->datosMarca->id);
        i++;
        rec=rec->sig;
    }
}


/*
 mostrarMarcasSucursal recibe la lista de sucursales y el id de la sucursal buscada. Se recorre la lista en busca de la
 sucursal deseada comparando id con cada sucursal de la lista. si se encontró, se llama a la función mostrarMarcasEnumeradas
 y se retorna 1.
 */
int mostrarMarcasSucursal(struct NodoSucursales*sucursales,int idSucursal){
    struct NodoSucursales *rec;
    if(sucursales!=NULL){
        rec=sucursales;
        do {
            if(rec->datosSucursal->id==idSucursal){
                if(rec->datosSucursal->marcasAutos!=NULL){
                    mostrarMarcasEnumeradas(rec->datosSucursal->marcasAutos);
                    return 1;
                }
                return 0;
            }
            rec=rec->sig;
        }while(rec!=sucursales);
    }
    return 0;
}


/*
 comprobarSiEnSucursalMarcaEstaVacio recibe la lista de sucursales y el id de la sucursal que se está buscando.
 La función recorre la lista circular de sucursales comparando nodo por nodo si tiene el mismo id buscado y si la lista
 de marcas es nula, si es así retorna 1, si no retorna 0.
 */

int comprobarSiEnSucursalMarcaEstaVacio(struct NodoSucursales *sucursales,int idSucursalBuscada){
    struct NodoSucursales *rec;
    if(sucursales!=NULL){
        rec=sucursales;
        do {
            if(rec->datosSucursal->id==idSucursalBuscada && rec->datosSucursal->marcasAutos!=NULL) return 1;
            rec=rec->sig;
        }while(rec!=sucursales);
    }
    return 0;
}

#endif //PROYECTODERCO_FUNCIONESBASICASMARCAS_H
