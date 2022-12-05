//AddressBookForm.cpp
/************************************************************************************************
파일명칭: AddressBookForm.cpp
기    능: 주소록 프레임윈도우 클래스 정의
작 성 자: 임다니엘
작성일자: 2022/08/11
*************************************************************************************************/
#include "AddressBookForm.h"
#include "FindingForm.h"
#include "AddressBook.h"
#include "Personal.h"
#include <afxcmn.h>
#include <afxdb.h>

/************************************************************************************************
기    능: Message-Mapping
*************************************************************************************************/
BEGIN_MESSAGE_MAP(AddressBookForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, OnEraseButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_ARRANGE, OnArrangeButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
/************************************************************************************************
명    칭: AddressBookForm
기    능: 디폴트 생성자
*************************************************************************************************/
AddressBookForm::AddressBookForm(CWnd* parent)
	:CDialog(AddressBookForm::IDD, parent) {
	this->addressBook = NULL;
}
/************************************************************************************************
명    칭: Load
기    능: 주소록을 데이터베이스에서 적재한다.
*************************************************************************************************/
void AddressBookForm::Load() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.name, Personal.address, Personal.telephoneNumber, Personal.emailAddress FROM Personal;";
	
	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, name);
		rs.GetFieldValue((short)1, address);
		rs.GetFieldValue((short)2, telephoneNumber);
		rs.GetFieldValue((short)3, emailAddress);
		this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}
/************************************************************************************************
명    칭: Save
기    능: 주소록을 데이터베이스에에 저장한다.
*************************************************************************************************/
void AddressBookForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	CString sql = "SELECT Personal.code FROM Personal;";
	Personal personal;
	Long i;
	
	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	sql = "DELETE FROM Personal;";
	db.ExecuteSQL(sql);
	i = 0;
	while (!rs.IsEOF() && i < this->addressBook->GetLength()) {
		rs.GetFieldValue((short)0, code);
		personal = this->addressBook->GetAt(i);
		sql.Format("INSERT INTO Personal(name, address, telephoneNumber, emailAddress, code) "
			"VALUES('%s', '%s', '%s', '%s', '%s');", personal.GetName().c_str(), personal.GetAddress().c_str(),
			personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str(), (LPCTSTR)code);
		db.ExecuteSQL(sql);
		i++;
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}
/************************************************************************************************
명    칭: Insert
기    능: 데이터베이스에서 삽입한다.
*************************************************************************************************/
void AddressBookForm::Insert(Long index) {
	CDatabase db;
	CString sql;
	Personal personal = this->addressBook->GetAt(index);

	sql.Format("INSERT INTO Personal(name, address, telephoneNumber, emailAddress, code) "
		"VALUES('%s', '%s', '%s', '%s', '%s');", personal.GetName().c_str(), personal.GetAddress().c_str(),
		personal.GetTelephoneNumber().c_str(), personal.GetEmailAddress().c_str(), (LPCTSTR)(this->GetCode()));
	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	db.ExecuteSQL(sql);
	db.Close();
}
/************************************************************************************************
명    칭: GetCode
기    능: 코드(Primary Key)를 가져온다.
*************************************************************************************************/
CString AddressBookForm::GetCode() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal ORDER BY code DESC;";
	Long i = 0;

	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString code;
	CString number;
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, code);
		number = code.Right(4);
		i = _ttoi(number);
	}
	code.Format("P%04d", i + 1);
	rs.Close();
	db.Close();

	return code;
}
/************************************************************************************************
명    칭: Modify
기    능: 데이터베이스에서 수정한다.
*************************************************************************************************/
void AddressBookForm::Modify(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	Personal personal = this->addressBook->GetAt(index);
	CString sql = "SELECT Personal.code FROM Personal;";
	CString code;
	Long i;

	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	i = 0;
	while (!rs.IsEOF() && i <= index) {
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("UPDATE Personal SET address = '%s', telephoneNumber = '%s', emailAddress = '%s' "
		"WHERE Personal.code = '%s';", personal.GetAddress().c_str(), personal.GetTelephoneNumber().c_str(),
		personal.GetEmailAddress().c_str(), (LPCTSTR)code);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();
}
/************************************************************************************************
명    칭: Delete
기    능: 데이터베이스에서 삭제한다.
*************************************************************************************************/
void AddressBookForm::Delete(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT Personal.code FROM Personal;";
	CString code;
	Long i;

	db.OpenEx("DSN=AddressBook;UID=root;PWD=Dlaeksldpf1!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	i = 0;
	while (!rs.IsEOF() && i <= index) {
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}
	sql.Format("DELETE FROM Personal WHERE Personal.code = '%s';", (LPCTSTR)code);
	db.ExecuteSQL(sql);

	rs.Close();
	db.Close();
}
/************************************************************************************************
명    칭: OnInitDialog
기    능: 윈도우가 생성될 때 시나리오.
*************************************************************************************************/
BOOL AddressBookForm::OnInitDialog() {
	CDialog::OnInitDialog();

	//1.1. 주소록을 만든다.
	this->addressBook = new AddressBook;
	//1.2. 주소록에서 적재한다.
	this->Load();
	//1.3. 리스트 뷰 컨트롤의 헤더를 만든다.
	((CListCtrl *)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "번호", LVCFMT_LEFT, 40);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "성명", LVCFMT_LEFT, 70);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "주소", LVCFMT_LEFT, 150);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "전화번호", LVCFMT_LEFT, 90);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "이메일주소", LVCFMT_LEFT, 120);
	//1.4. 리스트 뷰 컨트롤에 전체선택 기능을 설정한다.
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//1.5. 적재한 개수만큼 리스트 뷰 컨트롤에 항목을 추가한다.
	CString number;
	Personal personal;
	Long i = 0;
	while (i < this->addressBook->GetLength()) {
		personal = this->addressBook->GetAt(i);
		number.Format("%d", i + 1);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(i, (LPCTSTR)number);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 1, personal.GetName().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 2, personal.GetAddress().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 3, personal.GetTelephoneNumber().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 4, personal.GetEmailAddress().c_str());
		i++;
	}
	return FALSE;
}
/************************************************************************************************
명    칭: OnRecordButtonClicked
기    능: 기재하기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void AddressBookForm::OnRecordButtonClicked() {
	CString number;
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;
	Personal personal;

	//2.1. 성명, 주소, 전화번호, 이메일주소를 읽는다.
	this->GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	this->GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	//2.2. 주소록에서 기재한다.
	index = this->addressBook->Record((LPCTSTR)name, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
	this->Insert(index);
	//2.3. 리스트 뷰 컨트롤에 항목을 추가한다.
	personal = this->addressBook->GetAt(index);
	number.Format("%d", index + 1);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(index, (LPCTSTR)number);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 1, personal.GetName().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}
/************************************************************************************************
명    칭: OnFindButtonClicked
기    능: 찾기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void AddressBookForm::OnFindButtonClicked() {
	FindingForm findingForm;

	findingForm.DoModal();
}
/************************************************************************************************
명    칭: OnCorrectButtonClicked
기    능: 고치기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void AddressBookForm::OnCorrectButtonClicked() {
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;
	Personal personal;

	//4.1. 리스트 뷰  컨트롤에서 위치를 읽는다.
	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//4.2. 주소, 전화번호, 이메일주소를 읽는다.
	this->GetDlgItem(IDC_EDIT_ADDRESS)->GetWindowText(address);
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->GetWindowText(telephoneNumber);
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->GetWindowText(emailAddress);
	//4.3. 주소록에서 고친다.
	index = this->addressBook->Correct(index, (LPCTSTR)address, (LPCTSTR)telephoneNumber, (LPCTSTR)emailAddress);
	this->Modify(index);
	//4.4. 리스트 뷰 컨트롤에서 항목을 고친다.
	personal = this->addressBook->GetAt(index);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 2, personal.GetAddress().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 3, personal.GetTelephoneNumber().c_str());
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(index, 4, personal.GetEmailAddress().c_str());
}
/************************************************************************************************
명    칭: OnEraseButtonClicked
기    능: 지우기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void AddressBookForm::OnEraseButtonClicked() {
	CString number;
	Long index;
	Long i;

	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	this->Delete(index);
	this->addressBook->Erase(index);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->DeleteItem(index);
	i = index;
	while (i < this->addressBook->GetLength()) {
		number.Format("%d", i + 1);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 0, (LPCTSTR)number);
		i++;
	}
}
/************************************************************************************************
명    칭: OnArrangeButtonClicked
기    능: 정리하기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void AddressBookForm::OnArrangeButtonClicked() {
	CString number;
	Personal personal;
	Long i;

	this->addressBook->Arrange();
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	i = 0;
	while (i < this->addressBook->GetLength()) {
		personal = this->addressBook->GetAt(i);
		number.Format("%d", i + 1);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertItem(i, (LPCTSTR)number);
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 1, personal.GetName().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 2, personal.GetAddress().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 3, personal.GetTelephoneNumber().c_str());
		((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetItemText(i, 4, personal.GetEmailAddress().c_str());
		i++;
	}
}
/************************************************************************************************
명    칭: OnListViewItemDoubleClicked
기    능: 리스트뷰 컨트롤의 항목을 더블클릭했을 때 시나리오.
*************************************************************************************************/
void AddressBookForm::OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result) {
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;
	
	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	name = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	emailAddress = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);

	this->GetDlgItem(IDC_EDIT_NAME)->SetWindowText((LPCTSTR)name);
	this->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText((LPCTSTR)address);
	this->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText((LPCTSTR)telephoneNumber);
	this->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText((LPCTSTR)emailAddress);
}
/************************************************************************************************
명    칭: OnClose
기    능: 닫기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void AddressBookForm::OnClose() {
	this->Save();
	if (this->addressBook != NULL) {
		delete this->addressBook;
	}
	this->EndDialog(0);
}