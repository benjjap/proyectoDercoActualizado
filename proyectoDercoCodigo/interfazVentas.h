//
// Created by gerar on 5/31/2023.
//
#include "funcionesBasicasVentas.h"
#include "stdio.h"
#include "structs.h"
#include "string.h"
#ifndef PROYECTODERCO_INTERFAZVENTAS_H
#define PROYECTODERCO_INTERFAZVENTAS_H

/*
    "interfazEliminarVenta" esta función esta destinada para que el usuario tenga un medio visual
    que le ayudara a la hora de eliminar una venta y agregarlo a la marca de la sucursal correspondiente. Mostrando
    todas la ventas efectuadas.

    *Se ingresara el ID de la marca a eliminar y si es válida llamara a la función "eliminarVenta"
*/

void interfazEliminarVenta(struct NodoCompras **ventas)
{
    int idVenta;
    if(*ventas!=NULL){
        printf("Compras efectuadas disponibles para eliminar\n");
        mostrarVentas(*ventas);
        do
        {
            printf("Ingrese una id valida para Eliminar\n");
            scanf("%d",&idVenta);
        }while (buscarCompra(*ventas,idVenta)==0);

        eliminarVenta(ventas,idVenta);
        printf("La compra ha sido eliminada de manera exitosa\n");
        return;
    }
    printf("No existen ventas registradas en el sistema, porfavor registre una venta antes de intentarlo \n");
}

/*
    "interfazActualizarVenta" esta función esta destinada para que el usuario tenga un medio visual
    que le ayudara a la hora de actualizar una venta a la marca de la sucursal correspondiente. Mostrando
    todas la ventas efectuadas, para despues llamar a la función

    *Los valores a actualizar seran el nombre y rut del cliente buscarYActualizarDatosCompra.
*/

void interfazActualizarVenta(struct NodoCompras *ventas)
{
    int id;
    int respuesta;
    int i;

    char Nombre[50], rut[13];
    struct Compra *compra=NULL;
    if(ventas!=NULL){
        printf("Compras disponibles para actualizar \n");
        mostrarVentas(ventas);
        do
        {
            printf("Ingrese una ID valida para actualizar\n");
            scanf("%d",&id);
            compra= buscarYRetornarCompra(ventas,id);
        }while(compra==NULL);

        printf("Ingrese el nombre del cliente que estara relacionado con la venta\n");

        scanf("%s[^\n] ",Nombre);
        printf("Ingrese el rut del  cliente que estara relacionado con la venta\n");
        scanf("%s[^\n] ",rut);

        if(compra->productos!=NULL){
            for(i=0;i<maxCompras && compra->productos[i]!=NULL;i++)
            {
                if(compra->productos[i]!=NULL){
                    printf("Desea mandar a Recall el producto %s de id %d?\n",compra->productos[i]->nombreProducto,compra->productos[i]->idProducto);
                    printf("Ingrese 1 para modificar, 0 para lo contrario\n");
                    scanf("%d",&respuesta);
                    while(respuesta!=0 && respuesta !=1)
                    {
                        printf("Ingrese una respuesta valida\n");
                        scanf("%d",&respuesta);
                    }
                    if(respuesta==1){
                        compra->productos[i]->estadoRecall=true;
                    }
                }

            }
        }

        compra->rutCliente=NULL;
        compra->nombreCliente=NULL;

        compra->nombreCliente=(char *)malloc(sizeof(char)*strlen(Nombre));
        compra->rutCliente=(char *)malloc(sizeof(char)* strlen(rut));

        strcpy(compra->nombreCliente,Nombre);
        strcpy(compra->rutCliente,rut);


        buscarYActualizarDatosCompra(&(ventas),compra);

        printf("La venta ha sido actualizada correctamente\n");
        return;
    }
    printf("No existen ventas registradas en el sistema, porfavor registre una venta antes de intentarlo\n");

}


#endif //PROYECTODERCO_INTERFAZVENTAS_H



