#include "InterfazMejorada.h"

// Definición de constantes de color
const std::string InterfazMejorada::RESET = "\033[0m";
const std::string InterfazMejorada::ROJO = "\033[31m";
const std::string InterfazMejorada::VERDE = "\033[32m";
const std::string InterfazMejorada::AMARILLO = "\033[33m";
const std::string InterfazMejorada::AZUL = "\033[34m";
const std::string InterfazMejorada::MAGENTA = "\033[35m";
const std::string InterfazMejorada::CYAN = "\033[36m";
const std::string InterfazMejorada::BLANCO = "\033[37m";
const std::string InterfazMejorada::NEGRITA = "\033[1m";

// Limpiar pantalla multiplataforma
void InterfazMejorada::limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Animación de carga (SIN ICONOS)
void InterfazMejorada::mostrarCarga(const std::string &mensaje, int duracion_ms)
{
    std::cout << AMARILLO << mensaje;
    char animacion[] = {'|', '/', '-', '\\'};
    int pasos = duracion_ms / 100;

    for (int i = 0; i < pasos; ++i)
    {
        std::cout << " " << CYAN << animacion[i % 4] << "\r" << AMARILLO << mensaje;
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << " " << VERDE << "[OK]" << RESET << std::endl;
}

// Banner animado (SIN ICONOS)
void InterfazMejorada::mostrarBannerInicio()
{
    limpiarPantalla();
    std::cout << CYAN << NEGRITA;
    std::string lineas[] = {
        "================================================================",
        "||                                                            ||",
        "||       SISTEMA DE GESTION - PRODUCTOS FRESCOS              ||",
        "||                                                            ||",
        "||         Frutas * Verduras * Carnes * Individuales         ||",
        "||                                                            ||",
        "================================================================"};

    for (const auto &linea : lineas)
    {
        std::cout << linea << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    std::cout << RESET << std::endl;
}

// Mostrar notificación con estilo (SIN ICONOS)
void InterfazMejorada::mostrarNotificacion(const std::string &mensaje, const std::string &tipo)
{
    std::string color = AZUL;
    std::string prefijo = "[INFO]";

    if (tipo == "exito")
    {
        color = VERDE;
        prefijo = "[EXITO]";
    }
    else if (tipo == "error")
    {
        color = ROJO;
        prefijo = "[ERROR]";
    }
    else if (tipo == "advertencia")
    {
        color = AMARILLO;
        prefijo = "[ADVERTENCIA]";
    }

    std::cout << color << prefijo << " " << mensaje << RESET << std::endl;
}

// Título con estilo (SIN ICONOS)
void InterfazMejorada::mostrarTitulo(const std::string &titulo)
{
    std::cout << CYAN << NEGRITA << "\n+--" << std::string(titulo.length() + 2, '-') << "--+" << std::endl;
    std::cout << "|  " << titulo << "  |" << std::endl;
    std::cout << "+--" << std::string(titulo.length() + 2, '-') << "--+" << RESET << std::endl;
}

void InterfazMejorada::pausar()
{
    std::cout << AMARILLO << "\n>> Presione Enter para continuar..." << RESET;
    std::cin.ignore();
    std::cin.get();
}