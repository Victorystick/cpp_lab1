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

Matrix::~Matrix() {}

Matrix& Matrix::transpose() {
	Matrix m (cols(), rows());

	for (index i = 0; i < rows(); ++i) {
		for (index j = 0; j < cols(); ++j) {
			m[j][i] = m_vectors[i][j];
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

Matrix Matrix::operator+ ( const Matrix& other) const {
	if (other.cols() != cols() || other.rows() != rows()) {
		throw std::out_of_range("Incompatible sizes");
	}

	Matrix res (cols(), rows());
	for (index i = 0; i < rows(); ++i) {
		for (index j = 0; j < cols(); ++j) {
			res[j][i] = m_vectors[j][i] + other[j][i];
		}
	}
	return res;
}

Matrix Matrix::operator- ( const Matrix& other) const {
	if (other.cols() != cols() || other.rows() != rows()) {
		throw std::out_of_range("Incompatible sizes");
	}

	Matrix res (cols(), rows());
	for (index i = 0; i < rows(); ++i) {
		for (index j = 0; j < cols(); ++j) {
			res[j][i] = m_vectors[j][i] - other[j][i];
		}
	}
	return res;
}

Matrix Matrix::operator* ( int coefficient) const {
	Matrix res (cols(), rows());
	for (index i = 0; i < rows(); ++i) {
		for (index j = 0; j < cols(); ++j) {
			res[j][i] = m_vectors[j][i] * coefficient;
		}
	}
	return res;
}

Matrix & Matrix::operator=(const Matrix & m) {
	m_vectors = Vector<matrix_row>(m.rows());

	for (index i = 0; i < rows(); ++i) {
		matrix_row & r = m_vectors[i] = matrix_row(cols());
		for (index j = 0; j < cols(); ++j) {
			r[j] = m[i][j];
		}
	}

	return *this;
}

Matrix Matrix::operator-() const {
	Matrix m (rows(), cols());

	for (index i = 0; i < rows(); ++i) {
		for (index j = 0; j < cols(); ++j) {
			m[j][i] = -m_vectors[j][i];
		}
	}

	return m;
}

std::istream& operator>> ( std::istream& in, Matrix& m) {
	// Clear internal vectors.
	m.m_vectors = Vector<Matrix::matrix_row>();

	Matrix::matrix_row row;
	char chr;
	int num;

	in >> std::ws >> chr >> std::ws; // No error handling. Always starts with '['

	chr = in.peek();

	// Determine when end of row.
	while (chr != ';') {
		in >> num;
		row.push_back(num);
		in >> std::ws;
		chr = in.peek();
	}

	m.m_cols = row.size();

	m.m_vectors.push_back(row);

	while (chr != ']') {
		Matrix::matrix_row row;
		for (Matrix::index i = 0; i < m.cols(); ++i) {
			in >> num;
			row.push_back(num);
		}
		m.m_vectors.push_back(row);

		// eat ';' or ']'
		in >> chr;
	}

	m.m_rows = m.m_vectors.size();

	return in;
}

std::ostream& operator<< ( std::ostream& out, Matrix& m) {
	out << "[ ";

	for (Matrix::index i = 0; i < m.rows();) {
		for (Matrix::index j = 0; j < m.cols(); ++j) {
			out << m[i][j] << ' ';
		}

		if (++i != m.rows()) {
			out << "\n; ";
		} else {
			break;
		}
	}

	return out << "]";
}
