#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include "gestores/GestorCliente.h"
#include "gestores/GestorRepartidor.h"
#include "gestores/GestorSector.h"
#include "gestores/GestorEntrega.h"
#include "gestores/GestorServicioDiario.h"
#include "Semillero.h"

// Se ve feo, pero me deja mostrar paginado en el terminal
template <typename T, typename Func>
int seleccionarElemento(const std::vector<T>& items, Func displayFunc) {
    if (items.empty()) {
        std::cout << "No hay elementos disponibles." << std::endl;
        return -1;
    }

    int page = 0;
    const int pageSize = 9;
    
    while (true) {
        size_t start = page * pageSize;
        size_t end = std::min(start + pageSize, items.size());
        
        std::cout << "\n--- Seleccione (1-" << (end - start) << "), [A]nt, [S]ig, [0] Salir ---" << std::endl;
        for (size_t i = start; i < end; ++i) {
            std::cout << (i - start + 1) << ". ";
            displayFunc(items[i]);
            std::cout << std::endl;
        }

        char opcion;
        std::cin >> opcion;
        opcion = std::toupper(opcion);
        
        if (opcion == '0') return -1;
        else if (opcion == 'A') { if (page > 0) page--; }
        else if (opcion == 'S') { if (end < items.size()) page++; }

        // Selecciono una de las opciones
        else if (opcion >= '1' && opcion <= '9') {
            int index = (opcion - '1');

            // Porque estamos paginando hay que mapear.
            if (index >= 0 && index < static_cast<int>(end - start)) {
                return items[start + index].id;
            }
            std::cout << "Opción inválida." << std::endl;
        }
        else {
            std::cout << "Opción inválida." << std::endl;
        }
    }
}

class Menu {
private:
    GestorCliente gc;
    GestorRepartidor gr;
    GestorSector gs;
    GestorEntrega ge;

    void mostrarError(int codigo) {
        std::cout << " [!] Error: ";
        switch (static_cast<Resultado>(-codigo)) {
            case ENTIDAD_NO_ENCONTRADA: std::cout << "Entidad no encontrada."; break;
            case ERROR_VALIDACION:      std::cout << "Datos inválidos."; break;
            case REPARTIDOR_OCUPADO:    std::cout << "Repartidor ocupado."; break;
            case ESTADO_ILEGAL:         std::cout << "Estado ilegal."; break;
            case ERROR_UNICIDAD:        std::cout << "Duplicado detectado (Cedula/Placa)."; break;
            case ERROR_IO:              std::cout << "Error de acceso al archivo."; break;
            default:                    std::cout << "Error desconocido (" << codigo << ").";
        }
        std::cout << std::endl;
    }

    void mostrarSubmenuGestion() {
        int opcion;
        do {
            std::cout << "\n--- Gestión (CRUD) ---" << std::endl;
            std::cout << "1. Clientes" << std::endl;
            std::cout << "2. Repartidores" << std::endl;
            std::cout << "3. Sectores" << std::endl;
            std::cout << "0. Volver" << std::endl;
            if (!(std::cin >> opcion)) {
                std::cin.clear(); std::cin.ignore(1000, '\n'); 
                std::cout << "Entrada inválida." << std::endl; opcion = -1;
                continue;
            }

            switch (opcion) {
                case 1: mostrarSubmenuClientes(); break;
                case 2: mostrarSubmenuRepartidores(); break;
                case 3: mostrarSubmenuSectores(); break;
                case 0: break;
                default: std::cout << "Opción inválida." << std::endl;
            }
        } while (opcion != 0);
    }

    void mostrarSubmenuClientes() {
        int opcion;
        do {
            std::cout << "\n--- Gestión de Clientes ---" << std::endl;
            std::cout << "1. Registrar" << std::endl;
            std::cout << "2. Listar" << std::endl;
            std::cout << "3. Eliminar" << std::endl;
            std::cout << "0. Volver" << std::endl;
            if (!(std::cin >> opcion)) {
                std::cin.clear(); std::cin.ignore(1000, '\n'); 
                std::cout << "Entrada inválida." << std::endl; opcion = -1;
                continue;
            }
            switch(opcion) {
                case 1: registrarCliente(); break;
                case 2: listarClientes(); break;
                case 3: eliminarCliente(); break;
                case 0: break;
            }
        } while (opcion != 0);
    }

    // Template method for paginated selection
    template <typename T>
    int seleccionarElemento(const std::vector<T>& items) {
        if (items.empty()) {
            std::cout << "No hay elementos disponibles." << std::endl;
            return -1;
        }

        int page = 0;
        const int pageSize = 9;
        
        while (true) {
            size_t start = page * pageSize;
            size_t end = std::min(start + pageSize, items.size());
            
            std::cout << "\n--- Seleccione (1-" << (end - start) << "), [A]nt, [S]ig, [0] Salir ---" << std::endl;
            for (size_t i = start; i < end; ++i) {
                std::cout << (i - start + 1) << ". " << items[i].nombre << std::endl;
            }

            char opcion;
            std::cin >> opcion;
            
            if (opcion == '0') return -1;
            if (opcion == 'A' || opcion == 'a') { if (page > 0) page--; }
            else if (opcion == 'S' || opcion == 's') { if (end < items.size()) page++; }
            else if (opcion >= '1' && opcion <= '9') {
                int index = (opcion - '1');
                if (index >= 0 && index < (int)(end - start)) {
                    return items[start + index].id;
                }
            }
            std::cout << "Opción inválida." << std::endl;
        }
    }

    void eliminarCliente() {
        int id; std::cout << "ID a eliminar: "; std::cin >> id;
        gc.eliminar(id);
    }

    void mostrarSubmenuRepartidores() {
        int opcion;
        do {
            std::cout << "\n--- Gestión de Repartidores ---" << std::endl;
            std::cout << "1. Registrar" << std::endl;
            std::cout << "2. Listar" << std::endl;
            std::cout << "3. Eliminar" << std::endl;
            std::cout << "0. Volver" << std::endl;
            if (!(std::cin >> opcion)) {
                std::cin.clear(); std::cin.ignore(1000, '\n'); 
                std::cout << "Entrada inválida." << std::endl; opcion = -1;
                continue;
            }
            switch(opcion) {
                case 1: registrarRepartidor(); break;
                case 2: listarRepartidores(); break;
                case 3: eliminarRepartidor(); break;
                case 0: break;
            }
        } while (opcion != 0);
    }

    void registrarRepartidor() {
        Repartidor r;
        std::cout << "Nombre: ";
        std::cin.ignore();
        std::cin.getline(r.nombre, 64);
        std::cout << "ID Sector: ";
        std::cin >> r.id_sector;
        r.disponible = true;
        r.borrado_en = 0;
        
        std::cout << "Tipo Vehiculo (0=MOTO, 1=CARRO): ";
        int tipo; std::cin >> tipo;
        r.vehiculo.tipo = (TipoVehiculo)tipo;
        std::cout << "Modelo: ";
        std::cin.ignore();
        std::cin.getline(r.vehiculo.modelo, 50);
        std::cout << "Placa: ";
        std::cin.getline(r.vehiculo.placa, 7);
        
        int res = gr.registrar(r);
        if (res < 0) mostrarError(res);
        else std::cout << "Repartidor registrado con ID: " << res << std::endl;
    }
    void listarRepartidores() {
        for (const auto& r : gr.listarActivos()) {
            std::cout << "ID: " << r.id << " | Nombre: " << r.nombre << std::endl;
        }
    }
    void eliminarRepartidor() {
        int id; std::cout << "ID a eliminar: "; std::cin >> id;
        gr.eliminar(id);
    }

    void mostrarSubmenuSectores() {
        int opcion;
        do {
            std::cout << "\n--- Gestión de Sectores ---" << std::endl;
            std::cout << "1. Registrar" << std::endl;
            std::cout << "2. Listar" << std::endl;
            std::cout << "3. Eliminar" << std::endl;
            std::cout << "0. Volver" << std::endl;
            if (!(std::cin >> opcion)) {
                std::cin.clear(); std::cin.ignore(1000, '\n'); 
                std::cout << "Entrada inválida." << std::endl; opcion = -1;
                continue;
            }
            switch(opcion) {
                case 1: registrarSector(); break;
                case 2: listarSectores(); break;
                case 3: eliminarSector(); break;
                case 0: break;
            }
        } while (opcion != 0);
    }

    void registrarSector() {
        Sector s;
        std::cout << "Nombre del sector: ";
        std::cin.ignore();
        std::cin.getline(s.nombre, 32);
        s.borrado_en = 0;

        int res = gs.registrar(s);
        if (res < 0) mostrarError(res);
        else std::cout << "Sector registrado con ID: " << res << std::endl;
    }
    void listarSectores() {
        for (const auto& s : gs.listarActivos()) {
            std::cout << "ID: " << s.id << " | Nombre: " << s.nombre << std::endl;
        }
    }
    void eliminarSector() {
        int id; std::cout << "ID a eliminar: "; std::cin >> id;
        gs.eliminar(id);
    }


    void mostrarSubmenuServicioDiario() {
        int opcion;
        do {
            std::cout << "\n--- Submenú de Servicio Diario ---" << std::endl;
            std::cout << "1. Iniciar Jornada (Randomizar Repartidores)" << std::endl;
            std::cout << "2. Solicitar Envío" << std::endl;
            std::cout << "3. Asignar Repartidor a Envío" << std::endl;
            std::cout << "4. Marcar Entrega como Finalizada" << std::endl;
            std::cout << "5. Cancelar Envío" << std::endl;
            std::cout << "6. Listar Envíos" << std::endl;
            std::cout << "7. Listar Envíos Pendientes" << std::endl;
            std::cout << "0. Volver" << std::endl;
            if (!(std::cin >> opcion)) {
                std::cin.clear(); std::cin.ignore(1000, '\n'); 
                std::cout << "Entrada inválida." << std::endl; opcion = -1;
                continue;
            }

            switch (opcion) {
                case 1: iniciarJornada(); break;
                case 2: solicitarEnvio(); break;
                case 3: asignarRepartidor(); break;
                case 4: marcarFinalizada(); break;
                case 5: cancelarEntrega(); break;
                case 6: listarEnvios(false); break;
                case 7: listarEnvios(true); break;
                case 0: break;
                default: std::cout << "Opción inválida." << std::endl;
            }
        } while (opcion != 0);
    }

    void listarEnvios(bool soloPendientes) {
        std::vector<Entrega> lista = soloPendientes ? ge.listarPorEstatus(EstatusEntrega::REPARTIDOR_PENDIENTE) : ge.listarTodo();
        std::cout << "\n--- Envíos ---" << std::endl;
        for (const auto& e : lista) {
            std::cout << "ID: " << e.id << " | Cliente: " << e.cedula_cliente.numero 
                      << " | Estatus: " << (int)e.estatus << std::endl;
        }
    }

    void iniciarJornada() {
        GestorServicioDiario gsd;
        gsd.asignarAleatorios();
        std::cout << "Jornada iniciada y repartidores distribuidos." << std::endl;
    }

    void solicitarEnvio() {
        std::cout << "Cedula Cliente (Tipo [V,E,G,C,J] número): ";
        char tipo; long num;
        if (!(std::cin >> tipo >> num)) {
            std::cin.clear(); std::cin.ignore(1000, '\n');
            std::cout << "Entrada inválida." << std::endl; return;
        }
        int id_c = gc.encontrarIdPorCedula(static_cast<TipoIdentificacion>(tipo), num);
        if (id_c < 0) { mostrarError(id_c); return; }

        std::cout << "Nombre Sector Origen: ";
        char nomOrigen[32]; std::cin.ignore(); std::cin.getline(nomOrigen, 32);
        int id_origen = gs.encontrarIdPorNombre(nomOrigen);
        if (id_origen < 0) { mostrarError(id_origen); return; }

        std::cout << "Nombre Sector Destino: ";
        char nomDestino[32]; std::cin.getline(nomDestino, 32);
        int id_destino = gs.encontrarIdPorNombre(nomDestino);
        if (id_destino < 0) { mostrarError(id_destino); return; }

        std::vector<Repartidor> disponibles = gr.listarDisponiblesEnZona(id_origen);
        
        Entrega e; e.cedula_cliente = {static_cast<TipoIdentificacion>(tipo), num}; e.id_sector_origen = id_origen; e.id_sector_destino = id_destino; e.estatus = EstatusEntrega::REPARTIDOR_PENDIENTE; e.id_repartidor = -1; e.borrado_en = 0; int id_e = ge.solicitarEnvio(e);
        if (id_e < 0) { mostrarError(id_e); return; }
        std::cout << "Envío solicitado con ID: " << id_e << std::endl;

        if (disponibles.empty()) {
            std::cout << "Disculpe, no hay repartidores disponibles. El envío queda pendiente." << std::endl;
            return;
        }

        std::cout << "Repartidores disponibles en " << nomOrigen << ":" << std::endl;
        for (const auto& r : disponibles) {
            std::cout << "- ID: " << r.id << " | Nombre: " << r.nombre 
                      << " | Vehiculo: " << r.vehiculo.modelo << std::endl;
        }

        std::cout << "Seleccione ID de repartidor (o -1 para asignar después): ";
        int id_r; 
        if (!(std::cin >> id_r)) {
            std::cin.clear(); std::cin.ignore(1000, '\n');
            std::cout << "Entrada inválida." << std::endl; return;
        }
        
        if (id_r != -1) {
            int res = ge.asignarRepartidor(id_e, id_r);
            if (res != 0) mostrarError(-res);
            else std::cout << "Repartidor asignado correctamente." << std::endl;
        }
    }

    void asignarRepartidor() {
        int id_e, id_r;
        std::cout << "ID Entrega: "; 
        if (!(std::cin >> id_e)) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Inválido." << std::endl; return; }
        std::cout << "ID Repartidor: "; 
        if (!(std::cin >> id_r)) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Inválido." << std::endl; return; }
        int res = ge.asignarRepartidor(id_e, id_r);
        if (res != 0) mostrarError(-res);
        else std::cout << "Repartidor asignado correctamente." << std::endl;
    }

    void marcarFinalizada() {
        int id_e;
        std::cout << "ID Entrega: "; 
        if (!(std::cin >> id_e)) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Inválido." << std::endl; return; }
        ge.marcarEntregada(id_e);
        std::cout << "Entrega marcada como finalizada." << std::endl;
    }

    void cancelarEntrega() {
        int id_e;
        std::cout << "ID Entrega: "; 
        if (!(std::cin >> id_e)) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Inválido." << std::endl; return; }
        ge.cancelar(id_e);
        std::cout << "Entrega cancelada." << std::endl;
    }

    void registrarCliente() {
        Cliente c;
        std::cout << "Cédula (Tipo [V,E,G,C,J] número): ";
        char tipo; long num;
        if (!(std::cin >> tipo >> num)) {
            std::cin.clear(); std::cin.ignore(1000, '\n');
            std::cout << "Entrada inválida." << std::endl; return;
        }
        c.cedula = {static_cast<TipoIdentificacion>(tipo), num};
        
        std::cout << "Nombre: ";
        std::cin.ignore();
        std::cin.getline(c.nombre, 64);
        
        std::cout << "Teléfono (Prefijo número): ";
        int pref; unsigned int numTel;
        if (!(std::cin >> pref >> numTel)) {
            std::cin.clear(); std::cin.ignore(1000, '\n');
            std::cout << "Entrada inválida." << std::endl; return;
        }
        c.telefono = {static_cast<OpTelfMovil>(pref), numTel};
        c.borrado_en = 0;

        int res = gc.registrar(c);
        if (res < 0) mostrarError(res);
        else std::cout << "Cliente registrado con ID: " << res << std::endl;
    }

public:
    Menu() {
        Semillero::ejecutar();
    }

    void mostrarPrincipal() {
        int opcion;
        do {
            std::cout << "\n--- SpeedDelivery Main Menu ---" << std::endl;
            std::cout << "1. Gestión (CRUD)" << std::endl;
            std::cout << "2. Servicio Diario (Delivery)" << std::endl;
            std::cout << "0. Salir" << std::endl;
        // En la entrada de menú principal:
        if (!(std::cin >> opcion)) {
            std::cin.clear(); std::cin.ignore(1000, '\n'); 
            std::cout << "Entrada inválida." << std::endl; opcion = -1;
        }

// (Applying this logic to all cin points in Menu.h)

            switch (opcion) {
                case 1: mostrarSubmenuGestion(); break;
                case 2: mostrarSubmenuServicioDiario(); break;
                case 0: std::cout << "Saliendo..." << std::endl; break;
                default: std::cout << "Opción inválida." << std::endl;
            }
        } while (opcion != 0);
    }
};

#endif
