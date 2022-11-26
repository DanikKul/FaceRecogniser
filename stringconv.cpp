#include "stringconv.h"
#include "exceptions.h"

#include <iostream>

using namespace std;

StringConv::StringConv(const char *string) {
    try {
        if (strlen(string) > 1000) throw ExceptionBadAlloc();
        this -> string = new char[strlen(string) + 1];
        strcpy(this -> string, string);
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }
}

StringConv::StringConv(const StringConv& str) {
    try {
        if (strlen(str.string) > 1000) throw ExceptionBadAlloc();
        string = new char[strlen(str.string) + 1];
        strcpy(string, str.string);
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }
}

StringConv::~StringConv() {
    delete [] string;
}

char* StringConv::get() {
    return string;
}

void StringConv::set(const char* str) {
    try {
        if (strlen(str) > 1000) throw ExceptionBadAlloc();
        string = new char[strlen(str) + 1];
        strcpy(string, str);
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }
}

StringConv StringConv::operator + (StringConv str) {
    StringConv ret;

    try {
        if ((strlen(string) + strlen(str.get())) > 1000) throw ExceptionBadAlloc();
        char *buff = new char[strlen(string) + strlen(str.get()) + 1];
        strcat(buff, string);
        strcat(buff, str.get());
        ret.set(buff);
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }

    return ret;
}

StringConv operator + (const char* ch, StringConv str) {
    StringConv ret;

    try {
        if ((strlen(ch) + strlen(str.get())) > 1000) throw ExceptionBadAlloc();
        char *buff = new char[strlen(ch) + strlen(str.get()) + 1];
        strcat(buff, ch);
        strcat(buff, str.get());
        ret.set(buff);
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }

    return ret;
}

StringConv StringConv::operator * (int times) {
    StringConv buff;
    for (int i = 0; i < times; i++) {
        buff.append(string);
    }
    return buff;
}

StringConv operator * (int times, StringConv s) {
    StringConv buff;
    for (int i = 0; i < times; i++) {
        buff.append(s.get());
    }
    return buff;
}

StringConv& StringConv::operator = (StringConv str) {

    try {
        if (strlen(str.get()) > 1000) throw ExceptionBadAlloc();
        this -> string = new char[strlen(str.get()) + 1];
        strcpy(string, str.get());
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }

    return *this;
}

void StringConv::operator += (StringConv str) {
    char* buff;
    try {
        if (strlen(string) > 1000) throw ExceptionBadAlloc();
        buff = new char[strlen(string) + 1];
        strcpy(buff, string);
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }

    try {
        if ((strlen(buff) + strlen(str.get())) > 1000) throw ExceptionBadAlloc();
        string = new char[strlen(buff) + strlen(str.get()) + 1];
        strcat(string, buff);
        strcat(string, str.get());
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }

}

bool StringConv::operator == (StringConv str) {
    return strcmp(str.get(), string) == 0;
}

bool StringConv::operator == (const char* str) {
    return strcmp(str, string) == 0;
}

bool StringConv::operator != (StringConv str) {
    return strcmp(str.get(), string) != 0;
}

bool StringConv::operator != (const char* str) {
    return strcmp(str, string) != 0;
}

char StringConv::operator [] (int idx) {
    if (idx < 0){
        idx = (int)strlen(string) + idx;
    }
    idx = abs(idx);
    if (idx >= strlen(string)){
        idx %= (int)strlen(string);
    }
    return string[idx];
}

StringConv StringConv::operator () (int idx1, int idx2) {
    if (idx1 > idx2) swap(idx1, idx2);
    if (idx2 > strlen(string) || idx2 < 0){
        idx2 = (int)strlen(string);
    }
    if (idx1 < 0 || idx1 > strlen(string)){
        idx1 = 0;
    }
    char* buff = new char[idx2 - idx1];
    for (int i = idx1; i <= idx2; i++){
        buff[i - idx1] = string[i];
    }
    StringConv str(buff);
    return str;
}

bool StringConv::isdigit() {
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] < '0' || string[i] > '9') {
            return false;
        }
    }
    return true;
}

bool StringConv::isalpha() {
    for (int i = 0; i < strlen(string); i++) {
        if ((string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z')) {
            return false;
        }
    }
    return true;
}

void StringConv::capitalize() {
    string[0] = (char)std::toupper(string[0]);
}

void StringConv::toupper(){
    for (int i = 0; i < strlen(string); i++) {
        string[i] = (char)std::toupper(string[i]);
    }
}

void StringConv::tolower() {
    for (int i = 0; i < strlen(string); i++) {
        string[i] = (char)std::tolower(string[i]);
    }
}

unsigned int StringConv::len() {
    return strlen(string);
}

StringConv* StringConv::split(char sep) {
    int count_blocks = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (sep == string[i]) count_blocks++;
    }
    auto* sp = new StringConv[count_blocks];
    int block = 0;
    for (int i = 0; i < strlen(string); i++) {
        int count_literals;
        for (count_literals = i; count_literals < strlen(string) && string[count_literals] != sep; count_literals++);
        char* buff = new char[count_literals - i];
        if (i == count_literals) continue;
        int idx = 0;
        while (i != count_literals) {
            buff[idx] = string[i];
            i++, idx++;
        }
        sp[block].set(buff);
        block++;
    }
    return sp;
}

int StringConv::find(char c) {
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == c) {
            return i;
        }
    }
    return -1;
}

int* StringConv::find(const char* s) {
    int* f = new int[2];
    int first = 0, last = (int)strlen(s) - 1;
    while (last < strlen(string)) {
        if (string[first] == s[0] && string[last] == s[strlen(s) - 1]) {
            int idx = first, s_idx = 0;
            while (idx != last) {
                if (string[idx] != s[s_idx]) break;
                idx++, s_idx++;
            }
            if (idx == last) {
                f[0] = first;
                f[1] = last;
                return f;
            }
        }
        first++, last++;
    }
    f[0] = -1, f[1] = -1;
    return f;
}

int* StringConv::find(StringConv s) {
    int* f = new int[2];
    int first = 0, last = (int)s.len() - 1;
    while (last < strlen(string)) {
        if (string[first] == s[0] && string[last] == s[(int)s.len() - 1]) {
            int idx = first, s_idx = 0;
            while (idx != last) {
                if (string[idx] != s[s_idx]) break;
                idx++, s_idx++;
            }
            if (idx == last) {
                f[0] = first;
                f[1] = last;
                return f;
            }
        }
        first++, last++;
    }
    f[0] = -1, f[1] = -1;
    return f;
}

void StringConv::append(char c) {
    try {
        if ((strlen(string) + 2) > 1000) throw ExceptionBadAlloc();
        char* buff = new char[strlen(string) + 2];
        strcpy(buff, string);
        buff[strlen(string)] = c;
        buff[strlen(string) + 1] = '\0';
        this -> set(buff);
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }
}

void StringConv::append(const char* s) {
    try {
        if ((strlen(string) + strlen(s)) > 1000) throw ExceptionBadAlloc();
        char* buff = new char[strlen(string) + strlen(s) + 1];
        strcpy(buff, string);
        strcat(buff, s);
        buff[strlen(string) + strlen(s)] = '\0';
        this -> set(buff);
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }
}

void StringConv::append(StringConv s) {

    try {
        if ((strlen(string) + s.len()) > 1000) throw ExceptionBadAlloc();
        char* buff = new char[strlen(string) + s.len() + 1];
        strcpy(buff, string);
        strcat(buff, s.get());
        buff[strlen(string) + s.len()] = '\0';
        this -> set(buff);
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }
}

char StringConv::pop() {
    char c;

    try {
        if (strlen(string) == 0) throw ExceptionEmpty();
        c = string[strlen(string) - 1];
        string[strlen(string) - 1] = '\0';
    } catch (ExceptionEmpty& exception) {
        exception.getError();
        return '\0';
    } catch (...) {
        Exception exception;
        exception.getError();
        return '\0';
    }

    return c;
}

const char* StringConv::c_str() const {
    return this -> string;
}

std::string StringConv::cpp_str() const {
    return std::string(this -> string);
}

ostream& operator << (ostream& out, StringConv str) {
    return out << str.get();
}

istream& operator >> (istream& in, StringConv& str) {
    char* buff;

    try {
        if (strlen(str.get()) > 1000) throw ExceptionBadAlloc();
        char* buff = new char[strlen(str.get()) + 1];
    } catch (ExceptionBadAlloc& exception) {
        exception.getError();
    } catch (...) {
        Exception exception;
        exception.getError();
    }

    in >> buff;
    str.set(buff);
    return in;
}
