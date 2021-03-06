/*
 * Created by Ivan Istomin on Alprazolam.
 */

// хэдер для задания

#ifndef HSE_VECTOR_H
#define HSE_VECTOR_H

#include <ostream>
#include <iostream>
// ... другие include директивы ...

// рассматривается упрощенный шаблон класса Vector< >
// как "обёртка" вокруг динамического массива произвольной
// длины 
template<typename T>
class Vector
{
public:
    enum
    {
        CAPACITY = 8
    };

    // конструктор
    // edit: changed the initialization of VSize to 0, because use it as a pointer
    explicit Vector(std::size_t init_size = 0) : VSize(0), VCapacity(init_size + CAPACITY)
    {
        std::cout << "Ctor\n";
        vec = new T[VCapacity];
    };

    // конструктор копирования
    Vector(const Vector &right) : vec(new T[right.size()])
    {
        std::cout << "CCtor\n";
        operator=(right);
    }

    // конструктор перемещения
    Vector(Vector &&right) noexcept : vec(nullptr)
    {
        std::cout << "CtorMove\n";

        // I'm tired
        operator=(std::move(right));
    }

    // деструктор
    ~Vector() noexcept
    {
        std::cout << "Dtor\n";
        delete[] vec;
    }

    Vector& operator=(const Vector& right)
    {
        VSize = right.size();
        VCapacity = right.capacity();

        for (std::size_t i = 0; i < VSize; ++i)
        {
            vec[i] = right[i];
        }

        return *this;
    }

    Vector& operator=(Vector&& right)
    {
        if (this != &right)
        {
            delete[] vec;

            vec = right.vec;
            VSize = right.VSize;
            VCapacity = right.VCapacity;

            right.vec = nullptr;
            right.VSize = 0;
            right.VCapacity = 8;
        }

        return *this;
    }

    void resize(std::size_t newSize)
    {
        if (newSize > VCapacity)
            reserve(newSize * 2 + 1);

        VSize = newSize;
    }

    void reserve(size_t newCapacity)
    {
        if (newCapacity > VCapacity)
        {
            T* tmp = new T[newCapacity];
            std::copy(vec, vec + VSize, tmp);

            delete vec;
            vec = tmp;
            VCapacity = newCapacity;
        }
    }

    T& operator[](int index)
    {
        return vec[index];
    }

    const T& operator[](int index) const
    {
        return vec[index];
    }

    bool empty() const
    {
        return VSize == 0;
    }

    std::size_t size() const
    {
        return VSize;
    }

    std::size_t capacity() const
    {
        return VCapacity;
    }

    T& front()
    {
        return vec[0];
    }

    const T& front() const
    {
        return vec[0];
    }

    T& back()
    {
        return vec[VSize - 1];
    }

    const T& back() const
    {
        return vec[0];
    }

    void push_back(const T& val)
    {
        if (VSize == VCapacity)
            reserve(VSize * 2 + 1);

        vec[VSize] = val;
        VSize += 1;
    };

    void push_back(T&& val)
    {
        if (VSize == VCapacity)
            reserve(VSize * 2 + 1);

        vec[VSize] = val;
        VSize += 1;
        val = nullptr;
    };

    void pop_back()
    {
        if (!empty())
            VSize -= 1;
    };

    // Good place
    typedef T* viterator;

    viterator begin() const
    {
        return vec;
    }

    viterator end() const
    {
        return vec + VSize;
    }

    template<typename T1>
    friend std::ostream &operator<<(std::ostream &out, const Vector<T1> &obj)
    {
        // вывод по 10 элементов в одной строке (переменная num).
        int num = 0;
        for (auto &i : obj) {
            out << i << " ";
            ++num;
            if (num / 11) {
                std::cout << std::endl;
                num = 0;
            }
        }
        std::cout << std::endl;
        return out;
    }

private:
    std::size_t VSize;
    std::size_t VCapacity;
    T* vec;
};

#endif
    
