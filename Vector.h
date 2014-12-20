#ifndef VECTOR_H
#define VECTOR_H 

#include <memory>
#include <algorithm>
#include <assert.h>

template<class T, typename Growth>
class Vector
{
public:
	Vector();
	// Vector(Vector<T, Growth>&);
	Vector(Vector<T, Growth>&&);

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

	void set_growth_rate(const Growth);
	Growth get_growth_rate();

	std::unique_ptr<T[ ]>& data();	

private:
	size_t inner_size;
	size_t inner_capacity;
	Growth growth_rate = 2;

	std::unique_ptr<T[ ]> inner_array;
	std::unique_ptr<T[ ]> tmparr;
};




template<class T, typename Growth> Vector<T, Growth>::Vector(){
	inner_array = std::unique_ptr<T[ ]>(new T[0]);
	inner_capacity = 2;
	inner_size = 0;
}


// // copy constructor
// template<class T, typename Growth> Vector<T, Growth>::Vector(Vector<T, Growth>& v){
// 	inner_array = std::unique_ptr<T[ ]>(new T[v.size()]);
// 	inner_capacity = v.capacity();
// 	inner_size = v.size();
// 	growth_rate = v.get_growth_rate();
	
// 	// inner_array.swap(v.data());

// 	std::copy(&inner_array[0], &inner_array[inner_size], &v.data()[0])  ;// nope
// }

// // rval constructor
template<class T, typename Growth> Vector<T, Growth>::Vector(Vector<T, Growth>&& v){
	inner_array = std::unique_ptr<T[ ]>(new T[v.size()]);
	inner_capacity = v.capacity();
	inner_size = v.size();
	growth_rate = v.get_growth_rate();

	inner_array.swap(v.data());
} 

template<class T, typename Growth> Vector<T, Growth>::Vector(const size_t count){
	inner_array = std::unique_ptr<T[ ]>(new T[count]);
	if (count < 2)
		inner_capacity = 2;
	else 
		inner_capacity = count;

	inner_size = count;
}

template<class T, typename Growth> T& Vector<T, Growth>::at(const size_t index){
	assert(index < inner_size);
	return inner_array[index];
}

template<class T, typename Growth> void Vector<T, Growth>::push_back(const T& value){
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

// template<class T, typename Growth> void Vector<T, Growth>::push_back(const T&& value){
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


template<class T, typename Growth> void Vector<T, Growth>::pop_back(){
	inner_size--;
}

template<class T, typename Growth> void Vector<T, Growth>::resize(const size_t new_size){
	inner_size = new_size;

	inner_capacity = inner_size;
	tmparr = std::unique_ptr<T[ ]>(new T[inner_capacity]);
	
	std::copy(&inner_array[0], &inner_array[inner_size], &tmparr[0]);

	inner_array = std::move(tmparr);
}

template<class T, typename Growth> void Vector<T, Growth>::shrink_to_fit(){
	inner_capacity = inner_size;

	tmparr = std::unique_ptr<T[ ]>(new T[inner_capacity]);

	for (size_t i = 0; i < inner_size; ++i)
		tmparr[i] = inner_array[i];

	inner_array = std::move(tmparr);
}


template<class T, typename Growth> size_t Vector<T, Growth>::capacity(){
	return inner_capacity;
}

template<class T, typename Growth> size_t Vector<T, Growth>::size(){
	return inner_size;
}

template<class T, typename Growth> Growth Vector<T, Growth>::get_growth_rate(){
	return growth_rate;
}

template<class T, typename Growth> void Vector<T, Growth>::set_growth_rate(const Growth gr){
	growth_rate = gr;
}

template<class T, typename Growth> std::unique_ptr<T[ ]>& Vector<T, Growth>::data(){
	return inner_array;
}


#endif