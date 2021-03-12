#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
template <typename T>

class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List;
	};
	Element* Head;
	Element* Tail;
	int size;
public:
	int get_size()const
	{
		return size;
	}

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "IConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "IDestructor:\t" << this << endl;
#endif // DEBUG

		}
		//				Operators:
		T& operator*()
		{
			return Temp->Data;
		}
		Iterator& operator++()
		{
			//Prefix increment:
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			//Postfix increment:
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return !(*this == other);
		}
	};

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	Iterator rbegin()
	{
		return Tail;
	}
	Iterator rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

	}
	List(int size) :List()
	{
		while (size--)push_back(0);
	}
	List(const initializer_list<int>& il) :List()
	{
		//(il.begin())
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~List()
	{
		while (Tail)pop_back();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG

	}

	//				Operators:
	int& operator[](int index)
	{
		if (index >= size || index < 0)throw exception("Error: Out of range");//Выход за пределы
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)
				Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)
				Temp = Temp->pPrev;
		}
		return Temp->Data;
	}
	
	
	//				Adding elements:
	void push_front(T Data)
	{
		//Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//New->pNext = Head;
			//Head->pPrev = New;
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(T Data)
	{
		if (empty())
			Head = Tail = new Element(Data);
		else
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Index, T Data)
	{
		if (empty() || Index == 0)
		{
			push_front(Data);
			return;
		}
		/*if (Index == 0)
		{
			push_front(Data);
			return;
		}*/
		if (Index > size)
		{
			return;
		}
		if (Index == size)
		{
			push_back(Data);
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)
				Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)
				Temp = Temp->pPrev;
		}
		//Сейчас Temp указывает на добавляемый элемент
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

	//				Removing elements
	void pop_front()
	{
		if (empty())return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}

	void pop_back()
	{
		if (this->empty())return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}

	void erase(int index)
	{
		if (index==0)
		{
			pop_front();
		}
		if (index>size)
		{
			return;
		}
		int i = 0;
		Element* Del = Head;
		while (i<index)
		{
			Del = Del->pNext;
			i++;
		}
		Element* PrevDel = Del->pPrev;
		Element* AfterDel = Del->pNext;
		if (PrevDel!=0&&size!=1)
		{
			PrevDel->pNext = AfterDel;
		}
		if (AfterDel!=0&&size!=1)
		{
			AfterDel->pPrev = PrevDel;
		}
		if (index == 1)
		{
			Head = AfterDel;
		}
		if (index==size)
		{
			Tail = PrevDel;
		}
		delete Del;
		size--;
	}

	//				Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp != nullptr; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка:\t" << size << endl;
	}
	void print_reverse()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pNext << tab << Temp << tab << Temp->Data << tab << Temp->pPrev << endl;
		cout << "Количество элементов списка:\t" << size << endl;
	}
	bool empty()const
	{
		/*if (Head == nullptr && Tail == nullptr)return true;
		else return false;*/
		return Head == nullptr && Tail == nullptr;
	}
};

#define BASE_CHECK
//#define ITERATORS_CHECK
//#define INDEX_VS_ITERATOR

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
#ifdef BASE_CHECK
	List <int> list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.print_reverse();

	int index;
	int value;
	int erase_index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите индекс значение элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.print_reverse();
	cout << "Введите индекс элемента, который хотите удалить: "; cin >> erase_index;
	list.erase(erase_index);
	list.print();
	list.print_reverse();
	



#endif // BASE_CHECK

	/*List list(n);
	for (int i = 0; i < list.get_size(); i++)
		list[i] = rand() % 100;
	for (int i = 0; i < list.get_size(); i++)
		cout << list[i] << tab;
	cout << endl;
	list.print();*/

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	//list.print();

	/*for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		*it = rand() % 100;
	}*/
	/*for (int i : list)
	{
		i = rand() % 1000;
	}*/
	for (int i : list)//range-based for
	{
		cout << i << tab;
	}
	cout << endl;
	for (List::Iterator it = list.rbegin(); it != list.rend(); --it)
		cout << *it << tab;
	cout << endl;
#endif // ITERATORS_CHECK

	//List list(n);
	//cout << "Список создан, загружаем данные...\n";
	//*for (int i = 0; i < list.get_size(); i++)
	//	list[i] = rand();*/
	//for (List::Iterator it = list.begin(); it != list.end(); it++)
	//	*it = rand();
	//cout << "Данные загружены." << endl;
	cout << "________________________________________________" << endl;
	List<char> list_2 = { 'H','E','L','L','O',' ','W','O','R','L','D'};
	
	list_2.print();


}