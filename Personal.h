//Personal.h
/************************************************************************************************
파일명칭: Personal.h
기    능: 개인 클래스 선언
작 성 자: 임다니엘
작성일자: 2022/08/05
*************************************************************************************************/
#ifndef _PERSONAL_H
#define _PERSONAL_H
#include <string>		//문자열 클래스.
using namespace std;

class Personal {
public:
	Personal();																			//디폴트생성자
	Personal(string name, string address, string telephoneNumber, string emailAddress); //매개변수를 갖는 생성자
	Personal(const Personal& source);													//복사생성자
	~Personal();																		//소멸자
	bool IsEqual(const Personal& other);
	bool IsNotEqual(const Personal& other);
	bool operator==(const Personal& other);
	bool operator!=(const Personal& other);
	Personal& operator=(const Personal& source);
	string& GetName() const;
	string& GetAddress() const;
	string& GetTelephoneNumber() const;
	string& GetEmailAddress() const;
private:
	string name;
	string address;
	string telephoneNumber;
	string emailAddress;
};
inline string& Personal::GetName()const {
	return const_cast<string&>(this->name);
}
inline string& Personal::GetAddress()const {
	return const_cast<string&>(this->address);
}
inline string& Personal::GetTelephoneNumber()const {
	return const_cast<string&>(this->telephoneNumber);
}
inline string& Personal::GetEmailAddress()const {
	return const_cast<string&>(this->emailAddress);
}

#endif //_PERSONAL_H