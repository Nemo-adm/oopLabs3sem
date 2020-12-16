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
	cout<< "1. �������� ����� �����"<< endl;
	cout<< "2. �������� ����� �����"<< endl;
	cout<< "3. ��������� ������"<< endl;
	cout<< "4. ��������� ����� � ���������"<< endl;
	cout<< "5. ���������� �� ������"<< endl;
	cout<< "6. �������� ����������� �����"<< endl;
	cout<< "7. ������� ����������� �����"<< endl;
	cout<< "8. ������ �������"<< endl;
	cout<< "9. �������� ����������� �����" << endl;
	cout<< "0. ������� ���������"<< endl;
}

// 1. �������� ����� �����
void EnterNewGuest(HotelManager* hotel)
{
	int key;
	int ng;
	string fname, lname;
	string datein;
	int days;
	cout << "����� ��� ���������: "; 
	getNum(key);
	HotelRoom* hr = hotel->GetRoom(key);
	if (hr == NULL || hr->isBuzy() == 1) { cout << "������ ���������." << endl;  return; }
	cout << "����� ������(�� 1 �� " << hr->freePlaces() << "):"; 
	if (getNum(ng) < 0 || ng < 1 || ng > hr->freePlaces())
	{
		cout << "������ ����� ������ �� ����� ������." << endl; return;
	}
	HotelSession* hs;
	for (int i = 0; i < ng; i++)
	{
		cout << "���: "; getNum(fname);
		cout << "�������: "; getNum(lname);
		cout << "���� ���������: "; getNum(datein);
		cout << "����� ����������: "; getNum(days);
		hs = hotel->EnterGuestToRoom(key, fname, lname, datein, days);
		if (hs == NULL) { cout << "������ ���������." << endl;  break; }
		else
		{
			cout << "����� ������. ����� ������ ����������: " << hs->Payment() << endl;
		}
	}
	//���� ���� �� ������ ��� �������, ���� ��� ����� �����
	if (hr->infotype() == "����") hr->takePlace();
}

// 2. �������� ����� �����
void ExitGuest(HotelManager* hotel)
{
	string fname, lname;
	int guid; // ����� �����
	cout << "���� �����: "; getNum(guid);
	hotel->OutGuest(guid);
}

// 3. ��������� ������
void ShowFreeRoom(HotelManager* hotel)
{
	cout << "������ �� ��������� �������:" << hotel->GetFreeRooms() << endl;
}

// 4.
void ShowFreePlaces(HotelManager* hotel)
{
	cout << "������ �� ��������� ������: " << hotel->GetFreePlaces() << endl;
}

// 6. �������� ����������� �����
void AddHotelRoom(HotelManager* hotel)
{
	cout << "1. ����" << endl;
	cout << "2. �����������" << endl;
	cout << "3. ������������" << endl;
	int nr, nb;
	float tariff;
	int key;
	getNum(key);
	if (key == 1) // ����
	{
		cout << "����� ������: ";
		if (getNum(nr) < 0 || nr < 1) { cout << "������.";	return; }
		cout << "�����  �������� (1 ��� 2): ";
		if (getNum(nb) < 0 || nb < 1 || nb > 2) { cout << "������.";  return; }
		cout << "�����(���.): ";
		if (getNum(tariff) < 0 || tariff < 0) { cout << "������.";	return; }

		HotelRoom* hr = new RoomLux(nb, nr, tariff);
		hotel->AddNewRoom(hr);
	}
	else
		if (key == 2) // �����������
		{
			cout << "�����(���.):";
			if (getNum(tariff) < 0 || tariff < 0) { cout << "������.";	return; }

			HotelRoom* hr = new RoomSingle(tariff);
			hotel->AddNewRoom(hr);
		}
		else
			if (key == 3) // ������������
			{

				cout << "�����  �������� (�� 1): ";
				if (getNum(nb) < 0 || nb < 1) { cout << "������.";  return; }
				cout << "�����(���.):";
				if (getNum(tariff) < 0 || tariff < 0) { cout << "������.";	return; }

				HotelRoom* hr = new RoomMultiBed(nb, tariff);
				hotel->AddNewRoom(hr);
			}
}

// 7. ������� ����������� �����
void RemoveHotelRoom(HotelManager *hotel)
{
	int key;
	cout << "������� �� ������� �����: ";
	if (getNum(key) < 0) { cout << "������."; return; }
	hotel->RemoveRoom(key);
}

// 9. �������� ����������� �����
void DisplayHotelRoom(HotelManager *hotel)
{
	int key;
	cout << "�������� �����: " ;
	if (getNum(key) < 0 || key < 0) { cout << "������."; return; }
	hotel->RoomInfo(key);
}

void Statistics(HotelManager *hotel)
{
	cout <<"������ �� ����������: " << endl;
	hotel->GetActiveGuestsInfo();
	cout << endl;
	//����� ��������� ���� � ������ ����� ����
	double stat = (double)hotel->GetFreePlaces()/hotel->GetCapacity();
	cout << "��������� ���������: " <<  100. * (1-stat) << '%' << endl;
}

int main()
{
setlocale(LC_ALL,"Russian");
HotelManager *hman = new HotelManager;
string fname="hotel.db";
ofstream os;
ifstream is;

cout <<"��������� ���������"<< endl;

is.open(fname);  // ��������� ����
	
if( ! is.is_open() ) { cout << "���� �� ��������� �� ������." << endl; return -1; }

hman->LoadData(is);
is.close();

bool bQuit = false;
int key;
do
{
	ShowMenu();
	if (getNum(key) < 0 || key < 0 || key > 9)
	{
		cout << "������������ ����." << endl;
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

} while (!bQuit); // ���� ��� ������� �����

os.open(fname);

if( ! os.is_open() ) 
{
  cout << "���� ��� ���������� �� ��������� �� ������." << endl; 
 
}
else
{
	hman->SaveData(os);
	os.close();
}
delete hman;
return 0;
}
