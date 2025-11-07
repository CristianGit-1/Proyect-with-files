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

// Función para listar productos del carrito
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

// Menú principal del usuario
void menuUsuario(Usuario* usuario) {
    int opcion;
    
    do {
        cout << "\n=== MENÚ PRINCIPAL ===" << endl;
        cout << "1. Listar Productos con stock bajo" << endl;
        cout << "2. Comentarios de una fecha en adelante" << endl;
        cout << "3. Listar usuarios" << endl;
        cout << "4. Adicionar productos al carrito" << endl;
        cout << "5. Listar productos del carrito" << endl;
        cout << "0. Cerrar sesión" << endl;
        cout << "Seleccione una opción: ";
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
                cout << "Cerrando sesión..." << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
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
        cout << "1. Iniciar sesión" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        if (opcion == 1) {
            Usuario* usuario = iniciarSesion();
            if (usuario != NULL) {
                menuUsuario(usuario);
            }
        } else if (opcion != 0) {
            cout << "Opción inválida" << endl;
        }
    } while (opcion != 0);
    
    cout << "Gracias por usar el sistema!" << endl;
    return 0;
}
