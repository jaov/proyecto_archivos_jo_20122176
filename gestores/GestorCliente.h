#ifndef GESTOR_CLIENTE_H
#define GESTOR_CLIENTE_H

#include <set>
#include "../DaoArchivo.cpp"
#include "../Modelos.h"
#include "../validadores/Validadores.h"
#include <vector>

class GestorCliente {
private:
    DaoArchivo<Cliente> dao;

    // Los clientes son unicos por cedula y telefono
    inline static std::set<Cedula> indiceCedulasUnicas;
    inline static std::set<Telefono> indiceTelefonoUnicos;
    inline static bool indicesCargados = false;

    void cargarIndices() {
        for (const auto& c : listarActivos()) {
            indiceCedulasUnicas.insert(c.cedula);
            indiceTelefonoUnicos.insert(c.telefono);
        }
    }

public:
    GestorCliente() : dao("clientes.dat") {
        if (!indicesCargados) {
            cargarIndices();
            indicesCargados = true;
        }
    }

    int registrar(Cliente& c) {
        if (!Validadores::esCedulaValida(c.cedula) || !Validadores::esTelefonoValido(c.telefono)) {
            return -ERROR_VALIDACION;
        }

        // Integridad: Cedula única en memoria
        if (indiceCedulasUnicas.count(c.cedula)) {
            return -ERROR_UNICIDAD;
        }

        const int res = dao.crear(c);
        if (res >= 0) {
            indiceCedulasUnicas.insert(c.cedula);
            indiceTelefonoUnicos.insert(c.telefono);
        }
        return res;
    }

    std::vector<Cliente> listarActivos() {
	// Borrado en es 0 para los activos
        return dao.listarPorCampo(offsetof(Cliente, borrado_en), static_cast<time_t>(0));
    }

    Cliente buscarPorId(const int id) {
        return dao.encontrarPorId(id);
    }

    int encontrarIdPorCedula(const TipoIdentificacion tipo, const long numero) {
        Cedula c = {tipo, numero};
        std::vector<Cliente> resultados = dao.listarPorCampo(offsetof(Cliente, cedula), c);
        if (resultados.empty()) return -ENTIDAD_NO_ENCONTRADA;
        return resultados[0].id;
    }

    Cliente buscarPorCedula(Cedula c) {
        std::vector<Cliente> resultados = dao.listarPorCampo(offsetof(Cliente, cedula), c);
        if (resultados.empty()) return {-1, {TipoIdentificacion::NATURAL, 0}, "No encontrado", {OpTelfMovil::MOVISTAR_1, 0}, 1};
        return resultados[0];
    }

    // (Soft-delete)
    void eliminar(const int id) {
        dao.eliminar(id);
    }
};

#endif
