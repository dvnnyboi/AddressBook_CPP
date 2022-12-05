//Personal.cpp
/************************************************************************************************
파일명칭: Personal.cpp
기    능: 개인 클래스 정의 및 테스트 시나리오
작 성 자: 임다니엘
작성일자: 2022/08/05
*************************************************************************************************/
#include "Personal.h"

/************************************************************************************************
명    칭: Personal (default)
기    능: 디폴트 생성자
입    력: 없음
출    력: 없음
*************************************************************************************************/
Personal::Personal()
	:name(""), address(""), telephoneNumber(""), emailAddress("") {
}
/************************************************************************************************
명    칭: Personal (parameter)
기    능: 매개변수를 갖는 생성자
입    력: 성명, 주소, 전화번호, 이메일주소
출    력: 없음
*************************************************************************************************/
Personal::Personal(string name, string address, string telephoneNumber, string emailAddress)
	:name(name), address(address), telephoneNumber(telephoneNumber), emailAddress(emailAddress) {
}
/************************************************************************************************
명    칭: Personal (copy)
기    능: 복사 생성자
입    력: 개인
출    력: 없음
*************************************************************************************************/
Personal::Personal(const Personal& source)
	:name(source.name), address(source.address),
		telephoneNumber(source.telephoneNumber), emailAddress(source.emailAddress) {
}
/************************************************************************************************
명    칭: ~Personal
기    능: 소멸자
입    력: 없음
출    력: 없음
*************************************************************************************************/
Personal::~Personal() {}
/************************************************************************************************
명    칭: IsEqual
기    능: 같은지 확인한다.
입    력: 개인
출    력: 확인결과
*************************************************************************************************/
bool Personal::IsEqual(const Personal& other) {
	bool ret = false;
	
	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0
		&& this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}/************************************************************************************************
명    칭: IsNotEqual
기    능: 다른지 확인한다.
입    력: 개인
출    력: 확인결과
*************************************************************************************************/
bool Personal::IsNotEqual(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0
		|| this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
명    칭: opertor ==
기    능: 같은지 확인한다.
입    력: 개인
출    력: 확인결과
*************************************************************************************************/
bool Personal::operator==(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0
		&& this->telephoneNumber.compare(other.telephoneNumber) == 0 && this->emailAddress.compare(other.emailAddress) == 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
명    칭: opertor !=
기    능: 다른지 확인한다.
입    력: 개인
출    력: 확인결과
*************************************************************************************************/
bool Personal::operator!=(const Personal& other) {
	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0
		|| this->telephoneNumber.compare(other.telephoneNumber) != 0 || this->emailAddress.compare(other.emailAddress) != 0) {
		ret = true;
	}
	return ret;
}
/************************************************************************************************
명    칭: opertor =
기    능: 치환 연산자 함수
입    력: 개인
출    력: 개인
*************************************************************************************************/
Personal& Personal::operator=(const Personal& source) {
	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->emailAddress = source.emailAddress;

	return *this;
}
#if 0
/************************************************************************************************/
//테스트시나리오
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	//디폴트 생성자
	Personal one;
	//매개변수를 갖는 생성자.
	cout << "***PARAMETER***" << endl;
	Personal two("Hong", "Seoul", "01012345678", "hong@naver.com");
	cout << two.GetName() << endl
		<< two.GetAddress() << endl
		<< two.GetTelephoneNumber() << endl
		<< two.GetEmailAddress() << endl;
	cout << "***************" << endl;
	//복사생성자
	cout << "*****COPY******" << endl;
	Personal three(two);
	cout << three.GetName() << endl
		<< three.GetAddress() << endl
		<< three.GetTelephoneNumber() << endl
		<< three.GetEmailAddress() << endl;
	cout << "***************" << endl;
	//IsNotEqual
	cout << "****IsEqual****" << endl;
	bool boolean;
	boolean = two.IsEqual(three);
	if (boolean == true) {
		cout << "EQUAL" << endl;
	}
	//operator ==
	if (two == three) {
		cout << "EQUAL" << endl;
	}
	cout << "***************" << endl;
	//IsNotEqual
	cout << "**IsNotEqual***" << endl;
	Personal four("Kim", "Busan", three.GetTelephoneNumber(), three.GetEmailAddress());
	boolean = three.IsNotEqual(four);
	if (boolean == true) {
		cout << "NOT EQUAL" << endl;
	}
	//operator !=
	if (three != four) {
		cout << "NOT EQUAL" << endl;
	}
	cout << "***************" << endl;
	//operator =
	one = four;
	cout << one.GetName() << endl
		<< one.GetAddress() << endl
		<< one.GetTelephoneNumber() << endl
		<< one.GetEmailAddress() << endl;
	cout << "***************" << endl;

	return 0;
}
#endif