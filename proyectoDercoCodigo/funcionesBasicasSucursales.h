//
// Created by gerar on 5/28/2023.
//

#include "structs.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define cantRegiones 16

#ifndef PROYECTODERCO_FUNCIONESBASICASSUCURSALES_H
#define PROYECTODERCO_FUNCIONESBASICASSUCURSALES_H

/*
    buscarSucursal recibe la lista de sucursales y el ID de la sucursal buscada. Se recorre la lista de sucursales y se
    hace un if preguntando si el ID de la sucursal recorrida es igual al de la buscada, si se encuentra, se retorna 1.
 */
int buscarSucursal(struct NodoSucursales *sucursales,int idSucursalBuscada){
    struct NodoSucursales *rec;
    if(sucursales!=NULL){
        rec=sucursales;
        do {
            if(rec->datosSucursal->id==idSucursalBuscada) return 1;
            rec=rec->sig;
        }while(rec!=sucursales);
    }
    return 0;
}

/*
 buscarSucursalYRetornar realiza lo mismo que la función anterior solo que retorna el struct de la sucursal buscada y si
 no se encuentra, se retorna NULL.
 */

struct Sucursal*buscarSucursalYRetornar(struct NodoSucursales *sucursales,int idSucursalBuscada){
    struct NodoSucursales *rec;
    if(sucursales!=NULL){
        rec=sucursales;
        do {
            if(rec->datosSucursal->id==idSucursalBuscada) return rec->datosSucursal;
            rec=rec->sig;
        }while(rec!=sucursales);
    }
    return NULL;
}

/*
agregarSucursal recibe la lista de sucursales y el struct de la nueva sucursal que se va a agregar. Primero se pregunta
 si el primer elemento de la lista es NULL, si es nulo, entonces se agrega la nueva sucursal en la primera posicion de la
 lista. Si el primer elemento existe, entonces se recorre la lista hasta el último elemento para poder agregar la nueva
 sucursal.
 */

int agregarSucursal(struct NodoSucursales**head,struct Sucursal *nuevo){
    struct NodoSucursales *nuevoNodo=NULL;
    if(*head==NULL)
    {
        (*head)=(struct NodoSucursales *)malloc(sizeof(struct NodoSucursales));
        (*head)->sig=(*head)->ant=(*head);
        (*head)->datosSucursal=nuevo;
        return 1;
    }else{
        if(buscarSucursal(*head,nuevo->id)==0){
            nuevoNodo=(struct NodoSucursales *)malloc(sizeof(struct NodoSucursales));
            nuevoNodo->ant=(*head)->ant;
            nuevoNodo->sig=(*head);
            (*head)->ant=(*head)->ant->sig=nuevoNodo;
            nuevoNodo->datosSucursal=nuevo;
            return 1;
        }
        return 0;
    }
}

/*
 actualizarSucursal recibe la lista de sucursales y la sucursal que vamos a actualizar. se recorre la lista de sucursales
 y se comparan los ID de la sucursal que vamos a actualizar con los de la lista, si se encuentra, se reemplazan los datos
 y se retorna 1.
 */
int actualizarSucursal(struct NodoSucursales **head,struct Sucursal *nuevosDatos){
    struct NodoSucursales *rec;
    if(*head!=NULL){
        rec=*head;
        do {
            if(rec->datosSucursal->id==nuevosDatos->id){
                rec->datosSucursal=nuevosDatos;
                return 1;
            }
            rec=rec->sig;
        }while(rec!=*head);
    }
    return 0;
}

/*
 eliminarSucursal recibe la lista de sucursales y el ID de la sucursal que vamos a eliminar. Se valida que el head es
 distinto de NULL y se recorre la lista de sucursales, donde comparamos los ID por cada iteración realizada. Si se
 encuentra la sucursal preguntamos si el elemento a eliminar se encuentra en la ultima posicion, se hace NULL, si no se
 pregunta si el elemento a eliminar es el primer elemento, se hace head al elemento siguiente. Si no se elimina un elemento
 que se encuentra entre medio de la lista.
 */

int eliminarSucursal(struct NodoSucursales **head,int idSucursalEliminar){
    struct NodoSucursales *rec;
    if(*head!=NULL){
        rec=*head;
        do {
            if(rec->datosSucursal->id==idSucursalEliminar){
                if(rec->sig==(*head) && rec->ant==(*head) && rec==*head){
                    (*head)=NULL;
                    return 1;
                }else{
                    if(rec==*head){
                        (*head)=(*head)->sig;
                        (*head)->ant=rec->ant;
                        rec->ant->sig=(*head);
                    }else{
                        rec->ant->sig=rec->sig;
                        rec->sig->ant=rec->ant;
                    }
                    rec=NULL;
                    return 1;
                }
            }
            rec=rec->sig;
        }while(rec!=*head);
    }
    return 0;
}

/*
    mostrarSucursalesEnumerada recibira una lista de sucursales y las imprimira en orden, mostrando el nombre de esta
    la comuna donde se encuentra y su ID.

 */
void mostrarSucursalesEnumeradas(struct NodoSucursales *sucursales){
    struct NodoSucursales *rec;
    int i=1;
    if(sucursales!=NULL){
        rec=sucursales;
        do {
            printf("-%d. Nombre: %s - Comuna: %s -ID: %d\n",i,rec->datosSucursal->nombre,rec->datosSucursal->comuna,rec->datosSucursal->id);
            rec=rec->sig;
            i++;
        }while(rec!=sucursales);
    }
}

/*
    BuscarPorNombre, recibe una lista de sucursales y un string relacionado al nombre de esta
    recorriendo la lista y con el uso de la función strcmp se retornara 1 o 0 dependiendo de si
    la condición se cumple o no.

 */
int BuscarPorNombre(struct NodoSucursales *sucursales,char *Nombre)
{
    struct NodoSucursales *rec;
    if(sucursales!=NULL)
    {
        rec=sucursales;
        do
        {
            if(strcmp(rec->datosSucursal->nombre,Nombre)==0)
                return 1;
            rec=rec->sig;
        }while(rec!=sucursales);
        return 0;
    }
   return 0;
}
/*
    BuscarPorNombre, recibe una lista de sucursales y un string relacionado al nombre de la comuna donde se encuentra
    recorriendo la lista y con el uso de la función strcmp se retornanara 1 o 0 dependiendo de si
    la condición se cumple o no.

 */
int BuscarPorComuna(struct NodoSucursales *sucursales,char *Comuna)
{
    struct NodoSucursales *rec;
    if(sucursales!=NULL)
    {
        rec=sucursales;
        do
        {
            if(strcmp(rec->datosSucursal->comuna,Comuna)==0)
                return 1;
            rec=rec->sig;
        }while(rec!=sucursales);
        return 0;
    }
    return 0;
}
/*
    crearSucursal y Agregar Sucursal, recibe una lista de sucursales y un string relacionado al nombre de la comuna
    donde se encuentra recorriendo la lista y con el uso de la funcion strcmp se retornanara 1 o 0 dependiendo de si
    la condición se cumple o no.

 */
void crearSucursalYAgregarSucursal(struct Regiones **regiones,int SiglaRegion) {
    srand(time(NULL));

    char nombreSucursal[40], Comuna[20];
    int respuesta = 2;
    struct Sucursal *nueva = (struct Sucursal *) malloc(sizeof(struct Sucursal));

    printf("siglaregion= %d\n", SiglaRegion);
    printf("Ingrese el nombre de la sucursal que quiere crear\n");
    getchar();
    scanf("%[^\n]s", nombreSucursal);
    getchar();

    while (BuscarPorNombre(regiones[SiglaRegion - 1]->sucursales, nombreSucursal) == 1) {
        printf("El nombre %s ya existe en la region, intentelo nuevamente\n", nombreSucursal);
        printf("Ingrese el nombre de la sucursal que quiere crear\n");
        scanf("%[^\n]s ", nombreSucursal);
        getchar();
    }

    nueva->nombre = (char *) malloc(sizeof(char) * strlen(nombreSucursal) + 1);
    strcpy(nueva->nombre, nombreSucursal);

    printf("Ingrese el nombre de la comuna donde quiera agregar la nueva sucursal\n");
    scanf("%[^\n]s ", Comuna);
    getchar();
    while (1) {
        if (BuscarPorComuna(regiones[SiglaRegion - 1]->sucursales, Comuna) == 0)
            break;

        printf("Ya existe una Sucursal en la comuna %s, Segur@ que quiere agregarla?\n", Comuna);
        printf("(1 para agregar | 0 para ingresar otra comuna)\n");
        printf("Ingrese su opcion = ");
        scanf("%d", &respuesta);

        if (respuesta == 1)
            break;
        if (respuesta == 0) {
            printf("Ingrese el nombre de la comuna donde quiera agregar la nueva sucursal\n");
            scanf("%s[^\n] ", Comuna);
            continue;
        } else
            printf("Ingrese una respuesta valida\n");
    }

    nueva->comuna = (char *) malloc(sizeof(char) * strlen(Comuna));
    strcpy(nueva->comuna, Comuna);

    nueva->id = rand();
    nueva->marcasAutos = NULL;

    agregarSucursal(&(regiones[SiglaRegion - 1]->sucursales), nueva);


}
void contarEnArbol(struct NodoProductos *abb, int *suma){

    if(abb){
        contarEnArbol(abb->izq,suma);
        contarEnArbol(abb->der,suma);
        if(abb->datosProducto)
            (*suma)+=abb->datosProducto->stock;
    }
}

int contarStockMarca(struct NodoMarcas *marca){
    int cont = 0;
    if (marca->datosMarca->autos)
        contarEnArbol(marca->datosMarca->autos, &cont);
    if (marca->datosMarca->productosAutos)
        contarEnArbol(marca->datosMarca->productosAutos, &cont);

    return cont;
}

void sucursalConMayorYMenorStock(struct SistemaDerco *derco, struct Sucursal **menor, struct Sucursal **mayor){
    int i = 0, cantStockSucursal, menorStock = 0,mayorStock = 0,j = 0;
    struct NodoSucursales *recSucursales;
    struct NodoMarcas *recMarcas;

    if(!derco->regiones){
        printf("Error, no existen regiones");
        return;
    }
    for (i = 0; i < cantRegiones; i++){
        if(derco->regiones[i]->sucursales){
            recSucursales = derco->regiones[i]->sucursales;
            do {
                cantStockSucursal = 0;
                if (recSucursales->datosSucursal->marcasAutos){
                    recMarcas = recSucursales->datosSucursal->marcasAutos;
                    while(recMarcas){
                        if(recMarcas->datosMarca->autos != NULL || recMarcas->datosMarca->productosAutos != NULL)
                            cantStockSucursal+= contarStockMarca(recMarcas);
                        if (j == 0){
                            (*menor) = recSucursales->datosSucursal;
                            menorStock = cantStockSucursal;
                            (*mayor) = recSucursales->datosSucursal;
                            mayorStock = cantStockSucursal;
                            j++;
                        }
                        else if(cantStockSucursal < menorStock){
                            (*menor) = recSucursales->datosSucursal;
                            menorStock = cantStockSucursal;
                        }
                        else if(cantStockSucursal > mayorStock){
                            (*mayor) = recSucursales->datosSucursal;
                            mayorStock = cantStockSucursal;
                        }
                        recMarcas = recMarcas->sig;
                    }
                }
                recSucursales = recSucursales->sig;
            }while(recSucursales!= derco->regiones[i]->sucursales);
        }
    }
}

void mostrarMayorYMenorStock(struct SistemaDerco *derco){
    struct Sucursal *menor = NULL, *mayor = NULL;
    if (derco){
        sucursalConMayorYMenorStock(derco, &menor, &mayor);
        if (menor == NULL || mayor == NULL){
            printf("No existen sucursales\n");
            return;
        }
        printf("Menor stock: Sucursal %s - ID: %d\n",menor->nombre, menor->id);
        printf("Mayor stock: Sucursal %s - ID: %d\n",mayor->nombre, mayor->id);
    }
}


#endif //PROYECTODERCO_FUNCIONESBASICASSUCURSALES_H
