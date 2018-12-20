/*
    Jacob Cadena
    11/22/18
    ds_string.cpp    
    
*/

#include "ds_string.h"

const std::size_t String::npos = -1;

String::String(){
    length = 0;
    data = nullptr;
}

String::String(const char* data){
    length = (std::size_t) strlen(data);
    this->data = new char[length+1];
    strcpy(this->data, data);
}

String::String(const String& s){
    length = s.length;
    this->data = new char[length+1];
    strcpy(this->data, s.data);
}

String::~String(){
    delete[] data;
}

const String& String::operator= (const char* data){
    length = (std::size_t) strlen(data);
    this->data = new char[length+1];
    strcpy(this->data, data);
    return *this;
}

const String& String::operator= (const String& s){
    length = s.length;
    this->data = new char[length+1];
    strcpy(this->data, s.data);
    return *this;
}

String String::operator+ (const String& s) {
    String temp;
    temp.length = length + s.length;
    temp.data = new char[temp.length+1];
    strcpy(temp.data, data);
    strcat(temp.data, s.data);
    return temp;
}

String String::operator+ (const char* d) {
    String temp;
    temp.length = length + (int) strlen(d);
    temp.data = new char[temp.length+1];
    strcpy(temp.data, data);
    strcat(temp.data, d);
    return temp;
}

String& String::operator+= (const char c) {
    PushBack(c);
    return *this;
}

String& String::operator+= (const char* c) {
    PushBack(c);
    return *this;
}

String& String::operator+= (const String& s) {
    PushBack(s);
    return *this;
}

void String::PushBack(const char c) {
    Resize(length+1);
    data[length-1] = c;
    data[length] = '\0';
}

void String::PushBack(const char* c) {
    Resize(length+strlen(c));
    strcpy(data, c);
}

void String::PushBack(const String& s) {
    Resize(length+strlen(s.data));
    strcpy(data, s.data);
}

void String::Clear() {
    delete[] data;
    data = nullptr;
    length = 0;
}

void String::Resize(const std::size_t n) {

    if(n == 0) {
        if(data != nullptr) 
            delete data;
        data = nullptr;
        length = 0;
    } else if(n > length) {
        if(!IsEmpty()) {
            char* temp = new char[n+3];
            strcpy(temp, data);
            delete data;
            data = temp;
        } else {
            data = new char[n+3];
            data[n] = '\0';
        }
        length = n;

    } else if(n < length) {

    }    
}

bool String::IsEmpty() const {
    return (data == nullptr) &&
           (length == 0);
}

bool String::operator== (const char* data) const {
    if(strcmp(this->data, data) == 0)
        return true;
    return false;
}

bool String::operator== (const String& s) const {
    if(strcmp(this->data, s.data) == 0)
        return true;
    return false;
}

bool String::operator> (const String& s) const {
    if(strcmp(this->data, s.data) > 0)
        return true;
    return false;
}

bool String::operator< (const String& s) const {
    if(strcmp(this->data, s.data) < 0)
        return true;
    return false;
}

char& String::operator[] (const int i) {
    return *(data + i);
}

const char* String::c_str() const {
    return data;
}

String String::Substring(int start, int numChars) {
    String temp;
    temp.length = numChars;
    temp.data = new char[temp.length+1];
    for(std::size_t i = start; i < temp.length -1; i++) {
        temp.data[i] = data[i];
    }
    temp.data[temp.length-1] = '\0';
    return temp;
}

std::ostream& operator<< (std::ostream& output, const String& s) {
    return output << s.data;
}

std::istream& operator>> (std::istream& input, String& str) {

    if(!str.IsEmpty())
        str.Clear();

    char c = input.get();

    if(input.eof()) return input;

    std::istream::sentry s(input, true);
    if (s) while (input.good()) {        
        if (std::isspace(c,input.getloc())) break;
        str += c;
        if(input.peek() == EOF)
            break;
        c = input.get();
    }
    return input;
} 

std::istream& Getline(std::istream& input, String& str) {

    if(!str.IsEmpty())
        str.Clear();

    char c = input.get();

    if(input.eof()) return input;

    std::istream::sentry s(input, true);
    if (s) while (input.good()) {        
        if(c == '\n') break;
        str += c;
        if(input.peek() == EOF)
            break;
        c = input.get();
    }
    return input;
}

std::istream& Getline(std::istream& input, String& str, char delim) {

    if(!str.IsEmpty())
        str.Clear();

    char c = input.get();

    if(input.eof()) return input;

    std::istream::sentry s(input, true);
    if (s) while (input.good()) {        
        if(c == delim) break;
        str += c;
        if(input.peek() == EOF)
            break;
        c = input.get();
    }
    return input;
}

std::size_t String::size() const {
    return length;
}

size_t String::Find(const String& s, std::size_t pos) const {
    return Find(s.data, pos);
}

size_t String::Find(const char* data, std::size_t pos) const {

    size_t found = npos;
    bool isFound = false;
    for(std::size_t i = pos; i < length && !isFound; i++) {
        if(data[0] == this->data[i]) {
            isFound = true;
            found = i;
            for(std::size_t j = 0; j < strlen(data); j++) {
                if(data[j] != this->data[j+i]) {
                    isFound = false;
                    break;
                }
            }
        }
    }

    if(isFound) {
        return found;
    }
    return npos;
}

