#include <iostream>
#include <sstream>
#include <string>

void addPackage();
void reportState();
void reception();
// void dispatchPackage();
void incrementCapacity();
// void inspectFront();
// void reportDestiny();
void liberarMemoria(); 
std::string priorityAText(int p); 


int *idPackage = nullptr;
double *weigth = nullptr;
std::string *destiny = nullptr;
int *priority = nullptr;
char *state = nullptr;

int capacity = 50;
int front = 0;
int packagesOnSystem = 0;
int packageOnWait = 0;

using namespace std;

int main() {
    int opcion;

    idPackage = new int[capacity];
    weigth = new double[capacity];
    destiny = new std::string[capacity];
    priority = new int[capacity];
    state = new char[capacity];
    
    do
    {
        std::cout << "-- Seleccione una operación --" << std::endl; 
        std::cout << "1. Recibir Nuevo Paquete (PUSH)" << std::endl; 
        std::cout << "2. Procesar Recepcion (POP y ENCOLAR)" << std::endl; 
        std::cout << "3. Despachar (DESENCOLAR con Prioridad)" << std::endl; 
        std::cout << "4. Reporte de Estados" << std::endl; 
        std::cout << "5. Salir (Liberar Memoria)" << std::endl; 
        std::cout << "Opcion: ";
        std::cin >> opcion;
        switch (opcion)
        {
            case 1:
                addPackage();
                break;
            case 2:
                reception(); 
                break;
            case 3:
                dispatchPackage();
                break;
            case 4:
                reportDestiny();
                break;
            case 5:
                liberarMemoria(); 
                std::cout << "Saliendo...." << std::endl;
                break;
            default:
                std::cout << "- Opcion invalida. Intente de nuevo -" << std::endl;
                break;
        }
    } while (opcion != 5 );
    return 0;
}

void reception(){
    for (int i = 0; i < packagesOnSystem; i++)
    {
        if (state[i] == 'R')
        {
            state[i] == 'E';
            std::cout << "POP de Pila - ID: " << idPackage[i] << ", Transferido a Cola. Estado: '" << state[i] << "'" << std::endl;
            break;
        }
    }
    
    
}

void reportState(){
    int cD = 0 , cE = 0, cR = 0;
    for (int i = 0; i < packagesOnSystem; i++)
    {
        if (state[i] == 'R')
        {
            cR++;
        }
        if (state[i] == 'E')
        {
            cE++;
        }
        if (state[i] == 'D')
        {
            cD++;
        }
    }
    std::cout << "Paquetes en Recepcion (R): " << cR << std::endl;
    std::cout << "Paquetes en Cola (E): " << cE << std::endl; 
    std::cout << "Paquetes en Recepcion (D): " << cD << std::endl; 
}

void liberarMemoria() {
    std::cout << "Liberando " << capacity << " bloques de memoria asignada..." << std::endl;
    delete[] idPackage;
    delete[] weigth;
    delete[] destiny;
    delete[] priority;
    delete[] state;
    
    idPackage = nullptr;
    weigth = nullptr;
    destiny = nullptr;
    priority = nullptr;
    state = nullptr;
    std::cout << "Sistema cerrado. ¡Memoria libre!" << std::endl;
}

void reportDestiny() {
    if (packageOnWait == 0) {
        std::cout << "No hay paquetes en cola para generar un reporte." << std::endl;
        return;
    }

    std::string searchDestiny;
    std::cout << "Ingrese el destino para el reporte: ";
    std::cin.ignore();
    std::getline(std::cin, searchDestiny);

    int destinyCount = 0;
    float totalDestinyWeigth = 0.0f;

    for (int i = front; i < packagesOnSystem; ++i) {
        if (state[i] == 'E' && destiny[i] == searchDestiny) {
            destinyCount++;
            totalDestinyWeigth += weigth[i];
        }
    }
    
    std::cout << "Reporte para destino '" << searchDestiny << "':" << std::endl;
    if (destinyCount > 0) {
        float promWeigth = totalDestinyWeigth / destinyCount;
        std::cout << "  Paquetes En Cola: " << destinyCount << std::endl;
        std::cout << "  Peso Promedio: " << promWeigth << " kg" << std::endl;
    } else {
        std::cout << "  No se encontraron paquetes en cola para este destino." << std::endl;
    }
}

void dispatchPackage(){
    if (packageOnWait == 0) {
        std::cout << "No hay paquetes en la cola para despachar." << std::endl;
        return;
    }

    std::cout << "Despachando paquete..." << std::endl;
    for (int i = 0; i < packagesOnSystem; i++)
    {
        if (state[i] == 'E' && priority[i] == 1)
        {
            state[i] == 'D';
            front++;
            packageOnWait--;
            std::cout << "DESPACHADO - ID: " << idPackage[i] << "(Prioridad " << priority[i] << "). Estado: '" << state[i] << "'" << std::endl;
            return;
        }
        if (state[i] == 'E' && priority[i] == 2)
        {
            state[i] == 'D';
            front++;
            packageOnWait--;
            std::cout << "DESPACHADO - ID: " << idPackage[i] << "(Prioridad " << priority[i] << "). Estado: '" << state[i] << "'" << std::endl;
            return;
        }
        if (state[i] == 'E' && priority[i] == 3)
        {
            state[i] == 'D';
            front++;
            packageOnWait--;
            std::cout << "DESPACHADO - ID: " << idPackage[i] << "(Prioridad " << priority[i] << "). Estado: '" << state[i] << "'" << std::endl;
            return;
        }
    }
    
}

void addPackage(){
    if (packagesOnSystem == capacity)
    {
        incrementCapacity();
    }
    int id, prioridad;
    double peso;
    string destino;

    std::cout << "Ingrese ID: ";
    std::cin >> id;
    std::cout << "Ingrese Peso (kg): ";
    std::cin >> peso;
    std::cout << "Ingrese Destino: ";
    std::cin.ignore();
    std::getline(std::cin, destino);
    
    std::cout << "Ingrese Prioridad (1 = Alta, 2 = Media, 3 = Baja): ";
    std::cin >> prioridad;

    agregarDatoPila(id, peso, destino, prioridad, 'R');

    packagesOnSystem++;
    packageOnWait++;

    std::cout << "Paquete " << id << " Recibido. Estado: " << state[0] << "." << std::endl;
}

void incrementCapacity(){
    int *ptr_aux_idPackage = new int[capacity + 1];
    double *ptr_aux_weigth = new double[capacity + 1];
    std::string *ptr_aux_destiny = new std::string[capacity + 1];
    int *ptr_aux_priority = new int[capacity + 1];
    char *ptr_aux_state = new char[capacity + 1];
    
    for (int i = 0; i < capacity; i++) {
        ptr_aux_idPackage[i] = idPackage[i];
        ptr_aux_weigth[i] = weigth[i];
        ptr_aux_destiny[i] = destiny[i];
        ptr_aux_priority[i] = priority[i];
        ptr_aux_state[i] = state[i];
    }
    
    delete[] idPackage;
    delete[] weigth;
    delete[] destiny;
    delete[] priority;
    delete[] state;

    idPackage = ptr_aux_idPackage;
    weigth = ptr_aux_weigth;
    destiny = ptr_aux_destiny;
    priority = ptr_aux_priority;
    state = ptr_aux_state;

    capacity++;
}

void agregarDatoPila(int id, double peso, string destino, int prioridad, char stado) {
    
    int *ptr_aux_idPackage = new int[packagesOnSystem + 1];
    double *ptr_aux_weigth = new double[packagesOnSystem + 1];
    string *ptr_aux_destiny = new string[packagesOnSystem + 1];
    int *ptr_aux_priority = new int[packagesOnSystem + 1];
    char *ptr_aux_state = new char[packagesOnSystem + 1];
    
    idPackage[0] = id;
    weigth[0] = peso;
    destiny[0] = destino;
    priority[0] = prioridad;
    state[0] = stado; 
    
    for (int i = 0; i < packagesOnSystem; i++) {

        ptr_aux_idPackage[i + 1] = idPackage[i];
        ptr_aux_weigth[i + 1] = weigth[i];
        ptr_aux_destiny[i + 1] = destiny[i];
        ptr_aux_priority[i + 1] = priority[i];
        ptr_aux_state[i + 1] = state[i];

    }
    
    delete[] idPackage;
    delete[] weigth;
    delete[] destiny;
    delete[] priority;
    delete[] state;

    idPackage = ptr_aux_idPackage;
    weigth = ptr_aux_weigth;
    destiny = ptr_aux_destiny;
    priority = ptr_aux_priority;
    state = ptr_aux_state;

}