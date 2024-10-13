#include <iostream>
#include <fstream>

using namespace std;

struct persona
{
    int id;
    string nombre;
    double sueldo;
};

bool lectura(persona arr[], int &n);

class maxHeap
{
private:
    static const int MAX_tam = 1200;
    persona heap[MAX_tam];
    int tam;

    int padre(int index)
    {
        return (index - 1) / 2;
    }

    int hijoIzq(int index)
    {
        return 2 * index + 1;
    }

    int hijoDer(int index)
    {
        return 2 * index + 2;
    }

    bool tieneHijoIzq(int index)
    {
        return hijoIzq(index) < tam;
    }

    bool tieneHijoDer(int index)
    {
        return hijoDer(index) < tam;
    }

    bool tienePadre(int index)
    {
        return padre(index) >= 0;
    }

    void swap(int indexUno, int indexDos)
    {
        persona temp = heap[indexUno];
        heap[indexUno] = heap[indexDos];
        heap[indexDos] = temp;
    }

    void agruparUp()
    {
        int index = tam - 1;
        while (tienePadre(index) && heap[padre(index)].sueldo < heap[index].sueldo)
        {
            swap(padre(index), index);
            index = padre(index);
        }
    }

    void agruparDo()
    {
        int index = 0;
        while (tieneHijoIzq(index))
        {
            int hijoMayorIndex = hijoIzq(index);
            if (tieneHijoDer(index) && heap[hijoDer(index)].sueldo > heap[hijoMayorIndex].sueldo)
            {
                hijoMayorIndex = hijoDer(index);
            }

            if (heap[index].sueldo > heap[hijoMayorIndex].sueldo)
            {
                break;
            }

            swap(index, hijoMayorIndex);
            index = hijoMayorIndex;
        }
    }

public:
    maxHeap() : tam(0) {}

    void insertar(persona elemento)
    {
        if (tam == MAX_tam)
        {
            std::cout << "El heap está lleno, no se puede insertar más elementos." << std::endl;
            return;
        }
        heap[tam] = elemento;
        tam++;
        agruparUp();
    }

    persona eliminarMax()
    {
        if (tam == 0)
        {
            std::cout << "El heap está vacío, no se puede eliminar el máximo." << std::endl;
            persona p = {-1, "", 0.0};
            return p;
        }
        persona maxElement = heap[0];
        heap[0] = heap[tam - 1];
        tam--;
        agruparDo();
        return maxElement;
    }

    void mostrarHeap()
    {
        cout << "Contenido del heap: " << endl;
        for (int i = 0; i < tam; ++i)
        {
            cout << heap[i].id << " " << heap[i].nombre << " " << heap[i].sueldo << endl;
        }
        cout << endl;
    }

    void headsort(persona arr[], int n)
    {
        maxHeap maxheap;
        for (int i = 0; i < n; ++i)
        {
            maxheap.insertar(arr[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            arr[i] = maxheap.eliminarMax();
        }
    };
};

int main()
{
    const int n = 1200;
    persona datos[n];
    int c = 0;

    if (!lectura(datos, c))
    {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    cout << "Número de elementos leídos: " << c << endl;

    if (c == 0)
    {
        cout << "No se leyeron datos del archivo." << endl;
        return 1;
    }

    maxHeap maxheap;
    maxheap.headsort(datos, c);

    cout << "Arreglo ordenado en orden descendente: " << endl;
    for (int i = 0; i < c; ++i)
    {
        cout << datos[i].id << " " << datos[i].nombre << " " << datos[i].sueldo << endl;
    }

    return 0;
}

bool lectura(persona arr[], int &n)
{
    ifstream archivo;
    archivo.open("/home/honic/Documentos/Honic/Proyectos/taller02_Algoritmos/datos.txt", ios::in);

    if (archivo.fail())
    {
        return false;
    }

    n = 0;
    while (archivo >> arr[n].id) 
    {
        archivo.ignore(); 
        getline(archivo, arr[n].nombre, '$'); 
        archivo >> arr[n].sueldo; 
        archivo.ignore(); 

        n++;

        if (n >= 1200)
        {
            break;
        }
    }

    archivo.close();

    return true;
}
