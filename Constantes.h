#ifndef CONSTANTES_H
#define CONSTANTES_H

enum class OpTelfMovil: unsigned short {
    MOVISTAR_1 = 414,
    MOVISTAR_2 = 424,
    DIGITEL_1 = 412,
    DIGITEL_2 = 422,
    MOVILNET_1 = 416,
    MOVILNET_2 = 426
};

enum class TipoIdentificacion: char {
    NATURAL = 'V',
    EXTRANJERO = 'E',
    GUBERNAMENTAL = 'G',
    COMUNA = 'C',
    JURIDICA = 'J'
};

enum class EstatusEntrega : int {
    REPARTIDOR_PENDIENTE = 0,
    REPARTIDOR_ASIGNADO = 1,
    ENTREGADA = 2,
    CANCELADO = 3
};

enum TipoVehiculo {
    MOTO,
    CARRO
};

#endif
