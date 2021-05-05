#pragma once
template<typename T> // template : 사용자가 원하는 타입을 저장할 수 있음
class singleton
{
public:
	static T* p; // 사용자가 넘겨준 T 타입의 변수 p

	singleton() {}
	~singleton() {}

	// GetInstance() : 해당 타입 내 모든 데이터를 가져옴
	static T* GetInstance()
	{
		if (!p) // p의 값이 없다면
			p = new T; // p는 T 타입의 변수
		return p; // p를 반환
	}
	//ReleaseInstance() : 해당 타입 내 모든 데이터를 제거함
	static void ReleaseInstance()
	{
		if (p) // p의 값이 있다면
			delete p; // p를 제거
		p = nullptr; // p는 nullptr
	}
};
template <typename T>
T* singleton<T>::p = nullptr; // 템플릿 초기화