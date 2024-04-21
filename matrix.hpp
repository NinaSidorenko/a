#ifndef Matrix_HPP
#define Matrix_HPP

#include <iostream>
#include <fstream>

template <typename T>
class Matrix
{
        size_t matr_rows;
        size_t matr_cols;
        T** matrix;

        Matrix (const Matrix<T>& matr, size_t row, size_t col): matr_rows (matr.matr_rows - 1), matr_cols(matr.matr_cols - 1), matrix (NULL)//создание алгебраического дополнения
        {
            if (matr.matrix != NULL)
            {
                matrix = new T* [matr_rows];
                for (size_t i = 0; i < matr_rows; ++i)
                {
                    matrix[i] = new T[matr_cols];
                }
                for (size_t i = 0; i < matr.matr_rows; ++i)
                {
                    if (i < row)
                    {
                        for (size_t j = 0; j < matr.matr_cols; ++j)
                        {
                            if (j < col)
                                matrix[i][j] = matr.matrix[i][j];
                            if (j > col)
                                matrix[i][j - 1] = matr.matrix[i][j];
                        }
                    }
                    if (i > row)
                    {
                        for (size_t j = 0; j < matr.matr_cols; ++j)
                        {
                            if (j < col)
                                matrix[i - 1][j] = matr.matrix[i][j];
                            if (j > col)
                                matrix[i - 1][j - 1] = matr.matrix[i][j];
                        }
                    }
                }
            }
        }

    public:
        Matrix () : matr_rows(0), matr_cols(0), matrix (NULL)// пустой
        {}

        Matrix (size_t rows, size_t cols, T** matr): matr_rows(rows), matr_cols(cols), matrix (std::move(matr))
        {}

        Matrix (size_t rows, size_t cols) : matr_rows(rows), matr_cols(cols), matrix (NULL)//с заданными размерами
        {
            /*matrix = new double* [matr_rows];
            for (unsigned i = 0; i < matr_rows; ++i)
            {
                matrix[i] = new double[matr_cols];
            }
            for (unsigned i = 0; i < matr_rows; ++i)
            {
                for (unsigned j = 0; j < matr_cols; ++j)
                {
                    matrix[i][j] = 0;
                }
            }*/
        }

        Matrix (const Matrix<T> &other): matr_rows (other.matr_rows), matr_cols (other.matr_cols), matrix (NULL)//копирования
        {
            if (other.matrix != NULL){
            matrix = new T* [other.matr_rows];

            for (unsigned i = 0; i < matr_rows; ++i)
            {
                matrix[i] = new T[matr_cols];
            }
            for (unsigned i = 0; i < matr_rows; ++i)
            {
                for (unsigned j = 0; j < matr_cols; ++j)
                {
                    matrix[i][j] = other.matrix[i][j];
                }
            }
            }
        }

        Matrix (std::ifstream& is)//считывание из файла
        {
            if (is.is_open())
            {
                is >> matr_rows;
                is >> matr_cols;

                matrix = new T* [matr_rows];

                for (size_t i = 0; i < matr_rows; ++i)
                {
                    matrix[i] = new T[matr_cols];
                }
                for (size_t i = 0; i < matr_rows; ++i)
                {
                    for (size_t j = 0; j < matr_cols; ++j)
                    {
                        is >> matrix[i][j];
                    }
                }
            }

            else
            {
                throw "Stream is not opened";
            }
        }

        ~Matrix ()//деструктор
        {
            for (unsigned i = 0; i < matr_rows; ++i)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }

        T& el (size_t i, size_t j) const //возврат элемента
        {
            if (i < matr_rows && j < matr_cols)
            {
                 return matrix[i][j];
            }
            else
            {
                 throw (std::out_of_range("Array::operator[] wrong index"));
            }
        }

        size_t& getrows() {return matr_rows;} //возврат количества строк
        size_t& getcols() {return matr_cols;} //возврат количества столбцов

        void setmatrix(T** matr) {matrix = std::move(matr);}
        void setrows (size_t rows) {matr_rows = rows;}
        void setcols (size_t cols) {matr_cols = cols;}

        Matrix<T>& operator =  (const Matrix<T>& other)
        {
            if (this != &other)
            {
                this->matr_rows = other.matr_rows;
                this->matr_cols = other.matr_cols;
                this->matrix = other.matrix;
            }
            return *this;
        }

        Matrix<T> operator + (const Matrix<T>& right) const
        {
            if ((matr_rows == right.matr_rows) && (matr_cols == right.matr_cols))
            {
                T** res_matrix = new T* [matr_rows];
                for (size_t i = 0; i < matr_rows; ++i)
                {
                    res_matrix [i] = new T [matr_cols];
                    for (size_t j = 0; j < matr_cols; ++j)
                    {
                        res_matrix[i][j] = matrix[i][j] + right.matrix[i][j];
                    }
                }
                Matrix<T> result (matr_rows, right.matr_cols, res_matrix);
                return result;
            }
            else
            {
                throw "Matrices have not equal sizes";
            }
        }

        Matrix<T> operator -   (const Matrix<T>& right) const
        {
            if ((matr_rows == right.matr_rows) && (matr_cols == right.matr_cols))
            {
                T** res_matrix = new T* [matr_rows];
                for (size_t i = 0; i < matr_rows; ++i)
                {
                    res_matrix [i] = new T [matr_cols];
                    for (size_t j = 0; j < matr_cols; ++j)
                    {
                        res_matrix[i][j] = matrix[i][j] - right.matrix[i][j];
                    }
            }
            Matrix<T> result (matr_rows, right.matr_cols, res_matrix);
            return result;
            }
            else
            {
                throw "Matrices have not equal sizes";
            }
        }

        Matrix<T> operator * (const Matrix<T>& right) const
        {
            if (matr_cols == right.matr_rows)
            {
                T** res_matrix = new T* [matr_rows];
                for (size_t i = 0; i < matr_rows; ++i)
                {
                    res_matrix[i] = new T [right.matr_cols];
                    for (size_t j = 0; j < right.matr_cols; ++j)
                    {
                        for (size_t k = 0; k < matr_cols; ++k)
                        {
                            if (k == 0)
                                res_matrix[i][j] = 0;
                            res_matrix[i][j] += matrix[i][k] * right.matrix[k][j];
                        }
                    }
                }
                Matrix<T> result (matr_rows, right.matr_cols, res_matrix);
                return result;
            }
            else
            {
                throw "Wrong matrices' sizes";
            }
        }

        Matrix <double> operator *   (const double scalar)   const
        {
            double** res_matrix = new double* [matr_rows];
            for (size_t i = 0; i < matr_rows; ++i)
            {
                res_matrix[i] = new double[matr_cols];
                for (size_t j = 0; j < matr_cols; ++j)
                {
                    res_matrix[i][j] = matrix[i][j] * scalar;
                }
            }
            Matrix<double> result(matr_rows, matr_cols, res_matrix);
            return result;
        }

    long double determ() const
    {
        if (matr_rows == matr_cols)
        {
            if (matr_rows == 1)
            {
                return matrix[0][0];
            }
            else
            {
                double determ = 0;
                for (size_t i = 0; i < matr_cols; ++i)
                {
                    Matrix<T> minmatr(*this, 0, i);
                    if ((i % 2) == 0)
                        determ += matrix[0][i] * minmatr.determ();
                    else
                        determ -= matrix[0][i] * minmatr.determ();
                }
                return determ;
            }
        }
        throw ("Not Possible!");
    }

    Matrix<double> operator ! ()
    {
        double det = this->determ();
        if (det != 0)
        {
          double** res_matr = new double* [matr_rows];
            for (size_t i = 0; i < matr_rows; ++i)
            {
              res_matr[i] = new double [matr_cols];
                for (size_t j = 0; j < matr_cols; ++j)
                {
                    Matrix<T> minmatr(*this, i, j);
                    {
                        double mindet = minmatr.determ();
                        if (((i + j) % 2) == 0)
                            res_matr[i][j] = mindet;
                        else
                            res_matr[i][j] = -1 * mindet;
                    }
                }
            }

            Matrix<double> A_matr (matr_rows, matr_cols, res_matr);
            Matrix<double> A_matr_transp = A_matr.transpose();

            double det1 = 1 / det;

            Matrix<double> res = A_matr_transp * det1;

            return res;
        }
        else
        {
            throw ("Not Possible!");
        }
    }

    Matrix<T> transpose() const
    {
        T** res_matr = new T* [matr_cols];
        for (size_t i = 0; i < matr_cols; ++i)
        {
            res_matr[i] = new T [matr_rows];
            for (size_t j = 0; j < matr_rows; ++j)
                res_matr[i][j] = matrix[j][i];
        }
        Matrix<T> matr_transpose(matr_cols, matr_rows, res_matr);
        return matr_transpose;
    }

        static Matrix<int> zero_matr (size_t size)
        {
            int** matr = new int* [size];
            for (size_t i = 0; i < size; ++i)
            {
                matr[i] = new int [size];
                for (size_t j = 0; j < size; ++j)
                    matr[i][j] = 0;
            }
            Matrix<int> result (size, size, matr);

            return result;
        }

        static Matrix<int> one_matr (size_t size)
        {
            int** matr = new int* [size];
            for (size_t i = 0; i < size; ++i)
            {
                matr[i] = new int [size];
                for (size_t j = 0; j < size; ++j)
                {
                    if (i == j)
                        matr[i][j] = 1;
                    else
                        matr[i][j] = 0;
                }
            }
            Matrix<int> result (size, size, matr);

            return result;
        }
};

template <typename T> // ввод матрицы
std::istream& operator >> (std::istream& is, Matrix<T>& matr)
{
    if (matr.getcols() == 0 or matr.getrows() == 0)
    {
        size_t rows = 0;
        size_t cols = 0;

        is >> rows;
        matr.setrows(rows);

        is >> cols;
        matr.setcols (cols);
    }

    T** matrix = new T* [matr.getrows()];
    for (size_t i = 0; i < matr.getrows(); ++i)
    {
        matrix[i] = new T [matr.getcols()];
        for (size_t j = 0; j < matr.getcols(); ++j)
        {
            is >> matrix[i][j];
        }
    }

    matr.setmatrix(matrix);
    return is;
}

template <typename T> // вывод матрицы
std::ostream& operator << (std::ostream& os, Matrix<T>& matr)
{
    for (size_t i = 0; i < matr.getrows(); ++i)
    {
        os << matr.el(i, 0);
        for (size_t j = 1; j < matr.getcols(); ++j)
        {
            os << " " << matr.el(i, j);
        }
        os << std::endl;
    }
    return os;
}

#endif
