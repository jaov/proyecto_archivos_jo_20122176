#ifndef ALEATORIO_H
#define ALEATORIO_H

#include <cstdlib>
#include <ctime>

namespace Aleatorio {
    inline const char* NOMBRES[] = {"Luis", "Marta", "Carlos", "Sofia", "Jorge", "Elena", "Pedro", "Ana"};
    inline const char* APELLIDOS[] = {"Mendez", "Vivas", "Colmenares", "Sanchez", "Perez", "Gomez", "Rondon"};

    inline const char* SECTORES[] = {
        "Barrio Obrero", "Pirineos", "Centro", "La Concordia", 
        "Pueblo Nuevo", "Paramillo", "Las Lomas", "Zulia"
    };

    inline const char* MODELOS_MOTO[] = {"Yamaha XT 660", "Suzuki GN 125", "Honda Bross 150", "Kawasaki KLR"};
    inline const char* MODELOS_CARRO[] = {"Toyota Corolla", "Chevrolet Aveo", "Ford Fiesta", "Renault Logan"};


    inline void generarPlaca(char* buffer) {
        const char caracteres[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < 6; ++i) {
            buffer[i] = caracteres[std::rand() % 36];
        }
        buffer[6] = '\0'; // terminar el string
    }
}

#endif
