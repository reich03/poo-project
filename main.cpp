#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <cfloat>
#include <climits>

#include "InterfazMejorada.h"
#include "DisenoMejorado.h"
#include "Validador.h"
#include "Entidades.h"

#include <C:\Users\redjh\Desktop\Cristian\libharu\include\hpdf.h>

class BusinessException : public std::exception
{
private:
    std::string message;

public:
    BusinessException(const std::string &msg) : message(msg) {}
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};


class SistemaNotificaciones
{
private:
    static std::vector<std::string> alertas_pendientes;

public:
    static void limpiarAlertas()
    {
        alertas_pendientes.clear();
    }

    static void agregarAlerta(const std::string &mensaje)
    {
        // Evitar duplicados
        if (std::find(alertas_pendientes.begin(), alertas_pendientes.end(), mensaje) == alertas_pendientes.end())
        {
            alertas_pendientes.push_back(mensaje);
        }
    }

    static void mostrarAlertas()
    {
        if (!alertas_pendientes.empty())
        {
            std::cout << InterfazMejorada::AMARILLO << "[!] ALERTAS PENDIENTES:" << InterfazMejorada::RESET << std::endl;
            for (const auto &alerta : alertas_pendientes)
            {
                std::cout << "  - " << alerta << std::endl;
            }
            std::cout << std::endl;
        }
    }

    template <typename ProductoType>
    static void verificarStockBajo(const std::vector<ProductoType> &productos)
    {
        limpiarAlertas(); 
        for (const auto &p : productos)
        {
            if (p.getCantidad() < 5)
            {
                agregarAlerta("Stock CRITICO: " + p.getNombre() + " (" + std::to_string(p.getCantidad()) + " unidades)");
            }
            else if (p.getCantidad() < 15)
            {
                agregarAlerta("Stock bajo: " + p.getNombre() + " (" + std::to_string(p.getCantidad()) + " unidades)");
            }
        }
    }
};

std::vector<std::string> SistemaNotificaciones::alertas_pendientes;


class GestorArchivos
{
public:
    static void guardarProductos(const std::vector<Producto> &productos, const std::string &archivo)
    {
        std::ofstream file(archivo);
        if (file.is_open())
        {
            for (const auto &p : productos)
            {
                file << p.toString() << std::endl;
            }
            file.close();
        }
    }

    static void cargarProductos(std::vector<Producto> &productos, const std::string &archivo)
    {
        productos.clear(); 
        std::ifstream file(archivo);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                if (!line.empty())
                {
                    Producto p;
                    p.fromString(line);
                    productos.push_back(p);
                }
            }
            file.close();
        }
    }

    static void guardarClientes(const std::vector<Cliente> &clientes, const std::string &archivo)
    {
        std::ofstream file(archivo);
        if (file.is_open())
        {
            for (const auto &c : clientes)
            {
                file << c.toString() << std::endl;
            }
            file.close();
        }
    }

    static void cargarClientes(std::vector<Cliente> &clientes, const std::string &archivo)
    {
        clientes.clear(); 
        std::ifstream file(archivo);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                if (!line.empty())
                {
                    Cliente c;
                    c.fromString(line);
                    clientes.push_back(c);
                }
            }
            file.close();
        }
    }

    static void guardarConfig(int prod_id, int cli_id, int fact_num, const std::string &archivo)
    {
        std::ofstream file(archivo);
        if (file.is_open())
        {
            file << prod_id << "|" << cli_id << "|" << fact_num << std::endl;
            file.close();
        }
    }

    static void cargarConfig(int &prod_id, int &cli_id, int &fact_num, const std::string &archivo)
    {
        std::ifstream file(archivo);
        if (file.is_open())
        {
            std::string line;
            if (std::getline(file, line))
            {
                std::istringstream iss(line);
                std::string token;

                if (std::getline(iss, token, '|'))
                    prod_id = std::stoi(token);
                if (std::getline(iss, token, '|'))
                    cli_id = std::stoi(token);
                if (std::getline(iss, token, '|'))
                    fact_num = std::stoi(token);
            }
            file.close();
        }
    }
};


class GeneradorCodigoBarras
{
public:
    static std::string generarCodigo(const Producto &producto)
    {
        return "750" + std::to_string(producto.getId() * 1000 + producto.getCategoria().length());
    }

    static void generarRepresentacionVisual(const std::string &codigo)
    {
        std::cout << InterfazMejorada::VERDE << "\n[CODIGO DE BARRAS] Representacion visual:" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::NEGRITA;
        for (char c : codigo)
        {
            int digit = c - '0';
            for (int i = 0; i < 4; i++)
            {
                if ((digit + i) % 2 == 0)
                {
                    std::cout << "|";
                }
                else
                {
                    std::cout << " ";
                }
            }
            std::cout << " ";
        }
        std::cout << InterfazMejorada::RESET << "\n"
                  << codigo << std::endl;
    }

    static void guardarCodigoEnArchivo(const Producto &producto, const std::string &codigo)
    {
        std::string nombreArchivo = "codigo_" + std::to_string(producto.getId()) + ".txt";
        std::ofstream file(nombreArchivo);
        if (file.is_open())
        {
            file << "Producto: " << producto.getNombre() << std::endl;
            file << "Codigo de barras: " << codigo << std::endl;
            file.close();
            InterfazMejorada::mostrarNotificacion("Codigo guardado en archivo: " + nombreArchivo, "exito");
        }
    }
};


class GeneradorPDF
{
public:
    static bool guardarFacturaPDF(const Factura &factura, const Cliente *cliente = nullptr)
    {
        HPDF_Doc pdf = HPDF_New(NULL, NULL);
        if (!pdf)
        {
            std::cerr << "Error al crear el documento PDF." << std::endl;
            return false;
        }

        HPDF_Page page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

        HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
        HPDF_Page_SetFontAndSize(page, font, 12);

        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 50, 800, ("Factura No: " + std::to_string(factura.getNumero())).c_str());
        HPDF_Page_TextOut(page, 50, 780, ("Fecha: " + factura.getFecha()).c_str());

        if (cliente != nullptr)
        {
            HPDF_Page_TextOut(page, 50, 760, ("Cliente: " + cliente->getNombre()).c_str());
        }

        HPDF_Page_EndText(page);

        float yPosition = 720;
        HPDF_Page_BeginText(page);

        for (const auto &item : factura.getItems())
        {
            std::string item_text = item.getNombreProducto() + " | " +
                                    std::to_string(item.getCantidad()) + " | " +
                                    "$" + std::to_string(item.getPrecioUnitario()) + " | " +
                                    "$" + std::to_string(item.getSubtotal());

            HPDF_Page_TextOut(page, 50, yPosition, item_text.c_str());
            yPosition -= 20;
        }

        HPDF_Page_EndText(page);

        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 50, yPosition, ("Subtotal sin IVA: $" + std::to_string(factura.getSubtotalSinIva())).c_str());
        yPosition -= 20;
        HPDF_Page_TextOut(page, 50, yPosition, ("Subtotal con IVA: $" + std::to_string(factura.getSubtotalConIva())).c_str());
        yPosition -= 20;
        HPDF_Page_TextOut(page, 50, yPosition, ("IVA (19%): $" + std::to_string(factura.getIvaTotal())).c_str());
        yPosition -= 20;
        HPDF_Page_TextOut(page, 50, yPosition, ("TOTAL FINAL: $" + std::to_string(factura.getTotalFinal())).c_str());
        HPDF_Page_EndText(page);

        try
        {
            HPDF_SaveToFile(pdf, ("factura_" + std::to_string(factura.getNumero()) + ".pdf").c_str());
            HPDF_Free(pdf);
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error al guardar el PDF: " << e.what() << std::endl;
            HPDF_Free(pdf);
            return false;
        }
    }
};


class FacturaMejorada
{
public:
    static void imprimirFacturaElegante(const Factura &factura, const Cliente *cliente = nullptr)
    {
        InterfazMejorada::limpiarPantalla();

        DisenoMejorado::mostrarHeaderEmpresa();

        std::cout << "\n";
        DisenoMejorado::crearCaja("FACTURA DE VENTA", 70);

        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA;
        std::cout << "Factura No: " << InterfazMejorada::VERDE << std::setw(15) << std::left << factura.getNumero()
                  << InterfazMejorada::AMARILLO << "   Fecha: " << InterfazMejorada::VERDE << factura.getFecha() << InterfazMejorada::RESET << std::endl;

        if (cliente != nullptr)
        {
            std::cout << InterfazMejorada::AMARILLO << "Cliente: " << InterfazMejorada::VERDE << cliente->getNombre()
                      << InterfazMejorada::AMARILLO << " (ID: " << cliente->getId() << ")" << InterfazMejorada::RESET << std::endl;
            std::cout << InterfazMejorada::AMARILLO << "Puntos disponibles: " << InterfazMejorada::VERDE
                      << std::fixed << std::setprecision(2) << cliente->getPuntos() << InterfazMejorada::RESET << std::endl;
        }
        else
        {
            std::cout << InterfazMejorada::AMARILLO << "Cliente: " << InterfazMejorada::BLANCO << "Cliente sin registro" << InterfazMejorada::RESET << std::endl;
        }

        std::cout << "\n";

        std::vector<std::string> headers = {"Producto", "Cant.", "P.Unit", "Subtotal", "IVA"};
        std::vector<int> anchos = {25, 6, 10, 12, 5};

        DisenoMejorado::iniciarTabla(headers, anchos);

        for (const auto &item : factura.getItems())
        {
            std::vector<std::string> fila = {
                item.getNombreProducto().length() > 24 ? item.getNombreProducto().substr(0, 24) : item.getNombreProducto(),
                std::to_string(item.getCantidad()),
                "$" + std::to_string(static_cast<int>(item.getPrecioUnitario() * 100) / 100) + "." +
                    (static_cast<int>(item.getPrecioUnitario() * 100) % 100 < 10 ? "0" : "") +
                    std::to_string(static_cast<int>(item.getPrecioUnitario() * 100) % 100),
                "$" + std::to_string(static_cast<int>(item.getSubtotal() * 100) / 100) + "." +
                    (static_cast<int>(item.getSubtotal() * 100) % 100 < 10 ? "0" : "") +
                    std::to_string(static_cast<int>(item.getSubtotal() * 100) % 100),
                item.isExentoIva() ? "No" : "Si"};

            DisenoMejorado::filaTabla(fila, anchos);
        }

        DisenoMejorado::finalizarTabla(anchos);


        DisenoMejorado::mostrarResumenTotales(factura);

        if (factura.getPuntosUsados() > 0 || factura.getDescuentoCarnes() > 0)
        {
            std::cout << "\n"
                      << InterfazMejorada::VERDE << "[DESCUENTOS APLICADOS]" << InterfazMejorada::RESET << std::endl;
            if (factura.getPuntosUsados() > 0)
            {
                std::cout << "  * Puntos utilizados: " << InterfazMejorada::VERDE << factura.getPuntosUsados() << " puntos" << InterfazMejorada::RESET << std::endl;
            }
            if (factura.getDescuentoCarnes() > 0)
            {
                std::cout << "  * " << InterfazMejorada::VERDE << "FELICIDADES! Gano el sorteo de carnes (10% desc.)" << InterfazMejorada::RESET << std::endl;
            }
        }

        DisenoMejorado::mostrarFooterFactura();

        std::cout << "\n"
                  << InterfazMejorada::CYAN << "Codigo QR de la factura:" << InterfazMejorada::RESET << std::endl;
        mostrarCodigoQRSimulado(factura.getNumero());
    }

private:
    static void mostrarCodigoQRSimulado(int numeroFactura)
    {
        std::cout << InterfazMejorada::BLANCO;

        srand(numeroFactura);

        std::cout << "  +";
        for (int i = 0; i < 20; i++)
            std::cout << "-";
        std::cout << "+" << std::endl;

        for (int fila = 0; fila < 8; fila++)
        {
            std::cout << "  |";
            for (int col = 0; col < 20; col++)
            {
                if ((fila + col + numeroFactura) % 3 == 0)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << " ";
                }
            }
            std::cout << "|" << std::endl;
        }

        std::cout << "  +";
        for (int i = 0; i < 20; i++)
            std::cout << "-";
        std::cout << "+" << InterfazMejorada::RESET << std::endl;

        std::cout << InterfazMejorada::CYAN << "    Factura #" << numeroFactura << InterfazMejorada::RESET << std::endl;
    }
};


class MenuMejorado
{
public:
    static void mostrarMenuPrincipal()
    {
        InterfazMejorada::limpiarPantalla();

        std::cout << InterfazMejorada::CYAN << InterfazMejorada::NEGRITA;
        std::cout << "\n"
                  << DisenoMejorado::ESQUINA_SUP_IZQ;
        for (int i = 0; i < 68; i++)
            std::cout << DisenoMejorado::LINEA_HOR;
        std::cout << DisenoMejorado::ESQUINA_SUP_DER << std::endl;

        std::cout << DisenoMejorado::LINEA_VER << "                                                                  " << DisenoMejorado::LINEA_VER << std::endl;
        std::cout << DisenoMejorado::LINEA_VER << "       " << InterfazMejorada::VERDE << "SISTEMA DE GESTION - PRODUCTOS FRESCOS v2.0" << InterfazMejorada::CYAN << "        " << DisenoMejorado::LINEA_VER << std::endl;
        std::cout << DisenoMejorado::LINEA_VER << "                                                                  " << DisenoMejorado::LINEA_VER << std::endl;

        std::cout << DisenoMejorado::ESQUINA_INF_IZQ;
        for (int i = 0; i < 68; i++)
            std::cout << DisenoMejorado::LINEA_HOR;
        std::cout << DisenoMejorado::ESQUINA_INF_DER << InterfazMejorada::RESET << std::endl;

        // Opciones del menú organizadas por categorías
        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[GESTION DE PRODUCTOS]" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "  1. " << InterfazMejorada::VERDE << "Agregar producto" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "  2. " << InterfazMejorada::VERDE << "Listar productos" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "  3. " << InterfazMejorada::VERDE << "Buscar producto por codigo" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "  4. " << InterfazMejorada::VERDE << "Actualizar inventario" << InterfazMejorada::RESET << std::endl;

        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[GESTION DE CLIENTES]" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "  5. " << InterfazMejorada::CYAN << "Agregar cliente" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "  6. " << InterfazMejorada::CYAN << "Listar clientes" << InterfazMejorada::RESET << std::endl;

        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[FACTURACION Y VENTAS]" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "  7. " << InterfazMejorada::MAGENTA << "Crear factura" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << " 11. " << InterfazMejorada::MAGENTA << "Reimprimir factura como PDF" << InterfazMejorada::RESET << std::endl;

        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[HERRAMIENTAS Y REPORTES]" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "  8. " << InterfazMejorada::AMARILLO << "Generar codigo de barras" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "  9. " << InterfazMejorada::AMARILLO << "Generar reporte de inventario" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << " 10. " << InterfazMejorada::AMARILLO << "Ver estadisticas" << InterfazMejorada::RESET << std::endl;

        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[SISTEMA]" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << " 12. " << InterfazMejorada::BLANCO << "Guardar datos" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << " 13. " << InterfazMejorada::BLANCO << "Cargar datos" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::ROJO << "  0. " << InterfazMejorada::ROJO << "Salir" << InterfazMejorada::RESET << std::endl;

        DisenoMejorado::mostrarSeparador('-', 70, InterfazMejorada::CYAN);
        std::cout << InterfazMejorada::CYAN << InterfazMejorada::NEGRITA << ">> Seleccione una opcion: " << InterfazMejorada::RESET;
    }
};


class GeneradorReportes
{
public:
    static void generarGraficoBarrasElegante(const std::map<std::string, int> &datos, const std::string &titulo)
    {
        InterfazMejorada::limpiarPantalla();
        DisenoMejorado::crearCaja(titulo, 70);

        if (datos.empty())
        {
            std::cout << InterfazMejorada::AMARILLO << "No hay datos para mostrar." << InterfazMejorada::RESET << std::endl;
            return;
        }

        int max_valor = 0;
        for (const auto &par : datos)
        {
            max_valor = std::max(max_valor, par.second);
        }

        const int max_barras = 50;
        std::cout << "\n";

        for (const auto &par : datos)
        {
            int longitud_barra = max_valor > 0 ? (par.second * max_barras) / max_valor : 0;

            std::cout << InterfazMejorada::CYAN << std::left << std::setw(20) << par.first << InterfazMejorada::RESET << " ";

            std::cout << InterfazMejorada::VERDE << "|";
            for (int i = 0; i < longitud_barra; ++i)
            {
                std::cout << "#";
            }

            for (int i = longitud_barra; i < max_barras; ++i)
            {
                std::cout << " ";
            }

            std::cout << "| " << InterfazMejorada::AMARILLO << par.second << InterfazMejorada::RESET << std::endl;
        }

        std::cout << "\n";
        DisenoMejorado::mostrarSeparador('=', 70, InterfazMejorada::CYAN);
    }
};


class SistemaGestion
{
private:
    std::vector<Producto> productos;
    std::vector<Cliente> clientes;
    std::vector<Factura> facturas;
    int siguiente_producto_id;
    int siguiente_cliente_id;
    int siguiente_factura_numero;

    const std::string ARCHIVO_PRODUCTOS = "productos.txt";
    const std::string ARCHIVO_CLIENTES = "clientes.txt";
    const std::string ARCHIVO_CONFIG = "config.txt";

public:
    SistemaGestion() : siguiente_producto_id(1), siguiente_cliente_id(1), siguiente_factura_numero(1)
    {
        InterfazMejorada::mostrarBannerInicio();
        InterfazMejorada::mostrarCarga("Inicializando sistema");
        cargar_datos();
    }

    ~SistemaGestion()
    {
        InterfazMejorada::mostrarCarga("Guardando datos");
        guardar_datos();
    }

    void cargar_datos()
    {
        try
        {
            GestorArchivos::cargarConfig(siguiente_producto_id, siguiente_cliente_id,
                                         siguiente_factura_numero, ARCHIVO_CONFIG);
            GestorArchivos::cargarProductos(productos, ARCHIVO_PRODUCTOS);
            GestorArchivos::cargarClientes(clientes, ARCHIVO_CLIENTES);
            InterfazMejorada::mostrarNotificacion("Datos cargados exitosamente", "exito");
        }
        catch (const std::exception &e)
        {
            InterfazMejorada::mostrarNotificacion("Error al cargar datos: " + std::string(e.what()), "error");
        }
    }

    void guardar_datos()
    {
        try
        {
            GestorArchivos::guardarConfig(siguiente_producto_id, siguiente_cliente_id,
                                          siguiente_factura_numero, ARCHIVO_CONFIG);
            GestorArchivos::guardarProductos(productos, ARCHIVO_PRODUCTOS);
            GestorArchivos::guardarClientes(clientes, ARCHIVO_CLIENTES);
            InterfazMejorada::mostrarNotificacion("Datos guardados exitosamente", "exito");
        }
        catch (const std::exception &e)
        {
            InterfazMejorada::mostrarNotificacion("Error al guardar datos: " + std::string(e.what()), "error");
        }
    }

    void agregar_producto()
    {
        try
        {
            DisenoMejorado::crearCaja("AGREGAR NUEVO PRODUCTO", 60);

            Producto nuevo;
            nuevo.setId(siguiente_producto_id++);

            std::cin.ignore();
            std::string nombre = Validador::leerEntradaSegura("Nombre del producto: ");
            nuevo.setNombre(nombre);

            std::cout << InterfazMejorada::CYAN << "\nCategorias disponibles:" << InterfazMejorada::RESET << std::endl;
            std::cout << "1. Frutas" << std::endl;
            std::cout << "2. Verduras" << std::endl;
            std::cout << "3. Carnes" << std::endl;
            std::cout << "4. Productos individuales" << std::endl;

            int cat_opcion = Validador::leerEnteroSeguro(">> Seleccione categoria (1-4): ", 1, 4);

            switch (cat_opcion)
            {
            case 1:
                nuevo.setCategoria("frutas");
                break;
            case 2:
                nuevo.setCategoria("verduras");
                break;
            case 3:
                nuevo.setCategoria("carnes");
                break;
            case 4:
                nuevo.setCategoria("productos_individuales");
                break;
            default:
                throw BusinessException("Categoria invalida");
            }

            double precio = Validador::leerDoubleSeguro("Precio unitario $", 0.01, 999999.99);
            nuevo.setPrecio(precio);

            int cantidad = Validador::leerEnteroSeguro("Cantidad inicial: ", 0, 99999);
            nuevo.setCantidad(cantidad);

            int exento = Validador::leerEnteroSeguro("¿Exento de IVA? (1=Si, 0=No): ", 0, 1);
            nuevo.setExentoIva(exento == 1);

            if (nuevo.getCategoria() == "carnes")
            {
                std::string origen = Validador::leerEntradaSegura("Origen del producto (rio/criadero/mar): ");
                nuevo.setOrigen(origen);
            }

            productos.push_back(nuevo);
            InterfazMejorada::mostrarNotificacion("Producto agregado exitosamente con ID: " + std::to_string(nuevo.getId()), "exito");
        }
        catch (const BusinessException &e)
        {
            InterfazMejorada::mostrarNotificacion("Error: " + std::string(e.what()), "error");
        }
        catch (const std::exception &e)
        {
            InterfazMejorada::mostrarNotificacion("Error inesperado: " + std::string(e.what()), "error");
        }
    }

    void listar_productos()
    {
        InterfazMejorada::limpiarPantalla();
        DisenoMejorado::crearCaja("INVENTARIO DE PRODUCTOS", 80);

        if (productos.empty())
        {
            InterfazMejorada::mostrarNotificacion("No hay productos registrados", "advertencia");
            return;
        }

        std::vector<std::string> headers = {"ID", "Nombre", "Categoria", "Precio", "Stock", "IVA", "Estado"};
        std::vector<int> anchos = {4, 25, 15, 10, 8, 6, 10};

        DisenoMejorado::iniciarTabla(headers, anchos);

        for (const auto &p : productos)
        {
            std::string estado, color;
            if (p.getCantidad() < 5)
            {
                estado = "CRITICO";
                color = InterfazMejorada::ROJO;
            }
            else if (p.getCantidad() < 15)
            {
                estado = "BAJO";
                color = InterfazMejorada::AMARILLO;
            }
            else
            {
                estado = "OK";
                color = InterfazMejorada::VERDE;
            }

            std::vector<std::string> fila = {
                std::to_string(p.getId()),
                p.getNombre().length() > 24 ? p.getNombre().substr(0, 24) : p.getNombre(),
                p.getCategoria(),
                "$" + std::to_string(static_cast<int>(p.getPrecio() * 100) / 100) + "." +
                    (static_cast<int>(p.getPrecio() * 100) % 100 < 10 ? "0" : "") +
                    std::to_string(static_cast<int>(p.getPrecio() * 100) % 100),
                std::to_string(p.getCantidad()),
                p.isExentoIva() ? "No" : "Si",
                estado};

            DisenoMejorado::filaTabla(fila, anchos, color);
        }

        DisenoMejorado::finalizarTabla(anchos);

        SistemaNotificaciones::verificarStockBajo(productos);
        SistemaNotificaciones::mostrarAlertas();
    }

    void buscar_producto_por_codigo()
    {
        DisenoMejorado::crearCaja("BUSCAR PRODUCTO POR ID", 50);

        int id = Validador::leerEnteroSeguro("Ingrese el ID del producto: ", 1, 99999);

        auto it = std::find_if(productos.begin(), productos.end(),
                               [id](const Producto &p)
                               { return p.getId() == id; });

        if (it != productos.end())
        {
            std::cout << InterfazMejorada::VERDE << "\n[ENCONTRADO] PRODUCTO ENCONTRADO" << InterfazMejorada::RESET << std::endl;
            std::cout << "ID: " << it->getId() << std::endl;
            std::cout << "Nombre: " << it->getNombre() << std::endl;
            std::cout << "Categoria: " << it->getCategoria() << std::endl;
            std::cout << "Precio: $" << std::fixed << std::setprecision(2) << it->getPrecio() << std::endl;
            std::cout << "Stock: " << it->getCantidad() << std::endl;
            std::cout << "IVA: " << (it->isExentoIva() ? "Exento" : "Incluido") << std::endl;
            if (!it->getOrigen().empty())
            {
                std::cout << "Origen: " << it->getOrigen() << std::endl;
            }
        }
        else
        {
            InterfazMejorada::mostrarNotificacion("Producto no encontrado", "error");
        }
    }

    void actualizar_inventario()
    {
        DisenoMejorado::crearCaja("ACTUALIZAR INVENTARIO", 50);
        listar_productos();

        if (productos.empty())
            return;

        int id = Validador::leerEnteroSeguro("\nIngrese el ID del producto a actualizar: ", 1, 99999);

        auto it = std::find_if(productos.begin(), productos.end(),
                               [id](const Producto &p)
                               { return p.getId() == id; });

        if (it != productos.end())
        {
            std::cout << "Stock actual: " << InterfazMejorada::AMARILLO << it->getCantidad() << InterfazMejorada::RESET << std::endl;
            int nueva_cantidad = Validador::leerEnteroSeguro("Nueva cantidad: ", 0, 99999);

            it->setCantidad(nueva_cantidad);
            InterfazMejorada::mostrarNotificacion("Inventario actualizado exitosamente", "exito");
        }
        else
        {
            InterfazMejorada::mostrarNotificacion("Producto no encontrado", "error");
        }
    }

    void agregar_cliente()
    {
        DisenoMejorado::crearCaja("AGREGAR NUEVO CLIENTE", 50);

        Cliente nuevo;
        nuevo.setId(siguiente_cliente_id++);

        std::cin.ignore();
        std::string nombre = Validador::leerEntradaSegura("Nombre del cliente: ");
        nuevo.setNombre(nombre);

        clientes.push_back(nuevo);
        InterfazMejorada::mostrarNotificacion("Cliente agregado exitosamente con ID: " + std::to_string(nuevo.getId()), "exito");
    }

    void listar_clientes()
    {
        InterfazMejorada::limpiarPantalla();
        DisenoMejorado::crearCaja("REGISTRO DE CLIENTES", 60);

        if (clientes.empty())
        {
            InterfazMejorada::mostrarNotificacion("No hay clientes registrados", "advertencia");
            return;
        }

        std::vector<std::string> headers = {"ID", "Nombre", "Puntos", "Categoria"};
        std::vector<int> anchos = {5, 30, 12, 15};

        DisenoMejorado::iniciarTabla(headers, anchos);

        for (const auto &c : clientes)
        {
            std::string categoria, color;
            if (c.getPuntos() >= 100)
            {
                categoria = "VIP";
                color = InterfazMejorada::VERDE;
            }
            else if (c.getPuntos() >= 50)
            {
                categoria = "PREMIUM";
                color = InterfazMejorada::AMARILLO;
            }
            else
            {
                categoria = "REGULAR";
                color = InterfazMejorada::BLANCO;
            }

            std::vector<std::string> fila = {
                std::to_string(c.getId()),
                c.getNombre(),
                std::to_string(static_cast<int>(c.getPuntos() * 100) / 100) + "." +
                    (static_cast<int>(c.getPuntos() * 100) % 100 < 10 ? "0" : "") +
                    std::to_string(static_cast<int>(c.getPuntos() * 100) % 100),
                categoria};

            DisenoMejorado::filaTabla(fila, anchos, color);
        }

        DisenoMejorado::finalizarTabla(anchos);

        std::cout << "\n"
                  << InterfazMejorada::CYAN << "[LEYENDA]" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::VERDE << "VIP: 100+ puntos  " << InterfazMejorada::AMARILLO << "PREMIUM: 50-99 puntos  " << InterfazMejorada::BLANCO << "REGULAR: 0-49 puntos" << InterfazMejorada::RESET << std::endl;
    }

    void crear_factura()
    {
        try
        {
            DisenoMejorado::crearCaja("CREAR NUEVA FACTURA", 60);

            Factura nueva_factura;
            nueva_factura.setNumero(siguiente_factura_numero++);

            // Obtener fecha actual
            time_t now = time(0);
            char *dt = ctime(&now);
            std::string fecha(dt);
            fecha.pop_back(); 
            nueva_factura.setFecha(fecha);

            std::cout << InterfazMejorada::AMARILLO << "Factura No: " << nueva_factura.getNumero() << InterfazMejorada::RESET << std::endl;

            listar_clientes();
            int cliente_id = Validador::leerEnteroSeguro("\nIngrese ID del cliente (0 para cliente sin registro): ", 0, 99999);
            nueva_factura.setClienteId(cliente_id);

            Cliente *cliente_actual = nullptr;
            if (cliente_id != 0)
            {
                auto it = std::find_if(clientes.begin(), clientes.end(),
                                       [cliente_id](const Cliente &c)
                                       { return c.getId() == cliente_id; });
                if (it != clientes.end())
                {
                    cliente_actual = &(*it);
                    std::cout << InterfazMejorada::VERDE << "[CLIENTE] " << cliente_actual->getNombre()
                              << " (Puntos: " << cliente_actual->getPuntos() << ")" << InterfazMejorada::RESET << std::endl;
                }
                else
                {
                    InterfazMejorada::mostrarNotificacion("Cliente no encontrado. Continuando sin cliente registrado.", "advertencia");
                    nueva_factura.setClienteId(0);
                }
            }

            char continuar = 'S';
            while (continuar == 'S' || continuar == 's')
            {
                listar_productos();

                if (productos.empty())
                {
                    InterfazMejorada::mostrarNotificacion("No hay productos disponibles", "error");
                    break;
                }

                int producto_id = Validador::leerEnteroSeguro("\nIngrese ID del producto: ", 1, 99999);

                auto prod_it = std::find_if(productos.begin(), productos.end(),
                                            [producto_id](const Producto &p)
                                            { return p.getId() == producto_id; });

                if (prod_it == productos.end())
                {
                    InterfazMejorada::mostrarNotificacion("Producto no encontrado", "error");
                    continue;
                }

                std::cout << "Stock disponible: " << InterfazMejorada::AMARILLO << prod_it->getCantidad() << InterfazMejorada::RESET << std::endl;
                int cantidad = Validador::leerEnteroSeguro("Cantidad requerida: ", 1, prod_it->getCantidad());

                if (cantidad > prod_it->getCantidad())
                {
                    InterfazMejorada::mostrarNotificacion("Stock insuficiente. Disponible: " + std::to_string(prod_it->getCantidad()), "error");
                    continue;
                }

                ItemFactura item(producto_id, prod_it->getNombre(), cantidad,
                                 prod_it->getPrecio(), prod_it->isExentoIva());
                nueva_factura.agregarItem(item);

                prod_it->setCantidad(prod_it->getCantidad() - cantidad);

                InterfazMejorada::mostrarNotificacion("Producto agregado a la factura", "exito");

                std::cout << InterfazMejorada::CYAN << ">> ¿Agregar otro producto? (S/N): " << InterfazMejorada::RESET;
                std::cin >> continuar;
            }

            if (nueva_factura.getItems().empty())
            {
                InterfazMejorada::mostrarNotificacion("No se puede crear factura sin productos", "error");
                return;
            }

            if (cliente_actual != nullptr)
            {
                if (cliente_actual->getPuntos() > 0)
                {
                    std::cout << InterfazMejorada::AMARILLO << "Puntos disponibles: " << cliente_actual->getPuntos() << InterfazMejorada::RESET << std::endl;
                    double puntos_usar = Validador::leerDoubleSeguro("¿Cuantos puntos desea usar? (1 punto = $1): ", 0, cliente_actual->getPuntos());

                    if (puntos_usar > 0 && cliente_actual->usarPuntos(puntos_usar))
                    {
                        nueva_factura.setPuntosUsados(puntos_usar);
                        InterfazMejorada::mostrarNotificacion("Puntos aplicados: $" + std::to_string(puntos_usar), "exito");
                    }
                }

                double total_carnes = 0;
                for (const auto &item : nueva_factura.getItems())
                {
                    auto prod_it = std::find_if(productos.begin(), productos.end(),
                                                [&item](const Producto &p)
                                                { return p.getId() == item.getProductoId(); });
                    if (prod_it != productos.end() && prod_it->getCategoria() == "carnes")
                    {
                        total_carnes += item.getSubtotal();
                    }
                }

                if (total_carnes > 0)
                {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(1, 10);

                    if (dis(gen) == 1)
                    {                                          
                        double descuento = total_carnes * 0.1; 
                        nueva_factura.setDescuentoCarnes(descuento);
                        InterfazMejorada::mostrarNotificacion("[GANADOR!] Ha ganado un 10% de descuento en carnes: $" +
                                                                  std::to_string(descuento),
                                                              "exito");
                    }
                }

                double puntos_ganados = nueva_factura.getTotalFinal() / 10000.0; 
                cliente_actual->agregarPuntos(puntos_ganados);
            }

            facturas.push_back(nueva_factura);

            Cliente *cliente_para_factura = nullptr;
            if (cliente_actual != nullptr)
            {
                cliente_para_factura = cliente_actual;
            }
            FacturaMejorada::imprimirFacturaElegante(nueva_factura, cliente_para_factura);

            InterfazMejorada::mostrarCarga("Generando archivo de factura");
            if (GeneradorPDF::guardarFacturaPDF(nueva_factura, cliente_para_factura))
            {
                InterfazMejorada::mostrarNotificacion("Factura guardada exitosamente!", "exito");
            }
            else
            {
                InterfazMejorada::mostrarNotificacion("Error al guardar la factura", "advertencia");
            }
        }
        catch (const std::exception &e)
        {
            InterfazMejorada::mostrarNotificacion("Error al crear factura: " + std::string(e.what()), "error");
        }
    }

    void generar_codigo_barras()
    {
        DisenoMejorado::crearCaja("GENERAR CODIGO DE BARRAS", 60);

        listar_productos();
        if (productos.empty())
            return;

        int id = Validador::leerEnteroSeguro("\nIngrese ID del producto para generar codigo de barras: ", 1, 99999);

        auto it = std::find_if(productos.begin(), productos.end(),
                               [id](const Producto &p)
                               { return p.getId() == id; });

        if (it != productos.end())
        {
            std::string codigo = GeneradorCodigoBarras::generarCodigo(*it);

            std::cout << InterfazMejorada::VERDE << "\n[CODIGO GENERADO]" << InterfazMejorada::RESET << std::endl;
            std::cout << "Producto: " << it->getNombre() << std::endl;
            std::cout << "Codigo: " << InterfazMejorada::AMARILLO << codigo << InterfazMejorada::RESET << std::endl;

            GeneradorCodigoBarras::generarRepresentacionVisual(codigo);
            GeneradorCodigoBarras::guardarCodigoEnArchivo(*it, codigo);
        }
        else
        {
            InterfazMejorada::mostrarNotificacion("Producto no encontrado", "error");
        }
    }

    void generar_reporte_inventario()
    {
        InterfazMejorada::limpiarPantalla();
        DisenoMejorado::crearCaja("REPORTE DE INVENTARIO", 80);

        time_t now = time(0);
        char *dt = ctime(&now);
        std::string fecha(dt);
        fecha.pop_back();

        std::cout << InterfazMejorada::AMARILLO << "Fecha del reporte: " << InterfazMejorada::VERDE << fecha << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::AMARILLO << "Total de productos: " << InterfazMejorada::VERDE << productos.size() << InterfazMejorada::RESET << std::endl;

        std::vector<std::string> headers = {"ID", "Producto", "Categoria", "Stock", "Precio", "Valor Total", "Estado"};
        std::vector<int> anchos = {4, 20, 15, 8, 10, 12, 10};

        std::cout << "\n";
        DisenoMejorado::iniciarTabla(headers, anchos);

        double valorTotal = 0;
        int productosStockBajo = 0;
        int productosStockCritico = 0;

        for (const auto &p : productos)
        {
            double valorProducto = p.getCantidad() * p.getPrecio();
            valorTotal += valorProducto;

            std::string estado;
            std::string color;
            if (p.getCantidad() < 5)
            {
                estado = "CRITICO";
                color = InterfazMejorada::ROJO;
                productosStockCritico++;
            }
            else if (p.getCantidad() < 15)
            {
                estado = "BAJO";
                color = InterfazMejorada::AMARILLO;
                productosStockBajo++;
            }
            else
            {
                estado = "OK";
                color = InterfazMejorada::VERDE;
            }

            std::vector<std::string> fila = {
                std::to_string(p.getId()),
                p.getNombre().length() > 19 ? p.getNombre().substr(0, 19) : p.getNombre(),
                p.getCategoria(),
                std::to_string(p.getCantidad()),
                "$" + std::to_string(static_cast<int>(p.getPrecio() * 100) / 100) + "." +
                    (static_cast<int>(p.getPrecio() * 100) % 100 < 10 ? "0" : "") +
                    std::to_string(static_cast<int>(p.getPrecio() * 100) % 100),
                "$" + std::to_string(static_cast<int>(valorProducto * 100) / 100) + "." +
                    (static_cast<int>(valorProducto * 100) % 100 < 10 ? "0" : "") +
                    std::to_string(static_cast<int>(valorProducto * 100) % 100),
                estado};

            DisenoMejorado::filaTabla(fila, anchos, color);
        }

        DisenoMejorado::finalizarTabla(anchos);

        std::cout << "\n";
        DisenoMejorado::crearCaja("RESUMEN ESTADISTICO", 60);

        std::cout << InterfazMejorada::VERDE << "Valor total del inventario: $" << std::fixed << std::setprecision(2) << valorTotal << InterfazMejorada::RESET << std::endl;
        std::cout << "Productos en stock normal: " << InterfazMejorada::VERDE << (productos.size() - productosStockBajo - productosStockCritico) << InterfazMejorada::RESET << std::endl;
        std::cout << "Productos con stock bajo: " << InterfazMejorada::AMARILLO << productosStockBajo << InterfazMejorada::RESET << std::endl;
        std::cout << "Productos con stock critico: " << InterfazMejorada::ROJO << productosStockCritico << InterfazMejorada::RESET << std::endl;

        if (productosStockCritico > 0 || productosStockBajo > 0)
        {
            std::cout << "\n"
                      << InterfazMejorada::ROJO << "[ATENCION REQUERIDA]" << InterfazMejorada::RESET << std::endl;
            std::cout << "Se recomienda reabastecer productos con stock bajo o critico." << std::endl;
        }

        std::ofstream reporte("reporte_inventario_detallado.txt");
        if (reporte.is_open())
        {
            reporte << "=== REPORTE DETALLADO DE INVENTARIO ===" << std::endl;
            reporte << "Fecha: " << fecha << std::endl;

            for (const auto &p : productos)
            {
                double valor_producto = p.getCantidad() * p.getPrecio();
                reporte << "ID: " << p.getId()
                        << " | Nombre: " << p.getNombre()
                        << " | Categoria: " << p.getCategoria()
                        << " | Stock: " << p.getCantidad()
                        << " | Precio: $" << std::fixed << std::setprecision(2) << p.getPrecio()
                        << " | Valor Total: $" << valor_producto;

                if (p.getCantidad() < 5)
                {
                    reporte << " | STOCK CRITICO";
                }
                else if (p.getCantidad() < 15)
                {
                    reporte << " | STOCK BAJO";
                }
                reporte << std::endl;
            }

            reporte << "\n=== RESUMEN ===" << std::endl;
            reporte << "VALOR TOTAL DEL INVENTARIO: $" << std::fixed << std::setprecision(2) << valorTotal << std::endl;
            reporte.close();

            InterfazMejorada::mostrarNotificacion("Reporte detallado guardado como: reporte_inventario_detallado.txt", "exito");
        }
    }

    void reimprimir_factura_pdf()
    {
        DisenoMejorado::crearCaja("REIMPRIMIR FACTURA COMO PDF", 70);

        if (facturas.empty())
        {
            InterfazMejorada::mostrarNotificacion("No hay facturas registradas", "advertencia");
            return;
        }

        std::vector<std::string> headers = {"No. Fact", "Fecha", "Cliente ID", "Total"};
        std::vector<int> anchos = {10, 15, 15, 15};

        DisenoMejorado::iniciarTabla(headers, anchos);

        for (const auto &f : facturas)
        {
            std::vector<std::string> fila = {
                std::to_string(f.getNumero()),
                f.getFecha().substr(0, 10), // Solo fecha, sin hora
                f.getClienteId() == 0 ? "Sin registro" : std::to_string(f.getClienteId()),
                "$" + std::to_string(static_cast<int>(f.getTotalFinal() * 100) / 100) + "." +
                    (static_cast<int>(f.getTotalFinal() * 100) % 100 < 10 ? "0" : "") +
                    std::to_string(static_cast<int>(f.getTotalFinal() * 100) % 100)};

            DisenoMejorado::filaTabla(fila, anchos);
        }

        DisenoMejorado::finalizarTabla(anchos);

        int numeroFactura = Validador::leerEnteroSeguro("\nIngrese el numero de factura a reimprimir: ", 1, 99999);

        auto it = std::find_if(facturas.begin(), facturas.end(),
                               [numeroFactura](const Factura &f)
                               { return f.getNumero() == numeroFactura; });

        if (it != facturas.end())
        {
            Cliente *cliente_info = nullptr;
            if (it->getClienteId() != 0)
            {
                auto cliente_it = std::find_if(clientes.begin(), clientes.end(),
                                               [&](const Cliente &c)
                                               { return c.getId() == it->getClienteId(); });
                if (cliente_it != clientes.end())
                {
                    cliente_info = &(*cliente_it);
                }
            }

            InterfazMejorada::mostrarCarga("Generando PDF de factura");
            if (GeneradorPDF::guardarFacturaPDF(*it, cliente_info))
            {
                InterfazMejorada::mostrarNotificacion("Factura PDF generada exitosamente!", "exito");
            }
            else
            {
                InterfazMejorada::mostrarNotificacion("Error al generar PDF de la factura", "error");
            }
        }
        else
        {
            InterfazMejorada::mostrarNotificacion("Factura no encontrada", "error");
        }
    }

    void mostrar_estadisticas()
    {
        InterfazMejorada::limpiarPantalla();
        DisenoMejorado::crearCaja("ESTADISTICAS DEL SISTEMA", 70);

        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[RESUMEN GENERAL]" << InterfazMejorada::RESET << std::endl;

        std::vector<std::string> stats_headers = {"Concepto", "Cantidad", "Observaciones"};
        std::vector<int> stats_anchos = {25, 12, 25};

        DisenoMejorado::iniciarTabla(stats_headers, stats_anchos);

        std::vector<std::string> fila_productos = {
            "Total Productos",
            std::to_string(productos.size()),
            productos.size() > 50 ? "Inventario amplio" : "Inventario normal"};
        DisenoMejorado::filaTabla(fila_productos, stats_anchos, InterfazMejorada::VERDE);

        std::vector<std::string> fila_clientes = {
            "Total Clientes",
            std::to_string(clientes.size()),
            clientes.size() > 20 ? "Base sólida" : "En crecimiento"};
        DisenoMejorado::filaTabla(fila_clientes, stats_anchos, InterfazMejorada::CYAN);

        std::vector<std::string> fila_facturas = {
            "Total Facturas",
            std::to_string(facturas.size()),
            facturas.size() > 10 ? "Buena actividad" : "Inicio de ventas"};
        DisenoMejorado::filaTabla(fila_facturas, stats_anchos, InterfazMejorada::MAGENTA);

        DisenoMejorado::finalizarTabla(stats_anchos);

        double valor_inventario = 0;
        for (const auto &p : productos)
        {
            valor_inventario += p.getCantidad() * p.getPrecio();
        }

        double total_ventas = 0;
        for (const auto &f : facturas)
        {
            total_ventas += f.getTotalFinal();
        }

        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[VALORES FINANCIEROS]" << InterfazMejorada::RESET << std::endl;
        std::cout << "Valor del inventario: " << InterfazMejorada::VERDE << "$" << std::fixed << std::setprecision(2) << valor_inventario << InterfazMejorada::RESET << std::endl;
        std::cout << "Total en ventas: " << InterfazMejorada::VERDE << "$" << std::fixed << std::setprecision(2) << total_ventas << InterfazMejorada::RESET << std::endl;

        int productos_ok = 0, productos_bajo = 0, productos_critico = 0;
        for (const auto &p : productos)
        {
            if (p.getCantidad() < 5)
                productos_critico++;
            else if (p.getCantidad() < 15)
                productos_bajo++;
            else
                productos_ok++;
        }

        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[ANALISIS DE STOCK]" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::VERDE << "Stock normal: " << productos_ok << " productos" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::AMARILLO << "Stock bajo: " << productos_bajo << " productos" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::ROJO << "Stock crítico: " << productos_critico << " productos" << InterfazMejorada::RESET << std::endl;

        if (productos_critico > 0 || productos_bajo > 0)
        {
            std::cout << "\n"
                      << InterfazMejorada::ROJO << "[RECOMENDACION]" << InterfazMejorada::RESET << std::endl;
            std::cout << "Se requiere reabastecer " << (productos_critico + productos_bajo) << " productos." << std::endl;
        }

        if (!facturas.empty())
        {
            InterfazMejorada::pausar();

            std::map<std::string, int> ventas_categoria;
            for (const auto &factura : facturas)
            {
                for (const auto &item : factura.getItems())
                {
                    auto prod_it = std::find_if(productos.begin(), productos.end(),
                                                [&item](const Producto &p)
                                                { return p.getId() == item.getProductoId(); });

                    if (prod_it != productos.end())
                    {
                        ventas_categoria[prod_it->getCategoria()] += item.getCantidad();
                    }
                }
            }

            GeneradorReportes::generarGraficoBarrasElegante(ventas_categoria, "VENTAS POR CATEGORIA");
            InterfazMejorada::pausar();

            std::map<std::string, int> productos_vendidos;
            for (const auto &factura : facturas)
            {
                for (const auto &item : factura.getItems())
                {
                    productos_vendidos[item.getNombreProducto()] += item.getCantidad();
                }
            }

            std::vector<std::pair<std::string, int>> productos_ordenados(productos_vendidos.begin(), productos_vendidos.end());
            std::sort(productos_ordenados.begin(), productos_ordenados.end(),
                      [](const auto &a, const auto &b)
                      { return a.second > b.second; });

            std::map<std::string, int> top_productos;
            for (size_t i = 0; i < std::min(size_t(10), productos_ordenados.size()); ++i)
            {
                top_productos[productos_ordenados[i].first] = productos_ordenados[i].second;
            }

            GeneradorReportes::generarGraficoBarrasElegante(top_productos, "TOP 10 PRODUCTOS MAS VENDIDOS");
        }
    }

    void mostrar_menu()
    {
        SistemaNotificaciones::verificarStockBajo(productos);
        SistemaNotificaciones::mostrarAlertas();

        MenuMejorado::mostrarMenuPrincipal();
    }

    void ejecutar()
    {
        int opcion;
        do
        {
            try
            {
                mostrar_menu();
                opcion = Validador::leerEnteroSeguro("", 0, 13);

                switch (opcion)
                {
                case 1:
                    agregar_producto();
                    break;
                case 2:
                    listar_productos();
                    break;
                case 3:
                    buscar_producto_por_codigo();
                    break;
                case 4:
                    actualizar_inventario();
                    break;
                case 5:
                    agregar_cliente();
                    break;
                case 6:
                    listar_clientes();
                    break;
                case 7:
                    crear_factura();
                    break;
                case 8:
                    generar_codigo_barras();
                    break;
                case 9:
                    generar_reporte_inventario();
                    break;
                case 10:
                    mostrar_estadisticas();
                    break;
                case 11:
                    reimprimir_factura_pdf();
                    break;
                case 12:
                    InterfazMejorada::mostrarCarga("Guardando datos");
                    guardar_datos();
                    break;
                case 13:
                    InterfazMejorada::mostrarCarga("Cargando datos");
                    cargar_datos();
                    break;
                case 0:
                    InterfazMejorada::mostrarNotificacion("Guardando datos y saliendo...", "info");
                    InterfazMejorada::mostrarCarga("Finalizando sistema");
                    guardar_datos();
                    break;
                default:
                    InterfazMejorada::mostrarNotificacion("Opcion invalida. Intente nuevamente.", "error");
                    break;
                }

                if (opcion != 0)
                {
                    InterfazMejorada::pausar();
                }
            }
            catch (const BusinessException &e)
            {
                InterfazMejorada::mostrarNotificacion("Error del negocio: " + std::string(e.what()), "error");
                InterfazMejorada::pausar();
            }
            catch (const std::exception &e)
            {
                InterfazMejorada::mostrarNotificacion("Error inesperado: " + std::string(e.what()), "error");
                InterfazMejorada::pausar();
            }

        } while (opcion != 0);
    }
};


int main()
{
    try
    {
        SistemaGestion sistema;
        sistema.ejecutar();

        std::cout << InterfazMejorada::VERDE << InterfazMejorada::NEGRITA;
        std::cout << "\n"
                  << DisenoMejorado::ESQUINA_SUP_IZQ;
        for (int i = 0; i < 66; i++)
            std::cout << DisenoMejorado::LINEA_HOR;
        std::cout << DisenoMejorado::ESQUINA_SUP_DER << std::endl;

        std::cout << DisenoMejorado::LINEA_VER << "                                                                " << DisenoMejorado::LINEA_VER << std::endl;
        std::cout << DisenoMejorado::LINEA_VER << "            " << InterfazMejorada::AMARILLO << "[EXITO] GRACIAS POR USAR EL SISTEMA!" << InterfazMejorada::VERDE << "            " << DisenoMejorado::LINEA_VER << std::endl;
        std::cout << DisenoMejorado::LINEA_VER << "                                                                " << DisenoMejorado::LINEA_VER << std::endl;
        std::cout << DisenoMejorado::LINEA_VER << "                      " << InterfazMejorada::BLANCO << "Hasta la proxima!" << InterfazMejorada::VERDE << "                       " << DisenoMejorado::LINEA_VER << std::endl;
        std::cout << DisenoMejorado::LINEA_VER << "                                                                " << DisenoMejorado::LINEA_VER << std::endl;

        std::cout << DisenoMejorado::ESQUINA_INF_IZQ;
        for (int i = 0; i < 66; i++)
            std::cout << DisenoMejorado::LINEA_HOR;
        std::cout << DisenoMejorado::ESQUINA_INF_DER << std::endl;
        std::cout << InterfazMejorada::RESET << std::endl;
    }
    catch (const std::exception &e)
    {
        InterfazMejorada::mostrarNotificacion("Error critico: " + std::string(e.what()), "error");
        return 1;
    }

    return 0;
}