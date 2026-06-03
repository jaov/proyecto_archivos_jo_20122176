#ifndef GESTOR_SECTOR_H
#define GESTOR_SECTOR_H

#include "../DaoArchivo.cpp"
#include "../Modelos.h"
#include <vector>

class GestorSector {
private:
    DaoArchivo<Sector> dao;

public:
    GestorSector() : dao("sectores.dat") {}

    int registrar(Sector& s) {
        return dao.crear(s);
    }

    Sector buscarPorId(int id) {
        return dao.encontrarPorId(id);
    }

    std::vector<Sector> listarActivos() {
        return dao.listarPorCampo(offsetof(Sector, borrado_en), static_cast<time_t>(0));
    }

    void eliminar(int id) {
        dao.eliminar(id);
    }
};

#endif
