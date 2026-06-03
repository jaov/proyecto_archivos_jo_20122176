#ifndef GESTOR_CLIENTE_H
#define GESTOR_CLIENTE_H

#include "../DaoArchivo.cpp"
#include "../Modelos.h"
#include "../validadores/Validadores.h"
#include <vector>

class GestorCliente {
private:
    DaoArchivo<Cliente> dao;

public:
    GestorCliente() : dao("clientes.dat") {}

    int registrar(Cliente& c) {
        if (!Validadores::esCedulaValida(c.cedula) || !Validadores::esTelefonoValido(c.telefono)) {
            return -1;
        }
        return dao.crear(c);
    }

    std::vector<Cliente> listarActivos() {
	// Borrado en es 0 para los activos
        return dao.listarPorCampo(offsetof(Cliente, borrado_en), (time_t)0);
    }

    Cliente buscarPorId(int id) {
        return dao.encontrarPorId(id);
    }

    // (Soft-delete)
    void eliminar(int id) {
        dao.eliminar(id);
    }
};

#endif
