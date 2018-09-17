#include "Functions.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
using namespace std;
int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "russian");
	string location;
	cout << "������� ���� �� �����(������� ��������, ��� �������������� ������ � ���� ������� �����\n ��� ����������� ��� ��������������\n���� � �������� ���� ������\n����� ��������� ������� �� ����� ������)" << endl;
	getline(cin, location);
	fstream fstr(location, ios::in | ios::binary);
	if (!fstr) {
		cout << "�������� ���� �� �����" << endl;
		system("pause");
		return 0;
	}
	int size = fstr.seekg(0, ios::end).tellg();
	fstr.seekg(0);
	byte * message = new byte[size + 1];
	fstr.read((char*)message, size);
	message[size] = 0;	

	byte out[64];
	hash512(message, out);
	cout << "Hash" << endl;
	for (int i = 0; i < 64; i++)
	{
		std::cout << std::hex << (int)out[i];
	}
	cout << endl;
	delete[] message;

	
	system("pause");

	return 0;
}