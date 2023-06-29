//
// Created by benja on 28-06-2023.
//

#define maxCompras 20
#define cantRegiones 16
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include "funcionesBasicasSucursales.h"

#ifndef PROYECTODERCO_SUCURSALCONMASVENTASAUTOS_H
#define PROYECTODERCO_SUCURSALCONMASVENTASAUTOS_H


int calcularCantidadAutosVendidos(struct Productos **vendido, int idSucursal)
{
    int i, contAutos = 0;
    for(i = 0; i < maxCompras && vendido[i] != NULL; i++){
        if(vendido[i]->idDistribuidora == idSucursal && vendido[i]->tipoDeProducto == 2){
            contAutos++;
        }
    }
    return contAutos;
}

int cantidadAutosVendidos(struct NodoCompras *compras, int idSucursal)
{
    struct NodoCompras *rec = NULL;
    int cantAutosVendidos = 0;
    if(compras != NULL){
        rec = compras;
        do{
            if(rec->datosCompra->productos != NULL){
                cantAutosVendidos += calcularCantidadAutosVendidos(rec->datosCompra->productos, idSucursal);
            }
            rec = rec->sig;
        }while(rec != compras);
    }
    return cantAutosVendidos;
}

int MasAutosVendidosSucursales(struct NodoSucursales *sucursales, struct NodoCompras *compras){
    struct NodoSucursales *rec = NULL;
    int mayorCantidadAutosVendidos = 0, temp = 0;
    if(sucursales != NULL){
        mayorCantidadAutosVendidos = cantidadAutosVendidos(compras, sucursales->datosSucursal->id);
        rec = sucursales;
        do {
            if(compras)
                temp = cantidadAutosVendidos(compras, rec->datosSucursal->id);
            if(temp > mayorCantidadAutosVendidos){
                mayorCantidadAutosVendidos = temp;
            }
            rec = rec->sig;
        }while(rec != sucursales);
    }
    return mayorCantidadAutosVendidos;
}

int MasAutosVendidosRegiones(struct Regiones **regiones, struct NodoCompras *compras){
    int i, mayorCantidadAutosVendidos = 0, temp = 0;
    for(i = 0; i < cantRegiones; i++){
        if(regiones[i] != NULL){
            if(i == 0)
                mayorCantidadAutosVendidos = MasAutosVendidosSucursales(regiones[i]->sucursales, compras);
            else
            {
                temp = MasAutosVendidosSucursales(regiones[i]->sucursales, compras);
                if(temp > mayorCantidadAutosVendidos)
                    mayorCantidadAutosVendidos = temp;
            }
        }
    }
    return mayorCantidadAutosVendidos;
}

void AgregarSucursalConMasVentasAutos(struct NodoSucursales *sucursales, struct NodoCompras *compras,
                                      struct NodoSucursales **nuevo, int mayorCantAutosVendidos){
    struct NodoSucursales *rec = NULL;
    int cantVentasAutos = 0;
    if(sucursales != NULL){
        rec = sucursales;
        do {
            cantVentasAutos = cantidadAutosVendidos(compras, rec->datosSucursal->id);
            if(cantVentasAutos == mayorCantAutosVendidos && buscarSucursal((*nuevo), rec->datosSucursal->id) == 0)
                agregarSucursal(nuevo, rec->datosSucursal);
            rec = rec->sig;
        }while(rec != sucursales);
    }

}

struct NodoSucursales *buscarYAgregarSucursalConMasVentasAutos(struct Regiones **regiones, struct NodoCompras *compras,
                                                               int mayorCantAutosVendidos){
    int i;
    struct NodoSucursales *nuevo = NULL;
    for(i = 0; i<cantRegiones; i++){
        if(regiones[i] != NULL){
            AgregarSucursalConMasVentasAutos(regiones[i]->sucursales, compras, &(nuevo), mayorCantAutosVendidos);
        }
    }
    return nuevo;
}

void mostrarSucursalesConMasVentasAutos(struct SistemaDerco *derco){
    struct NodoSucursales *sucursalesConMasVentasAutos = NULL;
    int mayorCantAutosVendidos = 0;
    if(derco != NULL){
        if(derco->regiones != NULL && derco->ventas != NULL){
            mayorCantAutosVendidos = MasAutosVendidosRegiones(derco->regiones, derco->ventas);
            if(mayorCantAutosVendidos != 0){
                sucursalesConMasVentasAutos = buscarYAgregarSucursalConMasVentasAutos(derco->regiones, derco->ventas,
                                                                                      mayorCantAutosVendidos);
                printf("Las sucursales con mayor cantidad de ventas de autos son: \n");
                mostrarSucursalesEnumeradas(sucursalesConMasVentasAutos);
            }
            else
                printf("No hay sucursales registradas");
        }

    }
}

#endif //PROYECTODERCO_SUCURSALCONMASVENTASAUTOS_H


