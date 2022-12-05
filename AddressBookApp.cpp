//AddressBookApp.cpp
/************************************************************************************************
파일명칭: AddressBookApp.cpp
기    능:
작 성 자: 임다니엘
작성일자: 2022/08/11
*************************************************************************************************/
#include "AddressBookApp.h"
#include "AddressBookForm.h"

BOOL AddressBookApp::InitInstance() {
	AddressBookForm addressBookForm;

	this->m_pMainWnd = &addressBookForm;
	addressBookForm.DoModal();

	return TRUE;
}
AddressBookApp addressBookApp;