#ifndef INTERFAZ_MEJORADA_H
#define INTERFAZ_MEJORADA_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

class InterfazMejorada
{
public:
    // Colores ANSI para consola
    static const std::string RESET;
    static const std::string ROJO;
    static const std::string VERDE;
    static const std::string AMARILLO;
    static const std::string AZUL;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string BLANCO;
    static const std::string NEGRITA;

    // Métodos públicos
    static void limpiarPantalla();
    static void mostrarCarga(const std::string &mensaje, int duracion_ms = 1500);
    static void mostrarBannerInicio();
    static void mostrarNotificacion(const std::string &mensaje, const std::string &tipo = "info");
    static void mostrarTitulo(const std::string &titulo);
    static void pausar();
};

#endif // INTERFAZ_MEJORADA_H