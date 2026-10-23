#include <iostream>
#include <algorithm>
#include <clocale>
using namespace std;

template <typename T>
class Vector {
private:
    T* data;
    int sz;
    int cap;

public:
    // Конструктор
    Vector() {
        data = nullptr;
        sz = 0;
        cap = 0;
    }

    // 1. Конструктор копирования
    Vector(const Vector& other) {
        sz = other.sz;
        cap = other.cap;
        data = new T[cap];

        for (int i = 0; i < sz; i++) {
            data[i] = other.data[i];
        }
    }

    // 2. Оператор копирующего присваивания
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        sz = other.sz;
        cap = other.cap;
        data = new T[cap];

        for (int i = 0; i < sz; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    // 3. Конструктор перемещения
    Vector(Vector&& other) noexcept {
        data = other.data;
        sz = other.sz;
        cap = other.cap;

        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;
    }

    // 4. Оператор перемещающего присваивания
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] data;

        data = other.data;
        sz = other.sz;
        cap = other.cap;

        other.data = nullptr;
        other.sz = 0;
        other.cap = 0;

        return *this;
    }

    // 5. Деструктор
    ~Vector() {
        delete[] data;
    }

    // Добавление элемента в конец
    void push_back(const T& value) {
        if (sz == cap) {
            int newCap = (cap == 0) ? 1 : cap * 2;
            T* newData = new T[newCap];

            for (int i = 0; i < sz; i++) {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            cap = newCap;
        }

        data[sz] = value;
        sz++;
    }

    // Итераторы
    T* begin() {
        return data;
    }

    T* end() {
        return data + sz;
    }

    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + sz;
    }

    // Циклический сдвиг влево
    void rotate(int k) {
        if (sz == 0) {
            return;
        }

        k = k % sz;

        if (k < 0) {
            k += sz;
        }

        rotate(begin(), begin() + k, end());
    }

    // Вывод вектора
    void print() const {
        for (int i = 0; i < sz; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    cout << "Исходный вектор: ";
    v.print();

    v.rotate(2);

    cout << "После rotate(2): ";
    v.print();

    v.rotate(1);

    cout << "После rotate(1): ";
    v.print();

    v.rotate(-2);

    cout << "После rotate(-2): ";
    v.print();

    return 0;
}
