cmake_minimum_required(VERSION 3.24)
project(proyectoDerco C)

set(CMAKE_C_STANDARD 99)

add_executable(proyectoDerco main.c structs.h menus.h funcionesBasicasVentas.h funcionesBasicasMarcas.h funcionesBasicasProductos.h sucursalConMasVentas.h productoMayorRecalls.h usuarioMayorGastado.h marcasConMasVentas.h modeloConMasVentas.h promedioVentasSucursales.h funcionesBasicasSucursales.h comprarProducto.h helpers.h fusionSucursales.h interfazesDatos.h interfazProductoArbol.h interfazMarca.h interfazVentas.h funcionesBasicasRegiones.h SucursalConMasVentasAutos.h SucursalConMasVentasRepuestos.h)
