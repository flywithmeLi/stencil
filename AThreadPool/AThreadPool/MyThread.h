#pragma once
#include <process.h>
#include <windows.h>
#include<list>

#include"MyQueue.h"
using namespace std;

class ITask
{
public :
	ITask()
	{}
	virtual~ITask()
	{}
public:
	virtual  void process()=0;

};
//template <typename T>
class MyThread
{
public:
	MyThread(void);
	virtual~MyThread(void);//���еĸ��༸������������
public:
	//����һЩ�߳�
	bool IsCreatThread(long min,long max);
	//�����̳߳�
	void  DestoryThreadPool();
    //�̺߳���
	static unsigned __stdcall ThreadProc( void * );
	//Ͷ������
	bool PushITask(ITask * p);
public :

	list<HANDLE > m_lstHandle;
	//�ź���
    HANDLE  m_hsempfore;
	bool m_bFlagQuit;
	long m_lCreatThreadnum;
	volatile long m_lRunThreadnum;   //ԭ����,�̺߳����ﴦ��ı���,Ӧ�������߳�ͬʱ����ͬһ������
	long m_lMaxThreadnum;
	Myqueue<ITask>myqueue;
};

