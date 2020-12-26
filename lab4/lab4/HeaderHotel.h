#include <C:\Users\user\Desktop\hotel_\Hotel\map.h>
#include <list>
#include <vector>
#include <string>

using namespace std;

//гость
class HotelGuest
{
private:
	string firstname;
	string lastname;
public:
	HotelGuest(string& f, string& l) :firstname(f), lastname(l) {}
	friend bool operator==(HotelGuest& guest1, HotelGuest& guest2);
	string GetFN() { return firstname; }
	string GetLN() { return lastname; }
};


//заселение
class HotelSession
{
private:
	int keyroom;			// номер
	int guestID;			// гость
	string dateIn;			// заезд  dd-mm-yyyy
	int days;				// количество суток проживани€
	float tariff;			// тариф
public:
	HotelSession() {};
	HotelSession(int key, int guid, string date, int days, float trf);

	float Payment() { return days * tariff; }
	int GetKeyRoom() { return keyroom; }
	int GetGuestID() { return guestID; }
	string DateIn() { return dateIn; }
	int Days() { return days; }
	friend ostream& operator<< (ostream& os, HotelSession& hs);
	friend istream& operator>> (istream& is, HotelSession& hs);
};


//гостиничный номер
class HotelRoom
{
protected:
	bool buzy;						 // зан€тость
	int numbeds;						 // число мест в номере
	int numguest;						 // число заселенных гостей
	string dateIn;					 // заезд  dd-mm-yyyy
	int days;							 // число дней проживани€
	float tariff;						 // стоимость суток 
public:
	HotelRoom(int, float);

	bool isBuzy() { return buzy; }
	int  NumBeds() { return numbeds; }
	int  numGuests() { return numguest; }
	float Tariff() { return tariff; }

	virtual string info();
	virtual string infotype() = 0;

	virtual string getSData();
	virtual void putSData(istream&);

	virtual int takePlace() = 0;		 // зан€ть место
	virtual int outGuest() = 0;			 // освободить номер
	int freePlaces();

	friend ostream& operator<< (ostream& os, HotelRoom* hr);
	friend istream& operator>> (istream& is, HotelRoom* hr);
};


//люкс
class RoomLux : public HotelRoom
{
private:int numrooms;				 // число комнат
public:
	RoomLux(int _beds, int _nr, float trf);

	virtual string infotype();
	virtual string info(); 

	virtual int takePlace();		 // зан€ть место
	virtual int outGuest();			 // освободить номер

};


// ласс  ќдноместный Ќомер
class RoomSingle : public HotelRoom

{
public:
	RoomSingle(float);

	virtual string infotype();

	virtual int takePlace();		// зан€ть место
	virtual int outGuest();			// освободить номер
};

// ласс ћногоместный номер
class RoomMultiBed : public HotelRoom
{
private:
	bool* buzybeds;
public:
	RoomMultiBed(int, float);

	virtual string infotype();
	virtual string info();

	virtual int takePlace();		// зан€ть место
	virtual int outGuest();			// освободить номер

	virtual string getSData();
	virtual void putSData(istream&);
};


//ћенеджер гостиницы
class HotelManager
{
private:
	mymap::map <int, HotelRoom*> rooms;
	mymap::map <int, HotelGuest*> guests;
	//—писок активных заселений
	list <HotelSession*> activeSession;
public:
	HotelSession* EnterGuestToRoom(int keyroom, string& fname, string& lname, string date, int days); // заселение гост€
	void OutGuest(int);			 // выезд гост€

	int GetGuestID(string&, string&);

	// операции с номерами
	void AddNewRoom(HotelRoom* hr);
	void RemoveRoom(int key);
	void ListRooms();
	void GetActiveGuestsInfo();

	int GetFreeRooms();
	int GetFreePlaces();
	int GetCapacity();
	int SaveData(ofstream&);	 //сохранение данных в файл
	int LoadData(ifstream&);	 // загрузка данных из файла
	void RoomInfo(int key);

	HotelRoom* GetRoom(int key);
};
