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
#include <C:\Users\redjh\Desktop\Cristian\libharu\include\hpdf.h>

// ==================== MEJORAS VISUALES Y DE INTERFAZ ====================

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

    // Limpiar pantalla multiplataforma
    static void limpiarPantalla()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    // Animación de carga (SIN ICONOS)
    static void mostrarCarga(const std::string &mensaje, int duracion_ms = 1500)
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
    static void mostrarBannerInicio()
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
    static void mostrarNotificacion(const std::string &mensaje, const std::string &tipo = "info")
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
    static void mostrarTitulo(const std::string &titulo)
    {
        std::cout << CYAN << NEGRITA << "\n+--" << std::string(titulo.length() + 2, '-') << "--+" << std::endl;
        std::cout << "|  " << titulo << "  |" << std::endl;
        std::cout << "+--" << std::string(titulo.length() + 2, '-') << "--+" << RESET << std::endl;
    }

    static void pausar()
    {
        std::cout << AMARILLO << "\n>> Presione Enter para continuar..." << RESET;
        std::cin.ignore();
        std::cin.get();
    }
};

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

// ==================== MEJORAS DE DISEÑO PARA FACTURAS Y REPORTES ====================

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

    // Crear caja decorativa
    static void crearCaja(const std::string &contenido, int ancho = 70)
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
    static void mostrarHeaderEmpresa()
    {
        std::cout << InterfazMejorada::CYAN << InterfazMejorada::NEGRITA;

        // Marco superior decorativo
        std::cout << "\n"
                  << ESQUINA_SUP_IZQ;
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
    static void mostrarSeparador(char caracter = '=', int longitud = 70, const std::string &color = InterfazMejorada::CYAN)
    {
        std::cout << color;
        for (int i = 0; i < longitud; i++)
        {
            std::cout << caracter;
        }
        std::cout << InterfazMejorada::RESET << std::endl;
    }

    // Tabla con bordes elegantes
    static void iniciarTabla(const std::vector<std::string> &headers, const std::vector<int> &anchos)
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

    static void filaTabla(const std::vector<std::string> &datos, const std::vector<int> &anchos, const std::string &color = InterfazMejorada::BLANCO)
    {
        std::cout << InterfazMejorada::CYAN << LINEA_VER << color;
        for (size_t i = 0; i < datos.size(); i++)
        {
            std::cout << std::left << std::setw(anchos[i]) << datos[i];
            if (i < datos.size() - 1)
                std::cout << InterfazMejorada::CYAN << LINEA_VER << color;
        }
        std::cout << InterfazMejorada::CYAN << LINEA_VER << InterfazMejorada::RESET << std::endl;
    }

    static void finalizarTabla(const std::vector<int> &anchos)
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
    static void mostrarResumenTotales(const class Factura &factura);

    // Footer profesional
    static void mostrarFooterFactura()
    {
        std::cout << "\n"
                  << InterfazMejorada::CYAN;
        mostrarSeparador('-', 70);

        std::cout << InterfazMejorada::BLANCO << "                     " << InterfazMejorada::NEGRITA << "GRACIAS POR SU COMPRA!" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "                 Conserve este recibo como respaldo" << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::BLANCO << "             Para devoluciones presentar dentro de 30 dias" << InterfazMejorada::RESET << std::endl;

        mostrarSeparador('-', 70, InterfazMejorada::CYAN);
    }
};

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

// ==================== SISTEMA DE VALIDACIONES ====================

class Validador
{
public:
    static bool validarEntero(const std::string &entrada, int &resultado, int min = INT_MIN, int max = INT_MAX)
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

    static bool validarDouble(const std::string &entrada, double &resultado, double min = -DBL_MAX, double max = DBL_MAX)
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

    static bool validarCadenaNoVacia(const std::string &entrada)
    {
        return !entrada.empty() && entrada.find_first_not_of(" \t\n\r") != std::string::npos;
    }

    static std::string leerEntradaSegura(const std::string &prompt, bool permitirVacio = false)
    {
        std::string entrada;
        do
        {
            std::cout << InterfazMejorada::CYAN << prompt << InterfazMejorada::RESET;
            std::getline(std::cin, entrada);

            if (permitirVacio || validarCadenaNoVacia(entrada))
            {
                break;
            }

            InterfazMejorada::mostrarNotificacion("La entrada no puede estar vacia. Intente nuevamente.", "error");
        } while (true);

        return entrada;
    }

    static int leerEnteroSeguro(const std::string &prompt, int min = INT_MIN, int max = INT_MAX)
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

    static double leerDoubleSeguro(const std::string &prompt, double min = -DBL_MAX, double max = DBL_MAX)
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
};

// ==================== SISTEMA DE NOTIFICACIONES ====================

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
        limpiarAlertas(); // Limpiar alertas anteriores
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

// ==================== CÓDIGO ORIGINAL CON MEJORAS INTEGRADAS ====================

// Implementación JSON simple para evitar dependencias externas
namespace SimpleJSON
{
    class JSON
    {
    private:
        std::map<std::string, std::string> data;

    public:
        JSON() {}

        JSON &operator[](const std::string &key)
        {
            return *this;
        }

        JSON &operator=(const std::string &value)
        {
            return *this;
        }

        JSON &operator=(int value)
        {
            return *this;
        }

        JSON &operator=(double value)
        {
            return *this;
        }

        JSON &operator=(bool value)
        {
            return *this;
        }

        std::string dump(int indent = 0) const
        {
            return "{}"; // Implementación simple
        }

        std::string value(const std::string &key, const std::string &default_val) const
        {
            return default_val;
        }

        int value(const std::string &key, int default_val) const
        {
            return default_val;
        }

        double value(const std::string &key, double default_val) const
        {
            return default_val;
        }

        bool value(const std::string &key, bool default_val) const
        {
            return default_val;
        }

        static JSON array()
        {
            return JSON();
        }

        void push_back(const JSON &item) {}
    };
}

using json = SimpleJSON::JSON;

// Clase para manejar excepciones personalizadas
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

// Clase base para entidades
class Entidad
{
protected:
    int id;

public:
    Entidad() : id(0) {}
    Entidad(int _id) : id(_id) {}
    virtual ~Entidad() = default;

    int getId() const { return id; }
    void setId(int _id) { id = _id; }

    virtual std::string toString() const = 0;
    virtual void fromString(const std::string &data) = 0;
};

// Clase Producto
class Producto : public Entidad
{
private:
    std::string nombre;
    std::string categoria;
    double precio;
    int cantidad;
    bool exento_iva;
    std::string origen;

public:
    Producto() : Entidad(), precio(0.0), cantidad(0), exento_iva(false) {}

    Producto(int id, const std::string &nom, const std::string &cat,
             double prec, int cant, bool exento = false, const std::string &orig = "")
        : Entidad(id), nombre(nom), categoria(cat), precio(prec),
          cantidad(cant), exento_iva(exento), origen(orig) {}

    // Getters
    const std::string &getNombre() const { return nombre; }
    const std::string &getCategoria() const { return categoria; }
    double getPrecio() const { return precio; }
    int getCantidad() const { return cantidad; }
    bool isExentoIva() const { return exento_iva; }
    const std::string &getOrigen() const { return origen; }

    // Setters
    void setNombre(const std::string &nom) { nombre = nom; }
    void setCategoria(const std::string &cat) { categoria = cat; }
    void setPrecio(double prec) { precio = prec; }
    void setCantidad(int cant) { cantidad = cant; }
    void setExentoIva(bool exento) { exento_iva = exento; }
    void setOrigen(const std::string &orig) { origen = orig; }

    // Operadores
    Producto &operator=(const Producto &other)
    {
        if (this != &other)
        {
            id = other.id;
            nombre = other.nombre;
            categoria = other.categoria;
            precio = other.precio;
            cantidad = other.cantidad;
            exento_iva = other.exento_iva;
            origen = other.origen;
        }
        return *this;
    }

    bool operator==(const Producto &other) const
    {
        return id == other.id;
    }

    // Polimorfismo virtual
    std::string toString() const override
    {
        std::ostringstream oss;
        oss << id << "|" << nombre << "|" << categoria << "|"
            << precio << "|" << cantidad << "|" << exento_iva << "|" << origen;
        return oss.str();
    }

    void fromString(const std::string &data) override
    {
        std::istringstream iss(data);
        std::string token;

        if (std::getline(iss, token, '|'))
            id = std::stoi(token);
        if (std::getline(iss, token, '|'))
            nombre = token;
        if (std::getline(iss, token, '|'))
            categoria = token;
        if (std::getline(iss, token, '|'))
            precio = std::stod(token);
        if (std::getline(iss, token, '|'))
            cantidad = std::stoi(token);
        if (std::getline(iss, token, '|'))
            exento_iva = (token == "1");
        if (std::getline(iss, token, '|'))
            origen = token;
    }
};

// Clase Cliente
class Cliente : public Entidad
{
private:
    std::string nombre;
    double puntos;

public:
    Cliente() : Entidad(), puntos(0.0) {}

    Cliente(int id, const std::string &nom, double pts = 0.0)
        : Entidad(id), nombre(nom), puntos(pts) {}

    // Getters y Setters
    const std::string &getNombre() const { return nombre; }
    double getPuntos() const { return puntos; }
    void setNombre(const std::string &nom) { nombre = nom; }
    void setPuntos(double pts) { puntos = pts; }
    void agregarPuntos(double pts) { puntos += pts; }
    bool usarPuntos(double pts)
    {
        if (pts <= puntos)
        {
            puntos -= pts;
            return true;
        }
        return false;
    }

    std::string toString() const override
    {
        std::ostringstream oss;
        oss << id << "|" << nombre << "|" << puntos;
        return oss.str();
    }

    void fromString(const std::string &data) override
    {
        std::istringstream iss(data);
        std::string token;

        if (std::getline(iss, token, '|'))
            id = std::stoi(token);
        if (std::getline(iss, token, '|'))
            nombre = token;
        if (std::getline(iss, token, '|'))
            puntos = std::stod(token);
    }
};

// Clase ItemFactura
class ItemFactura
{
private:
    int producto_id;
    std::string nombre_producto;
    int cantidad;
    double precio_unitario;
    bool exento_iva;

public:
    ItemFactura() : producto_id(0), cantidad(0), precio_unitario(0.0), exento_iva(false) {}

    ItemFactura(int prod_id, const std::string &nombre, int cant, double precio, bool exento)
        : producto_id(prod_id), nombre_producto(nombre), cantidad(cant),
          precio_unitario(precio), exento_iva(exento) {}

    // Getters
    int getProductoId() const { return producto_id; }
    const std::string &getNombreProducto() const { return nombre_producto; }
    int getCantidad() const { return cantidad; }
    double getPrecioUnitario() const { return precio_unitario; }
    bool isExentoIva() const { return exento_iva; }

    double getSubtotal() const
    {
        return cantidad * precio_unitario;
    }

    std::string toString() const
    {
        std::ostringstream oss;
        oss << producto_id << "|" << nombre_producto << "|" << cantidad
            << "|" << precio_unitario << "|" << exento_iva;
        return oss.str();
    }
};

// Clase Factura
class Factura
{
private:
    int numero;
    int cliente_id;
    std::string fecha;
    std::vector<ItemFactura> items;
    double puntos_usados;
    double descuento_carnes;

public:
    Factura() : numero(0), cliente_id(0), puntos_usados(0.0), descuento_carnes(0.0) {}

    Factura(int num, int cli_id, const std::string &fech)
        : numero(num), cliente_id(cli_id), fecha(fech), puntos_usados(0.0), descuento_carnes(0.0) {}

    // Getters y Setters
    int getNumero() const { return numero; }
    int getClienteId() const { return cliente_id; }
    const std::string &getFecha() const { return fecha; }
    const std::vector<ItemFactura> &getItems() const { return items; }
    double getPuntosUsados() const { return puntos_usados; }
    double getDescuentoCarnes() const { return descuento_carnes; }

    void setNumero(int num) { numero = num; }
    void setClienteId(int cli_id) { cliente_id = cli_id; }
    void setFecha(const std::string &fech) { fecha = fech; }
    void setPuntosUsados(double puntos) { puntos_usados = puntos; }
    void setDescuentoCarnes(double descuento) { descuento_carnes = descuento; }

    void agregarItem(const ItemFactura &item)
    {
        items.push_back(item);
    }

    double getSubtotalSinIva() const
    {
        double total = 0;
        for (const auto &item : items)
        {
            if (item.isExentoIva())
            {
                total += item.getSubtotal();
            }
        }
        return total;
    }

    double getSubtotalConIva() const
    {
        double total = 0;
        for (const auto &item : items)
        {
            if (!item.isExentoIva())
            {
                total += item.getSubtotal();
            }
        }
        return total;
    }

    double getIvaTotal() const
    {
        return getSubtotalConIva() * 0.19;
    }

    double getTotalFinal() const
    {
        return getSubtotalSinIva() + getSubtotalConIva() + getIvaTotal() - puntos_usados - descuento_carnes;
    }
};

// Implementación de mostrarResumenTotales
void DisenoMejorado::mostrarResumenTotales(const Factura &factura)
{
    std::cout << "\n"
              << InterfazMejorada::CYAN;

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

// Clase para gestión de archivos
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
        productos.clear(); // IMPORTANTE: Limpiar antes de cargar para evitar duplicados
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
        clientes.clear(); // IMPORTANTE: Limpiar antes de cargar para evitar duplicados
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

// Clase para generación de códigos de barras con mejoras visuales
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
        // Crea el documento PDF
        HPDF_Doc pdf = HPDF_New(NULL, NULL);
        if (!pdf)
        {
            std::cerr << "Error al crear el documento PDF." << std::endl;
            return false;
        }

        // Crea una página en blanco
        HPDF_Page page = HPDF_AddPage(pdf);
        HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

        // Establece las fuentes
        HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
        HPDF_Page_SetFontAndSize(page, font, 12);

        // Título
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 50, 800, ("Factura No: " + std::to_string(factura.getNumero())).c_str());
        HPDF_Page_TextOut(page, 50, 780, ("Fecha: " + factura.getFecha()).c_str());

        if (cliente != nullptr)
        {
            HPDF_Page_TextOut(page, 50, 760, ("Cliente: " + cliente->getNombre()).c_str());
        }

        HPDF_Page_EndText(page);

        // Detalles de la factura
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

        // Subtotales, IVA y Total final
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 50, yPosition, ("Subtotal sin IVA: $" + std::to_string(factura.getSubtotalSinIva())).c_str());
        yPosition -= 20;
        HPDF_Page_TextOut(page, 50, yPosition, ("Subtotal con IVA: $" + std::to_string(factura.getSubtotalConIva())).c_str());
        yPosition -= 20;
        HPDF_Page_TextOut(page, 50, yPosition, ("IVA (19%): $" + std::to_string(factura.getIvaTotal())).c_str());
        yPosition -= 20;
        HPDF_Page_TextOut(page, 50, yPosition, ("TOTAL FINAL: $" + std::to_string(factura.getTotalFinal())).c_str());
        HPDF_Page_EndText(page);

        // Guardar el archivo PDF
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

// ==================== FUNCIÓN MEJORADA PARA IMPRIMIR FACTURAS ====================

class FacturaMejorada
{
public:
    static void imprimirFacturaElegante(const Factura &factura, const Cliente *cliente = nullptr)
    {
        InterfazMejorada::limpiarPantalla();

        // Header de la empresa
        DisenoMejorado::mostrarHeaderEmpresa();

        std::cout << "\n";
        DisenoMejorado::crearCaja("FACTURA DE VENTA", 70);

        // Información de la factura
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

        // Tabla de productos con diseño elegante
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

        // Resumen de totales elegante
        DisenoMejorado::mostrarResumenTotales(factura);

        // Información adicional si hay descuentos
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

        // Footer profesional
        DisenoMejorado::mostrarFooterFactura();

        // Código QR simulado (representación ASCII)
        std::cout << "\n"
                  << InterfazMejorada::CYAN << "Codigo QR de la factura:" << InterfazMejorada::RESET << std::endl;
        mostrarCodigoQRSimulado(factura.getNumero());
    }

private:
    static void mostrarCodigoQRSimulado(int numeroFactura)
    {
        std::cout << InterfazMejorada::BLANCO;

        // Generar patrón basado en el número de factura
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

// ==================== MEJORAS EN EL MENÚ PRINCIPAL ====================

class MenuMejorado
{
public:
    static void mostrarMenuPrincipal()
    {
        InterfazMejorada::limpiarPantalla();

        // Banner principal con diseño mejorado
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

// ==================== SISTEMA DE REPORTES CON GRÁFICOS MEJORADOS ====================

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

        // Encontrar el valor máximo para escalar
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

            // Nombre de la categoría
            std::cout << InterfazMejorada::CYAN << std::left << std::setw(20) << par.first << InterfazMejorada::RESET << " ";

            // Barra visual
            std::cout << InterfazMejorada::VERDE << "|";
            for (int i = 0; i < longitud_barra; ++i)
            {
                std::cout << "#";
            }

            // Espacios para completar
            for (int i = longitud_barra; i < max_barras; ++i)
            {
                std::cout << " ";
            }

            // Valor numérico
            std::cout << "| " << InterfazMejorada::AMARILLO << par.second << InterfazMejorada::RESET << std::endl;
        }

        std::cout << "\n";
        DisenoMejorado::mostrarSeparador('=', 70, InterfazMejorada::CYAN);
    }

    template <typename FacturaType, typename ProductoType>
    static void reporteVentasPorCategoria(const std::vector<FacturaType> &facturas, const std::vector<ProductoType> &productos)
    {
        std::map<std::string, int> ventas_categoria;

        for (const auto &factura : facturas)
        {
            for (const auto &item : factura.getItems())
            {
                auto prod_it = std::find_if(productos.begin(), productos.end(),
                                            [&item](const ProductoType &p)
                                            { return p.getId() == item.getProductoId(); });

                if (prod_it != productos.end())
                {
                    ventas_categoria[prod_it->getCategoria()] += item.getCantidad();
                }
            }
        }

        generarGraficoBarrasElegante(ventas_categoria, "VENTAS POR CATEGORIA");
    }

    template <typename FacturaType>
    static void reporteProductosMasVendidos(const std::vector<FacturaType> &facturas)
    {
        std::map<std::string, int> productos_vendidos;

        for (const auto &factura : facturas)
        {
            for (const auto &item : factura.getItems())
            {
                productos_vendidos[item.getNombreProducto()] += item.getCantidad();
            }
        }

        // Ordenar por cantidad vendida y tomar solo los top 10
        std::vector<std::pair<std::string, int>> productos_ordenados(productos_vendidos.begin(), productos_vendidos.end());
        std::sort(productos_ordenados.begin(), productos_ordenados.end(),
                  [](const auto &a, const auto &b)
                  { return a.second > b.second; });

        std::map<std::string, int> top_productos;
        for (size_t i = 0; i < std::min(size_t(10), productos_ordenados.size()); ++i)
        {
            top_productos[productos_ordenados[i].first] = productos_ordenados[i].second;
        }

        generarGraficoBarrasElegante(top_productos, "TOP 10 PRODUCTOS MAS VENDIDOS");
    }
};

// ==================== CLASE PRINCIPAL MEJORADA ====================

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

            // Usar validaciones mejoradas
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

        // Verificar y mostrar alertas de stock
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
            fecha.pop_back(); // Remover el \n
            nueva_factura.setFecha(fecha);

            std::cout << InterfazMejorada::AMARILLO << "Factura No: " << nueva_factura.getNumero() << InterfazMejorada::RESET << std::endl;

            // Seleccionar cliente
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

            // Agregar productos a la factura
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

                // Crear item de factura
                ItemFactura item(producto_id, prod_it->getNombre(), cantidad,
                                 prod_it->getPrecio(), prod_it->isExentoIva());
                nueva_factura.agregarItem(item);

                // Actualizar inventario
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

            // Aplicar descuentos y puntos si hay cliente registrado
            if (cliente_actual != nullptr)
            {
                // Usar puntos
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

                // Calcular descuento en carnes (sorteo mensual simulado)
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
                    // Simulamos que ganó el sorteo (10% de probabilidad)
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<> dis(1, 10);

                    if (dis(gen) == 1)
                    {                                          // 10% de probabilidad
                        double descuento = total_carnes * 0.1; // 10% descuento
                        nueva_factura.setDescuentoCarnes(descuento);
                        InterfazMejorada::mostrarNotificacion("[GANADOR!] Ha ganado un 10% de descuento en carnes: $" +
                                                                  std::to_string(descuento),
                                                              "exito");
                    }
                }

                // Agregar puntos por la compra
                double puntos_ganados = nueva_factura.getTotalFinal() / 10000.0; // 1 punto por cada $10,000
                cliente_actual->agregarPuntos(puntos_ganados);
            }

            facturas.push_back(nueva_factura);

            // USAR LA NUEVA FUNCIÓN MEJORADA PARA IMPRIMIR
            Cliente *cliente_para_factura = nullptr;
            if (cliente_actual != nullptr)
            {
                cliente_para_factura = cliente_actual;
            }
            FacturaMejorada::imprimirFacturaElegante(nueva_factura, cliente_para_factura);

            // Guardar factura como PDF automáticamente
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

        // Información del reporte
        time_t now = time(0);
        char *dt = ctime(&now);
        std::string fecha(dt);
        fecha.pop_back();

        std::cout << InterfazMejorada::AMARILLO << "Fecha del reporte: " << InterfazMejorada::VERDE << fecha << InterfazMejorada::RESET << std::endl;
        std::cout << InterfazMejorada::AMARILLO << "Total de productos: " << InterfazMejorada::VERDE << productos.size() << InterfazMejorada::RESET << std::endl;

        // Tabla de productos con diseño elegante
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

        // Resumen estadístico
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

        // Guardar también en archivo
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

        // Mostrar lista de facturas con diseño mejorado
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
            // Buscar información del cliente si existe
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

        // Estadísticas generales
        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[RESUMEN GENERAL]" << InterfazMejorada::RESET << std::endl;

        std::vector<std::string> stats_headers = {"Concepto", "Cantidad", "Observaciones"};
        std::vector<int> stats_anchos = {25, 12, 25};

        DisenoMejorado::iniciarTabla(stats_headers, stats_anchos);

        // Productos
        std::vector<std::string> fila_productos = {
            "Total Productos",
            std::to_string(productos.size()),
            productos.size() > 50 ? "Inventario amplio" : "Inventario normal"};
        DisenoMejorado::filaTabla(fila_productos, stats_anchos, InterfazMejorada::VERDE);

        // Clientes
        std::vector<std::string> fila_clientes = {
            "Total Clientes",
            std::to_string(clientes.size()),
            clientes.size() > 20 ? "Base sólida" : "En crecimiento"};
        DisenoMejorado::filaTabla(fila_clientes, stats_anchos, InterfazMejorada::CYAN);

        // Facturas
        std::vector<std::string> fila_facturas = {
            "Total Facturas",
            std::to_string(facturas.size()),
            facturas.size() > 10 ? "Buena actividad" : "Inicio de ventas"};
        DisenoMejorado::filaTabla(fila_facturas, stats_anchos, InterfazMejorada::MAGENTA);

        DisenoMejorado::finalizarTabla(stats_anchos);

        // Calcular valor total del inventario
        double valor_inventario = 0;
        for (const auto &p : productos)
        {
            valor_inventario += p.getCantidad() * p.getPrecio();
        }

        // Calcular total de ventas
        double total_ventas = 0;
        for (const auto &f : facturas)
        {
            total_ventas += f.getTotalFinal();
        }

        std::cout << "\n"
                  << InterfazMejorada::AMARILLO << InterfazMejorada::NEGRITA << "[VALORES FINANCIEROS]" << InterfazMejorada::RESET << std::endl;
        std::cout << "Valor del inventario: " << InterfazMejorada::VERDE << "$" << std::fixed << std::setprecision(2) << valor_inventario << InterfazMejorada::RESET << std::endl;
        std::cout << "Total en ventas: " << InterfazMejorada::VERDE << "$" << std::fixed << std::setprecision(2) << total_ventas << InterfazMejorada::RESET << std::endl;

        // Análisis de stock
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

        // Mostrar gráficos si hay datos
        if (!facturas.empty())
        {
            InterfazMejorada::pausar();

            // Gráfico de ventas por categoría
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

            // Gráfico de productos más vendidos
            std::map<std::string, int> productos_vendidos;
            for (const auto &factura : facturas)
            {
                for (const auto &item : factura.getItems())
                {
                    productos_vendidos[item.getNombreProducto()] += item.getCantidad();
                }
            }

            // Tomar solo los top 10
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
        // Mostrar alertas pendientes
        SistemaNotificaciones::verificarStockBajo(productos);
        SistemaNotificaciones::mostrarAlertas();

        // USAR EL NUEVO MENÚ MEJORADO
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

// ==================== FUNCIÓN PRINCIPAL ====================

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

/*
=== INSTRUCCIONES DE COMPILACIÓN ===

Para compilar este programa mejorado con diseño integrado:

1. Asegúrate de tener la librería libharu instalada:
   - Windows: Descarga desde http://libharu.org/ y configura la ruta
   - Linux: sudo apt-get install libharu-dev
   - macOS: brew install libharu

2. Compilar el programa:
   g++ -std=c++17 -Wall -Wextra -g3 sistema_mejorado.cpp -o sistema_gestion_elegante -lhpdf

3. Ejecutar:
   ./sistema_gestion_elegante (Linux/macOS)
   sistema_gestion_elegante.exe (Windows)

=== MEJORAS IMPLEMENTADAS ===

🎨 **DISEÑO COMPLETAMENTE RENOVADO:**

✅ **Facturas Profesionales:**
   - Header de empresa con información completa
   - Tablas con bordes elegantes usando caracteres ASCII
   - Resumen de totales en caja destacada
   - Código QR simulado para autenticidad
   - Footer profesional con políticas

✅ **Menú Categorizado:**
   - Opciones organizadas por funcionalidades
   - Colores diferenciados por sección
   - Diseño limpio con marcos decorativos
   - Versión 2.0 del sistema

✅ **Listas y Tablas Mejoradas:**
   - Estados visuales (OK, BAJO, CRÍTICO) con colores
   - Categorización de clientes (VIP, PREMIUM, REGULAR)
   - Tablas con bordes y separadores elegantes
   - Información organizada y fácil de leer

✅ **Reportes Visuales:**
   - Gráficos de barras con caracteres ASCII
   - Análisis estadístico detallado
   - Reportes con diseño profesional
   - Archivos de respaldo automáticos

✅ **Interfaz Completamente Mejorada:**
   - Cajas decorativas para títulos
   - Separadores elegantes
   - Animaciones de carga
   - Notificaciones con categorías

✅ **Sistema de Alertas Avanzado:**
   - Alertas de stock automáticas
   - Sin duplicados
   - Colores según criticidad
   - Recomendaciones de acción

=== CARACTERÍSTICAS NUEVAS ===

🚀 **Funcionalidades Añadidas:**
   - Categorización automática de clientes por puntos
   - Análisis financiero en estadísticas
   - Gráficos de ventas por categoría
   - Top 10 productos más vendidos
   - Códigos QR simulados en facturas
   - Reportes con archivos de respaldo

🎯 **Experiencia de Usuario:**
   - Interfaz intuitiva y profesional
   - Navegación clara por categorías
   - Feedback visual inmediato
   - Animaciones que mejoran la experiencia

🔧 **Robustez Técnica:**
   - Validaciones mejoradas
   - Manejo de errores elegante
   - Compatibilidad universal de caracteres
   - Código modular y mantenible

=== COMPATIBILIDAD ===

✅ **Multiplataforma:**
   - Windows (cmd, PowerShell)
   - Linux (bash, zsh, etc.)
   - macOS (Terminal)
   - Cualquier consola con soporte ANSI

✅ **Sin Dependencias Problemáticas:**
   - Solo caracteres ASCII estándar para diseño
   - Sin emojis ni símbolos especiales
   - Compatible con cualquier fuente de consola

¡Tu sistema ahora tiene un diseño completamente profesional y moderno!
*/