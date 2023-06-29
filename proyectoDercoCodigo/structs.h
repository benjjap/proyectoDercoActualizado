//
// Created by gerar on 5/28/2023.
//
#include <stdbool.h>
#ifndef PROYECTODERCO_STRUCTS_H
#define PROYECTODERCO_STRUCTS_H
struct SistemaDerco{
    struct Regiones **regiones;     //arreglo dinamico de regiones compacto
    struct NodoCompras *ventas;  //lista circular doble enlazada
};

struct Regiones{
    char *Nombre;
    int sigla;
    struct NodoSucursales *sucursales; //lista circular doblemente enlazada
};

struct NodoSucursales{
    struct Sucursal *datosSucursal;
    struct NodoSucursales *sig,*ant;
};

struct Sucursal{
    int id;
    char *comuna;
    char *nombre;
    struct NodoMarcas *marcasAutos;// Lista Doblemente enlazada
};

struct NodoMarcas{
    struct Marca *datosMarca;
    struct NodoMarcas *ant,*sig;

};

struct Marca{
    int id;
    char *nombre;
    struct NodoProductos *autos;// ABB postOrden
    struct NodoProductos *productosAutos;// ABB postOrden
};

struct NodoProductos
{
    struct Producto *datosProducto;
    struct NodoProductos *izq, *der;
};

struct Producto
{
    int idProducto;
    int tipoProducto; //1: autos 2:productos autos
    int valor;
    int stock;
    char *nombre;
    char *descripcion;
};

struct NodoCompras {
    struct Compra *datosCompra;
    struct NodoCompras *sig,*ant;
};

struct Compra {
    int codigoCompra;
    char *rutCliente;
    char *nombreCliente;
    int valorCompra;
    struct Productos **productos; //arreglo
};

struct Productos{
    char *nombreProducto;
    int idProducto;
    int idMarca;
    int tipoDeProducto;
    int idDistribuidora;
    bool estadoRecall;
};

#endif //PROYECTODERCO_STRUCTS_H
