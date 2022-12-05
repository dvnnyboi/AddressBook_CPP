//FindingForm.cpp
/************************************************************************************************
파일명칭: FindingForm.cpp
기    능: 주소록 - 찾기 윈도우 클래스 정의
작 성 자: 임다니엘
작성일자: 2022/08/11
*************************************************************************************************/
#include "FindingForm.h"
#include "AddressBookForm.h"
#include "AddressBook.h"
#include <afxcmn.h>

/************************************************************************************************
기    능: Message-Mapping
*************************************************************************************************/
BEGIN_MESSAGE_MAP(FindingForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PERSONALS, OnListViewItemDoubleClicked)
	ON_WM_CLOSE()
END_MESSAGE_MAP()
/************************************************************************************************
명    칭: FindingForm
기    능: 디폴트 생성자
*************************************************************************************************/
FindingForm::FindingForm(CWnd* parent)
	:CDialog(IDD, parent) {
	this->indexes = NULL;
	this->count = 0;
}
/************************************************************************************************
명    칭: OnInitDialog
기    능: 윈도우가 생성될 때 시나리오.
*************************************************************************************************/
BOOL FindingForm::OnInitDialog() {
	CDialog::OnInitDialog();

	//1.1. 리스트 뷰 컨트롤의 헤더를 만든다.
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(0, "번호", LVCFMT_LEFT, 40);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(1, "성명", LVCFMT_LEFT, 70);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(2, "주소", LVCFMT_LEFT, 150);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(3, "전화번호", LVCFMT_LEFT, 90);
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->InsertColumn(4, "이메일주소", LVCFMT_LEFT, 120);
	//1.2. 리스트 뷰 컨트롤에 전체선택 기능을 추가한다.
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return FALSE;
}
/************************************************************************************************
명    칭: OnFindButtonClicked
기    능: 찾기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void FindingForm::OnFindButtonClicked() {
	CString name;
	CString number;
	Long index;
	Long i;
	AddressBookForm* addressBookForm;
	Personal personal;

	//2.1. 성명을 읽는다.
	this->GetDlgItem(IDC_EDIT_NAME)->GetWindowText(name);
	//2.2. 주소록 윈도우를 찾는다.
	addressBookForm = (AddressBookForm*)CWnd::FindWindowA("#32770", "주소록");
	//2.3. 주소록 윈도우의 주소록에서 찾는다.
	if (this->indexes != NULL) {
		delete[]this->indexes;
	}
	addressBookForm->addressBook->Find((LPCTSTR)name, &(this->indexes), &(this->count));
	//2.4. 리스트 뷰 컨트롤의 모든 항목을 지운다.
	((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->DeleteAllItems();
	//2.5. 리스트 뷰 컨트롤에 찾은 개수만큼 항목들을 추가한다.
	i = 0;
	while (i < this->count) {
		personal = addressBookForm->addressBook->GetAt(this->indexes[i]);
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
void FindingForm::OnListViewItemDoubleClicked(NMHDR* pNotifyStruct, LRESULT* result) {
	CString name;
	CString address;
	CString telephoneNumber;
	CString emailAddress;
	Long index;
	Long previous;
	AddressBookForm* addressBookForm;
	
	//3.1. 리스트 뷰 컨트롤에서 위치를 읽는다.
	index = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetSelectionMark();
	//3.2. 리스트 뷰 컨트롤에서 항목을 읽는다.
	name = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 1);
	address = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 2);
	telephoneNumber = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 3);
	emailAddress = ((CListCtrl*)this->GetDlgItem(IDC_LIST_PERSONALS))->GetItemText(index, 4);
	//3.3. 주소록 윈도우를 찾는다.
	addressBookForm = (AddressBookForm*)CWnd::FindWindowA("#32770", "주소록");
	//3.4. 주소록 윈도우의 리스트 뷰 컨트롤에서 항목을 선택한다.
	previous = ((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetSelectionMark(this->indexes[index]);
	
	//3.5. 주소록 윈도우에 성명, 주소, 전화번호, 이메일주소를 쓴다.
	addressBookForm->GetDlgItem(IDC_EDIT_NAME)->SetWindowText((LPCTSTR)name);
	addressBookForm->GetDlgItem(IDC_EDIT_ADDRESS)->SetWindowText((LPCTSTR)address);
	addressBookForm->GetDlgItem(IDC_EDIT_TELEPHONENUMBER)->SetWindowText((LPCTSTR)telephoneNumber);
	addressBookForm->GetDlgItem(IDC_EDIT_EMAILADDRESS)->SetWindowText((LPCTSTR)emailAddress);

	((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetItemState(previous, 0, LVIS_SELECTED);
	((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetItemState(this->indexes[index], LVIS_SELECTED, LVIS_SELECTED);
	
	//3.6. 찾기 윈도우를 닫는다.
	if (this->indexes != NULL) {
		delete[]this->indexes;
	}
	this->EndDialog(0);

	((CListCtrl*)addressBookForm->GetDlgItem(IDC_LIST_PERSONALS))->SetFocus();
}
/************************************************************************************************
명    칭: OnClose
기    능: 닫기 버튼을 클릭했을 때 시나리오.
*************************************************************************************************/
void FindingForm::OnClose() {
	//4.1. 찾기 윈도우를 닫는다.
	if (this->indexes != NULL) {
		delete[]this->indexes;
	}
	this->EndDialog(0);
}