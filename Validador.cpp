#include "Validador.h"
#include "InterfazMejorada.h"
#include <iostream>
using namespace std;

bool Validador::validarEntero(const std::string &entrada, int &resultado, int min, int max)
{
    try
    {
        size_t pos;
        resultado = std::stoi(entrada, &pos);

        if (pos != entrada.length())
            return false;
        return resultado >= min && resultado <= max;
    }
    catch (...)
    {
        return false;
    }
}

bool Validador::validarDouble(const std::string &entrada, double &resultado, double min, double max)
{
    try
    {
        size_t pos;
        resultado = std::stod(entrada, &pos);

        if (pos != entrada.length())
            return false;
        return resultado >= min && resultado <= max;
    }
    catch (...)
    {
        return false;
    }
}

bool Validador::validarCadenaNoVacia(const std::string &entrada)
{
    return !entrada.empty() && entrada.find_first_not_of(" \t\n\r") != std::string::npos;
}

std::string Validador::leerEntradaSegura(const std::string &prompt, bool permitirVacio)
{
    std::string entrada;
    do
    {
        cout << InterfazMejorada::CYAN << prompt << InterfazMejorada::RESET;
        std::getline(std::cin, entrada);

        if (permitirVacio || validarCadenaNoVacia(entrada))
        {
            break;
        }

        InterfazMejorada::mostrarNotificacion("La entrada no puede estar vacia. Intente nuevamente.", "error");
    } while (true);

    return entrada;
}

int Validador::leerEnteroSeguro(const std::string &prompt, int min, int max)
{
    std::string entrada;
    int resultado;

    do
    {
        entrada = leerEntradaSegura(prompt);

        if (validarEntero(entrada, resultado, min, max))
        {
            break;
        }

        InterfazMejorada::mostrarNotificacion(
            "Entrada invalida. Ingrese un numero entre " +
                std::to_string(min) + " y " + std::to_string(max),
            "error");
    } while (true);

    return resultado;
}

double Validador::leerDoubleSeguro(const std::string &prompt, double min, double max)
{
    std::string entrada;
    double resultado;

    do
    {
        entrada = leerEntradaSegura(prompt);

        if (validarDouble(entrada, resultado, min, max))
        {
            break;
        }

        InterfazMejorada::mostrarNotificacion(
            "Entrada invalida. Ingrese un numero valido mayor a 0.", "error");
    } while (true);

    return resultado;
}