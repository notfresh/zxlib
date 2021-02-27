//
// Created by zxzx on 2021/1/8.
//

#ifndef CPP_LEARN_PRINT_H
#define CPP_LEARN_PRINT_H

#include <iostream>
#include <vector>
#include <list>
#include <mutex>
// 不能在包头里使用 using namespace std; 这样会给引入的包造成濡染，明白吗！！

using std::recursive_mutex;
using std::lock_guard;
std::recursive_mutex print_mtx;

// 这个方法是线程不安全的! 应该把它改造一下
template<typename T>
void print(T t){ // @print	
	lock_guard<recursive_mutex> locker(print_mtx);
	std::cout << t << std::endl;
}

template<typename T, typename... Ts>
void print(T t, Ts... args){
	lock_guard<recursive_mutex> locker(print_mtx);
	std::cout << t << ", " ;
	print(args...);
}

template<typename T>
void print(std::vector<T> arr){ // @print
	for(int i=0; i<arr.size(); i++){
		std::cout << arr[i] << "\t";
	}
	std::cout << std::endl;
}

template<typename T>
void print(std::list<T> arr){ // @print
	for(auto i=arr.begin(); i!=arr.end(); i++){
		std::cout << *i << "\t";
	}
	std::cout << std::endl;
}


#endif //CPP_LEARN_PRINT_H

