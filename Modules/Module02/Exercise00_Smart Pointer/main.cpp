/*
Reference : https://gdngy.tistory.com/183
<기본 메모리에 대한 이해>

스택 메모리: 함수, 지역변수, 객체를 생성하면 스택메모리에 생성되고
함수나 블록의 범위를 벗어날 때 자동으로 해제된다.
-> 스마트 포인터와 관련이 적음

힙 메모리: 동적으로 메모리 할당을위해 사용되는 메모리영역
프로그래머가 명시적으로 할당(new) 및 해제(delete)를 해줘야함
-> 관리가 잘 되지않으면 메모리 누수, dangling pointer문제 발생 할 수 있음
-> 스마트 포인터 사용해야함
*/

#include <iostream>
#include <string>
#include <memory>

using namespace std;
int main()
{
	unique_ptr<int> ptr(new int(10)); //main함수가 끝나고 ptr이 사라질때 ptr이 가르키는 메모리도 자동으로 해제가 된다.
	*ptr = 20; //smart pointer를 통해 메모리에 접근
	return 0;
}

// <스마트 포인터의 종류>
void auto_ptr_problem() //1. auto_ptr -> 사용 권장되지않음(deprecated)
{
	auto_ptr<int> ptr1(new int);
	*ptr1 = 10;

	auto_ptr<int> ptr2 = ptr1; //복사연산을 허용

	cout << *ptr2 << endl; //이건 괜찮은데
	cout << *ptr1 << endl; //얘는 예상하지 못한 동작이 발생함
}


void unique_ptr_problem() //1. unique_ptr -> 동일한 메모리를 가르키는 여러개의 스마트포인터 존재할수없음
{
	unique_ptr<int> ptr1(new int(10));

	//unique_ptr<int> ptr2 = ptr1; //복사연산을 허용하지않음
	unique_ptr<int> ptr2 = move(ptr1); //move를 통해 소유권을 이동시켜야함\
										 즉 유일한 소유자만 가능
}

void shared_ptr_problem() //3. shared_ptr -> Reference Count를 통해 관리
{
	shared_ptr<int> ptr1(new int(10));
	{
		shared_ptr<int> ptr2 = ptr1;
		//ptr1, ptr2 모두 동일한 메모리 가르키며 Reference Count = 2
	} //ptr2가 범위를 벗어나며 해제되고 Reference Count = 1
	// ptr1이 메모리를 가지고 있으므로 메모리유지
}// ptr1이 범위를 벗어나며 헤제되고 Reference Count = 0이 되면서 메모리 해제
