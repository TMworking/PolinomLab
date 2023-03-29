#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;
template <typename T>
struct Triple
{
	T x, y, z;
	Triple(T _x = T(), T _y = T(), T _z = T()) : x(_x), y(_y), z(_z) {};
};
template <typename T>
bool operator <(Triple<T> left, Triple<T> right)
{
	if (left.x != right.x) return left.x < right.x;
	if (left.y != right.y) return left.y < right.y;
	if (left.z != right.z) return left.z < right.z;
	return false;
}
template <typename T>
bool operator ==(Triple<T> left, Triple<T> right)
{
	if (left.x == right.x && left.y == right.y && left.z == right.z) return true;
	return false;
}
template <typename T>
bool operator >(Triple<T> left, Triple<T> right)
{
	return (right < left);
}
template <typename T>
Triple<T> operator+(Triple<T> left, Triple<T> right)
{
	return Triple<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}
template <typename T>
Triple<T> operator-(Triple<T> left, Triple<T> right)
{
	return Triple<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

struct Monom
{
	float coef;
	int xyz; //x^3 y^2 z^1 -> 321;
	Monom* next;
	Monom(float _coef, int _xyz, Monom* _m = nullptr) : coef(_coef), xyz(_xyz), next(_m) {};
};
istream& operator >>(istream& cin, Monom& m)
{
	string tmp;
	char cha;
	int i = 1;
	
	cin >> tmp;
	m.coef = 0;
	int x = 0, y = 0, z = 0;
	int st = 0;
	int prevst = 0;
	bool ch = false;
	string t = "";

	for (int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i] == '^')
		{
			t = "";
			continue;
		}

		if (tmp[i] == 'x')
		{
			ch = true;
			prevst = st;
			st = 1;
		}

		if (tmp[i] == 'y')
		{
			ch = true;
			prevst = st;
			st = 2;
		}

		if (tmp[i] == 'z')
		{
			ch = true;
			prevst = st;
			st = 3;
		}

		if (!ch)
		{
			t += tmp[i];
		}
		else
		{
			if (prevst == 0)
			{
				if (t.size() > 0) { m.coef = stoi(t); }
			}
			/*if (prevst > 0)
			{
				m.xyz += (stoi(t) + 10) * pow(100, prevst - 1);
			}*/
			if (prevst == 1) { x = stoi(t); }
			if (prevst == 2) { y = stoi(t); }
			t = "";
			ch = false;
		}
	}
	if (t.size() > 0)
	{
		if (st == 0)
		{
			m.coef = stof(t);
		}
		if (st > 0)
		{
			z = stoi(t);
			//m.xyz += (stoi(t) + 10) * pow(10, st + 1);
		}
	}
	m.xyz = z + 10 + (y + 10) * 100 + (x + 10) * 10000;
	t = "";
	ch = false;
	return cin;
}

class Polynomial
{
private:
	Monom* start;
	Monom* last;
public:
	Polynomial()
	{
		start = new Monom(0, 0);
		start->next = start;
		last = start;
	}

	Monom* GetStart()
	{
		return start;
	}

	Monom* GetLast()
	{
		return last;
	}

	Polynomial(const Polynomial& p) : Polynomial()
	{
		Monom* b = p.start->next;
		while (b != p.start)
		{
			Push(b);
			b = b->next;
		}
	}

	void Push(Monom* m)
	{
		if (m->xyz > 202020 || m->xyz < 0) throw exception();
		if (m->coef != 0)
		{
			Monom* c = new Monom(m->coef, m->xyz, start);
			last->next = c;
			last = last->next;
		}
	}

	void Insert(Monom* _m) {
		Monom* m = start;
		if (_m->coef == 0) throw exception();
		if (_m->xyz > 202020 || _m->xyz < 0) throw exception();
		if (_m->coef != 0)
		{

			while (m->next != start)
			{
				if (m->next->xyz == _m->xyz)
				{
					m->next->coef += _m->coef;
					return;
				}
				else if (m->next->xyz > _m->xyz)
				{
					Monom* tmp = new Monom(_m->coef, _m->xyz, m->next);
					m->next = tmp;
					return;
				}
				m = m->next;
			}
			Push(_m);
		}
	}
	// 202020   1) /10000   2) %10000 / 100 3) %100
	friend ostream& operator <<(ostream& cout, Polynomial pol) {
		Monom* b = pol.start->next;
		while (b != pol.start)
		{
			if ((b != pol.start) && (b->coef < 0)) { cout << " - "; }
			if (b->coef != 0) { cout << abs(b->coef) << "x^" << b->xyz / 10000 - 10 << ' ' << "y^" << (b->xyz % 10000) / 100 - 10 << ' ' << "z^" << (b->xyz % 100) - 10; }
			b = b->next;
			if ((b != pol.start) && (b->coef > 0)) { cout << " + "; }
		}
		//cout << '$';

		return cout;
	}

	friend istream& operator >> (istream& cin, Polynomial& pol)
	{
		string str;
		cin >> str;
		string t;
		pol.Clear();
		t += str[0];
		for (int i = 1; i < str.size(); i++)
		{
			if ((str[i] == ' ') || (str[i] == '+') || ((str[i] == '-') && str[i-1] != '^'))
			{
				if (t.size() > 0)
				{
					istringstream ss(t);
					Monom m(0, 0);
					ss >> m;
					pol.Insert(&m);
				}
				t = "";
				/*if (str[i] == '-')
				{
					t += str[i];
				}*/
			}
			else
			{
				t += str[i];
			}
		}
		if (t.size() > 0) {
			istringstream ss(t);
			Monom m(0, 0);
			ss >> m;
			pol.Insert(&m);
		}
		t = "";
		return cin;
	}

	Polynomial operator =(const Polynomial& right)
	{
		if (start == right.start) return *this;
		Clear();
		Monom* second = right.start->next;
		while (second != right.start)
		{
			Push(second);
			second = second->next;
		}
		return *this;
	}


	friend Polynomial operator +(const Polynomial& left, const Polynomial& right)
	{
		Polynomial result;
		Monom* first = left.start->next;
		Monom* second = right.start->next;
		while (first != left.start || second != right.start)
		{
			if (first == left.start && second != right.start)
			{
				result.Push(second);
				second = second->next;
			}
			if (second == right.start && first != left.start)
			{
				result.Push(first);
				first = first->next;
			}
			if (first->xyz < second->xyz && first != left.start && second != right.start)
			{
				result.Push(first);
				first = first->next;
			}

			if (first->xyz > second->xyz && first != left.start && second != right.start)
			{
				result.Push(second);
				second = second->next;
			}
			if (first->xyz == second->xyz && first != left.start && second != right.start)
			{
				Monom* tmp = new Monom(0, 0);
				tmp->coef = first->coef + second->coef;
				tmp->xyz = second->xyz;
				result.Push(tmp);
				first = first->next;
				second = second->next;
			}
		}
		return result;
	}

	friend Polynomial operator -(const Polynomial& left, const Polynomial& right)
	{
		Polynomial result;
		Monom* first = left.start->next;
		Monom* second = right.start->next;
		while (first != left.start || second != right.start)
		{
			if (first == left.start && second != right.start)
			{
				Monom* tmp = new Monom(0, 0);
				tmp->coef =  -1 * second->coef;
				tmp->xyz = second->xyz;
				result.Push(tmp);
				second = second->next;
			}
			if (second == right.start && first != left.start)
			{
				result.Push(first);
				first = first->next;
			}
			if (first->xyz < second->xyz && first != left.start && second != right.start)
			{
				result.Push(first);
				first = first->next;
			}

			if (first->xyz > second->xyz && first != left.start && second != right.start)
			{
				Monom* tmp = new Monom(0, 0);
				tmp->coef = -1 * second->coef;
				tmp->xyz = second->xyz;
				result.Push(tmp);
				result.Push(second);
				second = second->next;
			}
			if (first->xyz == second->xyz && first != left.start && second != right.start)
			{
				Monom* tmp = new Monom(0, 0);
				tmp->coef = first->coef - second->coef;
				tmp->xyz = first->xyz;
				result.Push(tmp);
				first = first->next;
				second = second->next;
			}
		}

		return result;
	}

	friend Polynomial operator *(double a, const Polynomial& right)
	{
		Polynomial result;
		Monom* first = right.start->next;
		while (first != right.start)
		{
			Monom* tmp = new Monom(0, 0);
			tmp->coef = first->coef * a;
			tmp->xyz = first->xyz;
			result.Push(tmp);
			first = first->next;
		}

		return result;
	}

	friend Polynomial operator *(const Polynomial& left, double a)
	{
		Polynomial result;
		Monom* first = left.start->next;
		while (first != left.start)
		{
			Monom* tmp = new Monom(0, 0);
			tmp->coef = first->coef * a;
			tmp->xyz = first->xyz;
			result.Push(tmp);
			first = first->next;
		}

		return result;
	}

	friend Polynomial operator *(const Polynomial& left, const Polynomial& right)
	{
		Polynomial result;
		Monom* first = left.start->next;
		Monom* second = right.start->next;
		while (first != left.start)
		{
			while (second != right.start)
			{
				int rxyz = first->xyz + second->xyz;
				if (rxyz < 0 || rxyz > 404040) { throw exception(); }
				Monom* tmp = new Monom(0, 0);
				tmp->coef = first->coef * second->coef;
				tmp->xyz = first->xyz + second->xyz - 101010;
				result.Insert(tmp);
				second = second->next;
			}
			first = first->next;
			second = second->next;
		}

		return result;
	};


	float Calculate(Triple<float> tochka)
	{
		float result = 0;
		Monom* first = start->next;
		while (first != start)
		{
			result += pow(tochka.x, first->xyz / 10000 - 10) * pow(tochka.y, (first->xyz % 10000) / 100 - 10) * pow(tochka.z, (first->xyz % 100) - 10) * first->coef;
			first = first->next;
		}
		return result;
	}


	void Clear()
	{
		Monom* b = start->next;
		Monom* tmp;
		while (b->next != start)
		{
			tmp = b->next;
			delete b;
			b = tmp;
		}
		last = start;
		start->next = start;
	}

	~Polynomial() {
		Clear();
		delete start;
	}
};