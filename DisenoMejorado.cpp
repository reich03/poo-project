#include "DisenoMejorado.h"
#include "InterfazMejorada.h"
#include "Entidades.h"
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

void DisenoMejorado::crearCaja(const std::string &contenido, int ancho)
{
    cout << InterfazMejorada::CYAN;

    cout << ESQUINA_SUP_IZQ;
    for (int i = 0; i < ancho - 2; i++)
        cout << LINEA_HOR;
    cout << ESQUINA_SUP_DER << std::endl;

    int padding = (ancho - contenido.length() - 2) / 2;
    cout << LINEA_VER;
    for (int i = 0; i < padding; i++)
        cout << " ";
    cout << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << contenido << InterfazMejorada::CYAN;
    for (int i = 0; i < ancho - contenido.length() - padding - 2; i++)
        cout << " ";
    cout << LINEA_VER << std::endl;

    // Línea inferior
    cout << ESQUINA_INF_IZQ;
    for (int i = 0; i < ancho - 2; i++)
        cout << LINEA_HOR;
    cout << ESQUINA_INF_DER << InterfazMejorada::RESET << std::endl;
}

void DisenoMejorado::mostrarHeaderEmpresa()
{
    cout << InterfazMejorada::CYAN << InterfazMejorada::NEGRITA;

    cout << "\n" << ESQUINA_SUP_IZQ;
    for (int i = 0; i < 68; i++)
        cout << LINEA_HOR;
    cout << ESQUINA_SUP_DER << std::endl;

    cout << LINEA_VER << "                    " << InterfazMejorada::VERDE << "SUPERMERCADO PRODUCTOS FRESCOS" << InterfazMejorada::CYAN << "                    " << LINEA_VER << std::endl;
    cout << LINEA_VER << "                         " << InterfazMejorada::BLANCO << "Frutas - Verduras - Carnes" << InterfazMejorada::CYAN << "                        " << LINEA_VER << std::endl;
    cout << LINEA_VER << "                                                                  " << LINEA_VER << std::endl;
    cout << LINEA_VER << "  " << InterfazMejorada::BLANCO << "Tel: (601) 555-0123  |  Email: ventas@productosfrescos.com" << InterfazMejorada::CYAN << "   " << LINEA_VER << std::endl;
    cout << LINEA_VER << "           " << InterfazMejorada::BLANCO << "Calle 85 #45-23, Barranquilla, Atlantico" << InterfazMejorada::CYAN << "            " << LINEA_VER << std::endl;

    cout << ESQUINA_INF_IZQ;
    for (int i = 0; i < 68; i++)
        cout << LINEA_HOR;
    cout << ESQUINA_INF_DER << InterfazMejorada::RESET << std::endl;
}

void DisenoMejorado::mostrarSeparador(char caracter, int longitud, const std::string &color)
{
    std::string colorUsado = color.empty() ? InterfazMejorada::CYAN : color;
    cout << colorUsado;
    for (int i = 0; i < longitud; i++)
    {
        cout << caracter;
    }
    cout << InterfazMejorada::RESET << std::endl;
}

void DisenoMejorado::iniciarTabla(const std::vector<std::string> &headers, const std::vector<int> &anchos)
{
    cout << InterfazMejorada::CYAN;

    cout << ESQUINA_SUP_IZQ;
    for (size_t i = 0; i < headers.size(); i++)
    {
        for (int j = 0; j < anchos[i]; j++)
            cout << LINEA_HOR;
        if (i < headers.size() - 1)
            cout << T_SUPERIOR;
    }
    cout << ESQUINA_SUP_DER << std::endl;

    cout << LINEA_VER;
    for (size_t i = 0; i < headers.size(); i++)
    {
        cout << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA
                  << std::left << std::setw(anchos[i]) << headers[i]
                  << InterfazMejorada::CYAN;
        if (i < headers.size() - 1)
            cout << LINEA_VER;
    }
    cout << LINEA_VER << InterfazMejorada::RESET << std::endl;

    cout << InterfazMejorada::CYAN << T_IZQUIERDA;
    for (size_t i = 0; i < headers.size(); i++)
    {
        for (int j = 0; j < anchos[i]; j++)
            cout << LINEA_HOR;
        if (i < headers.size() - 1)
            cout << CRUZ;
    }
    cout << T_DERECHA << InterfazMejorada::RESET << std::endl;
}

void DisenoMejorado::filaTabla(const std::vector<std::string> &datos, const std::vector<int> &anchos, const std::string &color)
{
    std::string colorUsado = color.empty() ? InterfazMejorada::BLANCO : color;
    cout << InterfazMejorada::CYAN << LINEA_VER << colorUsado;
    for (size_t i = 0; i < datos.size(); i++)
    {
        cout << std::left << std::setw(anchos[i]) << datos[i];
        if (i < datos.size() - 1)
            cout << InterfazMejorada::CYAN << LINEA_VER << colorUsado;
    }
    cout << InterfazMejorada::CYAN << LINEA_VER << InterfazMejorada::RESET << std::endl;
}

void DisenoMejorado::finalizarTabla(const std::vector<int> &anchos)
{
    cout << InterfazMejorada::CYAN << ESQUINA_INF_IZQ;
    for (size_t i = 0; i < anchos.size(); i++)
    {
        for (int j = 0; j < anchos[i]; j++)
            cout << LINEA_HOR;
        if (i < anchos.size() - 1)
            cout << T_INFERIOR;
    }
    cout << ESQUINA_INF_DER << InterfazMejorada::RESET << std::endl;
}

void DisenoMejorado::mostrarResumenTotales(const Factura &factura)
{
    cout << "\n" << InterfazMejorada::CYAN;

    cout << ESQUINA_SUP_IZQ;
    for (int i = 0; i < 40; i++)
        cout << LINEA_HOR;
    cout << ESQUINA_SUP_DER << std::endl;

    auto mostrarLineaTotal = [](const std::string &concepto, double valor, const std::string &color = InterfazMejorada::BLANCO)
    {
        cout << InterfazMejorada::CYAN << LINEA_VER << color
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

    cout << InterfazMejorada::CYAN << T_IZQUIERDA;
    for (int i = 0; i < 40; i++)
        cout << LINEA_HOR;
    cout << T_DERECHA << std::endl;

    cout << LINEA_VER << InterfazMejorada::VERDE << InterfazMejorada::NEGRITA
              << std::right << std::setw(22) << "TOTAL FINAL" << ": $"
              << std::fixed << std::setprecision(2) << std::setw(12) << factura.getTotalFinal()
              << InterfazMejorada::CYAN << " " << LINEA_VER << InterfazMejorada::RESET << std::endl;

    cout << InterfazMejorada::CYAN << ESQUINA_INF_IZQ;
    for (int i = 0; i < 40; i++)
        cout << LINEA_HOR;
    cout << ESQUINA_INF_DER << InterfazMejorada::RESET << std::endl;
}

void DisenoMejorado::mostrarFooterFactura()
{
    cout << "\n" << InterfazMejorada::CYAN;
    mostrarSeparador('-', 70);

    cout << InterfazMejorada::BLANCO << "                     " << InterfazMejorada::NEGRITA << "GRACIAS POR SU COMPRA!" << InterfazMejorada::RESET << std::endl;
    cout << InterfazMejorada::BLANCO << "                 Conserve este recibo como respaldo" << InterfazMejorada::RESET << std::endl;
    cout << InterfazMejorada::BLANCO << "             Para devoluciones presentar dentro de 30 dias" << InterfazMejorada::RESET << std::endl;

    mostrarSeparador('-', 70, InterfazMejorada::CYAN);
}