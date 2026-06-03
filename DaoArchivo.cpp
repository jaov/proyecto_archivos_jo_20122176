#include <vector>
#include <type_traits>
#include <cstddef>

template <typename T>
class DaoArchivo {
     std::string nombreArchivo;
     public:
	 DaoArchivo(std::string na) : nombreArchivo(na) {
	     static_assert(std::is_standard_layout<T>::value, "T debe ser standard");
	     static_assert(offsetof(T,id)>= 0, "T tiene que tener id");
	     static_assert(offsetof(T,borrado_en)>= 0, "T tiene que tener borrado_en");
	 }

     // CREATE
     int crear(T& item) {
	 
         std::fstream file(nombreArchivo, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
	 if(!file.is_open()) {
	    file.clear();
	    file.open(nombreArchivo, std::ios::binary | std::ios::out | std::ios::app);
	 }
	 // Voy hasta el final de archivo
	 file.seekp(0, std::ios::end);

	 // mido tamaño con tell put position
	 int tamanoArchivo = file.tellp();
	 // se el id porque el tamaño de mis estructuras es fijo
	 int nuevoId = tamanoArchivo / sizeof(T);
	 // lo uso para dar valor
	 item.id = nuevoId;
         file.write(reinterpret_cast<const char*>(&item), sizeof(T));
	 file.close(); //muy importante

	 return nuevoId;
     }

     // READ
     T encontrarPorId(int id) {
         T item;
         std::ifstream file(nombreArchivo, std::ios::binary);
         file.seekg(id * sizeof(T));
         file.read(reinterpret_cast<char*>(&item), sizeof(T));
         return item;
     }
     
     // UPDATE
     template <typename C> // C de campo
    
    
    // para el offset se usa offsetof(T, campo)
     int actualizarCampo(int id, size_t offset, const C& nuevoValor) {
	 std::fstream file(nombreArchivo, std::ios::binary | std::ios::in |
		 std::ios::out);

	 if(!file.is_open()) return 1;

	 // Calcular posicion
	 // id*sizeof(T) me da la "fila"
	 // sumar offset es la "columna"
	 // Gracias Joel Spolsky
	 size_t posicionCampo = (id * sizeof(T)) + offset;

	 // Me muevo a esa posicion
	 file.seekp(posicionCampo);

	 // uso el tamaño del campo
	 file.write(reinterpret_cast<const char*>(&nuevoValor), sizeof(C));

	 file.close();

	 return 0;
     }

     // no funciona con char[] por el comparador ==
    template <typename C>
    std::vector<T> listarPorCampo(size_t offset, const C& valorBuscado) {
	std::vector<T> resultados;
	std::ifstream file(nombreArchivo, std::ios::binary);
	if(!file.is_open()) return resultados;

	file.seekg(0, std::ios::end);
	size_t numRecords = file.tellg() / sizeof(T);

	for(size_t i = 0; i<numRecords; ++i) {
	    C valorCampo;

	    // Ir al campo directamente
	    file.seekg((i*sizeof(T)) + offset);
	    file.read(reinterpret_cast<char*>(&valorCampo), sizeof(C));

	    if(valorCampo == valorBuscado) {
		file.seekg(i*sizeof(T));
		T item;
		file.read(reinterpret_cast<char*>(&item), sizeof(T));

		if(item.borrado_en == 0) {
		    resultados.push_back(item);
		}
	    }
	}

	return resultados;
    }

    // LISTAR POR STRING
    std::vector<T> listarPorString(size_t offset, const char* valorBuscado, size_t bufferSize) {
        std::vector<T> resultados;
        std::ifstream file(nombreArchivo, std::ios::binary);
        if(!file.is_open()) return resultados;

        file.seekg(0, std::ios::end);
        size_t numRecords = file.tellg() / sizeof(T);

        std::vector<char> buffer(bufferSize);

        for(size_t i = 0; i<numRecords; ++i) {
            // Ir al campo directamente
            file.seekg((i*sizeof(T)) + offset);
            file.read(buffer.data(), bufferSize);

            if(std::strncmp(buffer.data(), valorBuscado, bufferSize) == 0) {
                file.seekg(i*sizeof(T));
                T item;
                file.read(reinterpret_cast<char*>(&item), sizeof(T));

                if(item.borrado_en == 0) {
                    resultados.push_back(item);
                }
            }
        }
        return resultados;
    }

    int eliminar(int id) {
	time_t ahora = std::time(nullptr);
	actualizarCampo(id, offsetof(T, borrado_en), ahora);
	return 0;
    }
};
