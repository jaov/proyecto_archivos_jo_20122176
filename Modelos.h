// Pre procesador
#ifndef MODELOS_H
#define MODELOS_H

#include <ctime> // para time_t

struct Repartidor {
    int id;
    char usuario[32];
    char contrasena[32];
    int id_sector; // llave foranea
    bool disponible;
    time_t borrado_en;
};

struct Sector {
    int id;
    char nombre[32];
    time_t borrado_en;
}
#endif
