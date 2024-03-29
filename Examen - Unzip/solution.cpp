/*
 * ---------------------------------------------------
 *     ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregir� el c�digo contenido entre
  * las etiquetas <answer> y </answer>. Toda modificaci�n fuera
  * de esas etiquetas no ser� corregida.
  */

  /*@ <answer>
   *
   * Nombre y apellidos: ____________________________________________________
   *
   *@ </answer> */

   /*
    * Implementa las operaciones pedidas en el ejercicio al final de
    * este fichero, entre las etiquetas.
    */


#include <iostream>
#include <fstream>
#include <cassert>

    /* --------------------------------------------------------------------
     * Clase ListLinkedSingle
     * --------------------------------------------------------------------
     * Implementa el TAD lista mediante una lista enlazada simple con
     * nodo fantasma y punteros al primer y �ltimo elemento.
     * --------------------------------------------------------------------
     */

template<typename T>
class ListLinkedSingle {
private:
    struct Node {
        T value;
        Node* next;
    };

public:
    ListLinkedSingle() : num_elems(0) {
        head = new Node;
        head->next = nullptr;
        last = head;
    }

    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)), num_elems(other.num_elems) {
        last = last_node();
    }

    void push_front(const T& elem) {
        Node* new_node = new Node{ elem, head->next };
        if (head->next == nullptr) { last = new_node; }
        head->next = new_node;
        num_elems++;
    }

    void push_back(const T& elem);

    void pop_front() {
        assert(num_elems > 0);
        Node* old_head = head->next;
        head->next = head->next->next;
        if (head->next == nullptr) { last = head; }
        delete old_head;
        num_elems--;
    }

    void pop_back();

    int size() const {
        return num_elems;
    }

    bool empty() const {
        return num_elems == 0;
    };

    const T& front() const {
        assert(num_elems > 0);
        return head->next->value;
    }

    T& front() {
        assert(num_elems > 0);
        return head->next->value;
    }

    const T& back() const {
        return last->value;
    }

    T& back() {
        return last->value;
    }

    const T& operator[](int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    T& operator[](int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    ListLinkedSingle& operator=(const ListLinkedSingle& other) {
        if (this != &other) {
            delete_list(head);
            head = copy_nodes(other.head);
            last = last_node();
            num_elems = other.num_elems;
        }
        return *this;
    }

    void display(std::ostream& out) const;

    void display() const {
        display(std::cout);
    }

    void unzip(ListLinkedSingle& dest);

private:
    Node* head;
    Node* last;
    int num_elems;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;
};

template<typename T>
typename ListLinkedSingle<T>::Node* ListLinkedSingle<T>::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node{ start_node->value, copy_nodes(start_node->next) };
        return result;
    }
    else {
        return nullptr;
    }
}

template<typename T>
void ListLinkedSingle<T>::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

template<typename T>
void ListLinkedSingle<T>::push_back(const T& elem) {
    Node* new_node = new Node{ elem, nullptr };
    last->next = new_node;
    last = new_node;
    num_elems++;
}

template<typename T>
void ListLinkedSingle<T>::pop_back() {
    assert(num_elems > 0);
    Node* previous = head;
    Node* current = head->next;

    while (current->next != nullptr) {
        previous = current;
        current = current->next;
    }

    delete current;
    previous->next = nullptr;
    last = previous;
    num_elems--;
}

template<typename T>
typename ListLinkedSingle<T>::Node* ListLinkedSingle<T>::last_node() const {
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

template<typename T>
typename ListLinkedSingle<T>::Node* ListLinkedSingle<T>::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head->next;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

template<typename T>
void ListLinkedSingle<T>::display(std::ostream& out) const {
    out << "[";
    if (head->next != nullptr) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}


template<typename T>
std::ostream& operator<<(std::ostream& out, const ListLinkedSingle<T>& l) {
    l.display(out);
    return out;
}

/* --------------------------------------------------------------------
 * Implementa el m�todo pedido aqu�
 * --------------------------------------------------------------------
 *
 * Puedes a�adir los m�todos privados auxiliares que quieras. Para eso
 * puedes declararlos en la clase, pero has de implementarlos aqu�, entre
 * las etiquetas <answer> y </answer>.
 *
 *@ <answer>
 */


template <typename T>
void ListLinkedSingle<T>::unzip(ListLinkedSingle& dest) {
    int pos = 0;
    Node* prev = this->head;
    Node* actual = this->head->next;
    while (actual != nullptr) {
        if (pos % 2 != 0) { //Es impar
            dest.push_back(actual->value);
            prev->next = actual->next;
            actual = prev->next;
        }
        else {
            prev = prev->next;
            actual = actual->next;
        }
        pos++;
    }
}

/*@ </answer> */

using namespace std;



void leer_lista(ListLinkedSingle<int>& l) {
    int num_elems;
    cin >> num_elems;

    for (int i = 0; i < num_elems; i++) {
        int elem;
        cin >> elem;
        l.push_back(elem);
    }
}


// Funci�n para tratar cada uno de los casos de prueba
void tratar_caso() {
    ListLinkedSingle<int> l1, l2;
    leer_lista(l1);
    leer_lista(l2);
    l1.unzip(l2);

    cout << l1 << endl << l2 << endl;
}

int main() {
    int num_casos;
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    std::cin >> num_casos;

    while (num_casos > 0) {
        tratar_caso();
        num_casos--;
    }


#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // Comentar si no se trabaja en Visual Studio
    system("PAUSE");
#endif

    return 0;
}

// SALT: ##