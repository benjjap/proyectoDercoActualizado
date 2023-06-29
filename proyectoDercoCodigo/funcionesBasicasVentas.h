//
// Created by gerar on 5/28/2023.
//

#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#ifndef PROYECTODERCO_FUNCIONESBASICASVENTAS_H
#define PROYECTODERCO_FUNCIONESBASICASVENTAS_H

/*
 buscarCompra recorre la lista circular doblemente enlazada de tipo NodoCompras y busca el nodo
 según su código de compra retornando 1 si encuentra l nodo o 0 si no lo encuentra
 */

int buscarCompra(struct NodoCompras *ventas,int codeCompra){
    struct NodoCompras *rec;
    if(ventas!=NULL){
        rec=ventas;
        do {
            if(rec->datosCompra->codigoCompra==codeCompra) return 1;
            rec=rec->sig;
        }while(rec!=ventas);
    }
    return 0;
}

/*
 agregarAVentas toma la lista circular doblemente enlazada y referenciada de tipo NodoCompras y reserva memoria
 y agrega a la lista un nuevo nodo a esta
 */

int agregarAVentas(struct NodoCompras **head,struct Compra *venta){
    struct NodoCompras *nuevo=NULL;
    if(*head==NULL)
    {
        *head=(struct NodoCompras *)malloc(sizeof(struct NodoCompras));
        (*head)->sig=(*head)->ant=(*head);
        (*head)->datosCompra=venta;
        return 1;
    }else
    {
        if(buscarCompra(*head,venta->codigoCompra)==0)
        {
            nuevo=(struct NodoCompras *) malloc(sizeof(struct NodoCompras));
            nuevo->ant=(*head)->ant;
            nuevo->sig=(*head);
            (*head)->ant=(*head)->ant->sig=nuevo;
            nuevo->datosCompra=venta;
            return 1;
        }
        return 0;
    }
}

/*
 buscarYRetornarCompra recorre la lista doblemente enlazada de tipo NodoCompras y buscar según el código de compra
 el nodo y si lo encuentra retorna los datos del nodo de tipo Compra y si no retorna NULL si no lo encuentra

 */

struct Compra *buscarYRetornarCompra(struct NodoCompras *ventas,int codeCompra){
    struct NodoCompras *rec;
    if(ventas!=NULL){
        rec=ventas;
        do {
            if(rec->datosCompra->codigoCompra==codeCompra) return rec->datosCompra;
            rec=rec->sig;
        }while(rec!=ventas);
    }
    return NULL;
}

/*
 buscarYActualizarDatosCompra recorre la lista doblemente enlazada circular y busca según el código de compra el nodo
 buscado y actualiza los datos del nodo por los ingresados anteriormente por el usuario
 */

int buscarYActualizarDatosCompra(struct NodoCompras **head,struct Compra *venta){
    struct NodoCompras *rec;
    if(*head!=NULL) {
        rec=*head;
        do {
            if(rec->datosCompra->codigoCompra==venta->codigoCompra){
                rec->datosCompra=venta;
                return 1;
            }
            rec=rec->sig;
        }while(rec!=*head);
    }
    return 0;
}

/*
 eliminarVenta recorre la lista circular doblemente enlazada referenciada de tipo NodoCompras y busca según el código
 de compra el nodo para luego eliminar este nodo de la lista
 */

int eliminarVenta(struct NodoCompras **ventas,int codeCompra){
    struct NodoCompras *rec;
    if(*ventas!=NULL) {
        rec=*ventas;
        do {
            if(rec->datosCompra->codigoCompra==codeCompra){
                if(rec->ant==(*ventas) && rec->sig==(*ventas) && rec==*ventas){
                    (*ventas)=NULL;
                    return 1;
                }else{
                    if(rec==*ventas){
                        (*ventas)=(*ventas)->sig;
                        (*ventas)->ant=rec->ant;
                        rec->ant->sig=(*ventas);
                    }else{
                        rec->ant->sig=rec->sig;
                        rec->sig->ant=rec->ant;
                    }
                    rec=NULL;
                    return 1;
                }
            }
            rec=rec->sig;
        }while(rec!=*ventas);
    }
    return 0;
}


int eliminarVenta2(struct NodoCompras **ventas,int codeCompra){
    struct NodoCompras *rec;
    if((*ventas)!=NULL)
    {
        rec=(*ventas);
        do {
            if(rec->datosCompra->codigoCompra==codeCompra)
            {
                if(rec==(*ventas))
                {
                    if(rec->sig==(*ventas))
                    {
                        (*ventas)=NULL;
                        return 1;
                    }
                    else
                    {
                        rec->sig->ant=rec->ant;
                        rec->ant->sig=rec->sig;
                        (*ventas)=rec->sig;
                        return 1;
                    }
                }
                else
                {
                    rec->ant->sig = rec->sig;
                    rec->sig->ant = rec->ant;
                    return 1;
                }
            }
            rec=rec->sig;
        }while(rec!=(*ventas));
    }
    return 0;
}


/*
 mostrarVentas recorre la lista circular doblemente de tipo NodoCompras y muestra los datos de cada nodo de la lista
 */
void mostrarVentas(struct NodoCompras *ventas)
{
    if(ventas!=NULL)
    {
        printf("Compras efectuadas en la consecionaria Derco\n");
        struct NodoCompras *rec=ventas;
        do {
            printf("Id Venta= %d con un valor de %d pesos Chilenos,  Rut Cliente %s\n",rec->datosCompra->codigoCompra, rec->datosCompra->valorCompra, rec->datosCompra->rutCliente);
            rec=rec->sig;
        }while(rec!=ventas);
    }
}



#endif //PROYECTODERCO_FUNCIONESBASICASVENTAS_H
