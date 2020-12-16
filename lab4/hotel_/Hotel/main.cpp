#include <iostream>
#include <fstream>
#include <string>
#include "hotel.h"

using namespace std;

template <class T>
int getNum(T& a)
{
	std::cin >> a;
	if (!std::cin.good()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return -1;
	}
	return 1;
};

void ShowMenu()
{
	cout << endl<<endl;
	cout<< "1. Оформить заезд гостя"<< endl;
	cout<< "2. Оформить выезд гостя"<< endl;
	cout<< "3. Свободные номера"<< endl;
	cout<< "4. Свободные места в гостинице"<< endl;
	cout<< "5. Статистика по гостям"<< endl;
	cout<< "6. Добавить гостиничный номер"<< endl;
	cout<< "7. Удалить гостиничный номер"<< endl;
	cout<< "8. Реестр номеров"<< endl;
	cout<< "9. Показать гостиничный номер" << endl;
	cout<< "0. Закрыть программу"<< endl;
}

// 1. Оформить заезд гостя
void EnterNewGuest(HotelManager* hotel)
{
	int key;
	int ng;
	string fname, lname;
	string datein;
	int days;
	cout << "Номер для заселения: "; 
	getNum(key);
	HotelRoom* hr = hotel->GetRoom(key);
	if (hr == NULL || hr->isBuzy() == 1) { cout << "Ошибка заселения." << endl;  return; }
	cout << "Число гостей(от 1 до " << hr->freePlaces() << "):"; 
	if (getNum(ng) < 0 || ng < 1 || ng > hr->freePlaces())
	{
		cout << "Ошибка ввода данных по числу гостей." << endl; return;
	}
	HotelSession* hs;
	for (int i = 0; i < ng; i++)
	{
		cout << "Имя: "; getNum(fname);
		cout << "Фамилия: "; getNum(lname);
		cout << "Дата заселения: "; getNum(datein);
		cout << "Суток проживания: "; getNum(days);
		hs = hotel->EnterGuestToRoom(key, fname, lname, datein, days);
		if (hs == NULL) { cout << "Ошибка заселения." << endl;  break; }
		else
		{
			cout << "Гость заселён. Сумма оплаты проживания: " << hs->Payment() << endl;
		}
	}
	//если Люкс то делаем его занятым, даже при одном госте
	if (hr->infotype() == "Люкс") hr->takePlace();
}

// 2. Оформить выезд гостя
void ExitGuest(HotelManager* hotel)
{
	string fname, lname;
	int guid; // номер гостя
	cout << "Ключ гостя: "; getNum(guid);
	hotel->OutGuest(guid);
}

// 3. Свободные номера
void ShowFreeRoom(HotelManager* hotel)
{
	cout << "Данные по свободным номерам:" << hotel->GetFreeRooms() << endl;
}

// 4.
void ShowFreePlaces(HotelManager* hotel)
{
	cout << "Данные по свободным местам: " << hotel->GetFreePlaces() << endl;
}

// 6. Добавить гостиничный номер
void AddHotelRoom(HotelManager* hotel)
{
	cout << "1. Люкс" << endl;
	cout << "2. Одноместный" << endl;
	cout << "3. Многоместный" << endl;
	int nr, nb;
	float tariff;
	int key;
	getNum(key);
	if (key == 1) // Люкс
	{
		cout << "Число комнат: ";
		if (getNum(nr) < 0 || nr < 1) { cout << "Ошибка.";	return; }
		cout << "Число  кроватей (1 или 2): ";
		if (getNum(nb) < 0 || nb < 1 || nb > 2) { cout << "Ошибка.";  return; }
		cout << "Тариф(руб.): ";
		if (getNum(tariff) < 0 || tariff < 0) { cout << "Ошибка.";	return; }

		HotelRoom* hr = new RoomLux(nb, nr, tariff);
		hotel->AddNewRoom(hr);
	}
	else
		if (key == 2) // Одноместный
		{
			cout << "Тариф(руб.):";
			if (getNum(tariff) < 0 || tariff < 0) { cout << "Ошибка.";	return; }

			HotelRoom* hr = new RoomSingle(tariff);
			hotel->AddNewRoom(hr);
		}
		else
			if (key == 3) // Многоместный
			{

				cout << "Число  кроватей (от 1): ";
				if (getNum(nb) < 0 || nb < 1) { cout << "Ошибка.";  return; }
				cout << "Тариф(руб.):";
				if (getNum(tariff) < 0 || tariff < 0) { cout << "Ошибка.";	return; }

				HotelRoom* hr = new RoomMultiBed(nb, tariff);
				hotel->AddNewRoom(hr);
			}
}

// 7. Удалить гостиничный номер
void RemoveHotelRoom(HotelManager *hotel)
{
	int key;
	cout << "Удалить из реестра номер: ";
	if (getNum(key) < 0) { cout << "Ошибка."; return; }
	hotel->RemoveRoom(key);
}

// 9. Показать гостиничный номер
void DisplayHotelRoom(HotelManager *hotel)
{
	int key;
	cout << "Показать номер: " ;
	if (getNum(key) < 0 || key < 0) { cout << "Ошибка."; return; }
	hotel->RoomInfo(key);
}

void Statistics(HotelManager *hotel)
{
	cout <<"Сводка по заселениям: " << endl;
	hotel->GetActiveGuestsInfo();
	cout << endl;
	//число свободных мест к общему числу мест
	double stat = (double)hotel->GetFreePlaces()/hotel->GetCapacity();
	cout << "Занятость гостиницы: " <<  100. * (1-stat) << '%' << endl;
}

int main()
{
setlocale(LC_ALL,"Russian");
HotelManager *hman = new HotelManager;
string fname="hotel.db";
ofstream os;
ifstream is;

cout <<"Программа ГОСТИНИЦА"<< endl;

is.open(fname);  // открываем файл
	
if( ! is.is_open() ) { cout << "Файл БД гостиницы не открыт." << endl; return -1; }

hman->LoadData(is);
is.close();

bool bQuit = false;
int key;
do
{
	ShowMenu();
	if (getNum(key) < 0 || key < 0 || key > 9)
	{
		cout << "Некорректный ввод." << endl;
		continue;
	}
	if (key == 1) { EnterNewGuest(hman); }
	else
	if (key == 2) { ExitGuest(hman); }
	else
	if (key == 3) { ShowFreeRoom(hman); }
	else
	if (key == 4) { ShowFreePlaces(hman); }
	else
	if (key == 5) { Statistics(hman); }
	else
	if (key == 6) { AddHotelRoom(hman); }
	else
	if (key == 7) { RemoveHotelRoom(hman); }
	else
	if (key == 8) { hman->ListRooms(); }
	else
	if (key == 9) { DisplayHotelRoom(hman); }

	if (key == 0) bQuit = true;

} while (!bQuit); // пока нет команды выход

os.open(fname);

if( ! os.is_open() ) 
{
  cout << "Файл для сохранения БД гостиницы не открыт." << endl; 
 
}
else
{
	hman->SaveData(os);
	os.close();
}
delete hman;
return 0;
}
