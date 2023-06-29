//
// Created by gerar on 5/31/2023.
//

#include "structs.h"
#include "funcionesBasicasProductos.h"
#include "funcionesBasicasMarcas.h"
#include "time.h"
#include "stdio.h"

#ifndef PROYECTODERCO_INTERFAZPRODUCTOARBOL_H
#define PROYECTODERCO_INTERFAZPRODUCTOARBOL_H

/*
    "interfazAgregadoProductoSucursal" esta función esta destinada para que el usuario tenga un medio visual
    que le ayudara a la hora  crear  una prducto y agregarlo a la marca de la sucursal correspondiente. Mostrando
    las marcas disponibles.

    *Se ingresara en que marca se desea crear el producto para después llamar a las funciones "Crear Producto" y
    "agregarProductoEnsucursal"
*/
int interfazAgregadoProductoSucursal(struct NodoSucursales* sucursales,int idSucursal,int tipoDeProducto){
    int idMarca;
    struct Producto *nuevo=NULL;
    struct NodoSucursales *rec;
    if(comprobarSiEnSucursalMarcaEstaVacio(sucursales,idSucursal)==1){
        rec=sucursales;
        do {
            if(rec->datosSucursal->id==idSucursal) break;
            rec=rec->sig;
        }while(rec!=sucursales);

        if(rec!=sucursales || (rec==sucursales && rec->datosSucursal->id==idSucursal)){
            do {
                printf("Marcas Disponibles: \n");
                mostrarMarcasEnumeradas(rec->datosSucursal->marcasAutos);
                printf("Ingrese un id de la marca en la que desea agregar un producto, asegurese que sea valido: ");
                scanf("%d",&idMarca);
            }while(buscarMarcaporId(rec->datosSucursal->marcasAutos,idMarca)==0);

            nuevo=crearProducto();
            nuevo->tipoProducto=tipoDeProducto;
            agregarProductoEnSucursal(rec->datosSucursal,nuevo,idMarca);
            return 1;
        }
        printf("No se encontro la sucursal solicitada por favor revise el registro de sucursales\n");

    }
    printf("No exiten marcas en la sucursal que se quiere agregar un producto, cree una marca antes de intentarlo denuevo\n");
    return 0;
}

/*
    "interfazMostrarProductoSucursal" esta función esta destinada para mostrar los autos o productos que estan disponibles
    en una sucursal, dependiendo del tipo de producto entregado.

*/

int interfazMostrarProductoSucursal(struct NodoSucursales* sucursales,int idSucursal,int tipoProducto){
    if(comprobarSiEnSucursalMarcaEstaVacio(sucursales,idSucursal)==1){

        if(tipoProducto==2){
            printf("Estos son los automoviles ofrecido por la sucursal: \n");
            mostrarAutosSucursal(sucursales,idSucursal);
        }
        if(tipoProducto==3){
            printf("Estos son los productos para Autos ofrecidos por la Sucursal: \n");
            mostrarProductosSucursal(sucursales,idSucursal);
        }

        return 1;
    }
    printf("No exiten marcas en la sucursal que se quiere agregar un producto, asegurese de crear una marca antes de intentarlo\n");
    return 0;
}

/*
    "interfazActualizarMarcaProductoMarca" esta función esta destinada para que el usuario tenga un medio visual
    que le ayudara a la hora de actualizar un producto , primero mostrando los productos disponibles para esto.

    *La actualizacion consiste en cambiar el valor y descripción para después llamar a la función "buscarYActualizarEnArbol".
*/

int interfazActualizarProductosMarca(struct NodoMarcas *marcas,int idMarca,int tipoProducto){
    int idProducto,valor,flag=0;
    char descripcionNueva[500];
    struct Producto *actualizado=NULL;
    struct NodoMarcas *rec=marcas;
    while(rec->datosMarca->id!=idMarca || rec==NULL){
        rec=rec->sig;
    }
    if(rec!=NULL){
        if(tipoProducto==2 && rec->datosMarca->autos!=NULL){
            do {
                printf("Estos son los autos disponibles: \n");
                mostrarProductos(rec->datosMarca->autos);
                printf("Ingrese  id del producto que desea actualizar, asegurese que sea valido: ");
                scanf("%d",&idProducto);
            }while(buscarProductoEnSucursal(marcas,idProducto)==0);

            buscarProductoYDevolver(rec->datosMarca->autos,idProducto,&actualizado);

            actualizado->descripcion=NULL;
            printf("Ingrese el nuevo valor del producto: ");
            scanf("%d",&valor);
            actualizado->valor=valor;
            printf("Ingrese la nueva descripcion del producto: ");
            getchar();
            scanf("%[^\n]s ",descripcionNueva);
            getchar();
            actualizado->descripcion=(char *)malloc(strlen(descripcionNueva) * sizeof(char));
            strcpy(actualizado->descripcion,descripcionNueva);
            printf("id actualizado = %d",actualizado->idProducto);
            buscarYActualizarEnArbol(&(rec->datosMarca->autos),actualizado,&flag);
            if(flag==1) return 1;
            return 0;
        }

        if(tipoProducto==3 && rec->datosMarca->productosAutos!=NULL){
            do {
                printf("Estos son los Productos para Autos disponibles: \n");
                mostrarProductos(rec->datosMarca->productosAutos);
                printf("Ingrese id del producto que desea actualizar, asegurese que sea valido: ");
                scanf("%d",&idProducto);
            }while(buscarProductoEnSucursal(marcas,idProducto)==0);

            buscarProductoYDevolver(rec->datosMarca->productosAutos,idProducto,&actualizado);

            printf("Ingrese el nuevo valor del producto: ");
            scanf("%d",&valor);
            printf("Ingrese nueva descripcion del producto: ");
            getchar();
            scanf("%[^\n]s ",descripcionNueva);
            getchar();
            actualizado->descripcion=(char *)malloc(strlen(descripcionNueva) * sizeof(char));
            strcpy(actualizado->descripcion,descripcionNueva);
            buscarYActualizarEnArbol(&(rec->datosMarca->productosAutos),actualizado,&flag);
            if(flag==1) return 1;
            return 0;
        }
    }
    printf("No hay registros de productos disponibles actualmente en esta marca\n");
    return 0;

}

/*
    "interfazActualizarProductosSucursal" funcinó que comprueba si los datos entregados son válidos para luego
    llamar a la función "intefazActualizadMarcaProductoSucursal"
*/
int interfazActualizarProductosSucursal(struct NodoSucursales *sucursales,int idSucursal,int tipoProducto){

    int idMarca;
    struct NodoSucursales *rec;
    if(comprobarSiEnSucursalMarcaEstaVacio(sucursales,idSucursal)==1){
        rec=sucursales;
        do {
            rec=rec->sig;
        }while(rec->datosSucursal->id!=idSucursal);

        do {
            printf("Marcas Disponibles: \n");
            mostrarMarcasEnumeradas(rec->datosSucursal->marcasAutos);
            printf("Ingrese id de la marca en la que desea agregar un producto,asegurese que sea valido: ");
            scanf("%d",&idMarca);
        }while(buscarMarcaporId(rec->datosSucursal->marcasAutos,idMarca)==0);

        if(interfazActualizarProductosMarca(rec->datosSucursal->marcasAutos,idMarca,tipoProducto)==1) return 1;
        return 0;

    }
    printf("No exiten marcas en la sucursal que se quiere agregar un producto, asegurese de crear una marca antes de intentarlo  \n");
    return 0;

}

/*
    "interfazActualizarProductosSucursal" esta función esta destinada para que el usuario tenga un medio visual
    que le ayudara a la hora de eliminar un producto de una marca en una sucursal, primero mostrando las sucursales
    disponibles para esto

    *La elimacion se efectua llamando a la función "descartarProducto".
*/
int interfazEliminarProductoSucursal(struct NodoSucursales*sucursales,int idSucursal,int tipoProducto){
    int idProductoEliminar;
    struct NodoSucursales *rec;
    if(comprobarSiEnSucursalMarcaEstaVacio(sucursales,idSucursal)==1){
        rec=sucursales;
        do {
            rec=rec->sig;
        }while(rec->datosSucursal->id!=idSucursal);
        if(tipoProducto==2){
            if(hayModelosEnMarcas(rec->datosSucursal->marcasAutos)==1){
                do {
                    printf("Estos son los Autos que se pueden eliminar: \n");
                    mostrarAutosSucursal(sucursales,idSucursal);
                    printf("Ingrese id del producto que desea eliminar,asegurese que sea valido: \n");
                    scanf("%d",&idProductoEliminar);
                }while(buscarProductoEnSucursal(rec->datosSucursal->marcasAutos,idProductoEliminar)==0);
                descartarProducto(rec->datosSucursal->marcasAutos,idProductoEliminar);
                return 1;
            }
            else{
                printf("No hay registros de modelos en esta marca\n");
                return 0;
            }

        }
        if(tipoProducto==3){
            if(hayProductosAutosEnMarcas(rec->datosSucursal->marcasAutos)==1){
                do {
                    printf("Estos son los Productos para Autos que se pueden eliminar: \n");
                    mostrarProductosSucursal(sucursales,idSucursal);
                    printf("Ingrese id del producto que desea eliminar,asegurese que sea valido: \n");
                    scanf("%d",&idProductoEliminar);
                }while(buscarProductoEnSucursal(rec->datosSucursal->marcasAutos,idProductoEliminar)==0);
                descartarProducto(rec->datosSucursal->marcasAutos,idProductoEliminar);
                return 1;
            }
            else{
                printf("No hay registros de productos para autos en esta marca\n");
                return 0;
            }
        }
        return 1;
    }
    printf("No exiten marcas en la sucursal que se quiere agregar un producto, asegurese de crear una marca antes de intentarlo\n");
    return 0;
}
#endif //PROYECTODERCO_INTERFAZPRODUCTOARBOL_H
