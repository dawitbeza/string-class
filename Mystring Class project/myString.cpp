#include "myString.hpp"

MyString::MyString()
	: capacity{ InitialCapacity }
{
	data = new char();
	length = 0;
	std::cout << "default constructor called" << std::endl;
}

MyString::MyString(const char* s)
	: capacity{ InitialCapacity }
{
	size_t size = strlen(s);
	if (size <= capacity) {
	data = new char[capacity];
	std::memcpy(data, s, size + 1);//for fast low level copies of memory byte by byte(new feature i learned)
	}
	else {
		//ensure the capacity is greater than that of the size
		while (capacity < size)
			capacity *= 2;
		data = new char[capacity];
		std::memcpy(data, s, size + 1);
	}
	length = size;
	std::cout << "Const char constructor called" << std::endl;
}

MyString::MyString(const MyString& other)
	: capacity{ InitialCapacity }
{
	if (other.length <= capacity) {
		data = new char[capacity];
		std::memcpy(data, other.data, other.length + 1);
		length = other.length;
	 }
	else {
		while (capacity < other.length)
			capacity *= 2;
		data = new char[capacity];
		std::memcpy(data, other.data, other.length + 1);
	}

	length = other.length;
	std::cout << "Constructor from string is called: " << std::endl;
}

MyString::MyString(MyString&& other) noexcept
	: capacity{ InitialCapacity }
{
	if (other.length <= capacity) {
		data = new char[capacity];
	std:memcpy(data, other.data, other.length + 1);
	}
	else {
		while (capacity < other.length)
			capacity *= 2;
		data = new char[capacity];
		std::memcpy(data, other.data, other.length + 1);
	}
	length = other.length;
	other.data = nullptr;
	other.length = 0;
	std::cout << "Move construcor is called: " << std::endl;
}

MyString::MyString(size_t n, char c)
	: capacity{ InitialCapacity }
{
	if (n <= capacity) {
		data = new char[capacity];
		std::memset(data, c, n);
	}
	else {
		while (capacity < n)
			capacity *= 2;
		data = new char[capacity];
		std::memset(data, c, n);
		
	}
	std::cout << "character duplicating constructor is called: ";
	length = n;
}

MyString::~MyString()
{
	delete[] data;
	length = 0;
	capacity = 0;
	data = nullptr;
}

MyString& MyString::operator=(const MyString& other)
{
	if (other.length <= capacity) {
		std::memcpy(data, other.data, other.length + 1);
	}
	else {
		while (capacity < other.length)
			capacity *= 2;
		std::memcpy(data, other.data, other.length + 1);
	}
		length = other.length;
	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (other.length <= capacity) {
		std::memcpy(data, other.data, other.length + 1);
	}
	else {
		while (capacity < other.length)
			capacity *= 2;
		std::memcpy(data, other.data, other.length + 1);
	}
	length = other.length;
	//clear  the state of the moved object
	delete[] other.data;
	other.data = nullptr;
	other.length = 0;
	other.capacity = 0;
	return *this;
	
}

MyString& MyString::operator=(const char* cstr)
{
	size_t size = strlen(cstr);
	if ( size <= capacity) {
		std::memcpy(data, cstr, size + 1);
	}
	else {
		while (capacity < size)
			capacity *= 2;
		std::memcpy(data, cstr, size + 1);
	}
	length = size;
	return *this;
}

MyString& MyString::operator=(char c)
{
	length = 1;
	capacity = InitialCapacity;
	data[0] = c;
	return *this;
}

 std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	 os.write(str.data, str.length);

	 return os;
}



 size_t MyString::size() const noexcept
 {
	 return length;
 }

 bool MyString::empty() const noexcept
 {
	 return length == 0;
 }

 size_t MyString::getCapacity() const noexcept
 {
	 return capacity;
 }

 void MyString::resize(size_t n, char c)
 {
	 if (n > capacity) {
		 while (capacity < n)
			 capacity *= 2;
		 //check if the given input is greater than length to fill it with defaule null terminator
		 if (n > length)
			 for (int i = length; i < n; i++)
				 data[i] = c;
	 }
	 length = n;


 }

 void MyString::reserve(size_t n)
 {
	 if (n > capacity) {
		 char* newData = new char(n);
		 std::memcpy(newData, data, length + 1);

		 delete[] data;

		 data = newData;
		 capacity = n;
		 length = n;
	 }
 }

 void MyString::clear() noexcept
 {
	 length = 0;
	 data[0] = '\0';//to maintain validity said chatgpt but not understand
 }

 MyString& MyString::append(const MyString& str)
 {
	 int totalSize = length + str.length;
	 if (totalSize <= capacity) {
		 std::memcpy(data + length, str.data, str.length + 1);
	 }
	 else {
		 while (capacity < totalSize) {
			 capacity *= 2;
		 }
		 char* newData = new char[capacity];
		 std::memcpy(newData, newData, length + 1);
		 std::memcpy(newData + length, str.data, str.length + 1);
		 delete[] data;

		 data = newData;
	 }
		 length = totalSize;
	 return *this;
 }

 MyString& MyString::append(const char* s)
 {
	 int totalSize = length + strlen(s);
	 if (totalSize <= capacity) {
		 std::memcpy(data + length, s, strlen(s) + 1);
	 }
	 else {
		 while (capacity < totalSize) {
			 capacity *= 2;
		 }
		 char* newData = new char[capacity];
		 std::memcpy(newData, newData, length + 1);
		 std::memcpy(newData + length, s, strlen(s) + 1);
		 delete[] data;

		 data = newData;
	 }
		 length = totalSize;
	 return  *this;
 }

 MyString& MyString::append(size_t n, char c)
 {
	 length += 1;
	 if (length > capacity) {
		 capacity *= 2;
		 char* newData = new char[capacity];
		 std::memcpy(data, newData, length + 1);

		 delete[] data;
		 data = newData;
	 }
	 data[length] = c;
	 return *this;
 }

 void MyString::push_back(char c)
 {
	 length += 1;
	 if (length > capacity) {
		 capacity *= 2;
		 char* newData = new char[capacity];
		 std::memcpy(data, newData, length + 1);

		 delete[] data;
		 data = newData;
	 }
	 data[length - 1] = c;
 }

 void MyString::pop_back()
 {
	 length--;
 }

 MyString& MyString::erase(size_t pos, size_t len)
 {

	 if (len > length)
		 throw std::logic_error("try to erase element more than the length of the array");
	 //shifting the element by len pos through overwriting the element to be deleted
	 std::memmove(data + pos, data + pos + len, length - len);
	 length -= len;
	 return *this;
 }

 MyString& MyString::insert(int pos, const MyString& str)
 {
	 if (str.length + length > capacity) {
		 while (capacity < str.length + length)
			 capacity *= 2;
		 char* newData = new char[capacity];
		 std::memcpy(newData, data, length);
		 delete[] data;
		 data = newData;
	  }
	 //shift the element by len and then insert the inserted string at the apropriate place
	 for (int i = length - 1; i >= pos; i--)
		 data[i + str.length] = data[i];
	 for (int i = 0; i < str.length; i++)
		 data[pos + i] = str.data[i];
	 length += str.length;
	 return *this;
 }


 char& MyString::operator[](size_t pos)
 {
	 return data[pos];
 }

 const char& MyString::operator[](size_t pos) const
 {
	 return data[pos];
 }

 char& MyString::at(size_t pos)
 {
	 if (pos >= length || pos < 0)
		 throw std::out_of_range("invalid index in the string classes");
	 return data[pos];
 }

 const char& MyString::at(size_t pos) const
 {
	 if (pos >= length || pos < 0)
		 throw std::out_of_range("invalid index in the string classes");
	 return data[pos];
 }

 char& MyString::front()
 {
	 if (length == 0)
		 throw std::logic_error("accesing empty string");
	 return data[0];
 }

 char& MyString::back()
 {
	 if (length == 0)
		 throw std::logic_error("accesing empty string");
	 return data[length - 1];
 }
