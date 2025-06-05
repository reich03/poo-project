#ifndef VALIDADOR_H
#define VALIDADOR_H

#include <string>
#include <climits>
#include <cfloat>

class Validador
{
public:
    static bool validarEntero(const std::string &entrada, int &resultado, int min = INT_MIN, int max = INT_MAX);
    static bool validarDouble(const std::string &entrada, double &resultado, double min = -DBL_MAX, double max = DBL_MAX);
    static bool validarCadenaNoVacia(const std::string &entrada);
    static std::string leerEntradaSegura(const std::string &prompt, bool permitirVacio = false);
    static int leerEnteroSeguro(const std::string &prompt, int min = INT_MIN, int max = INT_MAX);
    static double leerDoubleSeguro(const std::string &prompt, double min = -DBL_MAX, double max = DBL_MAX);
};

#endif // VALIDADOR_H