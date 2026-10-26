// Pruebas de CReportes. Responsable: GRUPO 8
#include "minitest.h"
#include "CReportes.h"

int main(){
    CInventario inv("Drogas La Especial", "07-10-2026");
    inv.adicionarMedicamento(CMedicamento(1, "Acetaminofen 60Mg", 1, 100, 1000, 2000));
    inv.adicionarMedicamento(CMedicamento(2, "Ibuprofeno 30x20 Caja", 2, 10000, 500, 2500));
    inv.adicionarMedicamento(CMedicamento(3, "Amoxicilina", 1, 20, 300, 5000));
    CReportes reportes(inv);

    SECCION("CReportes: totales");
    // costo: 100*1000 + 10000*500 + 20*300 = 5.106.000
    CHECK_NEAR(reportes.valorTotalCosto(), 5106000.0, 1.0);
    // venta: 100*2000 + 10000*2500 + 20*5000 = 25.300.000
    CHECK_NEAR(reportes.valorTotalVenta(), 25300000.0, 1.0);
    CHECK_NEAR(reportes.gananciaPotencial(), 20194000.0, 1.0);

    SECCION("CReportes: margenPorUnidad");
    CHECK_NEAR(reportes.margenPorUnidad(1), 1000.0, 0.001);
    CHECK_NEAR(reportes.margenPorUnidad(99), 0.0, 0.001);

    SECCION("CReportes: masRentables");
    {
        vector<CMedicamento> top = reportes.masRentables(2);
        CHECK_EQ((int)top.size(), 2);
        if (top.size() == 2) {
            CHECK_EQ(top[0].getNombre(), "Amoxicilina");   // margen 4700
            CHECK_EQ(top[1].getNombre(), "Ibuprofeno 30x20 Caja");   // margen 2000
        }
    }

    SECCION("CReportes: ordenamientos");
    {
        vector<CMedicamento> porPrecio = reportes.ordenadosPorPrecio();
        CHECK_EQ((int)porPrecio.size(), 3);
        if (porPrecio.size() == 3) CHECK_EQ(porPrecio[0].getNombre(), "Acetaminofen 60Mg");

        vector<CMedicamento> porNombre = reportes.ordenadosPorNombre();
        if (porNombre.size() == 3) CHECK_EQ(porNombre[0].getNombre(), "Acetaminofen 60Mg");

        vector<CMedicamento> porCantidad = reportes.ordenadosPorCantidad();
        if (porCantidad.size() == 3) CHECK_EQ(porCantidad[0].getNombre(), "Amoxicilina");
    }




    // ---------- Pruebas propias del Grupo 8 ----------

    SECCION("CReportes (Grupo 8): consistencia de totales y margenes");
    CHECK_NEAR(reportes.gananciaPotencial(),
               reportes.valorTotalVenta() - reportes.valorTotalCosto(), 1.0);
    CHECK_NEAR(reportes.margenPorUnidad(3), 4700.0, 0.001);
    CHECK_NEAR(reportes.margenPorUnidad(-5), 0.0, 0.001);

    SECCION("CReportes (Grupo 8): inventario vacio");
    {
        CInventario vacio("Vacia", "01-01-2026");
        CReportes rVacio(vacio);
        CHECK_NEAR(rVacio.valorTotalCosto(), 0.0, 0.001);
        CHECK_NEAR(rVacio.valorTotalVenta(), 0.0, 0.001);
        CHECK_NEAR(rVacio.gananciaPotencial(), 0.0, 0.001);
        CHECK_NEAR(rVacio.margenPorUnidad(1), 0.0, 0.001);
        CHECK_EQ((int)rVacio.masRentables(3).size(), 0);
        CHECK_EQ((int)rVacio.ordenadosPorPrecio().size(), 0);
        CHECK_EQ((int)rVacio.ordenadosPorNombre().size(), 0);
        CHECK_EQ((int)rVacio.ordenadosPorCantidad().size(), 0);
    }

    SECCION("CReportes (Grupo 8): masRentables con n distinto");
    {
        // n mayor que la cantidad de medicamentos: devuelve todos, de mayor a menor margen
        vector<CMedicamento> todos = reportes.masRentables(10);
        CHECK_EQ((int)todos.size(), 3);
        if (todos.size() == 2) {
            CHECK_EQ(todos[0].getNombre(), "Amoxicilina");              // 4700
            CHECK_EQ(todos[1].getNombre(), "Acetaminofen 60Mg");        // 1000
        }
        // n = 0 y n negativo: lista vacia
        CHECK_EQ((int)reportes.masRentables(0).size(), 0);
        CHECK_EQ((int)reportes.masRentables(-3).size(), 0);
    }

    SECCION("CReportes (Grupo 8): orden completo de los ordenamientos");
    {
        vector<CMedicamento> porPrecio = reportes.ordenadosPorPrecio();
        if (porPrecio.size() == 2) {
            CHECK_EQ(porPrecio[0].getNombre(), "Acetaminofen 60Mg");       // 2000
            CHECK_EQ(porPrecio[1].getNombre(), "Ibuprofeno 30x20 Caja");   // 2500
        }
        vector<CMedicamento> porNombre = reportes.ordenadosPorNombre();
        if (porNombre.size() == 2) {
            CHECK_EQ(porNombre[0].getNombre(), "Acetaminofen 60Mg");    // N/A
            CHECK_EQ(porNombre[1].getNombre(), "Amoxicilina");          // N/A
        }
        vector<CMedicamento> porCantidad = reportes.ordenadosPorCantidad();
        if (porCantidad.size() == 2) {
            CHECK_EQ(porCantidad[0].getNombre(), "Amoxicilina");           // 20
            CHECK_EQ(porCantidad[1].getNombre(), "Acetaminofen 60Mg");     // 100
        }
    }

    SECCION("CReportes (Grupo 8): ordenar NO cambia el inventario original");
    {
        reportes.ordenadosPorPrecio();
        reportes.ordenadosPorNombre();
        reportes.ordenadosPorCantidad();
        reportes.masRentables(2);
        const vector<CMedicamento>& original = inv.getMedicamentos();
        CHECK_EQ((int)original.size(), 3);
        if (original.size() == 2) {
            CHECK_EQ(original[0].getNombre(), "Acetaminofen 60Mg");
            CHECK_EQ(original[1].getNombre(), "Amoxicilina");
        }
    }

    SECCION("CReportes (Grupo 8): empates conservan el orden de insercion");
    {
        CInventario empates("Empates", "01-01-2026");
        empates.adicionarMedicamento(CMedicamento(10, "Zeta", 1, 5, 100, 1000));
        empates.adicionarMedicamento(CMedicamento(11, "Alfa", 1, 5, 100, 1000));
        CReportes rEmpates(empates);

        vector<CMedicamento> porPrecio = rEmpates.ordenadosPorPrecio();
        vector<CMedicamento> porCantidad = rEmpates.ordenadosPorCantidad();
        vector<CMedicamento> top = rEmpates.masRentables(2);
        CHECK_EQ((int)porPrecio.size(), 2);
        CHECK_EQ((int)porCantidad.size(), 2);
        CHECK_EQ((int)top.size(), 2);
        if (porPrecio.size() == 2)   CHECK_EQ(porPrecio[0].getNombre(), "Zeta");
        if (porCantidad.size() == 2) CHECK_EQ(porCantidad[0].getNombre(), "Zeta");
        if (top.size() == 2)         CHECK_EQ(top[0].getNombre(), "Zeta");
    }

    return RESUMEN();
}
