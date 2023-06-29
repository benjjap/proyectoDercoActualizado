
#ifndef PROYECTODERCO_PROMEDIOVENTASSUCURSALES_H
#define PROYECTODERCO_PROMEDIOVENTASSUCURSALES_H
#include "structs.h"
#include "stdio.h"
#include "stdlib.h"
#include "sucursalConMasVentas.h"
#include "funcionesBasicasSucursales.h"

/*
 ventaEnSucursal recibe el ID de la sucursal específica y el arreglo de productos comprados. Se recorre el arreglo en
 busca de si el ID de la distribuidora es igual al de la sucursal, retornando 1 si se encuentra.
 */
int ventaEnSucursal(int idSucursal,struct Productos **productos)
{
    int i;
    for(i = 0; i<maxCompras && productos[i] != NULL; i++)
    {
        if(productos[i]!=NULL){
            if(productos[i]->idDistribuidora == idSucursal)
                return 1;
        }
    }
    return 0;
}

/*
 calcularTotalVentas recibe ID de la sucursal y la lista de compras. Si la lista es distinta de NULL, entonces se recorre
 la lista en busca de si la función ventaEnSucursal retorna 1. Si es asi, entonces el totalCompras suma el valor de la
 compra cada vez que retorne 1. Al final se retorna el totalCompras.
 */
int calcularTotalVentas(int idSucursal, struct NodoCompras *ventas)
{
    int totalCompras = 0;
    struct NodoCompras *rec;
    if(ventas!=NULL){
        rec=ventas;
        do {
            if(ventaEnSucursal(idSucursal, rec->datosCompra->productos) == 1)
            {
                totalCompras += ventas->datosCompra->valorCompra;
            }
            rec=rec->sig;
        }while(rec!=ventas);
    }

    return totalCompras;
}

/*
 calcularPromedio recibe ID de sucursal y la lista de ventas. Se calculan las distribuciones con la función
 distribucinesSucursalVentas, se calcula totalVentas con calcularTotalVentas. Si las distribuciones son distintas de 0,
 entonces se calcula el promedio y se retorna ese promedio.
 */
float calcularPromedio(int idSucursal, struct NodoCompras *ventas)
{
    int distribuciones = distribucionesSucursalVentas(ventas, idSucursal);
    int totalVentas = calcularTotalVentas(idSucursal, ventas);
    float promedio = 0;
    if(distribuciones != 0){
        promedio = (float)totalVentas/(float)distribuciones;
    }
    return promedio;
}

/*
 MayorPromedioSucursales recibe el sistema Derco. Se recorre el sistema hasta el nivel de sucursales para encontrar que
 sucursal tiene el mejor promedio. Luego de recorrer todas las sucursales, se retorna el mayorPromedio.
 */
float MayorPromedioSucursales(struct SistemaDerco *derco)
{
    int i;
    float mayorPromedio = 0, promedioTemp = 0;
    struct NodoSucursales *rec;
    for(i=0; i < cantRegiones; i++)
    {
        if(derco->regiones[i]->sucursales!=NULL && derco->ventas!=NULL){
            rec = derco->regiones[i]->sucursales;
            do{
                promedioTemp = calcularPromedio(rec->datosSucursal->id, derco->ventas);
                if(promedioTemp > mayorPromedio)
                {
                    mayorPromedio = promedioTemp;
                }
                rec = rec->sig;
            }while(rec != derco->regiones[i]->sucursales);
        }
    }
    return mayorPromedio;
}

/*
 buscarYAgregarSucursalesConMejorPromedio recibe la lista de sucursales, el mejor promedio, la nueva lista de sucursales
 y la lista de compras. Se recorre la lista de sucursales preguntanto si el promedio de la sucursal es igual al mejor
 promedio, de ser asi, se agrega la sucursal en la nueva lista de sucursales.
 */
void buscarYAgregarSucursalesConMejorPromedio(struct NodoSucursales *sucursales, float mejorPromedio,
                                                struct NodoSucursales **nuevo, struct NodoCompras *ventas)
{
    float promedioActual=0;
    struct NodoSucursales *rec;
    if(sucursales != NULL)
    {
        rec = sucursales;
        do{
            promedioActual=calcularPromedio(rec->datosSucursal->id, ventas);
            if(promedioActual== mejorPromedio){
                agregarSucursal(nuevo, rec->datosSucursal);
            }
            rec = rec->sig;
        } while(rec != sucursales);
    }
}

/*
 crearListaSucursalesMejorPromedio recibe el arreglo de regiones, la lista de compras y el mejor promedio. Se crea una
 nueva lista para las sucursales con mejor promedio, luego se recorre el arreglo de funciones, si la posición es distinto
 de NULL, entonces se llama a la función buscarYAgregarSucursalesConMejorPromedio. Al terminar de recorrer se retorna
 la lista de sucursales con mejor promedio.
 */
struct NodoSucursales *crearListaSucursalesMejorPromedio(struct Regiones **regiones,struct NodoCompras *ventas ,float mejorPromedio)
{
    struct NodoSucursales *sucursalesMejorPromedio = NULL;
    int i;
    for(i = 0; i<cantRegiones; i++)
    {
        if(regiones[i] != NULL)
        {
            buscarYAgregarSucursalesConMejorPromedio(regiones[i]->sucursales, mejorPromedio, &(sucursalesMejorPromedio),
                                                     ventas);
        }
    }
    return sucursalesMejorPromedio;
}

/*
 SucursalesConMejorPromedio recibe el sistema Derco. Si el sistema es distinto de NULL, se calcula el mejor promedio del
 sistema, si el mejor promedio el igual a 0, retorna 0. Si regiones y ventas son distinto de NULL, se imprime el mejor
 promedio y las sucursales con mejor promedio, retornando 1.
 */
int SucursalesConMejorPromedio(struct SistemaDerco *derco)
{
    struct NodoSucursales *sucursalesMejorPromedio = NULL;
    float mejorPromedio=0;
    if(derco != NULL)
    {
        mejorPromedio = MayorPromedioSucursales(derco);
        if(mejorPromedio==0){
            printf("No hay suficientes datos para realizar esta operacion porfavor revise los registros del sistema\n");
            return 0;
        }
        if(derco->regiones!=NULL && derco->ventas!=NULL)
        {
            printf("El mejor promedio de una sucursal en ventas fue= %f\n",mejorPromedio);
            sucursalesMejorPromedio = crearListaSucursalesMejorPromedio(derco->regiones, derco->ventas, mejorPromedio);
            printf("Las sucursales con mejor promedio son: \n");
            mostrarSucursalesEnumeradas(sucursalesMejorPromedio);
            return 1;
        }
    }
    return 0;
}

#endif //PROYECTODERCO_PROMEDIOVENTASSUCURSALES_H
