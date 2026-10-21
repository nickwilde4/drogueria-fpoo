/*
    Proyecto: Drogueria - FPOO - Universidad del Valle
    Módulo: Reportes (GRUPO 8)

    ESTE ARCHIVO ES TUYO: reemplaza los STUB por la implementación real.
*/
#include "CReportes.h"
using namespace std;

CReportes::CReportes(const CInventario& inventario_) : inventario(inventario_) {
}

float CReportes::valorTotalCosto() const{
    //STUB (Grupo 8): implementar
    return 0;
}

float CReportes::valorTotalVenta() const{
        double total = 0.0;
    for (const CMedicamento& m : inventario.getMedicamentos()) {
        total += static_cast<double>(m.getPrecioDeVenta()) * m.getCantidadDisponible();
    }
    return static_cast<float>(total);
}

float CReportes::gananciaPotencial() const{
    double total = 0.0;
    for (const CMedicamento& m : inventario.getMedicamentos()) {
        double margen = static_cast<double>(m.getPrecioDeVenta()) - m.getCostoDeCompra();
        total += margen * m.getCantidadDisponible();
    }
    return static_cast<float>(total);
}

float CReportes::margenPorUnidad(int id) const{
    for (const CMedicamento& m : inventario.getMedicamentos()) {
        if (m.getId() == id) {
            return m.getPrecioDeVenta() - m.getCostoDeCompra();
        }
    }
    return 0;
}

vector<CMedicamento> CReportes::masRentables(int n) const{
    // STUB (Grupo 8): implementar
    return vector<CMedicamento>();
}

vector<CMedicamento> CReportes::ordenadosPorPrecio() const{
    // STUB (Grupo 8): implementar
    return vector<CMedicamento>();
}

vector<CMedicamento> CReportes::ordenadosPorNombre() const{
    // STUB (Grupo 8): implementar
    return vector<CMedicamento>();
}

vector<CMedicamento> CReportes::ordenadosPorCantidad() const{
    // STUB (Grupo 8): implementar
    return vector<CMedicamento>();
}
