/*
* ä�� ������ Ŭ������ ����� ���� Ŭ�������� ����Ʈ �����̳ʿ��� ���� �����Ѵ�.
* ������ �޽��� ������ �ϰ� �Ǹ� ������ Ŭ�������� �ڽ��� ������ ��ϵ� ���
* �����鿡�� �޽����� �����Ѵ�.
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

//Mediator �������̽�
class Colleague; //���� ����
class Mediator
{
public:
	virtual void AppendUser(Colleague* colleague) = 0;
	virtual void RemoveUser(Colleague* colleague) = 0;
	virtual void sendMessage(const TCHAR* message, Colleague* sender) = 0;
};

//Colleague �������̽�
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

//User ��� Ŭ����
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

//ChatMediator ��� Ŭ����
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

	User mUser1(&mChatMediator, L"ȫ�浿");
	User mUser2(&mChatMediator, L"���̽�");
	User mUser3(&mChatMediator, L"������");

	mChatMediator.AppendUser(&mUser1);
	mChatMediator.AppendUser(&mUser2);
	mChatMediator.AppendUser(&mUser3);

	mUser1.SendMessages(L"�ȳ��ϼ��� ȫ�浿�Դϴ�.");
}