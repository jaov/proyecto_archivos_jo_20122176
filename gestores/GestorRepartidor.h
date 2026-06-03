#ifndef GESTOR_REPARTIDOR_H
#define GESTOR_REPARTIDOR_H

#include "../DaoArchivo.cpp"
#include "../Modelos.h"
#include <vector>

class GestorRepartidor {
private:
    DaoArchivo<Repartidor> dao;

public:
    GestorRepartidor() : dao("repartidores.dat") {}

    int registrar(Repartidor& r) {
        return dao.crear(r);
    }

    void actualizarSector(int id, int nuevoIdSector) {
        dao.actualizarCampo(id, offsetof(Repartidor, id_sector), nuevoIdSector);
    }

    void actualizarEstado(int id, bool disponible) {
        dao.actualizarCampo(id, offsetof(Repartidor, disponible), disponible);
    }

    std::vector<Repartidor> listarActivos() {
        return dao.listarPorCampo(offsetof(Repartidor, borrado_en), (time_t)0);
    }

    std::vector<Repartidor> listarDisponibles() {
	std::vector<Repartidos> todosActivos = listarActivos();
	std::vector<Repartidos> disponibles;

	for (const auto& r : todosActivos) {
	    if(r.disponible == true) {
		disponibles.push_back(r);
	    }
	}
	return disponibles;
    }

    void eliminar(int id) {
        dao.eliminar(id);
    }
};

#endif
