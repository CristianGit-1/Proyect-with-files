#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>

using namespace std;

struct Usuario {
    int idUsuario;
    string nombre;
    string correoElectronico;
    string contrasena;
    string direccion;
    string metodoDePago;
};

struct Producto {
    int idProducto;
    string nombre;
    string descripcion;
    double precio;
    int stock;
};

struct Comentario {
    int idComentario;
    string nombreProducto; 
    string nombreUsuario; 
    string comentario;
    string fecha;
};

struct CarritoDeCompras {
    int idCarrito;
    Usuario usuario;
    vector<Producto> productos;
    double subtotal;
    double impuestos;
};

struct OrdenDeCompra {
    int idOrden;
    vector<Producto> productos;
    double subtotal;
    double impuestos;
    double envio;
    double total;
};

// Vectores globales
vector<Usuario> usuarios;
vector<Producto> productos;
vector<Comentario> comentarios;
vector<CarritoDeCompras> carritos;

// Función para dividir strings por comas
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Cargar usuarios desde archivo
void cargarUsuarios() {
    ifstream archivo("Usuarios.txt");
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo Usuarios.txt" << endl;
        return;
    }

    string linea;
    // Saltar la primera línea (cabecera)
    getline(archivo, linea);
    
    while (getline(archivo, linea)) {
        vector<string> datos = split(linea, ',');
        if (datos.size() >= 6) {
            Usuario usuario;
            usuario.idUsuario = stoi(datos[0]);
            usuario.nombre = datos[1];
            usuario.correoElectronico = datos[2];
            usuario.contrasena = datos[3];
            usuario.direccion = datos[4];
            usuario.metodoDePago = datos[5];
            usuarios.push_back(usuario);
        }
    }
    archivo.close();
    cout << "Usuarios cargados: " << usuarios.size() << endl;
}

// Cargar productos desde archivo
void cargarProductos() {
    ifstream archivo("Productos.txt");
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo Productos.txt" << endl;
        return;
    }

    string linea;
    // Saltar la primera línea (cabecera)
    getline(archivo, linea);
    
    while (getline(archivo, linea)) {
        vector<string> datos = split(linea, ',');
        if (datos.size() >= 5) {
            Producto producto;
            producto.idProducto = stoi(datos[0]);
            producto.nombre = datos[1];
            producto.descripcion = datos[2];
            producto.precio = stod(datos[3]);
            producto.stock = stoi(datos[4]);
            productos.push_back(producto);
        }
    }
    archivo.close();
    cout << "Productos cargados: " << productos.size() << endl;
}
