#include <stdio.h>
#define cantRegiones 16
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "menus.h"
#include "funcionesBasicasVentas.h"
#include "funcionesBasicasMarcas.h"
#include "funcionesBasicasProductos.h"
#include "sucursalConMasVentas.h"
#include "productoMayorRecalls.h"
#include "usuarioMayorGastado.h"
#include "marcasConMasVentas.h"
#include "funcionesBasicasRegiones.h"

/*
 Integrantes:
 -Benjamin Palamara 21.336.847-8
 -Sebastian Beltran Pereira 20.484.602-2
 -Felipe Engels 21.315.306-4
 */


int main(){
    struct SistemaDerco *derco=NULL;
    derco=(struct SistemaDerco *)malloc(sizeof (struct SistemaDerco));
    derco->regiones=crearRegiones();
    derco->ventas=NULL;
    SwitchMenuPrincipal(derco);
}




