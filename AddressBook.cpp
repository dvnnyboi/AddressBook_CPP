//AddressBook.cpp
/************************************************************************************************
파일명칭: AddressBook.cpp
기    능: 주소록 클래스 정의 및 테스트 시나리오
작 성 자: 임다니엘
작성일자: 2022/08/05
*************************************************************************************************/
#include "AddressBook.h"


/************************************************************************************************
명    칭: AddressBook (default)
기    능: 디폴트 생성자
입    력: 할당량
출    력: 없음
*************************************************************************************************/
AddressBook::AddressBook(Long capacity)
	:personals(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
/************************************************************************************************
명    칭: AddressBook (copy)
기    능: 복사 생성자
입    력: 주소록
출    력: 없음
*************************************************************************************************/
AddressBook::AddressBook(const AddressBook& source)
	:personals(source.personals) {
	this->capacity = source.capacity;
	this->length = source.length;
}
/************************************************************************************************
명    칭: ~AddressBook 
기    능: 소멸자
입    력: 없음
출    력: 없음
*************************************************************************************************/
AddressBook::~AddressBook() {}
/************************************************************************************************
명    칭: Record
기    능: 주소록에서 기재한다
입    력: 성명, 주소, 전화번호, 이메일주소
출    력: 위치
*************************************************************************************************/
Long AddressBook::Record(string name, string address, string telephoneNumber, string emailAddress) {
	Personal personal(name, address, telephoneNumber, emailAddress);
	Long index;

	if (this->length < this->capacity) {
		index = this->personals.Store(this->length, personal);
	}
	else {
		index = this->personals.AppendFromRear(personal);
		this->capacity++;
	}
	this->length++;

	return index;
}
/************************************************************************************************
명    칭: Find
기    능: 주소록에서 찾는다.
입    력: 성명
출    력: 위치들, 개수
*************************************************************************************************/
void AddressBook::Find(string name, Long* (*indexes), Long* count) {
	this->personals.LinearSearchDuplicate(&name, indexes, count, CompareNames);
}
/************************************************************************************************
명    칭: Correct
기    능: 주소록에서 고친다.
입    력: 위치, 주소, 전화번호, 이메일주소
출    력: 위치
*************************************************************************************************/
Long AddressBook::Correct(Long index, string address, string telephoneNumber, string emailAddress) {
	Personal personal;

	personal = this->personals.GetAt(index);
	personal = Personal(personal.GetName(), address, telephoneNumber, emailAddress);
	index = this->personals.Modify(index, personal);

	return index;
}
/************************************************************************************************
명    칭: Erase
기    능: 주소록에서 지운다.
입    력: 위치
출    력: 위치
*************************************************************************************************/
Long AddressBook::Erase(Long index) {
	index = this->personals.Delete(index);
	this->length--;
	this->capacity--;

	return index;
}
/************************************************************************************************
명    칭: Arrange
기    능: 주소록에서 정리한다.
입    력: 없음
출    력: 없음
*************************************************************************************************/
void AddressBook::Arrange() {
	this->personals.SelectionSort(ComparePersonals);
}
/************************************************************************************************
명    칭: GetAt
기    능: 주소록에서 가져온다
입    력: 위치
출    력: 개인
*************************************************************************************************/
Personal& AddressBook::GetAt(Long index) {
	return this->personals.GetAt(index);
}
/************************************************************************************************
명    칭: operator = 
기    능: 치환연산자
입    력: 주소록
출    력: 주소록
*************************************************************************************************/
AddressBook& AddressBook::operator=(const AddressBook& source) {
	this->personals = source.personals;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

/************************************************************************************************
 함수포인터형 변수로 사용될 함수들
************************************************************************************************/
int CompareNames(void* one, void* other) {
	Personal* one_ = static_cast<Personal*>(one);
	string* other_ = static_cast<string*>(other);

	return one_->GetName().compare(*other_);
}
int ComparePersonals(void* one, void* other) {
	Personal* one_ = static_cast<Personal*>(one);
	Personal* other_ = static_cast<Personal*>(other);

	return one_->GetName().compare(other_->GetName());
}
#if 0
/************************************************************************************************
테스트 시나리오
************************************************************************************************/
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	AddressBook addressBook(3);
	Personal personal;
	Long index;
	
	//기재한다.
	cout << "*******RECORD*******" << endl;
	index = addressBook.Record("Hong", "SeoCho-Dong, Seoul", "01012345678", "hong@gmail.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	index = addressBook.Record("Kim", "SongPa-Gu, Seoul", "01087654321", "kim@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	index = addressBook.Record("Go", "Nam-Gu, Pohang", "01056781234", "go@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	index = addressBook.Record("Choi", "GwangJin-Gu, Seoul", "01043218765", "choi@gmail.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	index = addressBook.Record("Hong", "SeongDong-Gu, Seoul", "01098765432", "hgd@gmail.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	//찾는다.
	cout << "********FIND********" << endl;
	Long(*indexes);
	Long count;
	Long i;

	addressBook.Find("Hong", &indexes, &count);
	i = 0;
	while (i < count) {
		personal = addressBook.GetAt(indexes[i]);
		cout << personal.GetName() << endl
			<< personal.GetAddress() << endl
			<< personal.GetTelephoneNumber() << endl
			<< personal.GetEmailAddress() << endl;
		cout << "********************" << endl;
		i++;
	}
	if (indexes != 0) {
		delete[]indexes;
		indexes = 0;
	}
	//고친다.
	cout << "*******CORRECT******" << endl;
	index = addressBook.Correct(1, "GangNam-Gu, Seoul", "01087654321", "gdkim@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << endl
		<< personal.GetAddress() << endl
		<< personal.GetTelephoneNumber() << endl
		<< personal.GetEmailAddress() << endl;
	cout << "********************" << endl;
	//지운다.
	index = addressBook.Erase(1);
	if (index < 0) {
		cout << "DELETED!" << endl;
	}
	cout << "********************" << endl;
	//정리한다.
	cout << "******ARRANGE*******" << endl;
	addressBook.Arrange();
	i = 0;
	while (i < addressBook.GetLength()) {
		personal = addressBook.GetAt(i);
		cout << personal.GetName() << endl
			<< personal.GetAddress() << endl
			<< personal.GetTelephoneNumber() << endl
			<< personal.GetEmailAddress() << endl;
		cout << "********************" << endl;
		i++;
	}
	//치환연산자.
	cout << "*****operator =*****" << endl;
	AddressBook copy(3);

	copy = addressBook;
	i = 0;
	while (i < copy.GetLength()) {
		personal = copy.GetAt(i);
		cout << personal.GetName() << endl
			<< personal.GetAddress() << endl
			<< personal.GetTelephoneNumber() << endl
			<< personal.GetEmailAddress() << endl;
		cout << "********************" << endl;
		i++;
	}

	return 0;
}
#endif