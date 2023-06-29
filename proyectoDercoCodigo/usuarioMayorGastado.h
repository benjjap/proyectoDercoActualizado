//
// Created by gerar on 5/28/2023.
//

#include "structs.h"
#include <stdio.h>
#include <string.h>
#include "funcionesBasicasVentas.h"

#ifndef PROYECTODERCO_USUARIOMAYORGASTADO_H
#define PROYECTODERCO_USUARIOMAYORGASTADO_H

/*
    "MostrarCLienteQueMasHaGastado" recibe  un struct de tipo NodoCompras que contendran el(los) clientes que
    hayan cumplido la condicion de mayor gasto en la consecionaria.
 */
void MostrarCLienteQueMasHaGastado(struct NodoCompras *compras)
{
    int i=1;
    struct NodoCompras *rec=compras;
    do
    {
        printf("-%i Nombre Cliente=%s     Rut=%s \n",i,rec->datosCompra->nombreCliente,rec->datosCompra->rutCliente);
        i++;
        rec=rec->sig;
    }while(rec!=compras);
}

/*
    "CalcularGastado" recibe el struct de todas las compras efectuadas en la consecionaria ademas de un string
    que hace referencia a un rut de un Cliente, mediantela función strcmp va comparando cada dato de la compra con el
    rut para poder ir sumando  y finalmente rotornando una variable de tipo entero relacionada al gasto total del comprador
 */
int CalcularGastado(struct NodoCompras *compras,char *rutCliente)
{
    int Gastado=0;
    struct NodoCompras *rec=compras;
    do {
        if(strcmp(rec->datosCompra->rutCliente,rutCliente)==0)
            Gastado+=rec->datosCompra->valorCompra;
        rec=rec->sig;
    }while(rec!=compras);
    return Gastado;
}

/*
    "ClienteQueMasHaGastado" (Funcion principal) recibe el sistema Derco, su función es poder calcular cual ha sido la suma de dinero
    mas grande que un cliente haya gastado en la consecionaria, para despues ir preguntando cliente por cliente
    si cumplen la condición de que si total gastado es igual a "MayorCantidadGastada" para agregarlo a una lista
    que luego los imprimira

    *Si no se ha realizado ninguna venta(derco->ventas ==NULL) imprimira el mensaje correspondiente.
 */

void ClienteQueMasHaGastado(struct SistemaDerco *derco)
{
    struct NodoCompras *clientesqueMasGastaron=NULL;
    struct NodoCompras *rec;
    int MayorCantidadGastada=0,aux;

    if(derco->ventas==NULL)
    {
        printf("No se ha realizado niguna venta en la consecionaria Derco\n");
        return;
    }

    else
    {
        rec=derco->ventas;
        do
        {
            aux=CalcularGastado(derco->ventas,rec->datosCompra->rutCliente);
            if(aux>MayorCantidadGastada){
                MayorCantidadGastada=aux;
            }
            rec=rec->sig;
        }while(rec!=derco->ventas);

    }

    do
    {
        if(CalcularGastado(derco->ventas,rec->datosCompra->rutCliente)==MayorCantidadGastada){
            agregarAVentas(&(clientesqueMasGastaron),rec->datosCompra);
        }
        rec=rec->sig;
    }while(rec!=derco->ventas);

    MostrarCLienteQueMasHaGastado(clientesqueMasGastaron);
}

#endif //PROYECTODERCO_USUARIOMAYORGASTADO_H
