#include "Matrix.h"

Matrix::Matrix() :
	m_rows(0),
	m_cols(0)
{
}

Matrix::Matrix(std::size_t size) :
	m_vectors(size, matrix_row(size)),
	m_rows(size),
	m_cols(size)
{
	index i = 0;

	for (matrix_row & v : m_vectors) {
		v[i++] = 1;
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
	m_vectors(rows, matrix_row(cols)),
	m_rows(rows),
	m_cols(cols)
{
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
	if (i >= rows()) {
		throw std::out_of_range("index out of bounds");
	}
	return m_vectors[i];
}

const Matrix::matrix_row& Matrix::operator[](index i) const {
	if (i >= rows()) {
		throw std::out_of_range("index out of bounds");
	}

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

	Matrix res (rows(), cols());
	for (index i = 0; i < rows(); ++i) {
		for (index j = 0; j < cols(); ++j) {
			res[i][j] = m_vectors[i][j] + other[i][j];
		}
	}
	return res;
}

Matrix Matrix::operator- ( const Matrix& other) const {
	if (other.cols() != cols() || other.rows() != rows()) {
		throw std::out_of_range("Incompatible sizes");
	}

	Matrix res (rows(), cols());
	for (index i = 0; i < rows(); ++i) {
		for (index j = 0; j < cols(); ++j) {
			res[i][j] = m_vectors[i][j] - other[i][j];
		}
	}
	return res;
}

Matrix Matrix::operator* ( int coefficient) const {
	Matrix res (rows(), cols());
	for (index i = 0; i < rows(); ++i) {
		for (index j = 0; j < cols(); ++j) {
			res[i][j] = m_vectors[i][j] * coefficient;
		}
	}
	return res;
}

Matrix Matrix::operator* (const Matrix & m) const {
	if (m.rows() != cols()) {
		throw std::out_of_range("Incompatible matrices"); //std::domain_error?
	}

	Matrix res (m.rows(), cols());
	for (index k = 0; k < res.cols(); ++k) {
		for (index i = 0; i < rows(); ++i) {
			for (index j = 0; j < cols(); ++j) {
				res[i][k] += m_vectors[i][j] * m[j][k];
			}
		}
	}

	return res;
}

Matrix & Matrix::operator=(const Matrix & m) {
	m_vectors = Vector<matrix_row>(m.rows());
	m_rows = m.rows();
	m_cols = m.cols();

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
			m[i][j] = -m_vectors[i][j];
		}
	}

	return m;
}

std::istream& operator>> ( std::istream& in, Matrix& m) {
	// Clear internal vectors.
	m.m_vectors = std::move(Vector<Matrix::matrix_row>());

	Matrix::matrix_row row;
	char chr;
	int num;

	in >> std::ws >> chr >> std::ws; // No error handling. Always starts with '['

	chr = in.peek();

	// Determine when end of row.
	while (chr != ';' && chr != ']') {
		in >> num;
		row.push_back(num);
		in >> std::ws;
		chr = in.peek();
	}

	m.m_cols = row.size();

	m.m_vectors.push_back(row);

	// eat ';' or ']'
	in >> std::ws >> chr >> std::ws;

	while (chr != ']') {
		Matrix::matrix_row row;

		for (Matrix::index i = 0; i < m.cols(); ++i) {
			in >> num;
			row.push_back(num);
		}
		m.m_vectors.push_back(row);

		// eat ';' or ']'
		in >> std::ws >> chr >> std::ws;
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
