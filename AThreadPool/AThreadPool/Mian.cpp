#include <iostream>
#include"MyThread.h"
class AA: public ITask
{
public:
  AA(int a,int b)
  {
	  m_a=a;
	  m_b=b;
  }
  virtual ~AA()
  {
  }
public:
  int m_a;
  int m_b;
public:
void process()
{
	cout<<m_a<<"+"<<m_b<<"="<<m_a+m_b<<endl;
}
};
class BB :public ITask
{
public :
	char a;
public :
	BB(char c)
	{
		a=c;
	}
	~BB()
	{}
public:
	void process()
{
	cout<<a<<endl;
}
};
int  main()
{

//	MyThread *mythreadpool = new MyThread;
		MyThread mythreadpool;
		mythreadpool.IsCreatThread(10,20);   
		for(int i=0;i<100;i++)
	{
		ITask *p=new AA(i,i+1);
		 mythreadpool.PushITask(p);
	}
		Sleep(10000);
		for(int a=0;a<10;a++)
		{
		ITask *p=new BB('k');
		mythreadpool.PushITask(p);
		}

	system("pause");
    return 0;
}