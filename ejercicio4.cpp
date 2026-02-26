#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

// Creamos un "candado" global para proteger la escritura del archivo
mutex mtx; 

// Función que ejecutará cada thread
void escribirArchivo(int threadID, ofstream& archivo) {
    // lock_guard bloquea el mutex. Si otro thread intenta entrar aquí, 
    // tendrá que esperar su turno.
    lock_guard<mutex> lock(mtx); 
    
    // Al estar protegido, garantizamos que la línea se escriba completa y correcta
    archivo << "Texto escrito correctamente por el thread numero: " << threadID << "\n";
}

int main() {
    // Abrimos el archivo de texto plano
    std::ofstream archivo("salida_hilos.txt");
    
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Vector para guardar y manejar nuestros 5 threads
    std::vector<thread> threads;

    // Lanzamos los 5 threads
    for (int i = 1; i <= 5; ++i) {
        threads.push_back(thread(escribirArchivo, i, ref(archivo)));
    }

    // Unimos (join) los threads al proceso principal para esperar a que terminen
    for (auto& t : threads) {
        t.join();
    }

    archivo.close();
    cout << "Programa finalizado. Revisa el archivo salida_hilos.txt" << endl;
    return 0;
}