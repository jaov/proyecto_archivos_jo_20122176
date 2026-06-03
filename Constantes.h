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

#endif
