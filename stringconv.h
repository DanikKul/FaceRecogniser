#ifndef STRINGCONV_H
#define STRINGCONV_H


#include <iostream>
#include <string>

using namespace std;

class StringConv{
    char* string;
public:
    StringConv(const char* = "");

    StringConv(const StringConv&);

    ~StringConv();

    char* get();
    void set(const char*);
    bool isdigit();
    bool isalpha();
    void capitalize();
    void toupper();
    void tolower();
    unsigned int len();
    StringConv* split(char);
    int find(char);
    int* find(const char*);
    int* find(StringConv);
    void append(char);
    void append(const char*);
    void append(StringConv);
    char pop();
    const char* c_str() const;
    std::string cpp_str() const;

    StringConv operator + (StringConv);
    friend StringConv operator + (const char*, StringConv);
    StringConv operator * (int);
    friend StringConv operator * (int, StringConv);
    StringConv& operator = (StringConv);
    void operator += (StringConv);
    bool operator == (StringConv);
    bool operator == (const char*);
    bool operator != (StringConv);
    bool operator != (const char*);
    char operator [] (int);
    StringConv operator () (int, int);
    friend ostream& operator << (ostream& out, StringConv str);
    friend istream& operator >> (istream& in, StringConv& str);
};

#endif // STRINGCONV_H
