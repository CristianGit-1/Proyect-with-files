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

// Funci√≥n para dividir strings por comas
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
    // Saltar la primera l√≠nea (cabecera)
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
    // Saltar la primera l√≠nea (cabecera)
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
void cargarComentarios() {
    ifstream archivo("Comentarios.txt", ios::in);
    if (!archivo) {
        cout << "Error: No se pudo abrir el archivo Comentarios.txt" << endl;
        return;
    }

    string linea;
    // Saltar la primera linea (cabecera)
    getline(archivo, linea);
    
    while (getline(archivo, linea)) {
        vector<string> datos = split(linea, ',');
        if (datos.size() >= 5) {
            try {
                Comentario comentario;
                comentario.idComentario = stoi(datos[0]);
                comentario.nombreProducto = datos[1];
                comentario.nombreUsuario = datos[2];
                comentario.comentario = datos[3];
                comentario.fecha = datos[4];
                comentarios.push_back(comentario);
            } catch (const exception& e) {
                cout << "Advertencia: datos de comentario invalidos ignorados." << endl;
            }
        }
    }
    archivo.close();
    cout << "Comentarios cargados: " << comentarios.size() << endl;
}

void verificarArchivos() {
    cout << "\n=== VERIFICANDO ARCHIVOS ===" << endl;
    
    ifstream archivo1("Usuarios.txt", ios::in);
    cout << "Usuarios.txt: " << (archivo1 ? "EXISTE" : "NO EXISTE") << endl;
    archivo1.close();
    
    ifstream archivo2("Productos.txt", ios::in);
    cout << "Productos.txt: " << (archivo2 ? "EXISTE" : "NO EXISTE") << endl;
    archivo2.close();
    
    ifstream archivo3("Comentarios.txt", ios::in);
    cout << "Comentarios.txt: " << (archivo3 ? "EXISTE" : "NO EXISTE") << endl;
    archivo3.close();
    
    // Mostrar ruta actual de trabajo
    system("cd");
}

void guardarCarritoEnArchivo(const CarritoDeCompras& carrito) {
    ofstream archivo("Carrito_" + to_string(carrito.usuario.idUsuario) + ".txt", ios::out);
    if (!archivo) {
        cout << "Error al crear archivo del carrito" << endl;
        return;
    }

    archivo << "=== CARRITO DE COMPRAS ===" << endl;
    archivo << "Usuario: " << carrito.usuario.nombre << endl;
    archivo << "ID Carrito: " << carrito.idCarrito << endl;
    archivo << "==========================" << endl;
    
    for (const auto& producto : carrito.productos) {
        archivo << producto.nombre << " | $" << producto.precio << endl;
    }
    
    archivo << "==========================" << endl;
    archivo << "Subtotal: $" << carrito.subtotal << endl;
    archivo << "Impuestos: $" << carrito.impuestos << endl;
    archivo << "Total: $" << carrito.subtotal + carrito.impuestos << endl;
    
    archivo.close();
    cout << "Carrito guardado en archivo: Carrito_" << carrito.usuario.idUsuario << ".txt" << endl;
}

void cargarDatos() {
    cout << "Cargando datos desde archivos..." << endl;
    Sleep(2000);
    
    cargarUsuarios();
    cargarProductos();
    cargarComentarios();
    
    cout << "\nDatos cargados correctamente!" << endl;
    cout << "- Usuarios: " << usuarios.size() << endl;
    cout << "- Productos: " << productos.size() << endl;
    cout << "- Comentarios: " << comentarios.size() << endl;
}

Usuario* iniciarSesion() {
    string correo, clave;
    
    cout << "\n=== INICIAR SESION ===" << endl;
    cout << "Correo electronico: ";
    cin >> correo;
    cout << "Contrasena: ";
    cin >> clave;
    
    for (size_t i = 0; i < usuarios.size(); i++) {
        if (usuarios[i].correoElectronico == correo && usuarios[i].contrasena == clave) {
            cout << "Bienvenido " << usuarios[i].nombre << "!" << endl;
            return &usuarios[i];
        }
    }
    
    cout << "Usuario invalido" << endl;
    return nullptr;
}
// FunciÛn para listar productos de bajo stock (<15 unidades)
void listarProductosBajoStock() {
    cout << "\n=== PRODUCTOS CON STOCK BAJO (<15 unidades) ===" << endl;
    bool encontrados = false;
    
    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].stock < 15) {
            cout << "ID: " << productos[i].idProducto << endl;
            cout << "Nombre: " << productos[i].nombre << endl;
            cout << "DescripciÛn: " << productos[i].descripcion << endl;
            cout << "Precio: $" << productos[i].precio << endl;
            cout << "Stock: " << productos[i].stock << endl;
            cout << "------------------------" << endl;
            encontrados = true;
        }
    }
    
    if (!encontrados) {
        cout << "No hay productos con stock bajo" << endl;
    }
}
//
// FunciÛn para convertir fecha a formato numÈrico
int fechaADias(const string& fecha) {
    // Verificar si es formato dd/mm/aaaa
    if (fecha.length() == 10 && fecha[2] == '/' && fecha[5] == '/') {
        // Formato dd/mm/aaaa
        string diaStr = fecha.substr(0, 2);
        string mesStr = fecha.substr(3, 2);
        string anioStr = fecha.substr(6, 4);
        
        int dia = stoi(diaStr);
        int mes = stoi(mesStr);
        int anio = stoi(anioStr);
        
        return anio * 10000 + mes * 100 + dia;
    }
    // Verificar si es formato aaaa-mm-dd
    else if (fecha.length() == 10 && fecha[4] == '-' && fecha[7] == '-') {
        // Formato aaaa-mm-dd
        string anioStr = fecha.substr(0, 4);
        string mesStr = fecha.substr(5, 2);
        string diaStr = fecha.substr(8, 2);
        
        int dia = stoi(diaStr);
        int mes = stoi(mesStr);
        int anio = stoi(anioStr);
        
        return anio * 10000 + mes * 100 + dia;
    }
    else {
        cout << "Error: Formato de fecha no reconocido: " << fecha << endl;
        return 0;
    }
}

// FunciÛn para filtrar comentarios desde cierta fecha
void listarComentariosDesdeFecha() {
    string fecha;
    cout << "\nIngrese fecha (formato: dd/mm/aaaa): ";
    cin >> fecha;
    
    // Validar formato b·sico de fecha
    if (fecha.length() != 10 || fecha[2] != '/' || fecha[5] != '/') {
        cout << "Error: Formato de fecha inv·lido. Use dd/mm/aaaa" << endl;
        return;
    }
    
    cout << "\n=== COMENTARIOS DESDE " << fecha << " ===" << endl;
    bool encontrados = false;
    int referencia = fechaADias(fecha);
    
    if (referencia == 0) {
        cout << "Error al procesar la fecha ingresada" << endl;
        return;
    }
    
    for (size_t i = 0; i < comentarios.size(); i++) {
        int fechaComentario = fechaADias(comentarios[i].fecha);
        if (fechaComentario >= referencia) {
            cout << "Producto: " << comentarios[i].nombreProducto << endl;
            cout << "Usuario: " << comentarios[i].nombreUsuario << endl;
            cout << "Comentario: " << comentarios[i].comentario << endl;
            cout << "Fecha: " << comentarios[i].fecha << endl;
            cout << "------------------------" << endl;
            encontrados = true;
        }
    }
    
    if (!encontrados) {
        cout << "No hay comentarios desde esa fecha" << endl;
    }
}

// Listado de usuarios sin mostrar contraseÒas
void listarUsuarios() {
    cout << "\n=== LISTA DE USUARIOS ===" << endl;
    
    for (size_t i = 0; i < usuarios.size(); i++) {
        // Convertir nombre a may˙sculas
        string nombreMayus = usuarios[i].nombre;
        for (size_t j = 0; j < nombreMayus.length(); j++) {
            if (nombreMayus[j] >= 'a' && nombreMayus[j] <= 'z') {
                nombreMayus[j] = nombreMayus[j] - 32;
            }
        }
        
        cout << "ID: " << usuarios[i].idUsuario << endl;
        cout << "Nombre: " << nombreMayus << endl;
        cout << "Correo: " << usuarios[i].correoElectronico << endl;
        cout << "DirecciÛn: " << usuarios[i].direccion << endl;
        cout << "MÈtodo de Pago: " << usuarios[i].metodoDePago << endl;
        cout << "------------------------" << endl;
    }
}

// Mostrar productos disponibles
void mostrarProductos() {
    cout << "\n=== PRODUCTOS DISPONIBLES ===" << endl;
    for (size_t i = 0; i < productos.size(); i++) {
        cout << "ID: " << productos[i].idProducto << " | " 
             << productos[i].nombre << " | $" 
             << productos[i].precio << " | Stock: " 
             << productos[i].stock << endl;
    }
}
// Agregar productos al carrito
void agregarAlCarrito(Usuario* usuarioActual) {
    mostrarProductos();
    
    int productoId, cantidad;
    cout << "\nIngrese el ID del producto: ";
    cin >> productoId;
    cout << "Ingrese la cantidad: ";
    cin >> cantidad;
    
    // Buscar producto
    Producto* producto = NULL;
    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].idProducto == productoId) {
            producto = &productos[i];
            break;
        }
    }
    
    if (producto == NULL) {
        cout << "Error: Producto no existe" << endl;
        return;
    }
    
    if (producto->stock < cantidad) {
        cout << "Error: Stock insuficiente. Solo hay " << producto->stock << " unidades" << endl;
        return;
    
	}// Buscar carrito existente
    CarritoDeCompras* carritoUsuario = NULL;
    for (size_t i = 0; i < carritos.size(); i++) {
        if (carritos[i].usuario.idUsuario == usuarioActual->idUsuario) {
            carritoUsuario = &carritos[i];
            break;
        }
    }
    
    if (carritoUsuario == NULL) {
        // Crear nuevo carrito
        CarritoDeCompras nuevoCarrito;
        nuevoCarrito.idCarrito = carritos.size() + 1;
        nuevoCarrito.usuario = *usuarioActual;
        
        // Agregar productos
        for (int i = 0; i < cantidad; i++) {
            nuevoCarrito.productos.push_back(*producto);
        }
        
        nuevoCarrito.subtotal = producto->precio * cantidad;
        nuevoCarrito.impuestos = nuevoCarrito.subtotal * 0.19;
        
        carritos.push_back(nuevoCarrito);
        cout << "Nuevo carrito creado!" << endl;
        
        // Guardar carrito en archivo
        guardarCarritoEnArchivo(nuevoCarrito);
    } else {
        // Agregar al carrito existente
        for (int i = 0; i < cantidad; i++) {
            carritoUsuario->productos.push_back(*producto);
        }
        carritoUsuario->subtotal += producto->precio * cantidad;
        carritoUsuario->impuestos = carritoUsuario->subtotal * 0.19;
        cout << "Producto agregado al carrito existente!" << endl;
        
        // Actualizar archivo del carrito
        guardarCarritoEnArchivo(*carritoUsuario);
    }
    
    // Actualizar stock
    producto->stock -= cantidad;
    cout << "Stock actualizado. Quedan " << producto->stock << " unidades" << endl;
}

// FunciÛn para listar productos del carrito
void listarCarrito(Usuario* usuarioActual) {
    CarritoDeCompras* carritoUsuario = NULL;
    
    for (size_t i = 0; i < carritos.size(); i++) {
        if (carritos[i].usuario.idUsuario == usuarioActual->idUsuario) {
            carritoUsuario = &carritos[i];
            break;
        }
    }
    
    if (carritoUsuario == NULL) {
        cout << "No tiene productos en el carrito" << endl;
        return;
    }
    
    cout << "\n=== CARRITO DE COMPRAS ===" << endl;
    cout << "ID Carrito: " << carritoUsuario->idCarrito << endl;
    
    for (size_t i = 0; i < carritoUsuario->productos.size(); i++) {
        cout << "- " << carritoUsuario->productos[i].nombre << " | $" << carritoUsuario->productos[i].precio << endl;
    }
    
    cout << "Subtotal: $" << carritoUsuario->subtotal << endl;
    cout << "Impuestos: $" << carritoUsuario->impuestos << endl;
    cout << "Total: $" << carritoUsuario->subtotal + carritoUsuario->impuestos << endl;
}

// Men˙ principal del usuario
void menuUsuario(Usuario* usuario) {
    int opcion;
    
    do {
        cout << "\n=== MEN⁄ PRINCIPAL ===" << endl;
        cout << "1. Listar Productos con stock bajo" << endl;
        cout << "2. Comentarios de una fecha en adelante" << endl;
        cout << "3. Listar usuarios" << endl;
        cout << "4. Adicionar productos al carrito" << endl;
        cout << "5. Listar productos del carrito" << endl;
        cout << "0. Cerrar sesiÛn" << endl;
        cout << "Seleccione una opciÛn: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                listarProductosBajoStock();
                break;
            case 2:
                listarComentariosDesdeFecha();
                break;
            case 3:
                listarUsuarios();
                break;
            case 4:
                agregarAlCarrito(usuario);
                break;
            case 5:
                listarCarrito(usuario);
                break;
            case 0:
                cout << "Cerrando sesiÛn..." << endl;
                break;
            default:
                cout << "OpciÛn inv·lida" << endl;
        }
    } while (opcion != 0);
}

int main() {
    setlocale(LC_ALL, "spanish");
    
    verificarArchivos();
    cargarDatos();
    
    int opcion;
    do {
        cout << "\n=== SISTEMA E-COMMERCE ===" << endl;
        cout << "1. Iniciar sesiÛn" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opciÛn: ";
        cin >> opcion;
        
        if (opcion == 1) {
            Usuario* usuario = iniciarSesion();
            if (usuario != NULL) {
                menuUsuario(usuario);
            }
        } else if (opcion != 0) {
            cout << "OpciÛn inv·lida" << endl;
        }
    } while (opcion != 0);
    
    cout << "Gracias por usar el sistema!" << endl;
    return 0;
}
