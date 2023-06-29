//
// Created by gerar on 5/28/2023.
//
#include "structs.h"
#include "funcionesBasicasVentas.h"
#include "funcionesBasicasSucursales.h"
#include "funcionesBasicasProductos.h"
#include <stdlib.h>
#include <stdio.h.>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define  maxCompras 20
#ifndef PROYECTODERCO_COMPRARPRODUCTO_H
#define PROYECTODERCO_COMPRARPRODUCTO_H

/*

    pedirIdsCompra esta función tiene como objetivo retornar un arreglo que contendrá los ids de la compra realizada,
    esto cuidando las condiciones correspondientes (EL producto debe existir y tiene que tener stock) finalmente cuando se
    retorne 0 o se llegue la cantidad máxima de compras permitidas retornara el arreglo.

 */
int *pedirIdsCompra(struct SistemaDerco *derco,int idSucursal, int *largoCompra,int siglaRegion)
{
    int *idsDeCompra=(int *)malloc(sizeof(int)*maxCompras);
    int contador=0;
    int idProducto;
    int dummy;
    printf("Ingrese id de los productos comprados(0 para terminar)\n");
    while(1)
    {
        mostrarAutosSucursal(derco->regiones[siglaRegion-1]->sucursales,idSucursal);
        mostrarProductosSucursal(derco->regiones[siglaRegion-1]->sucursales,idSucursal);
        printf("-ID=\n");
        scanf("%d",&idProducto);
        if(idProducto<0)
            printf("Ingrese una id Valida\n");

        if(idProducto==0)
        {
            printf("Se ha terminado de ingresar productos\n");
            (*largoCompra)=contador;
            return idsDeCompra;
        }

        if(BuscarProducto(derco->regiones,idProducto,idSucursal,&dummy)==0)
            printf("El producto no existe en la Sucursal ingresada\n");


        if(idProducto>0)
        {
            if (ComprobarStock(derco, idSucursal, idProducto) == 1)
            {
                if (contador < maxCompras)
                {
                    idsDeCompra[contador] = idProducto;
                    contador++;
                    DisminuirStock(derco,idSucursal,idProducto);
                }
                else
                {
                    printf("Se alcanzo el limite maximo de compras\n");
                    (*largoCompra) = contador;
                    return idsDeCompra;
                }

            }
            else
                if(BuscarProducto(derco->regiones,idProducto,idSucursal,&dummy)!=0)
                    printf("No queda Stock del producto\n");
        }
    }

}

/*

    obtenerNombreEnArbol, recibirá un árbol correspondiente a modelos o productos de una marca y un id del producto a buscar
    de manera recursiva si se encuentra el producto retornara un string correspondiente al nombre del producto

 */

char *obtenerNombreEnArbol(struct NodoProductos *abb,int *gastado,int idProducto)
{
    if(abb!=NULL)
    {
        char *resultadosIzq=obtenerNombreEnArbol(abb->izq,gastado,idProducto);
        if(resultadosIzq!=NULL) return resultadosIzq;
        char *resultadosDer=obtenerNombreEnArbol(abb->der,gastado,idProducto);
        if(resultadosDer!=NULL) return resultadosDer;
        if(abb->datosProducto->idProducto==idProducto)
        {
            printf("Nombre : %s\n",abb->datosProducto->nombre);
            *gastado=(*gastado)+abb->datosProducto->valor;
            return abb->datosProducto->nombre;
        }
    }
    return NULL;
}
/*
    obtenerNombre, recibe el arreglo de regiones, un id sucursal además de datos relacionados a una venta,
    recorrerá la sucursal correspondiente y cuando encuentre el producto mediante uso de punteros los valores de idMarca
    tipo de producto, el total gastado cambiaran y terminara llamando "obtenerNombreEnArbol" para retornar un string.
 */
char *obtenerNombre(struct Regiones *region, int *idMarca, int *tipoDeProducto,int *gastado ,int idProducto, int idSucursal)
{
    int Booleano=0;
    struct NodoSucursales *rec=region->sucursales;
    struct NodoMarcas *recMarcas;
    do
    {
        if(rec->datosSucursal->id==idSucursal)
        {
            recMarcas=rec->datosSucursal->marcasAutos;
            while(recMarcas!=NULL)
            {
                buscarProductoEnMarca(recMarcas->datosMarca->productosAutos,idProducto,&Booleano);
                if(Booleano==1)
                {
                    (*tipoDeProducto)=3;
                    (*idMarca)=recMarcas->datosMarca->id;
                    return obtenerNombreEnArbol(recMarcas->datosMarca->productosAutos,gastado,idProducto);
                }
                buscarProductoEnMarca(recMarcas->datosMarca->autos,idProducto,&Booleano);
                if(Booleano==1)
                {
                    (*tipoDeProducto)=2;
                    (*idMarca)=recMarcas->datosMarca->id;
                    return obtenerNombreEnArbol(recMarcas->datosMarca->autos,gastado,idProducto);
                }
                recMarcas=recMarcas->sig;
            }
        }
        rec=rec->sig;
    }while(rec!=region->sucursales);
    return NULL;
}
/*
    CrearArregloDeProductos, crea el arreglo de productos comprados, esto usando la función "pedirIdsDeCompra"
    ira buscando y agregando cada producto comprado con sus datos además de ir modificando el total gastado,
    finalmente retornando el struct creado.

 */
struct Productos **CrearArregloDeProductos(struct Regiones *region,int *idsDeCompra, int largo, int *gastado,int idSucursal)
{
    int i;
    int idMarca,tipoDeProducto;

    struct Productos **NuevoArreglo=(struct Productos**)malloc(largo*sizeof(struct Producto*));
    for(i=0;i<largo;i++)
    {

        NuevoArreglo[i]=(struct Productos *) malloc(sizeof(struct Producto));
        NuevoArreglo[i]->idProducto=idsDeCompra[i];
        NuevoArreglo[i]->estadoRecall=false;
        NuevoArreglo[i]->idDistribuidora=idSucursal;


        NuevoArreglo[i]->nombreProducto=obtenerNombre(region,&idMarca,&tipoDeProducto,gastado,idsDeCompra[i],idSucursal);
        NuevoArreglo[i]->tipoDeProducto=tipoDeProducto;
        NuevoArreglo[i]->idMarca=idMarca;
    }
    return NuevoArreglo;
}
/*
    CrearCompra, creara un struct de tipo Compra con sus datos correspondientes(Nombre y Rut del cliente, id
    generada de manera pseudorandomica), finalmente llama a la función "CrearArregloDeProductos" para agregar los productos
    comprados y guardar el total gastado.
 */
struct Compra *CrearCompra(struct SistemaDerco *derco ,int idSucursal, int siglaRegion)
{

    srand(time(NULL));
    struct Compra *nueva=(struct Compra*)malloc(sizeof(struct Compra));
    struct Productos** productos=NULL;

    int *idsDeCompra=NULL;
    int gastado=0;
    int largoCompra=0;


    char Nombre[100], Rut[13];

    printf("Ingrese rut Cliente :\n");
    scanf("%s[^\n] ",Rut);

    nueva->rutCliente=(char *)malloc(sizeof(char)* strlen(Rut));
    strcpy(nueva->rutCliente,Rut);

    printf("Ingrese nombre cliente :\n");
    getchar();
    scanf("%[^\n]s ",Nombre);
    getchar();

    nueva->nombreCliente=(char *)malloc(sizeof(char)* strlen(Nombre));
    strcpy(nueva->nombreCliente,Nombre);

    idsDeCompra=pedirIdsCompra(derco,idSucursal,&largoCompra,siglaRegion);

    productos=CrearArregloDeProductos(derco->regiones[siglaRegion-1],idsDeCompra,largoCompra,&gastado,idSucursal);
    nueva->productos=productos;

    nueva->valorCompra=gastado;

    nueva->codigoCompra=rand();

    return nueva;
}
/*
    crearYAgregarCompraAVentas, le mostrara al usuario la lista de sucursales de una región determinada, para luego
    pedirle que seleccione en cual se realizara la compra. Después mediante el uso "agregarAVentas" y "CrearCompra"
    para guardar los datos de la transacción.
 */
void crearYAgregarCompraAVentas(struct SistemaDerco *derco, int siglaRegion)
{
    int idSucursal;

    printf("Lista de sucursales en la region\n");
    mostrarSucursalesEnumeradas(derco->regiones[siglaRegion-1]->sucursales);

    printf("Ingrese id de la sucursal donde se realizara la compra:\n");
    scanf("%d", &idSucursal);


    while(buscarSucursal(derco->regiones[siglaRegion-1]->sucursales,idSucursal)==0){
        printf("La id ingresada no existe, inténtelo nuevamente\n");
        printf("Ingrese id de la sucursal donde se realizo la compra:\n");
        scanf("%d", &idSucursal);
    }


    agregarAVentas(&(derco->ventas),CrearCompra(derco,idSucursal, siglaRegion) );

}

#endif //PROYECTODERCO_COMPRARPRODUCTO_H
