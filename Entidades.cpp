#include "Entidades.h"
#include <sstream>

Entidad::Entidad() : id(0) {}
Entidad::Entidad(int _id) : id(_id) {}

int Entidad::getId() const { return id; }
void Entidad::setId(int _id) { id = _id; }

Producto::Producto() : Entidad(), precio(0.0), cantidad(0), exento_iva(false) {}

Producto::Producto(int id, const std::string &nom, const std::string &cat,
                   double prec, int cant, bool exento, const std::string &orig)
    : Entidad(id), nombre(nom), categoria(cat), precio(prec),
      cantidad(cant), exento_iva(exento), origen(orig) {}

const std::string &Producto::getNombre() const { return nombre; }
const std::string &Producto::getCategoria() const { return categoria; }
double Producto::getPrecio() const { return precio; }
int Producto::getCantidad() const { return cantidad; }
bool Producto::isExentoIva() const { return exento_iva; }
const std::string &Producto::getOrigen() const { return origen; }

void Producto::setNombre(const std::string &nom) { nombre = nom; }
void Producto::setCategoria(const std::string &cat) { categoria = cat; }
void Producto::setPrecio(double prec) { precio = prec; }
void Producto::setCantidad(int cant) { cantidad = cant; }
void Producto::setExentoIva(bool exento) { exento_iva = exento; }
void Producto::setOrigen(const std::string &orig) { origen = orig; }

Producto &Producto::operator=(const Producto &other)
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

bool Producto::operator==(const Producto &other) const
{
    return id == other.id;
}

std::string Producto::toString() const
{
    std::ostringstream oss;
    oss << id << "|" << nombre << "|" << categoria << "|"
        << precio << "|" << cantidad << "|" << exento_iva << "|" << origen;
    return oss.str();
}

void Producto::fromString(const std::string &data)
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

Cliente::Cliente() : Entidad(), puntos(0.0) {}

Cliente::Cliente(int id, const std::string &nom, double pts)
    : Entidad(id), nombre(nom), puntos(pts) {}

const std::string &Cliente::getNombre() const { return nombre; }
double Cliente::getPuntos() const { return puntos; }
void Cliente::setNombre(const std::string &nom) { nombre = nom; }
void Cliente::setPuntos(double pts) { puntos = pts; }
void Cliente::agregarPuntos(double pts) { puntos += pts; }

bool Cliente::usarPuntos(double pts)
{
    if (pts <= puntos)
    {
        puntos -= pts;
        return true;
    }
    return false;
}

std::string Cliente::toString() const
{
    std::ostringstream oss;
    oss << id << "|" << nombre << "|" << puntos;
    return oss.str();
}

void Cliente::fromString(const std::string &data)
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

ItemFactura::ItemFactura() : producto_id(0), cantidad(0), precio_unitario(0.0), exento_iva(false) {}

ItemFactura::ItemFactura(int prod_id, const std::string &nombre, int cant, double precio, bool exento)
    : producto_id(prod_id), nombre_producto(nombre), cantidad(cant),
      precio_unitario(precio), exento_iva(exento) {}

int ItemFactura::getProductoId() const { return producto_id; }
const std::string &ItemFactura::getNombreProducto() const { return nombre_producto; }
int ItemFactura::getCantidad() const { return cantidad; }
double ItemFactura::getPrecioUnitario() const { return precio_unitario; }
bool ItemFactura::isExentoIva() const { return exento_iva; }

double ItemFactura::getSubtotal() const
{
    return cantidad * precio_unitario;
}

std::string ItemFactura::toString() const
{
    std::ostringstream oss;
    oss << producto_id << "|" << nombre_producto << "|" << cantidad
        << "|" << precio_unitario << "|" << exento_iva;
    return oss.str();
}

Factura::Factura() : numero(0), cliente_id(0), puntos_usados(0.0), descuento_carnes(0.0) {}

Factura::Factura(int num, int cli_id, const std::string &fech)
    : numero(num), cliente_id(cli_id), fecha(fech), puntos_usados(0.0), descuento_carnes(0.0) {}

int Factura::getNumero() const { return numero; }
int Factura::getClienteId() const { return cliente_id; }
const std::string &Factura::getFecha() const { return fecha; }
const std::vector<ItemFactura> &Factura::getItems() const { return items; }
double Factura::getPuntosUsados() const { return puntos_usados; }
double Factura::getDescuentoCarnes() const { return descuento_carnes; }

void Factura::setNumero(int num) { numero = num; }
void Factura::setClienteId(int cli_id) { cliente_id = cli_id; }
void Factura::setFecha(const std::string &fech) { fecha = fech; }
void Factura::setPuntosUsados(double puntos) { puntos_usados = puntos; }
void Factura::setDescuentoCarnes(double descuento) { descuento_carnes = descuento; }

void Factura::agregarItem(const ItemFactura &item)
{
    items.push_back(item);
}

double Factura::getSubtotalSinIva() const
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

double Factura::getSubtotalConIva() const
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

double Factura::getIvaTotal() const
{
    return getSubtotalConIva() * 0.19;
}

double Factura::getTotalFinal() const
{
    return getSubtotalSinIva() + getSubtotalConIva() + getIvaTotal() - puntos_usados - descuento_carnes;
}