#ifndef GESTOR_SECTOR_H
#define GESTOR_SECTOR_H

#include "../DaoArchivo.cpp"
#include "../Modelos.h"
#include <vector>
#include <set>

class GestorSector {
private:
    DaoArchivo<Sector> dao;
    inline static std::set<std::string> indiceNombresUnicos;
    inline static bool estaCargado = false;

    void cargarIndiceNombresUnicos() {
        if (!estaCargado) {
            for (const Sector& sector : listarActivos()) {
                indiceNombresUnicos.insert(sector.nombre);
            }
        }
    }

public:
    GestorSector() : dao("sectores.dat") {}

    int registrar(Sector& s) {
        if (indiceNombresUnicos.count(s.nombre)) { return -ERROR_UNICIDAD;}
        const int id =  dao.crear(s);
        if (id >= 0) { indiceNombresUnicos.insert(s.nombre);}
        return id;
    }

    Sector buscarPorId(int id) {
        return dao.encontrarPorId(id);
    }

    int encontrarIdPorNombre(const char* nombre) {
        std::vector<Sector> resultados = dao.listarPorString(offsetof(Sector, nombre), nombre, 32);
        if (resultados.empty()) return -ENTIDAD_NO_ENCONTRADA;
        return resultados[0].id;
    }

    std::vector<Sector> listarActivos() {
        return dao.listarPorCampo(offsetof(Sector, borrado_en), static_cast<time_t>(0));
    }

    void eliminar(int id) {
        dao.eliminar(id);
    }
};

#endif
