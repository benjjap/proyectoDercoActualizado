//
// Created by gerar on 5/28/2023.
//

#define maxCompras 20
#define cantRegiones 16
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include "funcionesBasicasSucursales.h"


#ifndef PROYECTODERCO_SUCURSALCONMASVENTAS_H
#define PROYECTODERCO_SUCURSALCONMASVENTAS_H

/*
 distribuicionesSucursalCompra recibe un arreglo de productos y un ID de sucursal. Se recorre el arreglo contando cada
 distribución. Luego retorna distribuciones.
 */
int distribucionesSucursalCompra(struct Productos**productos,int idSucursal){
    int i,distribuciones=0;
    for(i=0;i<maxCompras && productos[i]!=NULL;i++){
        if(productos[i]->idDistribuidora==idSucursal) distribuciones++;
    }
    return distribuciones;
}

/*
 distribucionesSucursalVentas recibe lista de ventas y un ID de sucursal. Si ventas es distinto de NULL, se recorre la lista
 de ventas sumando las distribuciones, al final retornando las distribuciones.
 */
int distribucionesSucursalVentas(struct NodoCompras*ventas,int idSucursal){
    struct NodoCompras *rec;
    int distribuciones=0;
    if(ventas!=NULL){
        rec=ventas;
        do {
            distribuciones+= distribucionesSucursalCompra(rec->datosCompra->productos,idSucursal);
            rec=rec->sig;
        }while(rec!=ventas);
    }
    return distribuciones;
}

/*
 sucursalConMasVentasRegion recibe la lista de sucursales y la lista de ventas. Se recorre la lista de sucursales, se
 calculan las distribuciones por sucursal y se comparan las distribuciones por cada sucursal para ver quien tiene el mayor
 número. Se retorna la mayor distribuciones.
 */
int sucursalConMasVentasRegion(struct NodoSucursales *sucursales,struct NodoCompras *ventas){
    struct NodoSucursales *rec;
    int mayorDistribucion=0,distribuciones=0;
    if(sucursales!=NULL){
        rec=sucursales;
        do {
            distribuciones= distribucionesSucursalVentas(ventas,rec->datosSucursal->id);
            if(rec==sucursales){
                mayorDistribucion=distribuciones;
            }else{
                if(distribuciones>mayorDistribucion){
                    mayorDistribucion=distribuciones;
                }
            }
            rec=rec->sig;
        }while(rec!=sucursales);
    }
    return mayorDistribucion;
}

/*
 sucursalConMasVentasRegiones recibe un arreglo regiones y una lista de ventas. Se recorre el arreglo calculando las
 distribuciones por sucursal y se va comparando cada region por distribuciones. Al final retornando la mayor distribuciones.
 */
int sucursalConMasVentasRegiones(struct Regiones **regiones,struct NodoCompras *ventas){
    int mayorDistribuciones=0,distribuciones=0,i=0;
    for (i = 0; i <cantRegiones; ++i) {
        if(regiones[i]->sucursales!=NULL){
            distribuciones= sucursalConMasVentasRegion(regiones[i]->sucursales,ventas);
            if(i==0){
                mayorDistribuciones=distribuciones;
            }else{
                if(distribuciones>mayorDistribuciones){
                    mayorDistribuciones=distribuciones;
                }
            }
        }
    }
    return mayorDistribuciones;
}

/*
 buscarYAgregarSucursalesMayorVentasSucursales recibe lista de sucursales, lista de ventas, lista nueva de sucursales,
 mayor ventas. se recorre la lista de sucursales, si las distribusciones de la sucursal es igual a mayor ventas y es la
 sucursal buscada, se agrega la sucursal a la nueva lista de sucursales.
 */
void buscarYAgregarSucursalesMayorVentasSucursales(struct NodoSucursales *sucursales,struct NodoCompras*ventas,
                                                   struct NodoSucursales **nuevo,int mayorVentas){
    struct NodoSucursales *rec;
    int ventasSucursal=0;
    if(sucursales!=NULL){
        rec=sucursales;
        do {
            ventasSucursal= distribucionesSucursalVentas(ventas,rec->datosSucursal->id);
            if(ventasSucursal==mayorVentas && buscarSucursal(*nuevo,rec->datosSucursal->id)==0){
                agregarSucursal(nuevo,rec->datosSucursal);
            }
            rec=rec->sig;
        }while(rec!=sucursales);
    }
}

/*
 buscarYAgregarSucursalesMayorVentasRegiones recibe un arreglo de regiones, lista de ventas y mayor ventas. Se recorre
 el arreglo de regiones y la posicione es distinta de NULL, se llama a la funcion buscarYAgregarSucursalesMayorVentasSucursales.
 se retorna la nueva lista de sucursales.
 */
struct NodoSucursales *buscarYAgregarSucursalesMayorVentasRegiones(struct Regiones **regiones,struct NodoCompras *ventas
                                                                   ,int mayorVentas){
    int i;
    struct NodoSucursales *nuevo=NULL;
    for (i = 0;  i<cantRegiones ; i++) {
        if(regiones[i]!=NULL){
            buscarYAgregarSucursalesMayorVentasSucursales(regiones[i]->sucursales,ventas,&nuevo,mayorVentas);
        }
    }
    return nuevo;
}

/*
 mostrarSucursalesConMasVentas recibe el sistema Derco. Si el sistema Derco es distinto de NULL, pregunta si regiones es
 distinto de NULL y ventas distinto de NULL se asigna valor a mayor venta, si ese valor es distinto de 0, entonces se
 asigna valor a sucursalesMasVentas con la función buscarYAgregarSucursalesMayorVentasRegiones y se imprime la mayor venta
 y las sucursales con mayores ventas.
 */

int mostrarSucursalesConMasVentas(struct SistemaDerco *derco){
    struct NodoSucursales *sucursalesMasVentas=NULL;
    int mayorVentas=0;
    if(derco!=NULL){
        if(derco->regiones!=NULL && derco->ventas!=NULL){
            mayorVentas= sucursalConMasVentasRegiones(derco->regiones,derco->ventas);
            if(mayorVentas!=0){
                sucursalesMasVentas= buscarYAgregarSucursalesMayorVentasRegiones(derco->regiones,derco->ventas,mayorVentas);
                printf("La cantidad de la sucursal que mas ha vendido es : %d $\n",mayorVentas);
                printf("Las sucursales  mayores ventas son: \n");
                mostrarSucursalesEnumeradas(sucursalesMasVentas);
            }
            else{
                printf("No hay sucursales registradas\n");
            }
        }
    }
    return 0;
}

#endif //PROYECTODERCO_SUCURSALCONMASVENTAS_H
