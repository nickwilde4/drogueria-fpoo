/*
    Proyecto: Drogueria - FPOO - Universidad del Valle
    Módulo: Reportes (GRUPO 8)

    ESTE ARCHIVO ES TUYO: reemplaza los STUB por la implementación real.
*/
#include "CReportes.h"
#include <algorithm> 
using namespace std;

CReportes::CReportes(const CInventario& inventario_) : inventario(inventario_) {
}

float CReportes::valorTotalCosto() const {
    double total = 0.0;

    for (const CMedicamento& m : inventario.getMedicamentos()) {
        total += static_cast<double>(m.getCostoDeCompra())
                 * m.getCantidadDisponible();
    }

    return static_cast<float>(total);
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

//CAMBIO
float CReportes::margenPorUnidad(int id) const{
    const vector<CMedicamento>& meds = inventario.getMedicamentos();
    for (size_t i = 0; i < meds.size(); i++) {
        if (meds[i].getId() == id) {
            return meds[i].getPrecioDeVenta() - meds[i].getCostoDeCompra();
        }
    }
    return 0;
}

vector<CMedicamento> CReportes::masRentables(int n) const{
    if (n <= 0) {
        return vector<CMedicamento>();
    }

    vector<CMedicamento> copia = inventario.getMedicamentos();   

    stable_sort(copia.begin(), copia.end(),
        [](const CMedicamento& a, const CMedicamento& b) {
            return (a.getPrecioDeVenta() - a.getCostoDeCompra()) >
                   (b.getPrecioDeVenta() - b.getCostoDeCompra());
        });

    if ((size_t)n < copia.size()) {
        copia.erase(copia.begin() + n, copia.end());   
    }
    return copia;
}
//Fin De Cambio

vector<CMedicamento> CReportes::ordenadosPorPrecio() const{
    vector<CMedicamento> copia = inventario.getMedicamentos();
    stable_sort(copia.begin(), copia.end(),
        [](const CMedicamento& a, const CMedicamento& b) {
            return a.getPrecioDeVenta() < b.getPrecioDeVenta();
        });
    return copia;
}

vector<CMedicamento> CReportes::ordenadosPorNombre() const{
      vector<CMedicamento> copia = inventario.getMedicamentos();
    stable_sort(copia.begin(), copia.end(),
        [](const CMedicamento& a, const CMedicamento& b) {
            return a.getNombre() < b.getNombre();
        });
    return copia;
}

vector<CMedicamento> CReportes::ordenadosPorCantidad() const{
    vector<CMedicamento> copia = inventario.getMedicamentos();
    stable_sort(copia.begin(), copia.end(),
        [](const CMedicamento& a, const CMedicamento& b) {
            return a.getCantidadDisponible() < b.getCantidadDisponible();
        });
    return copia;
}
