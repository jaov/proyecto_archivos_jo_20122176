#ifndef ALEATORIO_H
#define ALEATORIO_H

#include <cstdlib>
#include <ctime>

namespace Aleatorio {
    extern const char* NOMBRES[];
    extern const char* APELLIDOS[];
    extern const char* SECTORES[];
    extern const char* MODELOS_MOTO[];
    extern const char* MODELOS_CARRO[];

    void generarPlaca(char* buffer);
}

#endif
