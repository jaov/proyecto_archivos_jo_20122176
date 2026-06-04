#ifndef GESTOR_ENTREGA_H
#define GESTOR_ENTREGA_H

#include "../DaoArchivo.cpp"
#include "../Modelos.h"
#include "GestorRepartidor.h"
#include <vector>

class GestorEntrega {
private:
    DaoArchivo<Entrega> dao;

public:
    GestorEntrega() : dao("entregas.dat") {}

    int registrar(Entrega& e) {
        return dao.crear(e);
    }

    Entrega buscarPorId(const int id) {
        return dao.encontrarPorId(id);
    }

    std::vector<Entrega> listarActivas() {
        return dao.listarPorCampo(offsetof(Entrega, borrado_en), static_cast<time_t>(0));
    }

    void eliminar(const int id) {
        dao.eliminar(id);
    }

    int solicitarEnvio(Entrega& e) {
        if (e.estatus != EstatusEntrega::REPARTIDOR_PENDIENTE) {
            return -1;
        }
        return dao.crear(e);

    }

    int asignarRepartidor(const int id_entrega, const int id_repartidor) {
	    GestorRepartidor gRep = GestorRepartidor();
        Entrega entrega = buscarPorId(id_entrega);
        if (!gRep.estaDisponible(id_repartidor)) return 1;
        if (entrega.estatus != EstatusEntrega::REPARTIDOR_PENDIENTE) { return 2;}
        dao.actualizarCampo(id_entrega, offsetof(Entrega, id_repartidor), id_repartidor);
        dao.actualizarCampo(id_entrega, offsetof(Entrega, estatus), EstatusEntrega::REPARTIDOR_ASIGNADO);
	    gRep.actualizarDisponible(id_repartidor, false);
    
        return 0;
    }

    int obtIdEntregaActiva(const int id_repartidor) {
        std::vector<Entrega> entregasRepartidor = dao.listarPorCampo(offsetof(Entrega, id_repartidor), id_repartidor);
        for (Entrega e : entregasRepartidor) {
            if (e.estatus == EstatusEntrega::REPARTIDOR_ASIGNADO) {
                return e.id;
            }
        }

        return -1;
    }

    void marcarEntregada(const int id_entrega) {
        dao.actualizarCampo(id_entrega, offsetof(Entrega, estatus), EstatusEntrega::ENTREGADA);
    }

    void cancelar(const int id_entrega) {
        dao.actualizarCampo(id_entrega, offsetof(Entrega, estatus), EstatusEntrega::CANCELADO);
    }

    void marcarEntregadaConRepartidor(const int id_repartidor) {
        marcarEntregada(obtIdEntregaActiva(id_repartidor));
    }

    void cancelarConRepartidor(const int id_repartidor) {
        cancelar(obtIdEntregaActiva(id_repartidor));
    }


};

#endif
