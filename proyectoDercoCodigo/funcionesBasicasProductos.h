 //
// Created by gerar on 5/28/2023.
//

#define cantRegiones 16
#include "structs.h"
#include "funcionesBasicasMarcas.h"
#include "funcionesBasicasSucursales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef PROYECTODERCO_FUNCIONESBASICASPRODUCTOS_H
#define PROYECTODERCO_FUNCIONESBASICASPRODUCTOS_H


/*
 buscarProductoYDevolver recibe un árbol, el Id de producto y un struct de producto. Primero se pregunta si el árbol es
 nulo, si es, se retorna. Si no es nulo se recorre el árbol de forma recursiva preguntando si el id mandado es igual al
 del producto, si se encuentra se remplaza el struct mandado por el producto en el árbol y se retorna.
 */

void buscarProductoYDevolver(struct NodoProductos *abb,int idProducto,struct Producto **producto){
    if(abb==NULL) return;
    buscarProductoYDevolver(abb->izq,idProducto,producto);
    buscarProductoYDevolver(abb->der,idProducto,producto);
    if(abb->datosProducto->idProducto==idProducto) {
        (*producto)=abb->datosProducto;
        return;
    }
}

/*
 buscarProductoEnMarca recibe el árbol, un Id de producto y un int que hace de booleano. Primero se pregunta si el árbol
 es nulo, si no es nulo entra a recorrer el árbol de forma recursiva preguntando si el id de producto es el mismo del
 nodo recorrido, si pasa, se asigna valor 1 al booleano y retorna.
 */

void buscarProductoEnMarca(struct NodoProductos *abb ,int idProducto, int *Booleano)
{
    if(abb!=NULL)
    {
        buscarProductoEnMarca(abb->izq,idProducto,Booleano);
        buscarProductoEnMarca(abb->der,idProducto,Booleano);
        if(abb->datosProducto->idProducto==idProducto){
            (*Booleano)=1;
            return;
        }
    }
}

/*
 buscarProductoEnSucursal recibe la lista de marcas y el id de Producto buscado. Se recorre la lista mientras el nodo sea
 distinto de NULL y se llama a buscarProductoEnMarca con el árbol de producto, si el booleano es 1, se retorna el
 booleano, si no se llama la misma función para el árbol de autos, se vuelve a preguntar por el booleano. si no se encuentra
 al final del ciclo, se retorna el booleano.
 */

int buscarProductoEnSucursal(struct NodoMarcas *marcas, int idProducto)
{
    struct NodoMarcas *rec=marcas;
    int Booleano=0;
    while(rec!=NULL)
    {
        buscarProductoEnMarca(rec->datosMarca->productosAutos,idProducto,&Booleano);
        if(Booleano==1)
            return Booleano;
        buscarProductoEnMarca(rec->datosMarca->autos,idProducto,&Booleano);
        if(Booleano==1)
            return Booleano;
        rec=rec->sig;
    }
    return Booleano;
}

/*
    BuscarProducto recorrera todas las sucursales en busca de una suscurdal dada por  un id,
    cuando la encuentre llamara a la funcion "buscarProductoEnSucursal" dependiendo  de lo retornado por la funcion
    retornara lo mismo dependiendo si se encuentra o no.

    *Ademas mediante uso de punteros cambiara la sigla correspondiente a la region donde se encuentra la sucursal.
 */

int BuscarProducto(struct Regiones **regiones, int idProducto,int idSucursal,int *Region)
{
    int i;
    struct NodoSucursales *rec;
    for(i=0;i<cantRegiones;i++)
    {
        if(regiones[i]->sucursales!=NULL)
        {
            rec=regiones[i]->sucursales;
            do
            {
                if(rec->datosSucursal->id==idSucursal)
                {
                    if(buscarProductoEnSucursal(rec->datosSucursal->marcasAutos,idProducto)==1)
                    {
                        (*Region)=i;
                        return 1;
                    }
                    return 0;
                }
                rec=rec->sig;
            }while(rec!=regiones[i]->sucursales);
        }
    }
    return 0;
}

 /*
 retornarrProductoEnMarca recibe un árbol, un Id de producto y el struct a retornar. Se pregunta si es distinto de NULL
 sí es distinto, comienza a recorrer el árbol de forma recursiva y pregunta si el id del nodo es igual al id de producto
  sí es igual, a retornar se le asigna el valor datos del producto.
  */

 bool retornarProductoEnMarca(struct NodoProductos *abb, int idProducto, struct Producto **retornar)
 {
     if (abb != NULL)
     {
         if (retornarProductoEnMarca(abb->izq, idProducto, retornar))
             return true;

         if (retornarProductoEnMarca(abb->der, idProducto, retornar))
             return true;

         if (abb->datosProducto->idProducto == idProducto)
         {
             (*retornar) = abb->datosProducto;
             return true;
         }
     }

     return false;
 }

 /*
    retornarProductoEnSucursal recibe la lista de marcas y el Id de Producto. Se crea un struct producto y se recorre
    la lista y se llama la función retornarrProductoEnMarca con el árbol de autos, el id del producto y el struct
    que se acaba de crear al principio, luego pregunta si el struct es distinto de NULL, si se cumple la condición, se
    retorna el producto.
  */

 struct Producto *retornarProductoEnSucursal(struct NodoMarcas *marcas, int idProducto)
 {
     struct NodoMarcas *rec=marcas;
     struct Producto *producto=NULL;
     while(rec!=NULL)
     {
         retornarProductoEnMarca(rec->datosMarca->autos,idProducto,&producto);
         if(producto !=NULL)
             return producto;
         retornarProductoEnMarca(rec->datosMarca->productosAutos,idProducto,&producto);
         if(producto !=NULL)
             return producto;
         rec=rec->sig;
     }
     return producto;
 }

 /*
  RetornarProducto recibe el arreglo de regiones y un ID de producto. Recorre el arreglo y la lista de sucursales por
  cada región y se llama la función retornarProductoEnSucursal en la variable retornar. Si retornar es distinto de NULL
  de va a retornar la variable, si no va a seguir recorriendo. si no se encuentra, se retornará NULL.
  */

struct Producto *RetornarProducto(struct Regiones **regiones, int idProducto)
 {
     int i;
     struct Producto *retornar=NULL;
     struct NodoSucursales *rec;
     for(i=0;i<cantRegiones;i++)
     {
         if(regiones[i]->sucursales!=NULL)
         {
             rec=regiones[i]->sucursales;
             do
             {

                 retornar=retornarProductoEnSucursal(rec->datosSucursal->marcasAutos,idProducto);
                 if(retornar!=NULL)
                     return retornar;
                 rec=rec->sig;
             }while(rec!=regiones[i]->sucursales);
         }
     }
     return retornar;
 }

 /*
  reemplazar recibe el árbol de productos y un auxiliar de árbol. si el nodo de la derecha el head del árbol es NULL, se asigna a los datos de aux los datos del head de productos, se crea una variable temporal y se le asigna
  productos. Si no se cumple con la condición se vuelve a llamar con el nodo de la derecha.
  */

void reemplazar(struct NodoProductos **productos, struct NodoProductos **aux) {
    if (!(*productos)->der) {
        (*aux)->datosProducto = (*productos)->datosProducto;
        struct NodoProductos *temp = *productos;
        *productos = (*productos)->izq;
        free(temp);
    } else {
        reemplazar(&(*productos)->der, aux);
    }
}

/*
 eliminarProductoEnArbol recibe el árbol de producto y un ID de producto. si el árbol es NULL retorna. si el id del nodo
 es menor a id producto buscado, se llama eliminarProductoEnArbol con el nodo de la derecha y el id de producto buscado
 sí es mayor se llama a la función recursiva con el nodo de la izq. si se encuentra el producto, se elimina el producto
 del árbol.
 */

void eliminarProductoEnArbol(struct NodoProductos **productos, int idProducto) {
    if (!(*productos))
        return;

    if ((*productos)->datosProducto->idProducto < idProducto) {
        eliminarProductoEnArbol(&(*productos)->der, idProducto);
    } else if ((*productos)->datosProducto->idProducto > idProducto) {
        eliminarProductoEnArbol(&(*productos)->izq, idProducto);
    } else {
        if ((*productos)->datosProducto->idProducto == idProducto) {
            struct NodoProductos *aux = *productos;
            if (!(*productos)->izq) {
                *productos = (*productos)->der;
            } else if (!(*productos)->der) {
                *productos = (*productos)->izq;
            } else {
                reemplazar(&(*productos)->izq, &aux);
            }
            free(aux);
        }
    }
}

/*
    descartarProducto recibe la lista de marcas y el id de producto buscado. Se recorre la lista y se hace llamado a la
    función buscarProductoEnMarca con árbol, el id buscado y el booleano. Si el booleanos es igual a 1, se llama a la
    función eliminarProductoEnArbol y se retorna 1. Si no se llama a buscarProductoEnMarca, si el booleano es igual a 1
    se llama a la función a eliminar y se retorna 1. Si no se encontró después del ciclo, se retorna 0.
 */

int descartarProducto(struct NodoMarcas *marcas, int idProducto)
{
    struct NodoMarcas *rec=marcas;
    int Booleano;
    while(rec!=NULL)
    {
        Booleano=0;
        buscarProductoEnMarca(rec->datosMarca->productosAutos,idProducto,&Booleano);
        if(Booleano==1)
        {
            eliminarProductoEnArbol(&(rec->datosMarca->productosAutos), idProducto);
            return 1;
        }
        Booleano=0;
        buscarProductoEnMarca(rec->datosMarca->autos,idProducto,&Booleano);
        if(Booleano==1)
        {
            eliminarProductoEnArbol(&(rec->datosMarca->autos), idProducto);
            return 1;
        }

        rec=rec->sig;
    }
    return 0;
}

/*
 buscarYActualizarEnArbol recibe un árbol, un producto y un int actualizado. Se pregunta si el árbol es distinto de NULL
 se recorre el árbol recursivamente post orden y se hace la condición, si el producto es igual al del árbol, se cambia el valor
 de actualizado a 1 y retorna.
 */

void buscarYActualizarEnArbol(struct NodoProductos **abb, struct Producto *producto,int *actualizado)
{
    if((*abb) != NULL)
    {
        buscarYActualizarEnArbol(&((*abb)->izq), producto,actualizado);
        buscarYActualizarEnArbol(&((*abb)->der), producto,actualizado);
        if((*abb)->datosProducto->idProducto == producto->idProducto)
        {
            (*abb)->datosProducto = producto;
            *actualizado=1;
            return;
        }
    }
}

/*
AumentarStock recibe árbol de productos y un struct producto. Si el árbol es distinto de NULL recorre el árbol de forma
 recursiva con AumentarStock y pregunta si el id del nodo que se encuentra y suma el stock del producto.
 */


void AumentarStock(struct NodoProductos **abb, struct Producto *producto)
{
    if(*abb!=NULL)
    {
        AumentarStock(&((*abb)->izq),producto);
        AumentarStock(&((*abb)->der),producto);
        if((*abb)->datosProducto->idProducto==producto->idProducto)
            (*abb)->datosProducto->stock+=producto->stock;
    }
}

/*
 buscar recibe un árbol de productos, el anterior del árbol de productos y un ID de producto. Se hace un ciclo mientras
 enc sea distinto de 0 y si el árbol es distinto de NULL. si el producto se encuentra en el árbol, se cambia el valor de
 enc a 1, si no se encuentra se cambia el ant a árbol y si el id del Producto es menor al del nodo izquierdo, árbol es
 igual a árbol izquierdo, si no a árbol derecho.
 */

struct NodoProductos* buscar(struct NodoProductos *abb, struct NodoProductos **ant, int idProducto)
{
    int enc = 0;
    while(!enc && abb)
    {
        if(abb->datosProducto->idProducto == idProducto)
            enc = 1;
        else
        {
            *ant = abb;
            if(idProducto < abb->datosProducto->idProducto)
                abb = abb->izq;
            else
                abb = abb->der;
        }
    }
    return abb;
}

/*
 agregarEnMarca recibe el árbol de productos y un struct producto. Se inicia una variable ptr que llama a la función
 buscar, luego mientras ptr sea igual a NULL se agrega el producto al árbol, si no se cumple la condición, se pregunta si
 el id del producto es menor que el del anterior, entonces el anterior izq es igual al nuevo, si no es el anterior derecho
 donde se agrega el producto.
 */

void agregarEnMarca(struct NodoProductos **abb,struct Producto *producto)
{
    struct NodoProductos *nuevo=NULL, *ant=NULL, *ptr=NULL;
    ptr=buscar(*abb,&ant,producto->idProducto);
    if(ptr==NULL)
    {
        nuevo=(struct NodoProductos*)malloc(sizeof(struct NodoProductos));
        nuevo->datosProducto=producto;
        nuevo->izq=nuevo->der=NULL;
        if(ant==NULL){
            *abb=nuevo;
        }

        else
        {
            if(producto->idProducto< ant->datosProducto->idProducto)
                ant->izq=nuevo;
            else
                ant->der=nuevo;
        }
    }
    else///El Producto existe
        AumentarStock(abb,producto);
}

 /*
  crearProducto es una función que reserva la memoria para el struct y va llenando los datos de forma interactiva con el
  usuario y al finalizar retorna el struct creado.
  */

struct Producto *crearProducto(){
    srand(time(NULL));
    struct Producto *producto=NULL;
    char buffer[500];
    int aux;
    producto=(struct Producto *)malloc(sizeof(struct Producto));
    producto->idProducto=rand();
    printf("El id para el nuevo producto es: %d\n",producto->idProducto);
    printf("Ingrese el nombre del producto que desea crear: \n");
    getchar();
    scanf("%[^\n]s ",buffer);
    getchar();
    producto->nombre=(char *)malloc(strlen(buffer) * sizeof(char));
    strcpy(producto->nombre,buffer);
    do {
        printf("Ingrese el stock inicial  del producto, asegurese que sea valido (mayor a cero) : \n");
        scanf("%d",&aux);
    }while(aux<0);
    producto->stock=aux;
    do {
        printf("Ingrese el precio del producto, asegurse que sea valido (mayor a cero): \n");
        scanf("%d",&aux);
    }while(aux<0);
    producto->valor=aux;
    printf("Ingrese una descripcion para el producto (max 500 caracteres): \n");
    getchar();
    scanf("%[^\n]s ",buffer);
    getchar();
    producto->descripcion=(char *)malloc(strlen(buffer) * sizeof(char));
    strcpy(producto->descripcion,buffer);
    return producto;
}

/*
 crearMarca recibe un Id de marca y lo que hace es reservar memoria para el struct y asignar los valores y datos con los
 que rellene el usuario, al final retornando la nueva marca.
 */

struct Marca *crearMarca(int idMarca){
    struct Marca *nuevo=NULL;
    char nombreMarca[50];
    nuevo=(struct Marca *)malloc(sizeof(struct Marca));
    printf("Ingrese nombre de la marca que desea crear\n ");
    getchar();
    scanf("%[^\n]s ",nombreMarca);
    getchar();
    nuevo->nombre=(char *)malloc(strlen(nombreMarca) * sizeof(char));
    strcpy(nuevo->nombre,nombreMarca);
    nuevo->id=idMarca;
    nuevo->productosAutos=NULL;
    nuevo->autos=NULL;
    return nuevo;
}

 /*
  cantNodosArbol recibe un árbol y un int para indicar la cantidad de Nodos. Si el árbol es igual a NULL retorna, si no
  recorre el árbol de forma recursiva sumando 1 por cada recorrido a cantNodos.
  */

void cantNodosArbol(struct NodoProductos *abb,int *cantNodos){
    if(abb==NULL) return;
    cantNodosArbol(abb->izq,cantNodos);
    cantNodosArbol(abb->der,cantNodos);
    (*cantNodos)=(*cantNodos)+1;
}

/*
 crearArregloNodos recibe un árbol de productos, un arreglo de productos y un int i. Si el árbol es igual a NULL se retorna.
 Si no se recorre el árbol de forma recursiva referenciando al arreglo con cada nodo el árbol y aumentando el índice i en
 1.
 */

void crearArregloNodos(struct NodoProductos *abb,struct NodoProductos **arreglo,int *i){
    if(abb==NULL) return;
    crearArregloNodos(abb->izq,arreglo,i);
    crearArregloNodos(abb->der,arreglo,i);
    arreglo[*i]=abb;
    (*i)=(*i)+1;
}

/*
 arbolBalanceado recibe un arreglo de productos, un int que indica inicio y un int fin. Se crea una variable medio,
 Si inicio es mayor que fin, se retorna nuevoNodo, si no se crea el nuevo nodo y se retorna el nuevo Nodo. (el id seria medio)
 para equilibrar el árbol.
 */

struct NodoProductos *arbolBalanceado(struct NodoProductos **arreglo,int inicio,int fin){
    struct NodoProductos *nuevoNodo=NULL;
    int medio=0;
    if(inicio>fin) return nuevoNodo;
    medio=(inicio + fin)/2;
    nuevoNodo=(struct NodoProductos *) malloc(sizeof (struct NodoProductos));
    nuevoNodo->datosProducto=arreglo[medio]->datosProducto;
    nuevoNodo->izq= arbolBalanceado(arreglo,inicio,medio-1);
    nuevoNodo->der= arbolBalanceado(arreglo,medio+1,fin);
    return nuevoNodo;
}


/*
 funcion que usa el quicksort para ordenar el arreglo de los nodos de arbol de menor a mayor segun los ids de cada uno
 */
int ordenar(const void *ptrPiv,const void *ptrObj){
    struct NodoProductos **piv= (struct NodoProductos **)ptrPiv;
    struct NodoProductos **obj= (struct NodoProductos **)ptrObj;

    if((*piv)->datosProducto->idProducto < (*obj)->datosProducto->idProducto) return 0;
    return 1;
}

/*
 reordernarArbolProductos recibe la raíz del árbol de productos. si raíz izquierda y raíz derecha igual a NULL, se retorna
 la raíz, si no se llama a la función cantNodosArbol, se asigna memoria a nodosArbol, se llama a la función crearArregloNodos
 y arbolOrdenado llama a arbolBalanceado, al final retornando arbolOrdenado.
 */

struct NodoProductos *reordenarArbolProductos(struct NodoProductos *raiz){
    int cantNodos=0,indice=0;
    struct NodoProductos *arbolOrdenando=NULL,**nodosArbol;
    if(raiz->izq==NULL && raiz->der==NULL) return raiz;
    cantNodosArbol(raiz,&cantNodos);
    nodosArbol=(struct NodoProductos **) malloc(cantNodos * sizeof(struct NodoProductos *));
    crearArregloNodos(raiz,nodosArbol,&indice);
    qsort(nodosArbol,cantNodos,sizeof(struct NodoProductos *),ordenar);
    arbolOrdenando= arbolBalanceado(nodosArbol,0,cantNodos-1);
    return arbolOrdenando;
}

/*
 agregarProductoEnSucursal recibe sucursal, un producto y un Id de marca. Se recorre la lista de marcas de la sucursal
 y se pregunta si el id buscado es igual al del nodo, entonces se pregunta si el tipo de producto es igual a 2,
 entonces se agrega en marca en el árbol de productos y se ordena el árbol. Si el tipo de producto es 3, se agrega en el
 árbol de productos de la marca correspondiente. Se retorna 1.
 */

int agregarProductoEnSucursal(struct Sucursal *sucursal, struct Producto *producto, int idMarca)
{
    struct NodoProductos*arbolOrdenado=NULL;
    struct NodoMarcas *rec=sucursal->marcasAutos;
    while(rec!=NULL)
    {
        if(rec->datosMarca->id==idMarca)
        {
            if(producto->tipoProducto==2){
                agregarEnMarca(&(rec->datosMarca->autos),producto);
                arbolOrdenado= reordenarArbolProductos(rec->datosMarca->autos);
                rec->datosMarca->autos=arbolOrdenado;
            }
            else if(producto->tipoProducto==3){
                agregarEnMarca(&(rec->datosMarca->productosAutos),producto);
                arbolOrdenado= reordenarArbolProductos(rec->datosMarca->productosAutos);
                rec->datosMarca->productosAutos=arbolOrdenado;
            }
            return 1;
        }
        rec=rec->sig;
    }
    return 0;
}

/*
 CantidadStock recibe el árbol, un id de producto y un stock. Si el árbol es distinto de NULL, se recorre el árbol de forma
 recursiva, si se encuentra el producto, se suma el stock del árbol, con el que recibe.
 */

void CantidadStock(struct NodoProductos *abb, int idProducto, int *Stock)
{
    if(abb!=NULL)
    {
        CantidadStock(abb->izq,idProducto,Stock);
        CantidadStock(abb->der,idProducto,Stock);
        if(abb->datosProducto->idProducto==idProducto)
            (*Stock)=abb->datosProducto->stock;
    }
}

/*
 CantidadStockEnMarca recibe la lista de marcas y un id de Producto. Mientras marcas es distinto de NULL, se recorre la
 lista llamando buscarProductoEnMarca con el árbol de productos, si el booleano es igual a 1 se llama a la función
 CantidadStock y retorna stock. Si es distinto de 1, se llama buscarProducto en marca con el árbol de autos y vuelve a
 preguntar si Booleano es igual a 1, llamando la función CantidadStock y retorna stock. Si no se encuentra, retorna 0.
 */
int CantidadStockEnMarca(struct NodoMarcas *marcas, int idProducto)
{
    struct NodoMarcas *rec;
    int Booleano;
    int Stock=0;
    if(marcas!=NULL)
    {
        rec=marcas;
        while(rec!=NULL)
        {
            buscarProductoEnMarca(rec->datosMarca->productosAutos,idProducto,&Booleano);
            if(Booleano==1)
            {
                CantidadStock(rec->datosMarca->productosAutos,idProducto,&Stock);
                return Stock;
            }
            buscarProductoEnMarca(rec->datosMarca->autos,idProducto,&Booleano);
            if(Booleano==1)
            {
                CantidadStock(rec->datosMarca->autos, idProducto,&Stock);
                return Stock;
            }
            rec=rec->sig;
        }
    }
    return Stock;
}

/*
 CantidadStockEnSucursal recibe la lista de sucursales, id de sucursal buscada e id de producto buscado. si la lista de
 sucursales es distinto de NULL, se recorre la lista de sucursales. Si se encuentra la sucursal, se retorna la función
 CantidadStockEnMarca con la lista de marcas y el id de Producto. si no se encuentra la sucursal se retorna 0.
 */
int CantidadStockEnSucursal(struct NodoSucursales *sucursales, int idSucursal, int idProducto)
{
    struct NodoSucursales *rec;
    if(sucursales!=NULL)
    {
        rec=sucursales;
        do {

            if(rec->datosSucursal->id==idSucursal)
                return CantidadStockEnMarca(rec->datosSucursal->marcasAutos,idProducto);
            rec=rec->sig;
        }while(rec!=sucursales);
    }
    return 0;
}

/*
 ComprobarStock recibe el sistema Derco, id de sucursal buscada y un id de producto. se recorre el arreglo de regiones,
 si se encuentra la sucursal con la función buscarSucursal, se pregunta si la cantidad de stock en la sucursal es distinto
 de 0, se retorna 1.
 */

int ComprobarStock(struct SistemaDerco *derco, int idSucursal, int idProducto)
{
    int i;
    for(i=0;i<cantRegiones;i++)
    {
        if(buscarSucursal(derco->regiones[i]->sucursales,idSucursal)==1)
        {

            if (CantidadStockEnSucursal(derco->regiones[i]->sucursales, idSucursal, idProducto) != 0){

                return 1;
            }
        }

    }
    return 0;
}

/*
 disminuirStockEnAbb recibe el árbol de productos y el id del producto buscado. Si el árbol es distinto de NULL, se recorre
 el árbol de forma recursiva. Si se encuentra el producto, el stock se disminuye en 1.
 */

void disminuirStockEnAbb(struct NodoProductos **abb, int idProducto)
{
    if(*abb!=NULL)
    {
        disminuirStockEnAbb(&((*abb)->izq),idProducto);
        disminuirStockEnAbb(&((*abb)->der),idProducto);
        if((*abb)->datosProducto->idProducto==idProducto) {
            (*abb)->datosProducto->stock -= 1;
            return;
        }
    }
}

/*
 dismuirStockEnMarca recibe la lista de marcas y un id de producto buscado. Mientras la lista sea distinta de NULL, se
 recorre la lista de marcas y se busca el producto en la marca, si se encuentra, se disminuye el stock dependiendo del
 tipo de producto que sea.
 */
void disminuirStockEnMarca(struct NodoMarcas *marcas,int idProducto)
{
    struct NodoMarcas *rec;
    int Booleano=0;
    if(marcas!=NULL)
    {
        rec=marcas;
        while(rec!=NULL)
        {
            buscarProductoEnMarca(rec->datosMarca->productosAutos,idProducto,&Booleano);
            if(Booleano==1)
            {
                disminuirStockEnAbb(&(rec->datosMarca->productosAutos),idProducto);
                return;
            }
            buscarProductoEnMarca(rec->datosMarca->autos,idProducto,&Booleano);
            if(Booleano==1)
            {
                disminuirStockEnAbb(&(rec->datosMarca->autos),idProducto);
                return;
            }
            rec=rec->sig;
        }

    }
}

/*
 disminuirStockSucursal recibe la lista de sucursales, un id de sucursal, un id de producto buscando. Si las sucursales
 es distinto de NULL entonces se recorre la lista de sucursales. Si se encontró la sucursal, se llama a la función para
 disminuir el stock en marca.
 */
void disminuirStockSucursal(struct NodoSucursales *sucursales,int idSucursal, int idProducto)
{
    struct NodoSucursales *rec;
    if(sucursales!=NULL)
    {
        rec=sucursales;
        do
        {
            if(rec->datosSucursal->id==idSucursal)
                disminuirStockEnMarca(rec->datosSucursal->marcasAutos,idProducto);
            rec=rec->sig;
        }while(rec!=sucursales);
    }

}

/*
 DisminuirStock recibe el sistema Derco, un id de sucursal y un id de producto. Se recorre el arreglo de regiones buscando
 la sucursal, si se encuentra, se llama a la función disminuirStockSucursal.
 */
void DisminuirStock(struct SistemaDerco *derco, int idSucursal, int idProducto)
{
    int i;
    for(i=0;i<cantRegiones;i++)
    {
        if(buscarSucursal(derco->regiones[i]->sucursales,idSucursal)==1)
            disminuirStockSucursal(derco->regiones[i]->sucursales,idSucursal,idProducto);
    }
}

/*
 mostrarProductos recibe un árbol de productos. Si el árbol es distinto de NULL, se recorre recursivamente el árbol y se
 imprime cada producto del árbol.
 */
void mostrarProductos(struct NodoProductos *abbProdutos)
{
    if(abbProdutos != NULL)
    {
        mostrarProductos(abbProdutos->izq);
        mostrarProductos(abbProdutos->der);
        printf("Nombre: %s   Valor: $%3d   Stock: %d   ID: %d\n", abbProdutos->datosProducto->nombre, abbProdutos->datosProducto->valor,
                                abbProdutos->datosProducto->stock,abbProdutos->datosProducto->idProducto);
    }
}

/*
 mostrarProductosSucursal recibe la lista de sucursales y un id de sucursal. Si la lista de sucursales es distinta de NULL,
 entonces se recorre la lista. Si se encuentra la sucursal, se recorre la lista de marcas de la sucursal y se imprime el
 nombre de la marca y sus productos.
 */
void mostrarProductosSucursal(struct NodoSucursales *sucursales, int idSucursal)
{
    int i = 1;
    struct NodoSucursales *rec;
    struct NodoMarcas *recMarcas;
    if(sucursales != NULL)
    {
        rec = sucursales;
        do{
            if(rec->datosSucursal->id == idSucursal)
            {
                recMarcas = rec->datosSucursal->marcasAutos;

                while(recMarcas != NULL)
                {
                    printf("%d Marca: %s\n", i, recMarcas->datosMarca->nombre);
                    if(recMarcas->datosMarca->productosAutos!=NULL){
                        mostrarProductos(recMarcas->datosMarca->productosAutos);
                        i++;
                    }
                    else{
                        printf("La marca actualmente no posee productos\n");
                    }
                    recMarcas = recMarcas->sig;
                }
            }
            rec = rec->sig;
        }while(rec != sucursales);
    }
}

/*
 mostrarAutosSucursal recibe la lista de sucursales y un id de Sucursal. Si la lista de sucursales es distinta de NULL,
 se recorre la lista de sucursales. Si se encuentra la sucursal, se recorre la lista de marcas de la sucursal, imprimiendo
 la marca y sus autos.
 */
void mostrarAutosSucursal(struct NodoSucursales *sucursales, int idSucursal)
{
    int i = 1;
    struct NodoSucursales *rec;
    struct NodoMarcas *recMarcas;
    if(sucursales != NULL)
    {
        rec = sucursales;
        do{
            if(rec->datosSucursal->id == idSucursal)
            {
                recMarcas = rec->datosSucursal->marcasAutos;
                while(recMarcas != NULL)
                {
                    printf("%d Marca: %s\n", i, recMarcas->datosMarca->nombre);
                    if(recMarcas->datosMarca->autos!=NULL){
                        mostrarProductos(recMarcas->datosMarca->autos);
                        i++;
                    }
                    else{
                        printf("La marca actualmente no posee automoviles\n");
                    }
                    recMarcas = recMarcas->sig;
                }
            }
            rec = rec->sig;
        }while(rec != sucursales);
    }
}
#endif //PROYECTODERCO_FUNCIONESBASICASPRODUCTOS_H
