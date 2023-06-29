//
// Created by gerar on 5/29/2023.
//


#include "stdio.h"
#include "structs.h"
#include "funcionesBasicasProductos.h"
#include "interfazesDatos.h"


#ifndef PROYECTODERCO_HELPERS_H
#define PROYECTODERCO_HELPERS_H

/*
 realizarAccion identifica el tipo de dato que se quiera aplicar una funcionalidad especifica mostrando la interfaz
 para cada tipo de dato de esta estructura
 */

void realizarAccion(struct SistemaDerco *derco,int idFuncion,int idDato,int siglaRegion){
    if(idDato == 1){
        interfazMarcaRegion(derco->regiones,siglaRegion,idFuncion);
        return;
    }
    if(idDato == 2){
        interfazProductoRegion(derco->regiones,siglaRegion,idFuncion,idDato);
        return;
    }
    if(idDato == 3){
        interfazProductoRegion(derco->regiones,siglaRegion,idFuncion,idDato);
        return;
    }
    if(idDato == 4){
        interfazSucursalRegion(derco->regiones,siglaRegion,idFuncion);
        return;
    }
    if(idDato== 5){
        interfazVentas(derco,idFuncion);
        return;
    }
}







#endif //PROYECTODERCO_HELPERS_H
