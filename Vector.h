#ifndef VECTOR_H
#define VECTOR_H 

#include <memory>
#include <algorithm>
#include <assert.h>

template<class T>
class Vector
{
public:
	Vector();
	// Vector(Vector<T>&);
	// Vector(Vector<T>&&);

	Vector(const size_t);

	void push_back(const T& value);
	// void push_back(const T&& value);
	void pop_back();

	T& at(const size_t index);
	T& operator[] (size_t i) { return inner_array[i]; };
	const T& operator[] (size_t i) const { return inner_array[i]; };

	void resize(const size_t);
	void shrink_to_fit();

	size_t capacity();
	size_t size();

	void set_growth_rate(const size_t);
	size_t get_growth_rate();

	std::unique_ptr<T[ ]>& data();	

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


// // copy constructor
// template<class T> Vector<T>::Vector(Vector<T>& v){
// 	inner_array = std::unique_ptr<T[ ]>(new T[v.size()]);
// 	inner_capacity = v.capacity();
// 	inner_size = v.size();
// 	growth_rate = v.get_growth_rate();
	
// 	// std::copy(&inner_array[0], &inner_array[inner_size], &v.data()[0]);`// nope
// }

// // rval constructor
// template<class T> Vector<T>::Vector(Vector<T>&& v){
// 	inner_array = std::unique_ptr<T[ ]>(new T[v.size()]);
// 	inner_capacity = v.capacity();
// 	inner_size = v.size();
// 	growth_rate = v.get_growth_rate();

// 	// std::move(&inner_array[0], &inner_array[inner_size], &v.data()[0]);`// nope
// } 

template<class T> Vector<T>::Vector(const size_t count){
	inner_array = std::unique_ptr<T[ ]>(new T[count]);
	if (count < 2)
		inner_capacity = 2;
	else 
		inner_capacity = count;

	inner_size = count;
}

template<class T> T& Vector<T>::at(const size_t index){
	assert(index < inner_size);
	return inner_array[index];
}

template<class T> void Vector<T>::push_back(const T& value){
	if (inner_size < inner_capacity)
	{
		inner_array[inner_size++] = value;

	} else {
		inner_capacity *= growth_rate;
		tmparr = std::unique_ptr<T[ ]>(new T[inner_capacity]);

		std::copy(&inner_array[0], &inner_array[inner_size], &tmparr[0]);

		tmparr[inner_size++] = value;
		inner_array = std::move(tmparr);
	}
}

// template<class T> void Vector<T>::push_back(const T&& value){
// 	if (inner_size < inner_capacity)
// 	{
// 		inner_array[inner_size++] = value;

// 	} else {
// 		inner_capacity *= growth_rate;
// 		tmparr = std::unique_ptr<T[ ]>(new T[inner_capacity]);

// 		std::copy(&inner_array[0], &inner_array[inner_size], &tmparr[0]);

// 		tmparr[inner_size++] = value;
// 		inner_array = std::move(tmparr);
// 	}
// }


template<class T> void Vector<T>::pop_back(){
	inner_size--;
}

template<class T> void Vector<T>::resize(const size_t new_size){
	inner_size = new_size;

	inner_capacity = inner_size;
	tmparr = std::unique_ptr<T[ ]>(new T[inner_capacity]);
	
	std::copy(&inner_array[0], &inner_array[inner_size], &tmparr[0]);

	// inner_array = std::move(tmparr);
}

template<class T> void Vector<T>::shrink_to_fit(){
	inner_capacity = inner_size;

	tmparr = std::unique_ptr<T[ ]>(new T[inner_capacity]);

	for (size_t i = 0; i < inner_size; ++i)
		tmparr[i] = inner_array[i];

	inner_array = std::move(tmparr);
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

template<class T> void Vector<T>::set_growth_rate(const size_t gr){
	growth_rate = gr;
}

template<class T> std::unique_ptr<T[ ]>& Vector<T>::data(){
	return inner_array;
}


#endif