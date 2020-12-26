#include <C:\Users\user\Desktop\hotel_\Hotel\map.h>
#include <list>
#include <vector>
#include <string>

using namespace std;

//�����
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


//���������
class HotelSession
{
private:
	int keyroom;			// �����
	int guestID;			// �����
	string dateIn;			// �����  dd-mm-yyyy
	int days;				// ���������� ����� ����������
	float tariff;			// �����
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


//����������� �����
class HotelRoom
{
protected:
	bool buzy;						 // ���������
	int numbeds;						 // ����� ���� � ������
	int numguest;						 // ����� ���������� ������
	string dateIn;					 // �����  dd-mm-yyyy
	int days;							 // ����� ���� ����������
	float tariff;						 // ��������� ����� 
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

	virtual int takePlace() = 0;		 // ������ �����
	virtual int outGuest() = 0;			 // ���������� �����
	int freePlaces();

	friend ostream& operator<< (ostream& os, HotelRoom* hr);
	friend istream& operator>> (istream& is, HotelRoom* hr);
};


//����
class RoomLux : public HotelRoom
{
private:int numrooms;				 // ����� ������
public:
	RoomLux(int _beds, int _nr, float trf);

	virtual string infotype();
	virtual string info(); 

	virtual int takePlace();		 // ������ �����
	virtual int outGuest();			 // ���������� �����

};


//�����  ����������� �����
class RoomSingle : public HotelRoom

{
public:
	RoomSingle(float);

	virtual string infotype();

	virtual int takePlace();		// ������ �����
	virtual int outGuest();			// ���������� �����
};

//����� ������������ �����
class RoomMultiBed : public HotelRoom
{
private:
	bool* buzybeds;
public:
	RoomMultiBed(int, float);

	virtual string infotype();
	virtual string info();

	virtual int takePlace();		// ������ �����
	virtual int outGuest();			// ���������� �����

	virtual string getSData();
	virtual void putSData(istream&);
};


//�������� ���������
class HotelManager
{
private:
	mymap::map <int, HotelRoom*> rooms;
	mymap::map <int, HotelGuest*> guests;
	//������ �������� ���������
	list <HotelSession*> activeSession;
public:
	HotelSession* EnterGuestToRoom(int keyroom, string& fname, string& lname, string date, int days); // ��������� �����
	void OutGuest(int);			 // ����� �����

	int GetGuestID(string&, string&);

	// �������� � ��������
	void AddNewRoom(HotelRoom* hr);
	void RemoveRoom(int key);
	void ListRooms();
	void GetActiveGuestsInfo();

	int GetFreeRooms();
	int GetFreePlaces();
	int GetCapacity();
	int SaveData(ofstream&);	 //���������� ������ � ����
	int LoadData(ifstream&);	 // �������� ������ �� �����
	void RoomInfo(int key);

	HotelRoom* GetRoom(int key);
};
