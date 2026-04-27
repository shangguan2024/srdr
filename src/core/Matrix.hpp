#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"
#include <array>
#include <cstddef>

namespace srdr {

template<typename T, std::size_t N, std::size_t M>
class Matrix {
public:
    Matrix();

    std::array<Vector<T, M>, N> data;

    T& operator()(std::size_t row, std::size_t col);
    const T& operator()(std::size_t row, std::size_t col) const;

    Vector<T, M>& operator[](std::size_t row);
    const Vector<T, M>& operator[](std::size_t row) const;

    static Matrix identity();

    static Matrix zero();

    Matrix<T, M, N> transposed() const;
};

using Mat3 = Matrix<float, 3, 3>;
using Mat4 = Matrix<float, 4, 4>;

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M>::Matrix()
        : data{} {}

template<typename T, std::size_t N, std::size_t M>
T& Matrix<T, N, M>::operator()(std::size_t row, std::size_t col) {
    return data[row][col];
}

template<typename T, std::size_t N, std::size_t M>
const T& Matrix<T, N, M>::operator()(std::size_t row, std::size_t col) const {
    return data[row][col];
}

template<typename T, std::size_t N, std::size_t M>
Vector<T, M>& Matrix<T, N, M>::operator[](std::size_t row) {
    return data[row];
}

template<typename T, std::size_t N, std::size_t M>
const Vector<T, M>& Matrix<T, N, M>::operator[](std::size_t row) const {
    return data[row];
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> Matrix<T, N, M>::identity() {
    Matrix m;
    for (std::size_t i = 0; i < N && i < M; ++i) {
        m.data[i][i] = T(1);
    }
    return m;
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, N, M> Matrix<T, N, M>::zero() {
    Matrix m;
    for (auto& row: m.data) {
        for (auto& elem: row.data) {
            elem = T(0);
        }
    }
    return m;
}

template<typename T, std::size_t N, std::size_t M>
Matrix<T, M, N> Matrix<T, N, M>::transposed() const {
    Matrix<T, M, N> result;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < M; ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

// Matrix * ColumnVector
template<typename T, std::size_t N, std::size_t M>
Vector<T, N> operator*(const Matrix<T, N, M>& mat, const Vector<T, M>& vec) {
    Vector<T, N> result;
    for (std::size_t i = 0; i < N; ++i) {
        T sum = T(0);
        for (std::size_t j = 0; j < M; ++j) {
            sum += mat.data[i][j] * vec[j];
        }
        result[i] = sum;
    }
    return result;
}

// Matrix * Matrix
template<typename T, std::size_t N, std::size_t K, std::size_t M>
Matrix<T, N, M> operator*(const Matrix<T, N, K>& a, const Matrix<T, K, M>& b) {
    Matrix<T, N, M> result = Matrix<T, N, M>::zero();
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t k = 0; k < K; ++k) {
            for (std::size_t j = 0; j < M; ++j) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

} // namespace srdr

#endif // MATRIX_HPP
