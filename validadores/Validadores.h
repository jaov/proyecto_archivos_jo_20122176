#ifndef VALIDADORES_H
#define VALIDADORES_H

#include "../Modelos.h"
#include "string"
#include "cstring"

class Validadores {
public:
    static bool esTelefonoValido(const Telefono& t) {
        bool prefijoValido = (t.prefijo == OpTelfMovil::MOVISTAR_1 || 
                             t.prefijo == OpTelfMovil::MOVISTAR_2 || 
                             t.prefijo == OpTelfMovil::DIGITEL_1 || 
                             t.prefijo == OpTelfMovil::DIGITEL_2 || 
                             t.prefijo == OpTelfMovil::MOVILNET_1 || 
                             t.prefijo == OpTelfMovil::MOVILNET_2);
        
        bool numeroValido = (t.numero <= 9999999);
        return prefijoValido && numeroValido;
    }

    static bool esCedulaValida(const Cedula& c) {
        return c.numero > 0; //Varia demasiado entre tipos;
    }

    static bool esPlacaValida(const char* placa) {
        if (std::strlen(placa) != 6) return false;
        
        for (int i = 0; i < 6; ++i) {
            // placa solo puede ser alfanumerica
            if (!std::isalnum(static_cast<unsigned char>(placa[i]))) return false;
        }
        return true;
    }

    static bool esVehiculoValido(const Vehiculo& v) {
        return esPlacaValida(v.placa) && (v.tipo == TipoVehiculo::CARRO || v.tipo == TipoVehiculo::MOTO);
    }
};

#endif
