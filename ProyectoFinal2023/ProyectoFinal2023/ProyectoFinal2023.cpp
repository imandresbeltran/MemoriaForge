#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

#include "DataSet.h"
#include "Node.h"
#include "DoublyLinkedList.h"
#include <openssl/sha.h>

//Función para generar una llave hash utilizando SHA-256

std::string hashFunction(const std::string& key) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, key.c_str(), key.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    return ss.str().substr(0, 10);
}

//Función para cargar datos desde un archivo

void loadData(DoublyLinkedList& list, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> values;

        while (std::getline(ss, item, ','))
            values.push_back(item);

        std::string key = values.front();
        values.erase(values.begin());
        DataSet* dataSet = new DataSet(key, values);
        std::string hashKey = hashFunction(key);
        Node* node = new Node(hashKey, dataSet);
        list.insertNode(node);
    }

    file.close();

    insertionSort(list);
}

//Método de ordenamiento

void insertionSort(DoublyLinkedList& list) {
    if (list.head == nullptr || list.head->next == nullptr)
        return;

    Node* sorted = nullptr;
    Node* current = list.head;

    while (current != nullptr) {
        Node* next = current->next;
        if (sorted == nullptr || sorted->hashKey >= current->hashKey) {
            current->next = sorted;
            if (sorted != nullptr)
                sorted->prev = current;

            sorted = current;
        }
        else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->hashKey < current->hashKey)
                temp = temp->next;

            current->next = temp->next;
            if (temp->next != nullptr)
                temp->next->prev = current;

            temp->next = current;
            current->prev = temp;
        }

        current = next;
    }

    list.head = sorted;
    list.head->prev = nullptr;

    Node* tail = list.head;

    while (tail != nullptr && tail->next != nullptr)
        tail = tail->next;

    list.tail = tail;
}

//Función para buscar los datos por llave
void searchByKey(DoublyLinkedList& list, const std::string& key) {
    std::string hashedKey = hashFunction(key);
    Node* node = list.searchNode(hashedKey);

    if (node != nullptr) {
        std::cout << "Datos encontrados: " << std::endl;
        for (const std::string& value : node->dataSet->values)
            std::cout << value << std::endl;
    }
    else
        std::cout << "No se encontraron los datos con esa llave" << std::endl;
}


//Función para buscar datos por valor

void searchByValue(DoublyLinkedList& list, const std::string& value) {
    Node* current = list.head;
    while (current != nullptr) {
        if (std::find(current->dataSet->values.begin(), current->dataSet->values.end(), value) != current->dataSet->values.end()) {
            std::cout << "Datos encontrados: " << std::endl;
            for (const std::string& value : current->dataSet->values)
                std::cout << value << std::endl;
        }

        current = current->next;
    }
}


//Función para buscar datos por valor utilizando búsqueda binaria

void binarySearchByValue(DoublyLinkedList& list, const std::string& value) {
    Node* current = list.head;
    while (current != nullptr) {
        auto it = std::lower_bound(current->dataSet->values.begin(), current->dataSet->values.end(), value);
        if (it != current->dataSet->values.end() && *it == value) {
            std::cout << "Datos encontrados: " << std::endl;
            for (const std::string& value : current->dataSet->values)
                std::cout << value << std::endl;
        }

        current = current->next;
    }
}

int main()
{
    DoublyLinkedList list;

    std::string filename;
    std::cout << "Ingresa la ruta del archivo: ";
    std::cin >> filename;

    loadData(list, filename);

    int option = 0;

    do {
        std::cout << "1. Cargar más datos\n2. Buscar por llave\n3. Buscar por valor\n4. Búsqueda binaria por valor\n5. Salir\nElige una opción: ";
        std::cin >> option;

        switch (option) {
        case 1: {
            std::cout << "Introduce la ruta del archivo: ";
            std::cin >> filename;
            loadData(list, filename);
            break;
        }

        case 2: {
            std::string key;
            std::cout << "Introduce la clave: ";
            std::cin >> key;
            searchByKey(list, key);
            break;
        }

        case 3: {
            std::string value;
            std::cout << "Introduce el valor: ";
            std::cin >> value;
            searchByValue(list, value);
            break;
        }
        case 4: {
            std::string value;
            std::cout << "Introduce un valor a buscar: ";
            std::cin >> value;
            binarySearchByValue(list, value);
            break;
        }
        case 5: {
            std::cout << "Saliendo..." << std::endl;
            break;
        }
        default: {
            std::cout << "La opción ingresada no es válida... Intentalo de nuevo " << std::endl;
            break;
        }

        }
    } while (option != 5);
}

