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

enum Resultado : int {
    EXITO = 0,
    ENTIDAD_NO_ENCONTRADA = 1,
    ERROR_VALIDACION = 2,
    REPARTIDOR_OCUPADO = 3,
    ESTADO_ILEGAL = 4,
    ERROR_IO = 10
};

enum TipoVehiculo {
    MOTO,
    CARRO
};

#endif
