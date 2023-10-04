/*
* 채팅 중재자 클래스를 만들고 유저 클래스들을 리스트 컨테이너에서 통합 관리한다.
* 유저가 메시지 전송을 하게 되면 중재자 클래스에서 자신을 제외한 등록된 모든
* 유저들에게 메시지를 전송한다.
*/

#include <iostream>
#include <list>
#include <tchar.h>
using namespace std;

#if _UNICODE
typedef wstring tstring;
#else
typedef string tstring;
#endif

//Mediator 인터페이스
class Colleague; //전방 선언
class Mediator
{
public:
	virtual void AppendUser(Colleague* colleague) = 0;
	virtual void RemoveUser(Colleague* colleague) = 0;
	virtual void sendMessage(const TCHAR* message, Colleague* sender) = 0;
};

//Colleague 인터페이스
class Colleague
{
public:
	Colleague(Mediator* m, const TCHAR* name) :pMediator(m), mName(name) {}
	
public:
	virtual void SendMessages(const TCHAR* str) = 0;
	virtual void ReceiveMessages(const TCHAR* str) = 0;

protected:
	Mediator* pMediator;
	tstring mName;
};

//User 상속 클래스
class User :public Colleague
{
public:
	User(Mediator* m, const TCHAR* name) :Colleague(m, name) {}

public:
	void SendMessages(const TCHAR* str) override
	{
		wcout << mName << "send: " << str << endl;
		pMediator->sendMessage(str, this);
	}

	void ReceiveMessages(const TCHAR* str) override
	{
		wcout << mName << "recv: " << str << endl;
	}
};

//ChatMediator 상속 클래스
class ChatMediator :public Mediator
{
public:
	void AppendUser(Colleague* colleague) override
	{
		mList.push_back(colleague);
	}

	void RemoveUser(Colleague* colleague) override
	{
		mList.remove(colleague);
	}

	void sendMessage(const TCHAR* message, Colleague* sender)
	{
		for (Colleague* object : mList)
		{
			if (object != sender)
			{
				object->ReceiveMessages(message);
			}
		}
	}

private:
	list<Colleague*> mList;
};

//Main
int main()
{
	ChatMediator mChatMediator;

	User mUser1(&mChatMediator, L"홍길동");
	User mUser2(&mChatMediator, L"나이스");
	User mUser3(&mChatMediator, L"디자인");

	mChatMediator.AppendUser(&mUser1);
	mChatMediator.AppendUser(&mUser2);
	mChatMediator.AppendUser(&mUser3);

	mUser1.SendMessages(L"안녕하세요 홍길동입니다.");
}