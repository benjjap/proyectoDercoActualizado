//
// Created by gerar on 5/28/2023.
//
#define maxCompras 20
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include "funcionesBasicasProductos.h"
#include "funcionesBasicasVentas.h"

#ifndef PROYECTODERCO_PRODUCTOMAYORRECALLS_H
#define PROYECTODERCO_PRODUCTOMAYORRECALLS_H

/*
    CalcularRecalls recibe el struct de Compras y un ID para ir calculando las veces que aparece en recall.
 */
int CalcularRecalls(struct NodoCompras *compras, int idProducto)
{
    struct NodoCompras *rec=compras;
    int i,cantidad=0;
    do
    {
        for(i=0;i<maxCompras && rec->datosCompra->productos[i]!=NULL;i++)
        {
            if(rec->datosCompra->productos[i]->idProducto==idProducto)
                if(rec->datosCompra->productos[i]->estadoRecall==true)
                    cantidad++;
        }
        rec=rec->sig;
    }while(rec!=compras);
    return cantidad;
}
/*
 retornarCantMayorDeRecalls retornara un entero que representa la mayor cantidad de veces que un productos en recall,
 esto gracias a reccorer las compras realizadas en la consecionaria y condicionales.
 */
int retornarCantMayorDeRecalls(struct NodoCompras *compras)
{
    struct NodoCompras *rec=compras;
    int i,Mayor=0,aux;
    do {
        for(i=0;i<maxCompras && rec->datosCompra->productos[i]!=NULL;i++)
        {
            aux=CalcularRecalls(compras,rec->datosCompra->productos[i]->idProducto);
            if(aux>Mayor)
                Mayor=aux;
        }
        rec=rec->sig;
    }while(rec!=compras);
    return Mayor;
}

/*
 BuscarRepetido retornara true o false dependiendo si un producto ya se encuentra en un arreglo.

 */

bool BuscarRepetido(struct Productos **productos, int idProducto,int j)
{
    int i;
    for(i=0;i<j && productos[i]!=NULL;i++)
        if(productos[i]->idProducto==idProducto)
            return false;
    return true;

}

/*
 MostrarProductosConMayorRecall recibe el struct relacionado a todas la ventas realiadas en la consecionaria
 y la mayor cantidad de recalls, si el producto cumple la condción se guardara en un arreglo, después de recorrer todas
 las ventas imprimira los productos correspondientes.
 */
void MostrarProductosConMayorRecall(struct NodoCompras *compras, int CantidadDeRecalls)
{
    printf("Lista de productos con mayor Recalls\n");
    int i,j=0;
    struct NodoCompras *rec=compras;
    struct Productos **Nuevo=(struct Productos**)malloc(maxCompras*sizeof(struct Producto*));
    do
    {
        for(i=0;i<maxCompras && rec->datosCompra->productos[i]!=NULL;i++)
        {
            if(CalcularRecalls(compras,rec->datosCompra->productos[i]->idProducto)==CantidadDeRecalls)
            {
                if(BuscarRepetido(Nuevo,rec->datosCompra->productos[i]->idProducto,j)==true)
                {
                    Nuevo[j] = rec->datosCompra->productos[i];
                    j++;
                }
            }

        }
        rec=rec->sig;
    }while(rec!=compras);

    for(i=0;i<j;i++)
        printf("%d- Nombre=%s- id=%d\n",i+1,Nuevo[i]->nombreProducto,Nuevo[i]->idProducto);

}


/*
 MostrarAutoConMasRecall recibe el sistema Derco llama a la función "retornarCantMayorDeRecalls"
 si esta cantidad es 0 imprimira el mensaje correspondiente, si no llamara a la funcion que imprime
 los productos que cumplen la condición.
 */
void MostrarAutoConMasRecalls(struct SistemaDerco *derco)
{

    int MayorCantidadRecalls=0;
    if(derco->ventas!=NULL)
    {
        MayorCantidadRecalls=retornarCantMayorDeRecalls(derco->ventas);
        if(MayorCantidadRecalls==0)
        {
            printf("No existe ningun producto con Recall\n");
            return;
        }
        else
            MostrarProductosConMayorRecall(derco->ventas,MayorCantidadRecalls);
        return;
    }
}


#endif //PROYECTODERCO_PRODUCTOMAYORRECALLS_H
