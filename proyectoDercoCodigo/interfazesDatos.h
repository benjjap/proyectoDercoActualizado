//
// Created by gerar on 5/30/2023.
//

#include "structs.h"
#include "funcionesBasicasSucursales.h"
#include "funcionesBasicasProductos.h"
#include "funcionesBasicasMarcas.h"
#include "interfazProductoArbol.h"
#include "interfazMarca.h"
#include "funcionesBasicasRegiones.h"
#include "comprarProducto.h"
#include "interfazVentas.h"

#ifndef PROYECTODERCO_INTERFAZDATOS_H
#define PROYECTODERCO_INTERFAZDATOS_H


/*
 interfazMarcaRegion pregunta en que sucursal se quiere buscar la marca para realizar una acción especifica, luego de
 esto, se identifica la acción a realizar ya sea agregar, eliminar, actualizar o mostrar marcas en esa sucursal
 */

int interfazMarcaRegion(struct Regiones **regiones,int siglaRegion,int idFuncion){
    int idSucursal;
    if(regiones!=NULL && regiones[siglaRegion-1]->sucursales!=NULL){
        printf("siglaRegion= %d\n",siglaRegion);
        do {
            printf("Sucursales Disponibles: \n");
            mostrarSucursalesEnumeradas(regiones[siglaRegion-1]->sucursales);
            printf("\nIngrese id de la sucursal en la cual  quiera modificar o mostrar una marca: ");
            scanf("%d",&idSucursal);
        }while(buscarSucursal(regiones[siglaRegion-1]->sucursales,idSucursal)==0);
        if(idFuncion==1){
            interfazAgregadoMarcaSucursal(regiones[siglaRegion-1]->sucursales,idSucursal);
        }
        if(idFuncion==2){
            interfazEliminarMarcaSucursal(regiones[siglaRegion-1]->sucursales,idSucursal);
        }
        if(idFuncion==3){
            interfazActualizarMarcaSucursal(regiones[siglaRegion-1]->sucursales,idSucursal);
        }
        if(idFuncion==4){
            mostrarMarcasSucursal(regiones[siglaRegion-1]->sucursales,idSucursal);
        }
        return 1;
    }
    printf("No se pudo completar la operacion solicitada\n");
    return 0;
}

/*
 interfazProductoRegion pregunta en que sucursal se quiere buscar el producto para realizar una acción especifica,luego de
 esto se identifica la accion a realizar ya sea agregar, eliminar, actualizar o mostrar productos en esa sucursal
 */

int interfazProductoRegion(struct Regiones **regiones,int siglaRegion,int idFuncion,int tipoProducto){
    int idSucursal;
    if(regiones!=NULL && regiones[siglaRegion-1]->sucursales!=NULL){
        do {
            printf("Sucursales Disponibles: \n");
            mostrarSucursalesEnumeradas(regiones[siglaRegion-1]->sucursales);
            printf("Ingrese id de la sucursal a la cual desea modificar o mostrar sus productos: ");
            scanf("%d",&idSucursal);
        }while(buscarSucursal(regiones[siglaRegion-1]->sucursales,idSucursal)==0);
        if(idFuncion==1){
            if(interfazAgregadoProductoSucursal(regiones[siglaRegion-1]->sucursales,idSucursal,tipoProducto)==1) return 1;
            return 0;
        }
        if(idFuncion==2){
            if(interfazEliminarProductoSucursal(regiones[siglaRegion-1]->sucursales,idSucursal,tipoProducto)==1)return 1;
            return 0;
        }
        if(idFuncion==3){
            if(interfazActualizarProductosSucursal(regiones[siglaRegion-1]->sucursales,idSucursal,tipoProducto)==1) return 1;
            return 0;
        }
        if(idFuncion==4){
            if(interfazMostrarProductoSucursal(regiones[siglaRegion-1]->sucursales,idSucursal,tipoProducto)==1) return 1;
            return 0;
        }
    }
    printf("No se pudo completar la operacion solicitada\n");
    return 0;
}

/*
 interfazSucursal se identifica que acción realizar sobre la sucursal ya sea agregar, eliminar, actualizar o mostrar sucursales
 */

int interfazSucursalRegion(struct Regiones **regiones,int siglaRegion,int idFuncion){
    int idSucursal;
    struct Sucursal *actualizado=NULL;
    char nuevoNombre[20];
    if(regiones!=NULL){
        if(idFuncion==1){
            crearSucursalYAgregarSucursal(regiones,siglaRegion);
        }
        if(idFuncion==2){
            if(regiones[siglaRegion-1]->sucursales!=NULL){
                do {
                    printf("Sucursales Disponibles: \n");
                    mostrarSucursalesEnumeradas(regiones[siglaRegion-1]->sucursales);
                    printf("Ingrese un id valido de la sucursal que desea eliminar: ");
                    scanf("%d",&idSucursal);
                }while(buscarSucursal(regiones[siglaRegion-1]->sucursales,idSucursal)==0);
                eliminarSucursal(&(regiones[siglaRegion-1]->sucursales),idSucursal);
                return 1;
            }
            else{
                printf("No hay sucursales registradas en esta region\n");
                return 0;
            }

        }
        if(idFuncion==3){
            if(regiones[siglaRegion-1]->sucursales!=NULL){
                do {
                    printf("Sucursales Disponibles: \n");
                    mostrarSucursalesEnumeradas(regiones[siglaRegion-1]->sucursales);
                    printf("Ingrese id de la sucursal en la cual  desea actualizar un producto:");
                    scanf("%d",&idSucursal);
                }while(buscarSucursal(regiones[siglaRegion-1]->sucursales,idSucursal)==0);
                actualizado= buscarSucursalYRetornar(regiones[siglaRegion-1]->sucursales,idSucursal);
                do {
                    printf("Ingrese un nombre distinto al que existe: ");
                    getchar();
                    scanf("%[^\n]s ", nuevoNombre);
                    getchar();
                }while(strcmp(actualizado->nombre,nuevoNombre)==0);
                actualizado->nombre=(char *)malloc(strlen(nuevoNombre) * sizeof(char));
                strcpy(actualizado->nombre,nuevoNombre);
                actualizarSucursal(&(regiones[siglaRegion-1]->sucursales),actualizado);
                return 1;
            }
            else{
                printf("No hay sucursales registradas en esta region\n");
                return 0;
            }

        }
        if(idFuncion==4){
            printf("Sucursales en la region: \n");
            mostrarSucursalesEnumeradas(regiones[siglaRegion-1]->sucursales);
        }
        return 1;
    }
    printf("La sucursal ingresada no existentes");
    return 0;
}

/*
 interfazVentas se identifica que acción realizar sobre la sucursal ya sea agregar, eliminar, actualizar o mostrar ventas
 */

int interfazVentas(struct SistemaDerco*derco,int idFuncion){
    int siglaRegion;
    if(derco->regiones!=NULL){
        if(idFuncion==1){
            do {
                printf("Regiones existentes: \n");
                mostrarRegiones(derco->regiones);
                scanf("%d",&siglaRegion);
            }while(siglaRegion<=0 || siglaRegion>16);
            crearYAgregarCompraAVentas(derco,siglaRegion);
        }
        if(idFuncion==2){
            interfazEliminarVenta(&derco->ventas);
        }
        if(idFuncion==3){
            interfazActualizarVenta(derco->ventas);
        }
        if(idFuncion==4){
            mostrarVentas(derco->ventas);
        }
        return 1;
    }
    printf("Region ingresada no existe \n");
    return 0;
}

void interfazEliminarRegiones(struct SistemaDerco*derco) {
    int siglaRegion;
    if (derco->regiones != NULL) {
        do {
            printf("Regiones existentes: \n");
            mostrarRegiones(derco->regiones);
            printf("Ingrese sigla de la region que desea eliminar:\n");
            scanf("%d", &siglaRegion);
        } while (siglaRegion <= 0 || siglaRegion > 16);
        eliminarRegion(derco, siglaRegion);
    }
}

void interfazModificarRegion(struct SistemaDerco*derco) {
    int siglaRegion;
    if (derco->regiones != NULL) {
        do {
            printf("Regiones existentes: \n");
            mostrarRegiones(derco->regiones);
            printf("Ingrese sigla de la region que desee cambiar el nombre:\n");
            scanf("%d", &siglaRegion);
        } while (siglaRegion <= 0 || siglaRegion > 16);
        cambiarNombreRegion(derco,siglaRegion);
    }
}


#endif //PROYECTODERCO_INTERFAZDATOS_H
