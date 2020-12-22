#pragma once
#include "structure.h"
#include "ds_structure_types.h"
#include "array.h"
#include "ds_routines.h"

namespace structures
{
	template<typename T>
	class Matrix : public Structure
	{
	public:
		virtual Structure* clone() const = 0;

		virtual size_t size() const = 0;

		Structure& operator=(const Structure& other) override;

		Structure& operator=(Structure&& other);

		virtual Matrix<T>& operator=(const Matrix<T>& other) = 0;

		virtual Matrix<T>& operator=(Matrix<T>&& other) = 0;

		virtual T& get(const int row, const int col) = 0;

		virtual const T get(const int row, const int col) const = 0;

		virtual void set(const int row, const int col, const T& data) = 0;

	protected:
		Matrix();
	};

	template<typename T>
	inline Structure& Matrix<T>::operator=(const Structure& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline Structure& Matrix<T>::operator=(Structure&& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Matrix<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline Matrix<T>::Matrix() :
		Structure()
	{
	}
}


