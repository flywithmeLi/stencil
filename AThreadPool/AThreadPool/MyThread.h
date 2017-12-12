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
	virtual~MyThread(void);//所有的父类几乎都是虚析构
public:
	//创建一些线程
	bool IsCreatThread(long min,long max);
	//销毁线程池
	void  DestoryThreadPool();
    //线程函数
	static unsigned __stdcall ThreadProc( void * );
	//投递任务
	bool PushITask(ITask * p);
public :

	list<HANDLE > m_lstHandle;
	//信号量
    HANDLE  m_hsempfore;
	bool m_bFlagQuit;
	long m_lCreatThreadnum;
	volatile long m_lRunThreadnum;   //原子锁,线程函数里处理的变量,应避免多跟线程同时处理同一个变量
	long m_lMaxThreadnum;
	Myqueue<ITask>myqueue;
};

