/*
    Jacob Cadena
    11/22/18
    ds_string.h   
    
*/

#ifndef DATA_STRUCTURES_CUSTOM_STRING_DSSTRING_H
#define DATA_STRUCTURES_CUSTOM_STRING_DSSTRING_H

#include <cstring>
#include <iostream>

class String {
    
private:
    char *data;
    std::size_t length;

    
public:

    // CONSTANTS //
    static const std::size_t npos;
    
    // MEMBER FUNCTIONS //
    String();
    String(const char*);
    String(const String&);
    ~String();
    
    const String& operator= (const char*);
    const String& operator= (const String&);
    String& operator+= (const char);
    String& operator+= (const char*);
    String& operator+= (const String&);
    String operator+ (const char*);
    String operator+ (const String&);
    bool operator== (const char*) const;
    bool operator== (const String&) const;
    bool operator> (const String&) const;
    bool operator< (const String&) const;
    char& operator[] (const int);
    

    void PushBack(const char c);
    void PushBack(const char* c);
    void PushBack(const String& s);

    void Resize(const std::size_t n);
    void Clear();
    bool IsEmpty() const;

    std::size_t size() const;
    
    /*
      The substring method returns a string object that contains a
      sequence of characters from this string object.
     
      param start - the index of where to start
      param numChars - the number (count) of characters to copy into
         the substring
    */
   String Substring(int start, int numChars);
    
    /*
      the c_str function returns a null-terminated c-string holding the
      contents of this object.
    */
    const char* c_str() const;
    
    /*
      Overloaded stream insertion operator to print the contents of this
      string to the output stream in the first argument.
    */
    friend std::ostream& operator<< (std::ostream&, const String&);
    friend std::istream& operator>> (std::istream&, String&);
    friend std::istream& Getline(std::istream&, String&);
    friend std::istream& Getline(std::istream&, String&, char);

    // You are free to add more functionality to the class.  For example,
    // you may want to add a find(...) function that will search for a
    // string within a string.  (just an example)
    //
    //Further - you will be able to update and modify this class as the
    //semester progresses.

    size_t Find(const String&, size_t npos=0) const;
    size_t Find(const char*, size_t npos=0) const;

};
#endif // DATA_STRUCTURES_CUSTOM_STRING_DSSTRING_H
