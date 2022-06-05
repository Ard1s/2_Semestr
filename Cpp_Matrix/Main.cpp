#include <fstream>
#include <iostream>
#include <vector>

class Matrix 
{
private:
    int n;
    int m;
    std::vector<std::vector<int>> matrix;

public:
    Matrix() : n(0), m(0), matrix() {}

    Matrix(int n_, int m_) : n(n_), m(m_), matrix(n_, std::vector<int>(m_, 0)) {}

    bool operator==(const Matrix& another) const 
    {
        return matrix == another.matrix;
    }

    bool operator!=(const Matrix& another) const 
    {
        return !(*this == another);
    }

    Matrix& operator+=(const Matrix& another) 
    {
        for (size_t i = 0; i < another.n; ++i) 
        {
            std::vector<int> rowAnother = another[i];
            for (size_t j = 0; j < m; ++j) 
            {
                matrix[i][j] += rowAnother[j];
            }
        }
        return *this;
    }

    Matrix& operator*=(const int& multiplier) 
    {
        for (size_t i = 0; i < n; ++i) 
        {
            for (size_t j = 0; j < m; ++j) 
            {
                matrix[i][j] *= multiplier;
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& another) 
    {
        for (size_t i = 0; i < n; ++i) 
        {
            std::vector<int> rowAnother = another[i];
            for (size_t j = 0; j < n; ++j) 
            {
                matrix[i][j] -= rowAnother[j];
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix& another) const 
    {
        Matrix result = *this;
        result += another;
        return result;
    }

    Matrix operator-(const Matrix& another) const 
    {
        Matrix result = *this;
        result -= another;
        return result;
    }

    template <size_t K, size_t L>
    Matrix operator*(const int& multiplier) const 
    {
        Matrix result = *this;
        result *= multiplier;
        return result;
    }

    std::vector<int> getColumn(unsigned columnNumber) const 
    {
        std::vector<int> result;
        for (size_t i = 0; i < n; ++i) 
        {
            result.push_back(matrix[i][columnNumber]);
        }
        return result;
    }

    Matrix operator*(const Matrix& another) const 
    {
        Matrix result = Matrix(n, another.m);
        for (size_t i = 0; i < n; ++i) 
        {
            std::vector<int> row(another.m, 0);
            for (size_t j = 0; j < another.m; ++j) 
            {
                std::vector<int> anotherColumn = another.getColumn(j);
                for (size_t k = 0; k < m; ++k) 
                {
                    row[j] += matrix[i][k] * anotherColumn[k];
                }
            }
            result[i] = row;
        }
        return result;
    }

    Matrix& operator*=(const Matrix& another) 
    {
        *this = *this * another;
        return *this;
    }

    std::vector<int>& operator[](size_t i) 
    {
        return matrix[i];
    }

    std::vector<int> operator[](size_t i) const 
    {
        return matrix[i];
    }

    int determinant() const 
    {
        if (n == 1 && m == 1) 
        {
            return matrix[0][0];
        }
        int result = 0;
        for (int col = 0; col < m; ++col) 
        {
            Matrix minor = Matrix(n - 1, m - 1);
            for (int i = 1; i < n; ++i) 
            {
                for (int j = 0; j < m; ++j) 
                {
                    if (j < col) 
                    {
                        minor[i - 1][j] = matrix[i][j];
                    }
                    else if (j > col) 
                    {
                        minor[i - 1][j - 1] = matrix[i][j];
                    }
                }
            }
            if (col & 1) 
            {
                result -= matrix[0][col] * minor.determinant();
            }
            else 
            {
                result += matrix[0][col] * minor.determinant();
            }
        }
        return result;
    }

    int cntRow() const 
    {
        return n;
    }

    int cntCol() const 
    {
        return m;
    }

    void generateRandom(int rows, int columns) 
    {
        n = rows;
        m = columns;
        matrix.clear();
        for (int i = 0; i < rows; ++i) 
        {
            matrix.emplace_back();
            for (int j = 0; j < columns; ++j) 
            {
                matrix.back().push_back(rand() % 10);
            }
        }
    }

    void input() 
    {
        std::cin >> n >> m;
        matrix.clear();
        for (int i = 0; i < n; ++i) 
        {
            matrix.emplace_back();
            for (int j = 0; j < m; ++j) 
            {
                int value;
                std::cin >> value;
                matrix[i].push_back(value);
            }
        }
    }

    void input(const std::string& fileName) 
    {
        std::ifstream file(fileName);
        file >> n >> m;
        matrix.clear();
        for (int i = 0; i < n; ++i) 
        {
            matrix.emplace_back();
            for (int j = 0; j < m; ++j) 
            {
                int value;
                file >> value;
                matrix[i].push_back(value);
            }
        }
    }

    void output() 
    {
        for (size_t i = 0; i < n; ++i) 
        {
            for (size_t j = 0; j < m; ++j) 
            {
                std::cout << matrix[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

    void output(const std::string& fileName) 
    {
        std::ofstream file(fileName, std::ios::binary | std::ios::app);
        for (size_t i = 0; i < n; ++i) 
        {
            for (size_t j = 0; j < m; ++j) 
            {
                file << matrix[i][j] << ' ';
            }
            file << '\n';
        }
    }
};

Matrix operator*(const int& multiplier, const Matrix& matrix) 
{
    Matrix result = Matrix(matrix.cntRow(), matrix.cntCol());
    result *= multiplier;
    return result;
}

int main() {
    Matrix* ar = new Matrix[10];
    std::ofstream file_clear("output.txt");
    for (int i = 0; i < 5; ++i) 
    {
        ar[i].generateRandom(3, 3);
        ar[i].output();
        std::cout << "determinant: " << ar[i].determinant() << '\n';
        ar[i].output("output.txt");
        std::ofstream file("output.txt", std::ios::binary | std::ios::app);
        file << "determinant: " << ar[i].determinant() << '\n';
    }
    delete[] ar;
}
