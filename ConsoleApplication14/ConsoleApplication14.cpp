#include "pch.h"
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include <Windows.h>
using namespace std;

struct book
{
	string author;
	string name;
	int year;
	int count;
};

typedef bool(*compare)(book b1, book b2);

book create_book();
void show_books(vector<book> books);
void write_in_file(vector<book> books);
void read_file(vector<book>& books);
void sort(vector<book>& books);
void sort_by(vector<book>& books, compare comp);
bool compare_by_author(book b1, book b2);
bool compare_by_year(book b1, book b2);
bool remove(vector<book>& books, int number);

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<book> books;
	read_file(books);

	int oper;

	do
	{
		system("cls");
		cout << "\tБиблиотека" << endl;
		cout << endl;

		cout << "0.Выход" << endl;
		cout << "1.Добавить книгу" << endl;
		cout << "2.Удалить книгу" << endl;
		cout << "3.Вывести все книги" << endl;
		cout << "4.Сортировка" << endl;

		cin >> oper;

		switch (oper)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			system("cls");
			book b = create_book();
			books.push_back(b);
			write_in_file(books);
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");

			int number;
			cout << "Введите номер удаляемой книги: ";
			cin >> number;

			bool res = remove(books, number);
			if (res)
			{
				cout << "Книга успешна удалена" << endl << endl;
				write_in_file(books);
				show_books(books);
			}
			else
				cout << "Нет такой книги" << endl;

			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			show_books(books);
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			sort(books);
			show_books(books);
			system("pause");
			break;
		}
		default:
			system("cls");
			cout << "Неверный пункт меню" << endl;
			system("pause");
			break;
		}
	} while (oper != 0);
}

book create_book()
{
	book b;

	cout << "Автор: ";
	cin.ignore();
	getline(cin, b.author);

	cout << "Название: ";
	getline(cin, b.name);

	cout << "Год издания: ";
	cin >> b.year;

	cout << "Кол-во книг: ";
	cin >> b.count;

	return b;
}

void show_books(vector<book> books)
{
	for (int i = 0; i < books.size(); i++)
	{
		cout << "Книга №" << (i + 1) << endl;
		cout << "Автор: " << books[i].author << endl;
		cout << "Название: " << books[i].name << endl;
		cout << "Год: " << books[i].year << endl;
		cout << "Кол-во: " << books[i].count << endl << endl;
	}
}

void write_in_file(vector<book> books)
{
	ofstream file("file.dat", ios::binary);

	for (int i = 0; i < books.size(); i++)
	{
		file.write((char*)&books[i], sizeof(book));
	}

	file.close();
}

void read_file(vector<book>& books)
{
	ifstream file("file.dat", ios::binary);
	if (file.is_open())
	{
		while (!file.eof())
		{
			book* b = new book();
			if (file.read((char*)b, sizeof(book)))
			{
				books.push_back(*b);
			}
		}

		file.close();
	}
}

void sort(vector<book>& books)
{
	cout << "1.По автору" << endl;
	cout << "2.По году" << endl;

	int oper;
	cin >> oper;

	switch (oper)
	{
	case 1:
		sort_by(books, compare_by_author);
		break;
	case 2:
		sort_by(books, compare_by_year);
		break;
	default:
		break;
	}
}

void sort_by(vector<book>& books, compare comp)
{
	book tmp;

	for (int i = 0; i < books.size() - 1; ++i)
	{
		for (int j = 0; j < books.size() - 1; ++j)
		{
			if (comp(books[j], books[j + 1]))
			{
				tmp = books[j + 1];
				books[j + 1] = books[j];
				books[j] = tmp;
			}
		}
	}
}

bool compare_by_author(book b1, book b2)
{
	return b1.author > b2.author;
}

bool compare_by_year(book b1, book b2)
{
	return b1.year > b2.year;
}

bool remove(vector<book>& books, int number)
{
	if (number < 1 || number > books.size())
		return false;

	books.erase(books.begin() + number - 1);

	return true;
}
