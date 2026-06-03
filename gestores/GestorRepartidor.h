#ifndef GESTOR_REPARTIDOR_H
#define GESTOR_REPARTIDOR_H

#include "../DaoArchivo.cpp"
#include "../Modelos.h"
#include "../validadores/Validadores.h"
#include <vector>

class GestorRepartidor {
private:
    DaoArchivo<Repartidor> dao;

public:
    GestorRepartidor() : dao("repartidores.dat") {}

    Repartidor buscarPorId(int id) {
        return dao.encontrarPorId(id);
    }

    int registrar(Repartidor& r) {
        if (!Validadores::esVehiculoValido(r.vehiculo)) {
            return -1;
        }
        return dao.crear(r);
    }

    void actualizarSector(int id, int nuevoIdSector) {
        dao.actualizarCampo(id, offsetof(Repartidor, id_sector), nuevoIdSector);
    }

    void actualizarEstado(int id, bool disponible) {
        dao.actualizarCampo(id, offsetof(Repartidor, disponible), disponible);
    }

    std::vector<Repartidor> listarActivos() {
        return dao.listarPorCampo(offsetof(Repartidor, borrado_en), static_cast<time_t>(0));
    }

    std::vector<Repartidor> listarDisponibles() {
	std::vector<Repartidor> todosActivos = listarActivos();
	std::vector<Repartidor> disponibles;

	for (const auto& r : todosActivos) {
	    if(r.disponible == true) {
		disponibles.push_back(r);
	    }
	}
	return disponibles;
    }

    std::vector<Repartidor> listarDisponiblesEnZona(int id_sector) {
        std::vector<Repartidor> resultados;
        std::vector<Repartidor> repartidoresEnZona = dao.listarPorCampo(offsetof(Repartidor,id_sector), id_sector);

        for (const auto& r : repartidoresEnZona) {
            if(r.disponible == true && r.borrado_en == static_cast<time_t>(0)) {
                resultados.push_back(r);
            }
        }
        return resultados;
    }

    bool estaDisponible(const int id_repartidor) {
        Repartidor encontrado =  dao.encontrarPorId(id_repartidor);
        return encontrado.disponible && encontrado.borrado_en==static_cast<time_t>(0);
    }

    void eliminar(int id) {
        dao.eliminar(id);
    }
};

#endif
