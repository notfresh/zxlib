//
// Created by zxzx on 2020/12/10.
//

#ifndef ZZZ_MY_STR_H
#define ZZZ_MY_STR_H

#include <iostream>

namespace  std{

    class MyStr{
    public:
        // explicit MyStr(void);
        MyStr(const char *chars=NULL); //普通构造函数,指定NULL 就可以代替无参函数，在cpp看来，NULL参数就是无参的
        MyStr(const MyStr& str); //拷贝构造函数
        MyStr(MyStr&& str); //转移构造函数
        MyStr& operator=(const MyStr& str); //为什么要返回引用呢？必须返回引用，因为是赋值，所以要指向同一个地方
        MyStr& operator=(const MyStr&& str);
        MyStr operator+(MyStr& str);
        ~MyStr(); //析构
        int size() const { return strlen(m_chars);};
        const char& operator [](int i) const;
        char& operator [](int i);
        friend ostream& operator <<(ostream& out, MyStr& s);
    private:
        char* m_chars;  //这里需要说明的是，m_chars不能被声明为数组类型，char[] m_chars，因为数组名无法被赋值。带方括号的无法被声明为动态数组
    };


//    MyStr::MyStr(){
//        cout << "default void constructor" << endl;
//        m_chars = new char[1];
//        *m_chars = '\0'; //非数组不能使用[]运算符，只能使用指针赋值
//    }

    MyStr::MyStr(const char* chars){
        cout << "char constuctor" << endl;
        if(chars == NULL){
            m_chars = new char[1];
            *m_chars = '\0'; //非数组不能使用[]运算符，只能使用指针赋值
        }else{
            m_chars = new char[strlen(chars)+1]; // strlen只统计有效的长度，不算最后一位\0
            strcpy(m_chars, chars);
        }
    }

    MyStr::MyStr(const MyStr &str){ //在拷贝构造函数里，可以访问私有属性,这点记住
        cout << "copy constructor" << endl;
        m_chars = new char[strlen(str.m_chars)+1];
        strcpy(m_chars, str.m_chars);
    }

    MyStr::MyStr(MyStr &&str){
        cout << "move constructor" << endl;
        this->m_chars = str.m_chars;
        str.m_chars = new char[1]{'\0'};
    }

    MyStr::~MyStr() {
        cout << "deconstructor" << endl;
        if(m_chars != NULL){ // 防止重复释放同一个内存导致系统崩溃,因为存在赋值和拷贝
            delete []m_chars; //先释放原有原有内存，归还操作系统
            m_chars = NULL; //再把指针指向NULL，防止野指针
        }
    }

    MyStr MyStr::operator+(MyStr &str)  { // 如果一个参数被定义为const了，那么函数本身也应该被定义为const
        int len = size() + str.size() + 1;
        char *tmp = new char[len];
        strcpy(tmp, m_chars);
        strcat(tmp, str.m_chars);
//        if(str == NULL) return *this;
        return *(new MyStr(tmp));
    }

    //
    MyStr& MyStr::operator=(const MyStr &str) { // 赋值函数也可以访问私有属性，所以务必给赋值函数参数加上const
        cout << "operator= " << endl;
        if( &str == this) return *this; //比较是不是同一块内存，如果是指向同一个内存，直接return，防止自己给自己赋值，这样第一关就通过了！！
//        else{
//            delete []m_chars; //先释放原有原有内存，归还操作系统， 这里其实是问题的，应该先
//        }
//        m_chars = new char[strlen(str.m_chars)+1];
//        strcpy(m_chars, str.m_chars);
        MyStr tmp(str);
        char *tmp_charp = tmp.m_chars;
        tmp.m_chars = m_chars;
        m_chars = tmp_charp;
        return *this; // 即便返回引用类型，我们只需要返回对象的本体即可，编译器会做处理，我们不用返回引用
    }

    ostream& operator <<(ostream& out, MyStr& s){
        for(int i=0;i<s.size();i++){
            cout << s.m_chars[i];
        }
//        cout << endl; // 这里没有必要再输出一个换行符的！
        return out;
    }

    const char& MyStr::operator[](int i) const {
        cout << "const " << endl;
        if(i<0){
            return *(m_chars+ (size() +i));
        }
        return *(m_chars+i);
    }

    char& MyStr::operator[](int i) {
        cout << "not const" << endl;
        if(i<0){
            return *(m_chars+ (size() +i));
        }
        return *(m_chars+i);
    }

    void test_String_f2(){
        MyStr a = "abc";
        using std::cout;
        cout << a << endl;
        cout << "a[2] is: " << a[2] << endl;
        cout << "hello" << endl;

        MyStr b("10");
        MyStr b2("10");
        MyStr b3 = b + b2;
        cout << b3 << endl;
        cout << "the b[-1] is " <<  b3[-2] << endl;
    }

    void test_copy_assign(){
        MyStr a;
        MyStr b = "abc";
        MyStr c = "abc";
        cout << "b is " << b << endl;
        a = b = c;
        cout << "a is " <<  a << endl;
        cout << "b is " <<  b << endl;

    }
}

#endif //ZZZ_MY_STR_H
