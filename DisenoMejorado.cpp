#include "DisenoMejorado.h"
#include "InterfazMejorada.h"
#include "Factura.h" // Incluir después para evitar dependencias circulares

// Definición de caracteres de diseño (usando caracteres ASCII estándar)
const std::string DisenoMejorado::ESQUINA_SUP_IZQ = "+";
const std::string DisenoMejorado::ESQUINA_SUP_DER = "+";
const std::string DisenoMejorado::ESQUINA_INF_IZQ = "+";
const std::string DisenoMejorado::ESQUINA_INF_DER = "+";
const std::string DisenoMejorado::LINEA_HOR = "-";
const std::string DisenoMejorado::LINEA_VER = "|";
const std::string DisenoMejorado::T_SUPERIOR = "+";
const std::string DisenoMejorado::T_INFERIOR = "+";
const std::string DisenoMejorado::T_IZQUIERDA = "+";
const std::string DisenoMejorado::T_DERECHA = "+";
const std::string DisenoMejorado::CRUZ = "+";

// Crear caja decorativa
void DisenoMejorado::crearCaja(const std::string &contenido, int ancho)
{
    std::cout << InterfazMejorada::CYAN;

    // Línea superior
    std::cout << ESQUINA_SUP_IZQ;
    for (int i = 0; i < ancho - 2; i++)
        std::cout << LINEA_HOR;
    std::cout << ESQUINA_SUP_DER << std::endl;

    // Contenido centrado
    int padding = (ancho - contenido.length() - 2) / 2;
    std::cout << LINEA_VER;
    for (int i = 0; i < padding; i++)
        std::cout << " ";
    std::cout << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << contenido << InterfazMejorada::CYAN;
    for (int i = 0; i < ancho - contenido.length() - padding - 2; i++)
        std::cout << " ";
    std::cout << LINEA_VER << std::endl;

    // Línea inferior
    std::cout << ESQUINA_INF_IZQ;
    for (int i = 0; i < ancho - 2; i++)
        std::cout << LINEA_HOR;
    std::cout << ESQUINA_INF_DER << InterfazMejorada::RESET << std::endl;
}

// Header de empresa elegante
void DisenoMejorado::mostrarHeaderEmpresa()
{
    std::cout << InterfazMejorada::CYAN << InterfazMejorada::NEGRITA;

    // Marco superior decorativo
    std::cout << "\n" << ESQUINA_SUP_IZQ;
    for (int i = 0; i < 68; i++)
        std::cout << LINEA_HOR;
    std::cout << ESQUINA_SUP_DER << std::endl;

    // Información de la empresa
    std::cout << LINEA_VER << "                    " << InterfazMejorada::VERDE << "SUPERMERCADO PRODUCTOS FRESCOS" << InterfazMejorada::CYAN << "                    " << LINEA_VER << std::endl;
    std::cout << LINEA_VER << "                         " << InterfazMejorada::BLANCO << "Frutas - Verduras - Carnes" << InterfazMejorada::CYAN << "                        " << LINEA_VER << std::endl;
    std::cout << LINEA_VER << "                                                                  " << LINEA_VER << std::endl;
    std::cout << LINEA_VER << "  " << InterfazMejorada::BLANCO << "Tel: (601) 555-0123  |  Email: ventas@productosfrescos.com" << InterfazMejorada::CYAN << "   " << LINEA_VER << std::endl;
    std::cout << LINEA_VER << "           " << InterfazMejorada::BLANCO << "Calle 85 #45-23, Barranquilla, Atlantico" << InterfazMejorada::CYAN << "            " << LINEA_VER << std::endl;

    // Marco inferior decorativo
    std::cout << ESQUINA_INF_IZQ;
    for (int i = 0; i < 68; i++)
        std::cout << LINEA_HOR;
    std::cout << ESQUINA_INF_DER << InterfazMejorada::RESET << std::endl;
}

// Separador decorativo
void DisenoMejorado::mostrarSeparador(char caracter, int longitud, const std::string &color)
{
    std::string colorUsado = color.empty() ? InterfazMejorada::CYAN : color;
    std::cout << colorUsado;
    for (int i = 0; i < longitud; i++)
    {
        std::cout << caracter;
    }
    std::cout << InterfazMejorada::RESET << std::endl;
}

// Tabla con bordes elegantes
void DisenoMejorado::iniciarTabla(const std::vector<std::string> &headers, const std::vector<int> &anchos)
{
    std::cout << InterfazMejorada::CYAN;

    // Línea superior
    std::cout << ESQUINA_SUP_IZQ;
    for (size_t i = 0; i < headers.size(); i++)
    {
        for (int j = 0; j < anchos[i]; j++)
            std::cout << LINEA_HOR;
        if (i < headers.size() - 1)
            std::cout << T_SUPERIOR;
    }
    std::cout << ESQUINA_SUP_DER << std::endl;

    // Headers
    std::cout << LINEA_VER;
    for (size_t i = 0; i < headers.size(); i++)
    {
        std::cout << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA
                  << std::left << std::setw(anchos[i]) << headers[i]
                  << InterfazMejorada::CYAN;
        if (i < headers.size() - 1)
            std::cout << LINEA_VER;
    }
    std::cout << LINEA_VER << InterfazMejorada::RESET << std::endl;

    // Línea separadora
    std::cout << InterfazMejorada::CYAN << T_IZQUIERDA;
    for (size_t i = 0; i < headers.size(); i++)
    {
        for (int j = 0; j < anchos[i]; j++)
            std::cout << LINEA_HOR;
        if (i < headers.size() - 1)
            std::cout << CRUZ;
    }
    std::cout << T_DERECHA << InterfazMejorada::RESET << std::endl;
}

void DisenoMejorado::filaTabla(const std::vector<std::string> &datos, const std::vector<int> &anchos, const std::string &color)
{
    std::string colorUsado = color.empty() ? InterfazMejorada::BLANCO : color;
    std::cout << InterfazMejorada::CYAN << LINEA_VER << colorUsado;
    for (size_t i = 0; i < datos.size(); i++)
    {
        std::cout << std::left << std::setw(anchos[i]) << datos[i];
        if (i < datos.size() - 1)
            std::cout << InterfazMejorada::CYAN << LINEA_VER << colorUsado;
    }
    std::cout << InterfazMejorada::CYAN << LINEA_VER << InterfazMejorada::RESET << std::endl;
}

void DisenoMejorado::finalizarTabla(const std::vector<int> &anchos)
{
    std::cout << InterfazMejorada::CYAN << ESQUINA_INF_IZQ;
    for (size_t i = 0; i < anchos.size(); i++)
    {
        for (int j = 0; j < anchos[i]; j++)
            std::cout << LINEA_HOR;
        if (i < anchos.size() - 1)
            std::cout << T_INFERIOR;
    }
    std::cout << ESQUINA_INF_DER << InterfazMejorada::RESET << std::endl;
}

// Resumen de totales elegante
void DisenoMejorado::mostrarResumenTotales(const Factura &factura)
{
    std::cout << "\n" << InterfazMejorada::CYAN;

    // Caja para el resumen
    std::cout << ESQUINA_SUP_IZQ;
    for (int i = 0; i < 40; i++)
        std::cout << LINEA_HOR;
    std::cout << ESQUINA_SUP_DER << std::endl;

    // Función auxiliar para mostrar línea de total
    auto mostrarLineaTotal = [](const std::string &concepto, double valor, const std::string &color = InterfazMejorada::BLANCO)
    {
        std::cout << InterfazMejorada::CYAN << LINEA_VER << color
                  << std::right << std::setw(22) << concepto << ": $"
                  << std::fixed << std::setprecision(2) << std::setw(12) << valor
                  << InterfazMejorada::CYAN << " " << LINEA_VER << InterfazMejorada::RESET << std::endl;
    };

    mostrarLineaTotal("Subtotal sin IVA", factura.getSubtotalSinIva());
    mostrarLineaTotal("Subtotal con IVA", factura.getSubtotalConIva());
    mostrarLineaTotal("IVA (19%)", factura.getIvaTotal(), InterfazMejorada::AMARILLO);

    if (factura.getPuntosUsados() > 0)
    {
        mostrarLineaTotal("Descuento puntos", -factura.getPuntosUsados(), InterfazMejorada::VERDE);
    }

    if (factura.getDescuentoCarnes() > 0)
    {
        mostrarLineaTotal("Descuento carnes", -factura.getDescuentoCarnes(), InterfazMejorada::VERDE);
    }

    // Línea separadora antes del total
    std::cout << InterfazMejorada::CYAN << T_IZQUIERDA;
    for (int i = 0; i < 40; i++)
        std::cout << LINEA_HOR;
    std::cout << T_DERECHA << std::endl;

    // Total final destacado
    std::cout << LINEA_VER << InterfazMejorada::VERDE << InterfazMejorada::NEGRITA
              << std::right << std::setw(22) << "TOTAL FINAL" << ": $"
              << std::fixed << std::setprecision(2) << std::setw(12) << factura.getTotalFinal()
              << InterfazMejorada::CYAN << " " << LINEA_VER << InterfazMejorada::RESET << std::endl;

    // Marco inferior
    std::cout << InterfazMejorada::CYAN << ESQUINA_INF_IZQ;
    for (int i = 0; i < 40; i++)
        std::cout << LINEA_HOR;
    std::cout << ESQUINA_INF_DER << InterfazMejorada::RESET << std::endl;
}

// Footer profesional
void DisenoMejorado::mostrarFooterFactura()
{
    std::cout << "\n" << InterfazMejorada::CYAN;
    mostrarSeparador('-', 70);

    std::cout << InterfazMejorada::BLANCO << "                     " << InterfazMejorada::NEGRITA << "GRACIAS POR SU COMPRA!" << InterfazMejorada::RESET << std::endl;
    std::cout << InterfazMejorada::BLANCO << "                 Conserve este recibo como respaldo" << InterfazMejorada::RESET << std::endl;
    std::cout << InterfazMejorada::BLANCO << "             Para devoluciones presentar dentro de 30 dias" << InterfazMejorada::RESET << std::endl;

    mostrarSeparador('-', 70, InterfazMejorada::CYAN);
}