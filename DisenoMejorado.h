#ifndef DISENO_MEJORADO_H
#define DISENO_MEJORADO_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// Forward declaration para evitar dependencias circulares
class Factura;

class DisenoMejorado
{
public:
    // Caracteres para diseño de cajas y bordes
    static const std::string ESQUINA_SUP_IZQ;
    static const std::string ESQUINA_SUP_DER;
    static const std::string ESQUINA_INF_IZQ;
    static const std::string ESQUINA_INF_DER;
    static const std::string LINEA_HOR;
    static const std::string LINEA_VER;
    static const std::string T_SUPERIOR;
    static const std::string T_INFERIOR;
    static const std::string T_IZQUIERDA;
    static const std::string T_DERECHA;
    static const std::string CRUZ;

    // Métodos públicos
    static void crearCaja(const std::string &contenido, int ancho = 70);
    static void mostrarHeaderEmpresa();
    static void mostrarSeparador(char caracter = '=', int longitud = 70, const std::string &color = "");
    static void iniciarTabla(const std::vector<std::string> &headers, const std::vector<int> &anchos);
    static void filaTabla(const std::vector<std::string> &datos, const std::vector<int> &anchos, const std::string &color = "");
    static void finalizarTabla(const std::vector<int> &anchos);
    static void mostrarResumenTotales(const Factura &factura);
    static void mostrarFooterFactura();
};

#endif // DISENO_MEJORADO_H