//
// Created by gerar on 5/28/2023.
//

#include <stdio.h>
#include "productoMayorRecalls.h"
#include "usuarioMayorGastado.h"
#include "modeloConMasVentas.h"
#include "marcasConMasVentas.h"
#include "sucursalConMasVentas.h"
#include "promedioVentasSucursales.h"
#include "helpers.h"
#include "fusionSucursales.h"
#include "SucursalConMasVentasAutos.h"
#include "SucursalConMasVentasRepuestos.h"

#ifndef PROYECTODERCO_MENUS_H
#define PROYECTODERCO_MENUS_H

void mostrarMenuPrincipal(){
    printf("\n");
    printf("        |========================================================|\n");
    printf("        |                          MENU                          |\n");
    printf("        |                      Sucursal Derco                    |\n");
    printf("        |========================================================|\n");
    printf("        |                       Seleccione                       |\n");
    printf("        |                       Una Opcion                       |\n");
    printf("        |========================================================|\n");
    printf("        |                                                        |\n");
    printf("        | 1. Agregar datos                                       |\n");
    printf("        | 2. Eliminar datos                                      |\n");
    printf("        | 3. Actualizar datos                                    |\n");
    printf("        | 4. Mostrar datos                                       |\n");
    printf("        | 5. Eliminar regiones                                   |\n");
    printf("        | 6. Mostrar Modelos y Marcas de autos vendidos por zona |\n");
    printf("        | 7. Mostrar Cliente que mas ha gastado en sus compras   |\n");
    printf("        | 8. Mostrar Sucursal con mayor distribucion             |\n");
    printf("        | 9. Mostrar Promedio de ventas de sucursales            |\n");
    printf("        | 10. Autos con mas recalls                              |\n");
    printf("        | 11. Fusionar Sucursales                                |\n");
    printf("        | 12. Sucursales con mayor stock y menor stock           |\n");
    printf("        | 13. Sucursales con mas autos vendidos                  |\n");
    printf("        | 14. Sucursales con mas accesorios vendidos             |\n");
    printf("        | 14. Modificar nombre de region                         |\n");
    printf("        | 0. Salir Del Menu                                      |\n");
    printf("        |                                                        |\n");
    printf("        |========================================================|\n");

}

void mostrarMenuDatos(){
    printf("\n");
    printf("        |========================================================|\n");
    printf("        |                          MENU                          |\n");
    printf("        |                      Sucursal Derco                    |\n");
    printf("        |========================================================|\n");
    printf("        |                       Seleccione                       |\n");
    printf("        |                       Una Opcion                       |\n");
    printf("        |========================================================|\n");
    printf("        |                                                        |\n");
    printf("        | 1. Marcas                                              |\n");
    printf("        | 2. Modelos                                             |\n");
    printf("        | 3. Productos Autos                                     |\n");
    printf("        | 4. Sucursales                                          |\n");
    printf("        | 5. Ventas                                              |\n");
    printf("        | 0. Volver al menu anterior                             |\n");
    printf("        |                                                        |\n");
    printf("        |========================================================|\n");
}

void menuRegiones(struct Regiones **regiones)
{
    printf("\n");
    printf("        |========================================================|\n");
    printf("        |                          MENU                          |\n");
    printf("        |                      Sucursal Derco                    |\n");
    printf("        |========================================================|\n");
    printf("        |                       Seleccione                       |\n");
    printf("        |                       una region                       |\n");
    printf("        |========================================================|\n");
    printf("        |                                                        |\n");
    for (int i = 0; i <cantRegiones ; ++i) {
        printf("        | %2d. %-50s |\n", i + 1, regiones[i]->Nombre);
    }
    printf("        | 0. Salir del menu                                      |\n");
    printf("        |                                                        |\n");
    printf("        |========================================================|\n");

}


void switchMenuRegiones(struct SistemaDerco*derco,int idFuncion,int idTipoDato){
    int opcion;
    do {
        menuRegiones(derco->regiones);
        printf("Ingrese la region deseada: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
                realizarAccion(derco,idFuncion,idTipoDato,opcion);
                break;
            case 0:
                printf("Volviendo al menu anterior\n");
                break;
            default:
                printf("Se ingreso una opcion no valida\n");
                break;
        }
    }while(opcion!=0);
}

void SwitchMenuDatos(struct SistemaDerco *derco,int idFuncion){
    int opcion;

    do{
        mostrarMenuDatos();
        printf("-Ingrese Opcion= ");
        scanf("%d",&opcion);
        switch(opcion)
        {
            case 1:
            case 2:
            case 3:
            case 4:
                switchMenuRegiones(derco,idFuncion,opcion);
                break;
            case 5:
                realizarAccion(derco,idFuncion,opcion,0);
                break;
            case 0:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nOpcion invalida. Seleccione una opcion valida\n");
                break;
        }
    }while(opcion!=0);
}

void SwitchMenuPrincipal(struct SistemaDerco *derco){
    int opcion;
    do {
        mostrarMenuPrincipal();
        printf("Ingrese una opcion: ");
        scanf("%d",&opcion);
        switch (opcion){
            case 1:
            case 2:
            case 3:
            case 4:
                SwitchMenuDatos(derco,opcion);
                break;
            case 5:
                interfazEliminarRegiones(derco);
                break;
            case 6:
                printf("\nEstos Son los Modelos y Marcas de autos mas vendidos por zona\n");
                printf("Modelos:\n");
                mostrarModeloConMasVentas(derco);
                printf("Marcas:\n");
                marcasConMasVentas(derco);
                break;
            case 7:
                printf("\nEste es el Cliente que mas ha gastado en compras\n");
                ClienteQueMasHaGastado(derco);
                break;
            case 8:
                printf("\nEsta es la Sucursal que mas ha distribuido\n");
                mostrarSucursalesConMasVentas(derco);
                break;
            case 9:
                printf("\nEstas son las Sucursales con mejor promedio");
                SucursalesConMejorPromedio(derco);
                break;
            case 10:
                printf("\nEstos son los Modelos de Autos con mas recalls\n");
                MostrarAutoConMasRecalls(derco);
                break;
            case 11:
                printf("\nFusionando Sucursales\n");
                if(derco->regiones!=NULL){
                    interfazFusionProducto(derco->regiones);
                    printf("Se fusionar las sucurlsales solicitadas\n");
                }
                else{
                    printf("No hay regiones registradas en el sistema\n");
                }
                break;
            case 12:
                printf("Esta es la sucursal con menos stock\n");
                mostrarMayorYMenorStock(derco);
                break;
            case 13:
                printf("Mostrando sucursales con mas autos vendidos\n");
                mostrarSucursalesConMasVentasAutos(derco);
                break;

            case 14:
                printf("Mostrando sucursales con mas accesorios vendidos\n");
                mostrarSucursalesConMasVentasProductos(derco);
                break;
            case 15:
                interfazModificarRegion(derco);
                break;
            case 0:
                printf("\nSaliendo...\n");
                break;
            default:
                printf("\nOpcion invalida. Seleccione una opcion valida\n");
                break;
        }
    } while(opcion!=0);
}



#endif //PROYECTODERCO_MENUS_H
