#include "matrix.h"
#include "array.h"
namespace structures
{
	template<typename T>
	class ArrayMatrix : public Matrix<T>
	{
	public:
		ArrayMatrix(const size_t rows, const size_t cols);

		ArrayMatrix(const ArrayMatrix<T>& other);

		ArrayMatrix(ArrayMatrix<T>&& other);

		~ArrayMatrix();

		Structure* clone() const override;

		size_t size() const override;

		Matrix<T>& operator=(const Matrix<T>& other) override;

		Matrix<T>& operator=(Matrix<T>&& other) override;

		ArrayMatrix<T>& operator=(const ArrayMatrix<T>& other);

		ArrayMatrix<T>& operator=(ArrayMatrix<T>&& other);

		T& get(const int row, const int col) override;

		const T get(const int row, const int col) const override;

		void set(const int row, const int col, const T& data);


	private:
		Array<T>* matrix_;
		size_t sizeRows_;
		size_t sizeCols_;
		int mapFunction(const int row, const int col) const;
	};

	template<typename T>
	inline ArrayMatrix<T>::ArrayMatrix(const size_t rows, const size_t cols)
	{
		matrix_ = new Array<T>(rows * cols);
		sizeRows_ = rows;
		sizeCols_ = cols;
	}

	template<typename T>
	inline ArrayMatrix<T>::ArrayMatrix(const ArrayMatrix<T>& other)
	{
		matrix_ = new Array<T>(*(other.matrix_)),
		sizeRows_ = other.sizeRows_;
		sizeCols_ = other.sizeCols_;
	}

	template<typename T>
	inline ArrayMatrix<T>::ArrayMatrix(ArrayMatrix<T>&& other)
	{
		matrix_ = other.matrix_,
		sizeRows_ = other.sizeRows_;
		sizeCols_ = other.sizeCols_;

		other.matrix_ = nullptr;
	}

	template<typename T>
	inline ArrayMatrix<T>::~ArrayMatrix()
	{
		delete matrix_;
		matrix_ = nullptr;
		sizeRows_ = 0;
		sizeCols_ = 0;
	}

	template<typename T>
	inline Structure* ArrayMatrix<T>::clone() const
	{
		return new ArrayMatrix<T>(*this);
	}

	template<typename T>
	inline Matrix<T>& ArrayMatrix<T>::operator=(const Matrix<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ArrayMatrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline Matrix<T>& ArrayMatrix<T>::operator=(Matrix<T>&& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ArrayMatrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ArrayMatrix<T>& ArrayMatrix<T>::operator=(const ArrayMatrix<T>& other)
	{
		if (this != &other)
		{
			if (other.sizeRows_ == sizeRows_ && other.sizeCols_ == sizeCols_)
			{
				*matrix_ = *(other.matrix_);
			}
			else
			{
				throw std::invalid_argument("Matrix sizes are different!");
			}
		}
	}

	template<typename T>
	inline ArrayMatrix<T>& ArrayMatrix<T>::operator=(ArrayMatrix<T>&& other)
	{
		if (this != &other)
		{
			if (other.sizeRows_ == sizeRows_ && other.sizeCols_ == sizeCols_)
			{
				matrix_ = other.matrix_;
				other.matrix_ = nullptr;
			}
			else
			{
				throw std::invalid_argument("Matrix sizes are different!");
			}
		}
	}

	template<typename T>
	inline size_t ArrayMatrix<T>::size() const
	{
		return sizeCols_ * sizeRows_;
	}

	template<typename T>
	inline T& ArrayMatrix<T>::get(const int row, const int col)
	{
		DSRoutines::rangeCheckExcept(row, sizeRows_, "Row index - out of range");
		DSRoutines::rangeCheckExcept(col, sizeCols_, "Col index - out of range");
		int index = mapFunction(row, col);
		return (*matrix_)[index];
	}

	template<typename T>
	inline const T ArrayMatrix<T>::get(const int row, const int col) const
	{
		DSRoutines::rangeCheckExcept(row, sizeRows_, "Row index - out of range");
		DSRoutines::rangeCheckExcept(col, sizeCols_, "Col index - out of range");
		int index = mapFunction(row, col);
		return (*matrix_)[index];
	}

	template<typename T>
	inline void ArrayMatrix<T>::set(const int row, const int col, const T& data)
	{
		DSRoutines::rangeCheckExcept(row, sizeRows_, "Row index - out of range");
		DSRoutines::rangeCheckExcept(col, sizeCols_, "Col index - out of range");
		int index = mapFunction(row, col);
	    (*matrix_)[index] = data;
	}


	template<typename T>
	inline int ArrayMatrix<T>::mapFunction(const int row, const int col) const
	{
		return row * sizeCols_ + col;
	}
}