#ifndef GESTOR_REPARTIDOR_H
#define GESTOR_REPARTIDOR_H

#include <set>
#include "../DaoArchivo.cpp"
#include "../Modelos.h"
#include "../validadores/Validadores.h"
#include <vector>
#include "GestorSector.h"

class GestorRepartidor {
private:
    DaoArchivo<Repartidor> dao;
    static bool indicesEstanCargados;
    static std::set<Cedula> indiceCedulasUnicas;
    static std::set<std::string> indicePlacasUnicas;

    void cargarIndices() {
        for (const Repartidor r : listarActivos()) {
            indiceCedulasUnicas.insert(r.cedula);
            indicePlacasUnicas.insert(r.vehiculo.placa);
        }
    }

public:
    GestorRepartidor() : dao("repartidores.dat") {
        if (!indicesEstanCargados) {
            cargarIndices();
            indicesEstanCargados = true;
        }
    }

    Repartidor buscarPorId(const int id) {
        return dao.encontrarPorId(id);
    }

    int registrar(Repartidor& r) {
        if (!Validadores::esVehiculoValido(r.vehiculo)) {
            return -ERROR_VALIDACION;
        }

        // Integridad: Cedula unica
        if (indiceCedulasUnicas.count(r.cedula)) {
            return -ERROR_UNICIDAD;
        }

        // Integridad: Placa unica
        if (indicePlacasUnicas.count(r.vehiculo.placa)) {
            return -ERROR_UNICIDAD;
        }

        const int id =  dao.crear(r);
        if (id >= 0) {
            indiceCedulasUnicas.insert(r.cedula);
            indicePlacasUnicas.insert(r.vehiculo.placa);
        }
        return id;
    }

    void actualizarSector(const int id, const int nuevoIdSector) {
        dao.actualizarCampo(id, offsetof(Repartidor, id_sector), nuevoIdSector);
    }

    void actualizarDisponible(int id, bool disponible) {
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

    void asignarTodosAleatoriamente() {;
        GestorSector gs;

        const std::vector<Repartidor> repartidores = listarActivos();
        const std::vector<Sector> sectores = gs.listarActivos();

        if (repartidores.empty() || sectores.empty()) return;

        std::srand(static_cast<unsigned>(std::time(nullptr)));

        for (const Repartidor & repartidor : repartidores) {
            const int randomIdx = std::rand() % sectores.size();
            const int sectorId = sectores[randomIdx].id;
            actualizarSector(repartidor.id, sectorId);
        }
    }
};

#endif
