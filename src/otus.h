//
// Created by xMellox on 10-Sep-20.
//

#ifndef OTUS_CPP_6_OTUS_H
#define OTUS_CPP_6_OTUS_H

#include "Matrix.h"

struct otus
{
    static void start()
    {
        init_matrix();
        showDiagonals();
        showSize();
        showValues();
    }

private:
    static Matrix<int,2,0> m;

    static void init_matrix()
    {
        for(std::size_t i{}; i < 9; ++i)
        {
            m[i][i] = i;
            m[i][9 - i] = 9 - i;
        }
    }

    static void showDiagonals()
    {
        for(std::size_t i{1}; i < 9; ++i)
        {
            for(std::size_t j{1}; j < 9; ++j)
            {
                std::cout << m[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    static void showSize()
    {
        std::cout << m.size() << '\n';
    }

    static void showValues()
    {
        for(const auto v : m)
        {
            std::cout << v << '\n';
        }
    }
};

Matrix<int,2,0> otus::m;

#endif //OTUS_CPP_6_OTUS_H
