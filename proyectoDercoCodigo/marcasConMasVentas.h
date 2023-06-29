//
// Created by gerar on 5/28/2023.
//

#define cantRegiones 16
#define maxCompras 20
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef PROYECTODERCO_MARCACONMASVENTAS_H
#define PROYECTODERCO_MARCACONMASVENTAS_H

/*
 veentasMarcaCompra busca y retorna todas las compras que se realizaron de una marca especifica dentro de las compras relacionadas
 a un cliente
 */

int ventasMarcaCompra(struct Productos **productos,int idMarcaBuscada){
    int i;
    int ventas=0;
    for ( i = 0; i <maxCompras && productos[i]!=NULL ; ++i) {
        if(productos[i]->idMarca==idMarcaBuscada){
            ventas++;
        }
    }
    return ventas;
}

/*
 ventasMarcaEnVentas busca y retorna todas las compras que se realizaron de una marca específica dentro de todas las compras
 registradas en el sistema.
 */

int ventasMarcaEnVentas(struct NodoCompras *ventas,int idMarcaBuscada){
    struct NodoCompras *rec;
    int ventasMarca=0;
    if(ventas!=NULL){
        rec=ventas;
        do {
            ventasMarca+= ventasMarcaCompra(rec->datosCompra->productos,idMarcaBuscada);
            rec=rec->sig;
        }while(rec!=ventas);
    }
    return ventasMarca;
}

/*
 mayorVentasMarcasEnSucursal compara las ventas de las marcas y devuelve las ventas de la marca con mayor cantidad de ventas
 dentro de una sucursal.
 */

int mayorVentasMarcasEnSucursal(struct NodoMarcas *marcas,struct NodoCompras *ventas){
    struct NodoMarcas *rec=marcas;
    int ventasMarca=0,mayorVentas=0;
    while(rec!=NULL){
        ventasMarca= ventasMarcaEnVentas(ventas,rec->datosMarca->id);
        if(rec==marcas){
            mayorVentas=ventasMarca;
        }else{
            if(ventasMarca>mayorVentas){
                mayorVentas=ventasMarca;
            }
        }
        rec=rec->sig;
    }
    return mayorVentas;
}

/*
 mayorVentasMarcaEnRegion compara las ventas de las marcas con mas ventas de cada sucursal de una región y devuelve las
 ventas de las marca con mas ventas de la region.
 */

int mayorVentasMarcaEnRegion(struct NodoSucursales *sucursales,struct NodoCompras *ventas){
    struct NodoSucursales *rec;
    int ventasMarca=0,mayorVentas=0;
    if(sucursales!=NULL){
        rec=sucursales;
        do {
            ventasMarca= mayorVentasMarcasEnSucursal(rec->datosSucursal->marcasAutos,ventas);
            if(rec==sucursales){
                mayorVentas=ventasMarca;
            }else{
                if(ventasMarca>mayorVentas){
                    mayorVentas=ventasMarca;
                }
            }
            rec=rec->sig;
        }while(rec!=sucursales);
    }
    return mayorVentas;
}

/*
 marcaConMasVentasRegiones compara las ventas de las marcas con mas ventas de cada regióo y devuelve las venta de la(s)
 marca(s) con mas ventas del sistema.
 */

int marcaConMasVentasRegiones(struct Regiones **regiones,struct NodoCompras *ventas){
    int ventasMarca=0,mayorVentas=0,i;
    for (i = 0;  i<cantRegiones ; i++) {
        ventasMarca= mayorVentasMarcaEnRegion(regiones[i]->sucursales,ventas);
        if(i==0){
            mayorVentas=ventasMarca;
        }else{
            if(ventasMarca>mayorVentas){
                mayorVentas=ventasMarca;
            }
        }
    }
    return mayorVentas;
}

/*
 buscarYAgregarMarcasMasVendidasMarcas busca y agrega a una lista doblemente enlazada todas las marcas que encuentre
 que tengan las misma cantidad de ventas que la mayor cantidad de ventas del sistema.
 */

void buscarYAgregarMarcasMasVendidasMarcas(struct NodoMarcas *marcas,struct NodoCompras *ventas,
                                            int mayorVentas,struct NodoMarcas**nuevo){
    struct NodoMarcas *rec=marcas;
    int ventasMarca=0;
    while(rec!=NULL){
        ventasMarca= ventasMarcaEnVentas(ventas,rec->datosMarca->id);
        if(ventasMarca==mayorVentas && buscarMarcaporId(*nuevo,rec->datosMarca->id)==0){
            agregarMarcaASucursal(nuevo,rec->datosMarca);
        }
        rec=rec->sig;
    }
}

/*
 buscarYAgregarMarcasMasVendidasSucursales esta funcion busca y agrega en cada sucursal las marcas que tengan la misma cantidad
 de ventas que la mayor cantidad ventas para ello llama a la funcion buscarYAgregarMarcasMasVendidasMarcas en cada ciclo.
 */

void buscarYAgregarMarcasMasVendidasSucursales(struct NodoSucursales *sucursales,struct NodoCompras *ventas,
                                                int mayorVentas,struct NodoMarcas **nuevo){
    struct NodoSucursales *rec;
    if(sucursales!=NULL){
        rec=sucursales;
        do {
            buscarYAgregarMarcasMasVendidasMarcas(rec->datosSucursal->marcasAutos,ventas,mayorVentas,nuevo);
            rec=rec->sig;
        }while(rec!=sucursales);
    }
}

/*
 crearListaConMarcasMasVendidas crea una lista doblemente enlazada y agrega a esta las marcas con la misma cantidad de ventas
 que la mayor cantidad de ventas del sistema retornando esta lista
 */

struct NodoMarcas *crearListaConMarcasMasVendidas(struct Regiones **regiones,struct NodoCompras *ventas,int mayorVentas){
    struct NodoMarcas *marcas=NULL;
    int i;
    for (i = 0; i<cantRegiones ; i++) {
        if(regiones[i]!=NULL){
            buscarYAgregarMarcasMasVendidasSucursales(regiones[i]->sucursales,ventas,mayorVentas,&marcas);
        }
    }
    return marcas;
}

/*
 marcasConMasVentas esta función crea y muestra las marcas con la mayor cantidad de compras del sistema realizando las verificaciones
 necesarias para ello.
 */

int marcasConMasVentas(struct SistemaDerco *derco){
    struct NodoMarcas *marcasConMasVentas=NULL;
    int mayorVentas=0;
    if(derco!=NULL){
        if(derco->regiones!=NULL && derco->ventas!=NULL){
            mayorVentas= marcaConMasVentasRegiones(derco->regiones,derco->ventas);
            if(mayorVentas!=0){
                marcasConMasVentas= crearListaConMarcasMasVendidas(derco->regiones,derco->ventas,mayorVentas);
                printf("La cantida de productos vendidos mas grande fue : %d \n",mayorVentas);
                printf("Las marcas que vendieron esa cantidad son : \n");
                mostrarMarcasEnumeradas(marcasConMasVentas);
            }
            else{
                printf("No hay marcas registradas");
            }
        }
    }
    return 0;
}

#endif //PROYECTODERCO_MARCACONMASVENTAS_H
