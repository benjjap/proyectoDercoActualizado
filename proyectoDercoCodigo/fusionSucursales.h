//
// Created by gerar on 5/30/2023.
//
#include <stdio.h>
#include "funcionesBasicasSucursales.h"
#include "funcionesBasicasMarcas.h"
#include "funcionesBasicasProductos.h"
#include "structs.h"
#ifndef PROYECTODERCO_FUSIONSUCURSALES_H
#define PROYECTODERCO_FUSIONSUCURSALES_H

/*
    "fusionar productos" recibe el struct Marca y el struct de productos de manera recursiva utilizando la función
    "buscarProductoEnMarca" ira preguntando si el producto se encuentra en esta, si no se encuentra lo agregara mediante
    la función correspondiente "agregarEnMarca" y en el caso contrario aumentara el stock del producto mediante la función
    "AumentarStock".

 */

void fusionarProductos(struct NodoProductos *marca, struct NodoProductos *abb)
{
    int Booleano=0;
    if(abb!=NULL)
    {
        fusionarProductos(marca,abb->izq);
        fusionarProductos(marca,abb->der);
        buscarProductoEnMarca(marca,abb->datosProducto->idProducto,&Booleano);
        if(Booleano==1){
            AumentarStock(&(marca),abb->datosProducto);

        }
        else{
            agregarEnMarca(&(marca),abb->datosProducto);

        }



    }
}

/*
    "fusionarMarca" recibe el struct recibe el struct de marcas de la sucursal además, de un struct de una marca
    que ya existe en esta cuando se recorra las marcas y las ids sean igual se llamara a la función "fusionar Productos"
    tanto para los autos y los accesorios/repuestos de este.

*/

void fusionarMarcas(struct NodoMarcas *marcas, struct Marca *marca)
{
    struct NodoMarcas *rec;
    if(marcas!=NULL)
    {
        rec=marcas;
        while(rec!=NULL)
        {
            if(rec->datosMarca->id==marca->id)
            {
                fusionarProductos(rec->datosMarca->autos,marca->autos);
                fusionarProductos(rec->datosMarca->productosAutos,marca->productosAutos);

            }
            rec=rec->sig;
        }
    }
}

/*
    "Traspasardatos" recibe dos struct de tipo Sucursal uno relacionado a la Sucursal donde recibe los nuevos datos
    y la otra con los datos que se traspasaran, se recorrerán las marcas que tiene la sucursal "traspaso" , si esta ya
    existe en el "Destino" se fusionaran sus productos con la función "fusionarMarcas" en caso contrario lo agregara
    llamando a "agregarMarcaASucursal"
*/

void Traspasardatos(struct Sucursal *Destino, struct Sucursal *traspaso)
{
    struct NodoMarcas *rectraspaso;

    if(traspaso->marcasAutos!=NULL)
    {
        rectraspaso=traspaso->marcasAutos;
        while(rectraspaso!=NULL)
        {
            if(buscarMarcaporId(Destino->marcasAutos,rectraspaso->datosMarca->id)==0){
                agregarMarcaASucursal(&(Destino->marcasAutos),rectraspaso->datosMarca);

            }
            else{
                fusionarMarcas(Destino->marcasAutos,rectraspaso->datosMarca);

            }
            rectraspaso=rectraspaso->sig;

        }
    }
}

/*
    "fusionar Sucursales"(Funcion principal ) recibe las sucursales de una región, además de dos ids de tipo entero
    las cuales serán las sucursales a "fusionar" se recorrerá el nodoSucursal hasta encontrar y poder "guardar" el
    struct relacionado a cada una de ellas, si las dos existen llamara a la función "traspasar datos" para después
    retornar 1, en caso contrario retornara 0.
*/
int FusionarSucursales(struct NodoSucursales *sucursales ,int idSucursalDestino, int idSucursalTraspaso)
{
    struct NodoSucursales *rec;
    struct Sucursal *Destino, *traspaso;
    unsigned short encontrado=2;
    if(sucursales!=NULL)
    {
        rec=sucursales;
        do
        {
            if(rec->datosSucursal->id==idSucursalDestino)
            {

                Destino=rec->datosSucursal;
                encontrado++;
            }
            if(rec->datosSucursal->id==idSucursalTraspaso)
            {

                traspaso=rec->datosSucursal;
                encontrado++;
            }
            rec=rec->sig;
        }while(rec!=sucursales||encontrado==2);


        Traspasardatos(Destino,traspaso);
        eliminarSucursal(&(sucursales),idSucursalTraspaso);
        return 1;
    }
    return 0;
}
/*
    "interfazFusionProducto" Ayuda al usuario para que tenga un medio visual para dar uso a la funcion
    "Fusionar sucursales", estas validadara que los datos a trabajar sean validos y mostrando las opciones
    a trabajar.
*/


void interfazFusionProducto(struct  Regiones **regiones)
{
    int siglaRegion=0;
    int idSucursalPadre, idSucursalTraspaso;

    while(siglaRegion <1 || siglaRegion>16)
    {
        mostrarRegiones(regiones);
        printf("Ingrese una sigla de region valida=\n");
        scanf("%d",&siglaRegion);
    }

    if(regiones[siglaRegion-1]->sucursales->sig==regiones[siglaRegion-1]->sucursales)
    {
        printf("No hay suficientes sucursales para realizar la accion\n");
        return;
    }

    while(true)
    {

        printf("Lista de sucursales disponibles\n");
        mostrarSucursalesEnumeradas(regiones[siglaRegion-1]->sucursales);
        printf("Ingrese un id valida para la sucursal  la cual le llegaran datos\n");
        scanf("%d", &idSucursalPadre);
        if(buscarSucursal(regiones[siglaRegion-1]->sucursales, idSucursalPadre)==1)
            break;
    }


    while(true)
    {
        printf("Lista de sucursales disponibles");
        mostrarSucursalesEnumeradas(regiones[siglaRegion-1]->sucursales);
        printf("Ingrese un id valida para la  sucursal la cual traspasara sus datos (asegurese que sea distinta a la anteriormente ingresada)\n");
        scanf("%d",&idSucursalTraspaso);
        if(buscarSucursal(regiones[siglaRegion-1]->sucursales,idSucursalTraspaso)==1 && idSucursalTraspaso!=idSucursalPadre)
            break;
    }
    FusionarSucursales(regiones[siglaRegion-1]->sucursales,idSucursalPadre,idSucursalTraspaso);
    printf("Sucursales fusionadas exitosamente\n");


}

#endif //PROYECTODERCO_FUSIONSUCURSALES_H
