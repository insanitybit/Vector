#ifndef VECTOR_H
#define VECTOR_H 

#include <memory>
#include <assert.h>

template<class T>
class Vector
{
public:
	Vector();
	Vector(size_t);

	void push_back(T value);
	void pop_back();

	T& at(size_t index);
	T& operator[] (size_t i) { return inner_array[i]; };
	const T& operator[] (size_t i) const { return inner_array[i]; };

	void resize(size_t);
	void shrink_to_fit();

	size_t capacity();
	size_t size();

	void set_growth_rate(size_t);
	size_t get_growth_rate();
private:
	size_t inner_size;
	size_t inner_capacity;
	size_t growth_rate = 2;
	std::unique_ptr<T[ ]> inner_array;
	std::unique_ptr<T[ ]> tmparr;
};




template<class T> Vector<T>::Vector(){
	inner_array = std::unique_ptr<T[ ]>(new T[0]);
	inner_capacity = 2;
	inner_size = 0;
}

template<class T> Vector<T>::Vector(size_t count){
	inner_array = std::unique_ptr<T[ ]>(new T[count]);
	if (count < 2)
		inner_capacity = 2;
	else 
		inner_capacity = count;

	inner_size = count;
}

template<class T> T& Vector<T>::at(size_t index){
	assert(index < inner_size);
	return inner_array[index];
}

template<class T> void Vector<T>::push_back(T value){
	inner_size++;
	if (inner_size <= inner_capacity)
	{
		inner_array[inner_size] = value;

	} else {
		inner_capacity *= growth_rate;
		tmparr = std::unique_ptr<T[ ]>(new T[inner_capacity]);

		for (size_t i = 0; i < inner_size - 1; ++i)
			tmparr[i] = inner_array[i];

		tmparr[inner_size] = value;
		inner_array = std::move(tmparr);
	}
}

template<class T> void Vector<T>::pop_back(){
	inner_size--;
}

template<class T> void Vector<T>::resize(size_t new_size){
	inner_size = new_size;

	if (inner_size <= inner_capacity)
	{
		inner_array[inner_size] = value;

	} else {
		inner_capacity *= growth_rate;
		tmparr = std::unique_ptr<T[ ]>(new T[inner_capacity]);

		for (size_t i = 0; i < inner_size; ++i)
			tmparr[i] = inner_array[i];

		inner_array = std::move(tmparr);
	}

}

template<class T> void Vector<T>::shrink_to_fit(){
	inner_capacity = inner_size;

	tmparr = std::unique_ptr<T[ ]>(new T[inner_capacity]);

	for (size_t i = 0; i < inner_size; ++i)
		tmparr[i] = inner_array[i];

	inner_array = std::move(tmparr);
	tmparr.reset();

}


template<class T> size_t Vector<T>::capacity(){
	return inner_capacity;
}

template<class T> size_t Vector<T>::size(){
	return inner_size;
}

template<class T> size_t Vector<T>::get_growth_rate(){
	return growth_rate;
}

template<class T> void Vector<T>::set_growth_rate(size_t gr){
	growth_rate = gr;
}

#endif