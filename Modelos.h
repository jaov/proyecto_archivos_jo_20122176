// Pre procesador
#ifndef MODELOS_H
#define MODELOS_H

#include <ctime> // para time_t
#include "Constantes.h"

struct Telefono{
    OpTelfMovil prefijo;
    unsigned int numero;
};

struct Vehiculo{
    TipoVehiculo tipo;
    char modelo[50];
    char placa[7];
};

struct Cedula{
    TipoIdentificacion tipIdent;
    long numero;
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
    bool finalizada;
    time_t borrado_en;
};

#endif
