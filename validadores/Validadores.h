#ifndef VALIDADORES_H
#define VALIDADORES_H

#include "../Modelos.h"

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
};

#endif
