#include "Aleatorio.h"

namespace Aleatorio {
    const char* NOMBRES[] = {"Luis", "Marta", "Carlos", "Sofia", "Jorge", "Elena", "Pedro", "Ana"};
    const char* APELLIDOS[] = {"Mendez", "Vivas", "Colmenares", "Sanchez", "Perez", "Gomez", "Rondon"};
    const char* SECTORES[] = {
        "Barrio Obrero", "Pirineos", "Centro", "La Concordia", 
        "Pueblo Nuevo", "Paramillo", "Las Lomas", "Zulia"
    };
    const char* MODELOS_MOTO[] = {"Yamaha XT 660", "Suzuki GN 125", "Honda Bross 150", "Kawasaki KLR"};
    const char* MODELOS_CARRO[] = {"Toyota Corolla", "Chevrolet Aveo", "Ford Fiesta", "Renault Logan"};

    void generarPlaca(char* buffer) {
        const char caracteres[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < 6; ++i) {
            buffer[i] = caracteres[std::rand() % 36];
        }
        buffer[6] = '\0';
    }
}
