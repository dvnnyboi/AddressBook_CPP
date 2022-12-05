//AddressBook.h
/************************************************************************************************
파일명칭: AddressBook.h
기    능: 주소록 클래스 선언
작 성 자: 임다니엘
작성일자: 2022/08/05
*************************************************************************************************/
#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H
#include "Array.h"
#include "Personal.h"
#include <string>
using namespace std;

typedef signed long int Long;
class AddressBook {
public:
	AddressBook(Long capacity = 256);						//디폴트 생성자
	AddressBook(const AddressBook& source);					//복사생성자
	~AddressBook();											//소멸자
	Long Record(string name, string address, string telephoneNumber, string emailAddress);
	void Find(string name, Long* (*indexes), Long* count);
	Long Correct(Long index, string address, string telephoneNumber, string emailAddress);
	Long Erase(Long index);
	void Arrange();
	Personal& GetAt(Long index);
	AddressBook& operator=(const AddressBook& source);		//치환연산자
	Long GetCapacity()const;
	Long GetLength() const;
private:
	Array<Personal> personals;
	Long capacity;
	Long length;
};
inline Long AddressBook::GetCapacity() const {
	return this->capacity;
}
inline Long AddressBook::GetLength() const {
	return this->length;
}

int CompareNames(void* one, void* other);
int ComparePersonals(void* one, void* other);

#endif //_ADDRESSBOOK_H