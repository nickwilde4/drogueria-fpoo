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

float CReportes::valorTotalCosto() const{
    // STUB (Grupo 8): implementar
    return 0;
}

float CReportes::valorTotalVenta() const{
    // STUB (Grupo 8): implementar
    return 0;
}

float CReportes::gananciaPotencial() const{
    // STUB (Grupo 8): implementar
    return 0;
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
