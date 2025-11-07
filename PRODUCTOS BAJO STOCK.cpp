// Función para listar productos de bajo stock (<15 unidades)
void listarProductosBajoStock() {
    cout << "\n=== PRODUCTOS CON STOCK BAJO (<15 unidades) ===" << endl;
    bool encontrados = false;
    
    for (size_t i = 0; i < productos.size(); i++) {
        if (productos[i].stock < 15) {
            cout << "ID: " << productos[i].idProducto << endl;
            cout << "Nombre: " << productos[i].nombre << endl;
            cout << "Descripción: " << productos[i].descripcion << endl;
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
// Función para convertir fecha a formato numérico
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

// Función para filtrar comentarios desde cierta fecha
void listarComentariosDesdeFecha() {
    string fecha;
    cout << "\nIngrese fecha (formato: dd/mm/aaaa): ";
    cin >> fecha;
    
    // Validar formato básico de fecha
    if (fecha.length() != 10 || fecha[2] != '/' || fecha[5] != '/') {
        cout << "Error: Formato de fecha inválido. Use dd/mm/aaaa" << endl;
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

// Listado de usuarios sin mostrar contraseñas
void listarUsuarios() {
    cout << "\n=== LISTA DE USUARIOS ===" << endl;
    
    for (size_t i = 0; i < usuarios.size(); i++) {
        // Convertir nombre a mayúsculas
        string nombreMayus = usuarios[i].nombre;
        for (size_t j = 0; j < nombreMayus.length(); j++) {
            if (nombreMayus[j] >= 'a' && nombreMayus[j] <= 'z') {
                nombreMayus[j] = nombreMayus[j] - 32;
            }
        }
        
        cout << "ID: " << usuarios[i].idUsuario << endl;
        cout << "Nombre: " << nombreMayus << endl;
        cout << "Correo: " << usuarios[i].correoElectronico << endl;
        cout << "Dirección: " << usuarios[i].direccion << endl;
        cout << "Método de Pago: " << usuarios[i].metodoDePago << endl;
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
