//Array.h
/************************************************************************************************
파일명칭: Array.h
기    능: 배열 라이브러리 클래스 선언 및 정의
작 성 자: 임다니엘
작성일자: 2022/08/03
*************************************************************************************************/
#ifndef _ARRAY_H
#define _ARRAY_H

typedef signed long int Long;
template <typename T>
class Array {
public:
	Array(Long capacity = 256);		//Default Constructor
	Array(const Array& source);		//Copy Constructor
	~Array();						//Destructor
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void* key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void* key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void* key, Long* (*indexes), Long* count, int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*, void*));
	void BubbleSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void Merge(const Array& one, const Array& other, int(*compare)(void*, void*));
	T& GetAt(Long index);
	Long GetCapacity() const;
	Long GetLength() const;
	Array& operator=(const Array& source);
	T& operator[](Long index);
	T* operator+(Long index);
private:
	T(*front);
	Long capacity;
	Long length;
};
template <typename T>
inline Long Array<T>::GetCapacity()const {
	return this->capacity;
}
template <typename T>
inline Long Array<T>::GetLength()const {
	return this->length;
}

/************************************************************************************************
명    칭: Array (default)
기    능: 디폴트 생성자
입    력: 할당량
출    력: 없음
*************************************************************************************************/
template <typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}
/************************************************************************************************
명    칭: Array (copy)
기    능: 복사 생성자
입    력: 배열
출    력: 없음
*************************************************************************************************/
template <typename T>
Array<T>::Array(const Array& source) {
	Long i = 0;

	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}
/************************************************************************************************
명    칭: ~Array
기    능: 소멸자
입    력: 없음
출    력: 없음
*************************************************************************************************/
template <typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
}
/************************************************************************************************
명    칭: Store
기    능: 배열에 항목을 저장한다.
입    력: 위치, 항목
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>:: Store(Long index, T object) {
	this->front[index] = object;
	this->length++;

	return index;
}
/************************************************************************************************
명    칭: Insert
기    능: 배열에 항목을 삽입한다.
입    력: 위치, 항목
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>::Insert(Long index, T object) {
	T(*temp) = 0;
	Long i = 0;

	temp = new T[this->capacity + 1];
	while (i < index) {
		temp[i] = this->front[i];
		i++;
	}
	while (i < this->length) {
		temp[i+1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}
/************************************************************************************************
명    칭: AppendFromFront
기    능: 배열에 항목을 추가한다.
입    력: 항목
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>::AppendFromFront(T object) {
	T(*temp);
	Long index = 0;
	Long i = 0;

	temp = new T[this->capacity + 1];
	while (i < this->length) {
		temp[i+1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = temp;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}
/************************************************************************************************
명    칭: AppendFromRear
기    능: 배열에 항목을 저장한다.
입    력: 항목
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>::AppendFromRear(T object) {
	T(*temp);
	Long index;
	Long i = 0;

	temp = new T[this->capacity + 1];
	while (i < this->length) {
		temp[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = temp;
	this->capacity++;
	index = this->capacity - 1;
	this->front[index] = object;
	this->length++;

	return index;
}
/************************************************************************************************
명    칭: Delete
기    능: 배열의 항목을 지운다.
입    력: 없음
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>::Delete(Long index) {
	T(*temp) = 0;
	Long i = 0;
	if (this->capacity > 1) {
		temp = new T[this->capacity];
	}
	while (i < index) {
		temp[i] = this->front[i];
		i++;
	}
	i++;
	while (i < this->length) {
		temp[i - 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->length--;
	this->capacity--;
	index = -1;

	return index;
}
/************************************************************************************************
명    칭: DeleteFromFront
기    능: 배열의 첫 항목을 지운다.
입    력: 없음
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>::DeleteFromFront() {
	T(*temp) = 0;
	Long index;
	Long i = 1;
	
	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < this->length) {
		temp[i - 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->length--;
	this->capacity--;
	index = -1;

	return index;
}
/************************************************************************************************
명    칭: DeleteFromRear
기    능: 배열의 마지막 항목을 지운다.
입    력: 없음
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>::DeleteFromRear() {
	T(*temp) = 0;
	Long index;
	Long i = 0;

	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}
	while (i < this->capacity - 1) {
		temp[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = temp;
	}
	this->length--;
	this->capacity--;
	index = -1;

	return index;
}
/************************************************************************************************
명    칭: Clear
기    능: 배열의 모든 항목을 지운다.
입    력: 없음
출    력: 없음
*************************************************************************************************/
template <typename T>
void Array<T>::Clear() {
	if (this->front != 0) {
		delete[]this->front;
		this->front = 0;
	}
	this->length = 0;
	this->capacity = 0;
}
/************************************************************************************************
명    칭: Modify
기    능: 배열의 항목을 고친다.
입    력: 위치, 항목
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>::Modify(Long index, T object) {
	this->front[index] = object;

	return index;
}
/************************************************************************************************
명    칭: LinearSearchUnique
기    능: 배열에서 찾는다
입    력: 조건
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>::LinearSearchUnique(void* key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;
	
	while (i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}
	if (i < this->length) {
		index = i;
	}

	return index;
}
/************************************************************************************************
명    칭: LinearSearchDuplicate
기    능: 배열에서 찾는다
입    력: 조건
출    력: 위치들, 개수
*************************************************************************************************/
template <typename T>
void Array<T>::LinearSearchDuplicate(void* key, Long*(*indexes), Long*count, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;

	*count = 0;
	*indexes = new Long[this->length];
	while (i < this->length) {
		if (compare(this->front + i, key) == 0) {
			(*indexes)[j] = i;
			(*count)++;
			j++;
		}
		i++;
	}
}
/************************************************************************************************
명    칭: BinarySearchUnique
기    능: 배열에서 찾는다
입    력: 조건
출    력: 위치
*************************************************************************************************/
template <typename T>
Long Array<T>::BinarySearchUnique(void* key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long low = 0;
	Long high = this->length - 1;
	Long middle = (low + high) / 2;

	while (low <= high && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			low = middle + 1;
		}
		else {
			high = middle - 1;
		}
		middle = (low + high) / 2;
	}
	if (low <= high) {
		index = middle;
	}
	return index;
}
/************************************************************************************************
명    칭: BinarySearchDuplicate
기    능: 배열에서 찾는다
입    력: 조건
출    력: 위치들, 개수
*************************************************************************************************/
template <typename T>
void Array<T>::BinarySearchDuplicate(void* key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long low = 0;
	Long high = this->length - 1;
	Long middle = (low + high) / 2;
	Long i;
	Long j = 0;

	*count = 0;
	*indexes = new Long[this->length];
	while (low <= high && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			low = middle + 1;
		}
		else {
			high = middle - 1;
		}
		middle = (low + high) / 2;
	}
	i = middle - 1;
	while (i >= low && compare(this->front + i, key) == 0) {
		i--;
	}
	i++;
	while (i <= high && compare(this->front + i, key) == 0) {
		(*indexes)[j] = i;
		(*count)++;
		j++;
		i++;
	}
}
/************************************************************************************************
명    칭: SelectionSort
기    능: 배열을 오름차순으로 정렬한다. (선택정렬)
입    력: 없음
출    력: 없음
*************************************************************************************************/
template <typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 0;
	Long j;
	Long smallest;

	while (i < this->length - 1) {
		smallest = i;
		j = i + 1;
		while (j < this->length) {
			if (compare(this->front + smallest, this->front + j) > 0) {
				smallest = j;
			}
			j++;
		}
		temp = this->front[smallest];
		this->front[smallest] = this->front[i];
		this->front[i] = temp;
		i++;
	}
}
/************************************************************************************************
명    칭: BubbleSort
기    능: 배열을 오름차순으로 정렬한다. ( 버블정렬)
입    력: 없음
출    력: 없음
*************************************************************************************************/
template <typename T>
void Array<T>::BubbleSort(int (*compare)(void*, void*)) {
	T temp;
	Long i = this->length - 2;
	Long j;
	Long count = 1;

	while (i >= 0 && count > 0) {
		count = 0;
		j = 0;
		while (j <= i) {
			if (compare(this->front + j, this->front + (j + 1)) > 0) {
				temp = this->front[j];
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = temp;
				count++;
			}
			j++;
		}
		i--;
	}
}
/************************************************************************************************
명    칭: BubbleSort
기    능: 배열을 오름차순으로 정렬한다. ( 버블정렬)
입    력: 없음
출    력: 없음
*************************************************************************************************/
template <typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {
	T temp;
	Long i = 1;
	Long j;

	while (i < this->length) {
		temp = this->front[i];
		j = i - 1;
		while (j >= 0 && compare(this->front + j, &temp) > 0) {
			this->front[j + 1] = this->front[j];
			j--;
		}
		this->front[j + 1] = temp;
		i++;
	}
}
/************************************************************************************************
명    칭: Merge
기    능: 두 배열을 병합한다.
입    력: 배열1, 배열2
출    력: 없음
*************************************************************************************************/
template <typename T>
void Array<T>::Merge(const Array& one, const Array& other, int(*compare)(void*, void*)) {
	Long i = 0;
	Long j = 0;
	Long k = 0;
	
	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = new T[one.length + other.length];
	this->capacity = one.length + other.length;
	while (i < one.length && j < other.length) {
		if (compare(one.front + i, other.front + j) <= 0) {
			this->front[k] = one.front[i];
			k++;
			i++;
		}
		else {
			this->front[k] = other.front[j];
			k++;
			j++;
		}
	}
	while (i < one.length) {
		this->front[k] = one.front[i];
		k++;
		i++;
	}
	while (j < other.length) {
		this->front[k] = other.front[j];
		k++;
		j++;
	}
	this->length = one.length + other.length;
}
/************************************************************************************************
명    칭: GetAt
기    능: 항목을 읽어온다
입    력: 위치
출    력: 항목
*************************************************************************************************/
template <typename T>
T& Array<T>::GetAt(Long index) {
	return this->front[index];
}
/************************************************************************************************
명    칭: Operator=
기    능: 치환연산자
입    력: 위치, 항목
출    력: 위치
*************************************************************************************************/
template <typename T>
Array<T>& Array<T>::operator=(const Array& source) {
	Long i = 0;

	if (this->front != 0) {
		delete[]this->front;
	}
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}
/************************************************************************************************
명    칭: Operator[]
기    능: 첨자연산자
입    력: 위치, 항목
출    력: 위치
*************************************************************************************************/
template <typename T>
T& Array<T>::operator[](Long index) {
	return this->front[index];
}
/************************************************************************************************
명    칭: Operator+
기    능: 주소 연산자
입    력: 위치, 항목
출    력: 위치
*************************************************************************************************/
template <typename T>
T* Array<T>::operator+(Long index) {
	return this->front + index;
}


#endif //_ARRAY_H