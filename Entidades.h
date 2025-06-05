#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <string>
#include <vector>

// Clase base para entidades
class Entidad
{
protected:
    int id;

public:
    Entidad();
    Entidad(int _id);
    virtual ~Entidad() = default;

    int getId() const;
    void setId(int _id);

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
    Producto();
    Producto(int id, const std::string &nom, const std::string &cat,
             double prec, int cant, bool exento = false, const std::string &orig = "");

    // Getters
    const std::string &getNombre() const;
    const std::string &getCategoria() const;
    double getPrecio() const;
    int getCantidad() const;
    bool isExentoIva() const;
    const std::string &getOrigen() const;

    // Setters
    void setNombre(const std::string &nom);
    void setCategoria(const std::string &cat);
    void setPrecio(double prec);
    void setCantidad(int cant);
    void setExentoIva(bool exento);
    void setOrigen(const std::string &orig);

    // Operadores
    Producto &operator=(const Producto &other);
    bool operator==(const Producto &other) const;

    // Polimorfismo virtual
    std::string toString() const override;
    void fromString(const std::string &data) override;
};

// Clase Cliente
class Cliente : public Entidad
{
private:
    std::string nombre;
    double puntos;

public:
    Cliente();
    Cliente(int id, const std::string &nom, double pts = 0.0);

    // Getters y Setters
    const std::string &getNombre() const;
    double getPuntos() const;
    void setNombre(const std::string &nom);
    void setPuntos(double pts);
    void agregarPuntos(double pts);
    bool usarPuntos(double pts);

    std::string toString() const override;
    void fromString(const std::string &data) override;
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
    ItemFactura();
    ItemFactura(int prod_id, const std::string &nombre, int cant, double precio, bool exento);

    // Getters
    int getProductoId() const;
    const std::string &getNombreProducto() const;
    int getCantidad() const;
    double getPrecioUnitario() const;
    bool isExentoIva() const;
    double getSubtotal() const;

    std::string toString() const;
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
    Factura();
    Factura(int num, int cli_id, const std::string &fech);

    // Getters y Setters
    int getNumero() const;
    int getClienteId() const;
    const std::string &getFecha() const;
    const std::vector<ItemFactura> &getItems() const;
    double getPuntosUsados() const;
    double getDescuentoCarnes() const;

    void setNumero(int num);
    void setClienteId(int cli_id);
    void setFecha(const std::string &fech);
    void setPuntosUsados(double puntos);
    void setDescuentoCarnes(double descuento);

    void agregarItem(const ItemFactura &item);

    double getSubtotalSinIva() const;
    double getSubtotalConIva() const;
    double getIvaTotal() const;
    double getTotalFinal() const;
};

#endif // ENTIDADES_H