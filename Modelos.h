// Pre procesador
#ifndef MODELOS_H
#define MODELOS_H

#include <ctime> // para time_t
#include "Constantes.h"

struct Telefono{
    OpTelfMovil prefijo;
    unsigned int numero;

    bool operator<(const Telefono& otro) const {
        if (prefijo != otro.prefijo) return prefijo < otro.prefijo;
        return numero < otro.numero;
    }
};

struct Vehiculo{
    TipoVehiculo tipo;
    char modelo[50];
    char placa[7];
};

struct Cedula{
    TipoIdentificacion tipIdent;
    long numero;

    // para usarlo en sets
    bool operator<(const Cedula& otro) const {
        if (tipIdent != otro.tipIdent) return tipIdent < otro.tipIdent;
        return numero < otro.numero;
    }

    bool operator==(const Cedula& otro) const {
        return tipIdent == otro.tipIdent && numero == otro.numero;
    }
};


struct Cliente {
    int id;
    Cedula cedula;
    char nombre[64];
    Telefono telefono;
    time_t borrado_en;
};

struct Repartidor {
    int id;
    Cedula cedula;
    char nombre[64];
    char usuario[32];
    char contrasena[32];
    int id_sector; // llave foranea
    Vehiculo vehiculo;
    bool disponible;
    time_t borrado_en;
};

struct Sector {
    int id;
    char nombre[32];
    time_t borrado_en;
};

struct Entrega {
    int id;
    Cedula cedula_cliente;
    int id_sector_origen;
    int id_sector_destino;
    int id_repartidor; // -1 pendiente por asignar.
    EstatusEntrega estatus;
    time_t borrado_en;
};

#endif
