#include "Matrix.h"

Matrix::Matrix() : m_rows(0), m_cols(0) {}

Matrix::Matrix(std::size_t size) : m_vectors(size), m_rows(size), m_cols(size) {
	std::size_t i = 0;

	for (Vector & v : m_vectors) {
		v = Vector(size);

		v[i] = 1;

		++i;
	}
}

Matrix::Matrix(const Matrix & m) : m_vectors(m.m_rows), m_rows(m.m_rows), m_cols(m.m_cols) {
	for (std::size_t i = 0; i < m_rows; ++i) {
		Vector & v = m_vectors[i];

		v = Vector(m_cols);

		for (std::size_t j = 0; j < m_cols; ++j) {
			v[j] = m.m_vectors[i][j];
		}
	}
}
