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
