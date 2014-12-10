#ifndef __LKDLIST_H_INCLUDED__
#define __LKDLIST_H_INCLUDED__

#include<iostream>
#include<sstream>
#include<string>

template<class T>
class LkdList
{
private:
	T value;
	LkdList<T>* next;
	LkdList<T>* itself;
	bool isCirculic;
public:
	LkdList():value(0),next(NULL){itself = this;isCirculic=false;}
	LkdList(T val){value = val;itself = this;isCirculic=false;}
	LkdList(T* vals,int N);
	~LkdList()
	{
		std::cout<<"deleted:"<<this->value<<std::endl;
	}

	T getValue(){return value;}
	void setValue(T v){value=v;}
	LkdList<T>* getNext(){return next;}
	void setNext(LkdList<T>* n){next = n;}
	LkdList<T>* getItself(){return itself;}

	void initN(int N);
	void initCir(int N,int cirN);
	void makeCir(int cirN);
	int checkCyclic(LkdList<T> **cirpoint=NULL);
	void insert(LkdList<T>* alist);
	static void insertAtN(LkdList<T>* &thelist,LkdList<T>* alist,int N);
	static LkdList<T>* flipR(LkdList<T>* original,LkdList<T>* tail=NULL);
	static LkdList<T>* flipI(LkdList<T>* original);
	static void clear(LkdList<T>* l);

	// see http://www.parashift.com/c++-faq-lite/templates.html 35.16
	friend std::ostream& operator<< (std::ostream& os, const LkdList<T>& thelist)
	{
		std::stringstream ss;
		LkdList<T> *p = thelist.itself;
		LkdList<T> *circlepoint;
		if(thelist.itself->checkCyclic(&circlepoint))
		{
			bool loopin = false;
			do
			{
				if (p==circlepoint)
				{
				loopin=true;
					ss<<"**"<<p->value;
				}
				else
					ss<<"->"<<p->value;
				p=p->next;
			}while(p!=circlepoint || !loopin);
		}
		else
			while(p!=NULL)
			{
				ss<<"->"<<p->value;
				p=p->next;
			}
		os <<ss.str();
		return os;
	}
};

//template<class T>


#endif
