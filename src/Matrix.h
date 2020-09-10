//
// Created by xMellox on 08-Sep-20.
//

#ifndef OTUS_CPP_6_MATRIX_H
#define OTUS_CPP_6_MATRIX_H

#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

template<typename T, std::size_t Size, T DefaultValue>
struct Matrix
{
    template<std::size_t id>
    struct ProxyValue
    {
        ProxyValue(const std::string& paramKey, Matrix& paramMatrix)
        :
        key{paramKey},
        matrix{paramMatrix}
        {

        }

        auto operator[](std::size_t Elem)
        {
            static_assert(id < Size, "No more operators[] available");
            auto NewKey = key + Matrix::getDel() + std::to_string(Elem);
            return ProxyValue<id + 1>(NewKey,matrix);
        }

        ProxyValue<id>& operator=(const T& value)
        {
            static_assert(id == Size, "You are not at value, use Size amount of operators[]");
            matrix.Assign(key,value);
            return *this;
        }

        operator T () const
        {
            static_assert(id == Size, "You are not at value, use Size amount of operators[]");
            return matrix.Get(key);
        }

    private:
        std::string key;
        Matrix& matrix;
    };


    struct MatrixValue
    {
        MatrixValue(std::string paramKey, const T& paramV)
        :
        key{std::move(paramKey)},
        v{paramV}
        {

        }

        friend std::ostream& operator<<(std::ostream& os, const MatrixValue& Value)
        {
            Value.Show(os);
            return os;
        }

        std::string key;
        T v;

    private:
        std::vector<std::size_t> UnpackKey() const
        {
            std::vector<std::size_t> accessElems;
            char del = Matrix::getDel();
            const auto res_amount = std::count(key.cbegin(),key.cend(),del) + 1;
            accessElems.reserve(res_amount);

            std::size_t start{};
            std::size_t end = key.find_first_of(del);
            while(end != std::string::npos)
            {
                auto str_v = key.substr(start,end);
                const std::size_t index_v = std::stoi(str_v);
                accessElems.push_back(index_v);

                start = end + 1;
                end = key.find_first_of(del,start);
            }

            auto str_v = key.substr(start,key.size());
            const std::size_t index_v = std::stoi(str_v);
            accessElems.push_back(index_v);

            return accessElems;
        }

        void Show(std::ostream& os) const
        {
            auto indexes = UnpackKey();

            for(const auto i : indexes)
            {
                os << i << ' ';
            }

            os << v;
        }
    };

    struct MatrixIterator
    {
        using IteratorType = typename std::map<std::string,T>::iterator;
        explicit MatrixIterator(const IteratorType& paramIt)
        :
        it{paramIt}
        {

        }

        MatrixIterator& operator++()
        {
            ++it;
            return *this;
        }

        bool operator!=(const MatrixIterator& rhs) const noexcept
        {
            return it != rhs.it;
        }

        MatrixValue operator*() const
        {
            auto HashPair = *it;

            auto k = HashPair.first;
            auto v = HashPair.second;

            return ShowValue(k,v);
        }

    private:
        IteratorType it;
    };


    auto operator[](std::size_t row)
    {
        return ProxyValue<1>(std::to_string(row),*this);
    }

    void Assign(const std::string& Key, const T& Value)
    {
        auto it = values.find(Key);
        if(it != std::end(values))
        {
            if(Value == DefaultValue)
            {
                values.erase(it);
            }
            else
            {
                it->second = Value;
            }
        }
        else
        {
            values[Key] = Value;
        }
    }

    T Get(const std::string& Key) const
    {
        auto it = values.find(Key);

        if(it != std::end(values))
        {
            return it->second;
        }
        else
        {
            return DefaultValue;
        }
    }

    std::size_t size() const noexcept
    {
        return values.size();
    }

    static char getDel() noexcept
    {
        return del;
    }

    MatrixIterator begin() { return MatrixIterator(values.begin()); }
    MatrixIterator end() { return MatrixIterator(values.end()); }

private:
    static char del;
    mutable std::map<std::string, T> values;
};

template<typename T, std::size_t Size, T DefaultValue>
char Matrix<T,Size,DefaultValue>::del = '_';

#endif //OTUS_CPP_6_MATRIX_H
