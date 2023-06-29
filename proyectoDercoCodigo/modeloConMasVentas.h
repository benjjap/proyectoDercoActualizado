//
// Created by gerar on 5/28/2023.
//

#define maxCompras 20
#define cantRegiones 16
#include "structs.h"
#include "stdlib.h"
#include "stdio.h"
#include "funcionesBasicasProductos.h"

#ifndef PROYECTODERCO_MODELOCONMASVENTAS_H
#define PROYECTODERCO_MODELOCONMASVENTAS_H

/*
 CalcularVentas recibe el struct de las ventas realizadas en la consecionaria y el ID de un producto,
 va recorriendo las ventas y retornara la ventas que ha sido comprado.
 */
int CalcularVentas(struct NodoCompras *ventas, int idProducto)
{
    int Ventas=0;
    int i;
    struct NodoCompras *rec=ventas;
    do{
        for(i=0;i<maxCompras && rec->datosCompra->productos[i]!=NULL;i++)
        {
            if(rec->datosCompra->productos[i]->idProducto==idProducto) Ventas++;
        }
        rec=rec->sig;
    }while(rec!=ventas);
    return Ventas;
}
/*
 calcularCantModeloMascomprado  recibe las ventas realizadas en la consecionaria y mediante condiconales
 y la función "CalcularVentas" retornara la Cantidad del(los) producto(s) mas comprando(s).
 */

int calcularCantModeloMascomprado(struct NodoCompras *ventas)
{
    int Max=0,aux,i;
    struct NodoCompras *rec=ventas;
    do
    {
        for(i=0;i<maxCompras && rec->datosCompra->productos[i]!=NULL;i++)
        {
                aux= CalcularVentas(ventas,rec->datosCompra->productos[i]->idProducto);
                if(aux>Max)
                    Max=aux;
        }
        rec=rec->sig;
    }while (rec!=ventas);
    return Max;
}


/*
 MostrarModelosMasComprado muestra los datos de un struct de tipo NodoProductos.
 */
void MostrarModelosMasComprado(struct NodoProductos *productosMasComprado)
{
    if(productosMasComprado!=NULL)
    {
        MostrarModelosMasComprado(productosMasComprado->izq);
        MostrarModelosMasComprado(productosMasComprado->der);
        printf("Nombre= %s - ID=%d\n",productosMasComprado->datosProducto->nombre,productosMasComprado->datosProducto->idProducto);
    }

}


/*
 mostrarModeloConMasVentas recibe el sistema Derco y tiene como finalidad calcular y mostrar cual es el producto
 y modelo de automóvil que más se ha vendido, para esto comprobara primero se han realizado ventas. Si esto paso,
 guardara los datos en el struct correspondiente con ayuda de la función "CalcularVentas" y "CantidaMasComprada"
 para luego mostrar los datos que cumplieron la condición.
 */
void mostrarModeloConMasVentas(struct SistemaDerco *derco)
{
    struct NodoCompras *rec;
    struct Producto *aux;
    int CantidadMasComprada;
    int i;
    struct NodoProductos *productosMasComprado=NULL;
    if(derco->ventas==NULL)
    {
        printf("No se ha realizado ninguna venta en la consecionaria Derco\n");
        return;
    }
    else
    {
        CantidadMasComprada=calcularCantModeloMascomprado(derco->ventas);
        rec=derco->ventas;
        do
        {
            for(i=0;i<maxCompras && rec->datosCompra->productos[i]!=NULL;i++)
            {
                if(CalcularVentas(derco->ventas,rec->datosCompra->productos[i]->idProducto)==CantidadMasComprada )
                {
                    aux=RetornarProducto(derco->regiones,rec->datosCompra->productos[i]->idProducto);
                    agregarEnMarca(&(productosMasComprado),aux);
                }
            }
            rec=rec->sig;
        }while(rec!=derco->ventas);
    }
    MostrarModelosMasComprado(productosMasComprado);
}

#endif //PROYECTODERCO_MODELOCONMASVENTAS_H
