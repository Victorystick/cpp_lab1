#include "../Vector/Vector.hpp"
#include "Matrix.h"

Matrix::Matrix() :
	m_rows(0),
	m_cols(0)
{
}

Matrix::Matrix(std::size_t size) :
	m_vectors(size),
	m_rows(size),
	m_cols(size)
{
	index i = 0;

	for (matrix_row & v : m_vectors) {
		v = matrix_row(size);

		v[i] = 1;

		++i;
	}
}

Matrix::Matrix(const Matrix & m) :
	m_vectors(m.m_rows),
	m_rows(m.m_rows),
	m_cols(m.m_cols)
{
	for (index i = 0; i < m_rows; ++i) {
		matrix_row & v = m_vectors[i];

		v = matrix_row(m_cols);

		for (index j = 0; j < m_cols; ++j) {
			v[j] = m.m_vectors[i][j];
		}
	}
}

Matrix::Matrix(std::size_t rows, std::size_t cols) :
	m_vectors(rows),
	m_rows(rows),
	m_cols(cols)
{
	for (matrix_row & v : m_vectors) {
		v = matrix_row(cols);
	}
}

Matrix& Matrix::transpose() {
	Matrix m (cols(), rows());

	for (index i = 0; i < rows(); ++i) {
		for (index j = 0; j < cols(); ++j) {
			m[j][i] = m_vectors[j][i];
		}
	}

	std::swap(m, *this);

	return *this;
}

Matrix::matrix_row& Matrix::operator[](index i) {
	return m_vectors[i];
}

const Matrix::matrix_row& Matrix::operator[](index i) const {
	return m_vectors[i];
}

std::size_t Matrix::rows() const {
	return m_rows;
}

std::size_t Matrix::cols() const {
	return m_cols;
}
