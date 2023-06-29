//
// Created by benja on 28-06-2023.
//

#define maxCompras 20
#define cantRegiones 16
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include "funcionesBasicasSucursales.h"

#ifndef PROYECTODERCO_SUCURSALCONMASVENTASREPUESTOS_H
#define PROYECTODERCO_SUCURSALCONMASVENTASREPUESTOS_H

int calcularCantidadProductosVendidos(struct Productos **vendido, int idSucursal){
    int i, contProductos = 0;
    for(i = 0; i < maxCompras && vendido[i] != NULL; i++){
        if(vendido[i]->idDistribuidora == idSucursal && vendido[i]->tipoDeProducto == 3){
            contProductos++;
        }
    }
    return contProductos;
}

int cantidadProductosVendidos(struct NodoCompras *compras, int idSucursal){
    struct NodoCompras *rec = NULL;
    int cantProductosVendidos = 0;
    if(compras != NULL){
        rec = compras;
        do{
            if(rec->datosCompra->productos != NULL){
                cantProductosVendidos += calcularCantidadProductosVendidos(rec->datosCompra->productos, idSucursal);
            }
            rec = rec->sig;
        }while(rec != compras);
    }
    return cantProductosVendidos;
}

int MasProductosVendidosSucursales(struct NodoSucursales *sucursales, struct NodoCompras *compras){
    struct NodoSucursales *rec;
    int mayorCantidadProductosVendidos = 0, temp = 0;
    if(sucursales != NULL){
        mayorCantidadProductosVendidos = cantidadProductosVendidos(compras, sucursales->datosSucursal->id);
        rec = sucursales;
        do {
            if(compras)
                temp = cantidadProductosVendidos(compras, rec->datosSucursal->id);
            if(temp > mayorCantidadProductosVendidos){
                mayorCantidadProductosVendidos = temp;
            }
            rec = rec->sig;
        }while(rec != sucursales);
    }
    return mayorCantidadProductosVendidos;
}

int MasProductosVendidosRegiones(struct Regiones **regiones, struct NodoCompras *compras){
    int i, mayorCantidadProductosVendidos = 0, temp = 0;
    for(i = 0; i < cantRegiones; i++){
        if(regiones[i] != NULL){
            if(i == 0)
                mayorCantidadProductosVendidos = MasProductosVendidosSucursales(regiones[i]->sucursales, compras);
            else{
                temp = MasProductosVendidosSucursales(regiones[i]->sucursales, compras);
                if(temp > mayorCantidadProductosVendidos)
                    mayorCantidadProductosVendidos = temp;
            }
        }
    }
    return mayorCantidadProductosVendidos;
}

void AgregarSucursalConMasVentasProductos(struct NodoSucursales *sucursales, struct NodoCompras *compras,
                                          struct NodoSucursales **nuevo, int mayorCantProductosVendidos){
    struct NodoSucursales *rec;
    int cantVentasProductos = 0;
    if(sucursales != NULL){
        rec = sucursales;
        do {
            cantVentasProductos = cantidadProductosVendidos(compras, rec->datosSucursal->id);
            if(cantVentasProductos   == mayorCantProductosVendidos && buscarSucursal((*nuevo), rec->datosSucursal->id) == 0)
                agregarSucursal(nuevo, rec->datosSucursal);
            rec = rec->sig;
        }while(rec != sucursales);
    }

}

struct NodoSucursales *buscarYAgregarSucursalConMasVentasProductos(struct Regiones **regiones, struct NodoCompras *compras,
                                                                   int mayorCantProductosVendidos){
    int i;
    struct NodoSucursales *nuevo = NULL;
    for(i = 0; i<cantRegiones; i++){
        if(regiones[i] != NULL){
            AgregarSucursalConMasVentasProductos(regiones[i]->sucursales, compras, &(nuevo), mayorCantProductosVendidos);
        }
    }
    return nuevo;
}

void mostrarSucursalesConMasVentasProductos(struct SistemaDerco *derco){
    struct NodoSucursales *sucursalesConMasVentasProductos = NULL;
    int mayorCantAutosVendidos = 0;
    if(derco != NULL){
        if(derco->regiones != NULL && derco->ventas != NULL){
            mayorCantAutosVendidos = MasProductosVendidosRegiones(derco->regiones, derco->ventas);
            if(mayorCantAutosVendidos != 0){
                sucursalesConMasVentasProductos = buscarYAgregarSucursalConMasVentasProductos(derco->regiones, derco->ventas,
                                                                                              mayorCantAutosVendidos);
                printf("Las sucursales con mayor cantidad de ventas de productos son: \n");
                mostrarSucursalesEnumeradas(sucursalesConMasVentasProductos);
            }
            else
                printf("No hay sucursales registradas");
        }

    }
}


#endif //PROYECTODERCO_SUCURSALCONMASVENTASREPUESTOS_H
