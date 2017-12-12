#pragma once
#include <process.h>
#include <iostream>
//#include "MyThread.h"
using namespace std;
class ITask;
#define ARR_LEN 100
class CLock
{
public:
	CLock()
	{
		InitializeCriticalSection(&m_cs);
	}
	~CLock()
	{
		DeleteCriticalSection(&m_cs);
	}
public:
	void  lock()
	{
		EnterCriticalSection(&m_cs);
	}
	void unlock()
	{
		LeaveCriticalSection(&m_cs);
	}
private:
	CRITICAL_SECTION m_cs;

};
template <typename TT>
class Myqueue
{
public:
	Myqueue()
	{
		for (int i = 0; i < ARR_LEN; i++)
			arr[i] = NULL;
		arr_push = 0;//尾
		arr_pop = 0;//头
		arr_size = 0;
		m_hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);//手动,push
		m_hEvent2=CreateEvent(NULL,FALSE,FALSE,NULL);//pop,自动
	}

	~Myqueue()
	{

	}
	void push(TT * a)
	{
		while(IsFull())
		{ 
			cout<<"队满1"<<endl;
			WaitForSingleObject(m_hEvent,1);
		}
		//if(IsFull())
  //     WaitForSingleObject(m_hEvent2,INFINITE);

		locking.lock();
		while(IsFull())
		{
			cout<<"队满2"<<endl;
			WaitForSingleObject(m_hEvent,10);
		}
				//if(IsFull())
    //   WaitForSingleObject(m_hEvent2,INFINITE);
		arr[arr_push] = a;
		arr_push =  (arr_push+1)%ARR_LEN;
		arr_size +=1;
		//if(arr_size-1==0)
		//	SetEvent(m_hEvent);
		locking.lock();
	}

	ITask * pop()
	{
				if(IsEmpty())
		{
			cout<<"队空1"<<endl;
			return NULL;
		}
		locking2.lock();
		if(IsEmpty())
		{
			cout<<"队空2"<<endl;
			return NULL;
		}
		TT * aa = arr[arr_pop];
		 arr[arr_pop] = NULL;                                 
		arr_pop = (arr_pop+1)%ARR_LEN;
		arr_size-=1;
		//if(arr_size+1==ARR_LEN)
		//	SetEvent(m_hEvent2);
		locking2.unlock();
		return aa;
	}

	bool IsEmpty()
	{ 
		if(arr_size == 0)	return true;
		return false;
	}
	bool IsFull()
	{
		if (arr_size == ARR_LEN)	return true;

		return false;
	}
public:
	TT * arr[ARR_LEN];
	int arr_push;
	int arr_pop;
	int arr_size;
	CLock  locking;
	CLock  locking2;
	HANDLE  m_hEvent;
	HANDLE m_hEvent2;
};

