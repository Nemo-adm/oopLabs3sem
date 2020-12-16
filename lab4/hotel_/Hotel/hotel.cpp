#include "C:\Users\user\Desktop\hotel_\Hotel\hotel.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool operator==(HotelGuest& guest1, HotelGuest& guest2)
{
	return(guest1.GetFN() == guest2.GetFN() && guest1.GetLN() == guest2.GetLN());
}

ostream& operator<<(ostream& os,  HotelRoom* hr)
{
	return os << hr->getSData();
};

//возвращает строку с данными для сохранния в потоке
string HotelRoom::getSData()
{
	stringstream ss;
	ss << infotype() << ' ';
	ss << buzy << ' ';
	ss << numbeds << ' ';
	ss << numguest << ' ';
	ss << dateIn << ' ';		   // Заезд  dd-mm-yyyy
	ss << days << ' ';			   // число дней проживания
	ss << tariff << ' ';		   // стоимость суток
	return ss.str();
}

istream& operator>>(istream& is, HotelRoom *hr)
{
	hr->putSData(is);
	return is;
}

//получает данные из строкового потока
void HotelRoom::putSData(istream& is)
{
	is >> buzy;
	is >> numbeds;
	is >> numguest;
	is >> dateIn;				// Заезд  dd-mm-yyyy
	is >> days;				    // число дней проживания
	is >> tariff;				// стоимость суток 
}

HotelSession::HotelSession(int key, int guid, string date, int _days, float trf)
{
	keyroom = key;
	guestID = guid;
	dateIn = date;
	days = _days;
	tariff = trf;
}

HotelRoom::HotelRoom(int nb, float pr)
{
	tariff = pr; 				// стоимость суток с человека
	numbeds = nb;   			// число мест в номере
	numguest = 0;
	buzy = false;
	days = 0;
	dateIn = "00-00-0000";
}

RoomLux::RoomLux(int beds, int nr, float trf) :HotelRoom(beds, trf)
{
	numrooms = nr;
}

RoomSingle::RoomSingle(float trf) :HotelRoom(1, trf)
{

}

RoomMultiBed::RoomMultiBed(int beds, float trf) :HotelRoom(beds, trf)
{
	buzybeds = new bool[numbeds]; // массив занятости мест
	for (int i = 0; i < numbeds; i++) buzybeds[i] = false;
}

int HotelRoom::freePlaces()
{
	return (buzy) ? 0 : (numbeds - numguest);
}

ostream& operator<< (ostream& os, HotelSession& hs)
{
	os<< hs.keyroom<<' ';   // номер
	os<< hs.guestID<< ' ';   // гость
	os<< hs.dateIn<< ' '; // Заезд  dd-mm-yyyy
	os<< hs.days<< ' ';// количество суток проживания
    os<< hs.tariff<< ' '; // тариф

	return os;
}

 istream& operator>> (istream& is, HotelSession& hs)
{
	 is >> hs.keyroom ;   // номер
	 is >> hs.guestID ;   // гость
	 is >> hs.dateIn ; // Заезд  dd-mm-yyyy
	 is >> hs.days ;// количество суток проживания
	 is >> hs.tariff ; // тариф
	 return is;
 
 }





string RoomMultiBed::getSData()
{
	stringstream ss;

	ss << HotelRoom::getSData();

	for (int i = 0; i < numbeds; i++) ss << ' '<< buzybeds[i];

	return ss.str();
}

void RoomMultiBed::putSData(istream& is)
{

	HotelRoom::putSData(is);

	for (int i = 0; i < numbeds; i++) is >> buzybeds[i];

	
}



//Выселение гостя
void HotelManager::OutGuest(int guid)
{
	HotelGuest* hg;
	mymap::map <int, HotelGuest*>::iterator itg;
	itg = guests.find(guid);
	if( itg==guests.end() ) { cout << "Такого гостя нет." << endl; return; }
	hg = itg->second;

	HotelSession* hs;
	// ищем поселение гостя
	list <HotelSession*>::iterator it;
	mymap::map <int, HotelRoom*>::iterator itroom;
	int keyroom=-1;
	HotelRoom* hr=NULL;

	it = activeSession.begin();
	// ищем поселение по гостю
	while (it != activeSession.end())
	{
		hs = *it;
		if ( hs->GetGuestID() == guid )
		{	// нашли
			keyroom = hs->GetKeyRoom();
			itroom = rooms.find(keyroom);
			if ( itroom == rooms.end()) { break; }
			hr=itroom->second;
			hr->outGuest(); // выводим гостя из номера
			cout << "Гость("<< hg->GetFN() <<' '<< hg->GetLN() <<") выселен. Сумма оплаты:" << hs->Payment() <<" руб."<< endl;
			activeSession.erase(it); // удаляем из списка заселений
			break;
		}
		it++;
	}

	if(hr==NULL) cout << "Не найдено поселение гостя "<< hg->GetFN() << ' ' << hg->GetLN() << endl;
	else
	{
		if (hr->infotype() == "Люкс" && hr->numGuests() > 0 )
		{	// если люкс , то освобождаем полностью
			hr->outGuest();
			//нужно найти второго гостя Люкса и выселить
			it = activeSession.begin();
			//ищем поселение по гостю
			while (it != activeSession.end())
			{
				hs = *it;
				if ( hs->GetKeyRoom() == keyroom)
				{
					hr->outGuest(); // выводим гостя из номера
					guid = hs->GetGuestID();
					itg = guests.find(guid);
					if (itg == guests.end()) { cout << "Ошибка поиска второго гостя Люкса." << endl; break; }
					hg = itg->second;
					cout << "Второй гость(" <<hg->GetFN() <<' '<<hg->GetLN() <<  ") выселен. Сумма оплаты:" << hs->Payment() << " рублей" << endl;
					activeSession.erase(it); // удаляем из списка заселений
					break;
				}
				it++;
			}// end while
		}
	}
}

int RoomLux::outGuest()
{
	if (!buzy) return 0;
	numguest--;
	if (numguest == 0)	buzy = false;
	return numguest;
}

int RoomSingle::outGuest()
{
	buzy = false;
	numguest = 0;
	return 0; // осталось гостей
}

int RoomMultiBed::outGuest()
{
	if (numguest > 0) { numguest--; buzybeds[numguest] = false; }
	if (numguest == 0) buzy = false;
	return numguest; // осталось гостей
}

// 1.
HotelRoom* HotelManager::GetRoom(int key)
{
	mymap::map<int, HotelRoom*>::iterator it;
	HotelRoom* hr = NULL;
	it = rooms.find(key);
	if (it != rooms.end())
		hr = it->second;
	return hr;
}

HotelSession* HotelManager::EnterGuestToRoom(int keyroom, string &fname,string &lname,string date,int days)
{
	if (rooms.size() == 0) return NULL;
	mymap::map <int, HotelRoom*>::iterator it;
	it = rooms.find(keyroom);
	if( it==rooms.end() ){ cout << "Номер не существует."<< endl; return NULL;	}
	HotelRoom* hr = it->second;
	if( hr->isBuzy() ){ cout <<"Номер занят." << endl; return NULL;}
	hr->takePlace(); // занимаем место в номере
	int guid;
	guid = GetGuestID(fname, lname);
	//создаем поселение гостя
	HotelSession* hs = new HotelSession(keyroom, guid, date, days, hr->Tariff());
	//помещаем в список поселений
	activeSession.push_back(hs);
	cout << hr->info() << endl;
	return hs;
}

int RoomLux::takePlace()
{
	if (numguest < numbeds) { numguest++; }
	if (numguest == numbeds) buzy = true;
	return (buzy) ? 0 : (numbeds - numguest);
}

int RoomSingle::takePlace()
{
	buzy = true;
	numguest = 1;
	return 0; // осталось мест
}

int RoomMultiBed::takePlace()
{
	if (numguest < numbeds) { buzybeds[numguest] = true;  numguest++; }
	if (numguest == numbeds) { buzy = true; }
	return (buzy) ? 0 : (numbeds - numguest);
}

// Получить ID гостя
int HotelManager::GetGuestID(string& fname, string& lname)
{
	HotelGuest* hgnew = new HotelGuest(fname, lname);
	HotelGuest* hg;
	mymap::map< int, HotelGuest* >::iterator  it;
	it = guests.begin();

	while (it != guests.end())
	{
		hg = it->second;
		// есть такой гость - возвращаем его номер из реестра
		if (*hg == *hgnew) { delete hgnew;  return it->first; }
		it++;
	}
	// Гость новый - выдаем ему новый ID
	int maxid = 0;
	if (guests.size() > 0) { maxid = guests.rbegin()->first; }
	maxid++;
	guests[maxid] = hgnew;
	return maxid;
}

// Вывод список заселенных гостей
void HotelManager::GetActiveGuestsInfo()
{
	HotelSession* hs;
	list <HotelSession*>::iterator item;

	for (item = activeSession.begin(); item != activeSession.end(); item++)
	{

		hs = *item;

		int keyroom = hs->GetKeyRoom();
		int guid = hs->GetGuestID();
		cout << '[' << keyroom << ']' << '(' << rooms[keyroom]->infotype() << ')' << ',';
		cout <<"Гость:" << guests[guid]->GetFN() << ' ' << guests[guid]->GetLN() <<"(ключ:"<< guid <<')' << ',';
		cout << "Заезд:" << hs->DateIn() << ',' << "Суток:" << hs->Days()<< ',';
		cout << "Цена:" << hs->Payment();
		cout << endl;

	}
}



// 3.
int HotelManager::GetFreeRooms()
{
	int count = 0;
	HotelRoom *hr;
	mymap::map <int,HotelRoom*>::iterator it;
	it=rooms.begin();
	
	while( it != rooms.end() )
	{
		hr = it->second;
		if( ! hr->isBuzy() )
		{
			cout << "["<<it->first<<"]:" << hr->info()<< endl;
			count++;	
		 } 
		it++;
	}
	return count;
}

// 4.
int HotelManager::GetFreePlaces()
{
	mymap::map <int, HotelRoom*>::iterator it;
	it = rooms.begin();
	HotelRoom* hr;
	int count = 0;

	while (it != rooms.end())
	{

		hr = it->second;
		count += hr->freePlaces();
		it++;
	}
	return count;
}

// Вместимость гостиницы по местам
int HotelManager::GetCapacity()
{
    int count=0;
 	HotelRoom *hr;
	mymap::map <int,HotelRoom*>::iterator it;
	it=rooms.begin();

	while(it!= rooms.end() )
	{
		hr=it->second;
		count += hr->NumBeds();
		it++;
	}
	
 return count;
}

// 6.
void HotelManager::AddNewRoom(HotelRoom* hr )
{
	int maxnum = 0;
	if( rooms.size() > 0 )	 maxnum=rooms.rbegin()->first; // номер
	maxnum++;
	rooms[maxnum]=hr;
}

// 7.
void HotelManager::RemoveRoom(int key)
{
	mymap::map<int, HotelRoom*>::iterator it;
	it = rooms.find(key);
	if (it == rooms.end())
		cout << "Такого номера в гостинице нет." << endl;
	else
	{
		HotelSession* hs;
		list <HotelSession*>::iterator it;
		it = activeSession.begin();
		while (it != activeSession.end())
		{
			hs = *it;
			if (hs->GetKeyRoom() == key) { it = activeSession.erase(it); continue; }
			it++;
		}
		rooms.erase(key);
		cout << "Комната и все заселения в неё удалены.";
	}
}

// 8.
void HotelManager::ListRooms()
{
	HotelRoom *hr;
	mymap::map <int,HotelRoom*>::iterator it;
	it=rooms.begin();

	while(it!= rooms.end() )
	{
		hr=it->second;
		cout << '[' << it->first <<']' << hr->info() << endl;
		it++;
	}
}

string HotelRoom::info()
{
	stringstream ss;
	ss << infotype() << ',' << " Мест: " << numbeds << ',' << " Тариф: " << tariff << ',' << ((buzy) ? " Занят" : " Свободен");
	if (buzy) ss << ',' << "Гостей: " << numguest;
	return ss.str();
}

string RoomLux::info()
{
	stringstream ss;
	ss << infotype() << ',' << " Мест: " << numbeds << ',' << " Тариф: " << tariff << ',' << ((buzy) ? " Занят" : " Свободен");
	return ss.str();
}

string RoomMultiBed::info()
{
	stringstream ss;
	ss << HotelRoom::info();
	for (int i = 0; i < numbeds; i++) ss << " Место_" << i << '(' << ((buzybeds[i] == false) ? "Свободно" : "Занято") << ')';
	return ss.str();
}

string RoomLux::infotype()
{
	stringstream ss;
	ss << "Люкс";
	return ss.str();
}

string RoomSingle::infotype()
{
	stringstream ss;
	ss << "Одноместный";
	return ss.str();
}

string RoomMultiBed::infotype()
{
	stringstream ss;
	ss << "Многоместный";
	return ss.str();
}

// 9.
void HotelManager::RoomInfo(int key)
{
	mymap::map<int, HotelRoom*>::iterator it;
	it = rooms.find(key);

	if (it == rooms.end())	 cout << "Нет номера в гостинице." << endl;
	else
	{
		HotelRoom* hr = it->second;
		cout << "Гостиничный номер:" << endl;
		cout << hr->info() << endl;
	}
}

//сохранение данных в файл
int HotelManager::SaveData(ofstream &os)
{
	int error = 0;
	 os <<"Hotel***"<< endl;
	
	 
	HotelRoom *hr;
	mymap::map <int,HotelRoom*>::iterator it;


	 os << rooms.size()<< endl; //число номеров
	
	 it=rooms.begin();

	while(it != rooms.end() )
	{
		hr=it->second;
		
		os << it->first <<' ';
		
		os << hr << endl;
		it++;
	}
	// реестр гостей

	mymap::map <int, HotelGuest*>::iterator itg;
	
	os << guests.size() << endl; // число гостей

	itg = guests.begin();
	HotelGuest* hg;

	while (itg != guests.end())
	{
		hg = itg->second;

		os << itg->first << ' ';

		os << hg->GetFN() <<' '<< hg->GetLN() << endl;
		itg++;
	}

	//список заселений
	HotelSession* hs;
	list<HotelSession*>::iterator its;

	os << activeSession.size() << endl; // количество заселений

	its = activeSession.begin();

	while (its != activeSession.end())
	{
		hs = *its;
		os << *hs << endl;
		its++;
	}
	return error;
}

// загрузка данных из файла
int HotelManager::LoadData(ifstream &is)
{
	string sig;
	is >> sig; 
	if( sig != "Hotel***" ) return false;
	
	rooms.clear(); // чистим контейнер
	int count = 0;
	is >> count;
	int key;
	string type;
	
	HotelRoom *hr;
	
	cout <<"Номеров в БД: " << count << endl;
	int error=0;
	for(int i=0; i < count && error==0; i++)
	{
		is >> key;
		is >> type;
		if(type=="Люкс")
		{
			hr=new RoomLux(0,0,0);
			is >> hr;
		}
		else
		if(type=="Одноместный")
		{
			hr=new RoomSingle(0);
			is >> hr;
		}
		else 
		if(type=="Многоместный")
		{
			hr=new RoomMultiBed(0,0);
			is >> hr;
		}
		else {	error=1; continue; }	
		
		rooms[key]=hr;
	}

	if( error == 0 )
	{
		// гости
		HotelGuest* hg;
		string fname, lname;
		count = 0;
		is >> count;
		for (int i = 0; i < count && error == 0; i++)
		{
			is >> key;
			is >> fname >> lname;
			hg = new HotelGuest(fname,lname);
			guests[key] = hg;
		}
		// заселение
		HotelSession *hs; 
		count = 0;
		is >> count;
		for (int i = 0; i < count && error == 0; i++)
		{
			hs = new HotelSession();
			is >> *hs;
			activeSession.push_back(hs);
		}
		cout << "Загружено номеров:"<< rooms.size()<< endl;
		cout << "Загружено заселений:" << activeSession.size() << endl;
	}
	return error;
}

