#ifndef SEMILLERO_H
#define SEMILLERO_H

#include <iostream>
#include <vector>
#include <cstring>
#include <ctime>
#include "gestores/GestorCliente.h"
#include "gestores/GestorRepartidor.h"
#include "gestores/GestorSector.h"
#include "Aleatorio.h"

namespace Semillero {
    inline void ejecutar() {
        GestorSector gs;
        GestorCliente gc;
        GestorRepartidor gr;

        if (!gs.listarActivos().empty()) {
            std::cout << "Data files found. Skipping bootstrap." << std::endl;
            return;
        }

        std::cout << "Iniciando siembra de datos aleatorios..." << std::endl;
        std::srand(std::time(nullptr));

        std::vector<int> sectorIds;
        for (int i = 0; i < 8; ++i) {
            const char* nombre = Aleatorio::SECTORES[i];
            Sector s = {0, "", 0};
            std::strncpy(s.nombre, nombre, 32);
            int res = gs.registrar(s);
            if (res == -ERROR_UNICIDAD) std::cout << "  [!] Sector duplicado: " << nombre << std::endl;
            else sectorIds.push_back(res);
        }

        int clientesCreados = 0;
        for (int i = 0; i < 10; ++i) {
            Cedula ced = { NATURAL, 10000000 + std::rand() % 20000000 };
            OpTelfMovil prefijos[] = {OpTelfMovil::MOVISTAR_1, OpTelfMovil::MOVISTAR_2, OpTelfMovil::DIGITEL_1, OpTelfMovil::DIGITEL_2, OpTelfMovil::MOVILNET_1, OpTelfMovil::MOVILNET_2};
            Telefono tel = { prefijos[std::rand() % 6], (unsigned int)(1000000 + std::rand() % 9000000) };
            
            Cliente c = {0, ced, "", tel, 0};
            std::snprintf(c.nombre, 64, "%s %s", Aleatorio::NOMBRES[std::rand() % 8], Aleatorio::APELLIDOS[std::rand() % 7]);
            int res = gc.registrar(c);
            if (res == -ERROR_UNICIDAD) std::cout << "  [!] Cliente duplicado." << std::endl;
            else clientesCreados++;
        }

        int repartidoresCreados = 0;
        for (int i = 0; i < 20; ++i) {
            Vehiculo v;
            v.tipo = (std::rand() % 2 == 0) ? TipoVehiculo::MOTO : TipoVehiculo::CARRO;
            std::strncpy(v.modelo, (v.tipo == MOTO) ? Aleatorio::MODELOS_MOTO[std::rand() % 4] : Aleatorio::MODELOS_CARRO[std::rand() % 4], 50);
            Aleatorio::generarPlaca(v.placa);

            Cedula ced = { NATURAL, 30000000 + std::rand() % 10000000 };
            Repartidor r = {0, ced, "", sectorIds[std::rand() % sectorIds.size()], v, true, 0};
            
            std::snprintf(r.nombre, 64, "%s %s", Aleatorio::NOMBRES[std::rand() % 8], Aleatorio::APELLIDOS[std::rand() % 7]);
            
            int res = gr.registrar(r);
            if (res == -ERROR_UNICIDAD) std::cout << "  [!] Repartidor duplicado." << std::endl;
            else repartidoresCreados++;
        }

        std::cout << "Siembra completada. Sectores: " << sectorIds.size() 
                  << ", Clientes: " << clientesCreados 
                  << ", Repartidores: " << repartidoresCreados << std::endl;
    }
}

#endif
