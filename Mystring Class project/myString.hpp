#pragma once
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <ostream>
#include <istream>
#include <string>

class MyString {
private:
    char* data;      
    size_t length;
    size_t capacity;

public:
    static const size_t npos = -1;
    static const size_t InitialCapacity = 15;
            // Constructors
            MyString();                                
            MyString(const char* s);                  
            MyString(const MyString& other);            
            MyString(MyString&& other) noexcept;         
            MyString(size_t n, char c);               
            ~MyString();                              

            // Assignment operators
            MyString& operator=(const MyString& other);  
            MyString& operator=(MyString&& other) noexcept;       
            MyString& operator=(const char* s);        
            MyString& operator=(char c);               

            // Element access
            char& operator[](size_t pos);            
            const char& operator[](size_t pos) const;
            char& at(size_t pos);                
            const char& at(size_t pos) const;
            char& front();
            char& back();

            // Capacity
            size_t size() const noexcept;                    
            bool empty() const noexcept;   
            size_t getCapacity() const noexcept;// Check if string is empty
            void resize(size_t n, char c = '\0');    // Resize string
            void reserve(size_t n);                  // Reserve memory

            // Modifiers
            void clear() noexcept;                   // Clear the string
            MyString& append(const MyString& str);       // Append another string
            MyString& append(const char* s);           // Append a C-string
            MyString& append(size_t n, char c);        // Append n characters
            void push_back(char c);                  // Append a single character
            void pop_back();                         // Remove last character
            MyString& erase(size_t pos = 0, size_t len = npos); // Erase part of the string
            MyString& insert(int pos, const MyString& str);    // Insert a string


            // Input/Output
            friend std::ostream& operator<<(std::ostream& os, const MyString& str);
            friend std::istream& operator>>(std::istream& is, MyString& str);//challenging to implement
        };