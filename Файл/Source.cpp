#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<stdio.h>
#include<io.h>
using namespace std;
void RussianMessage(const char* str)
{
	char message[100];
	CharToOemA(str, message);
	cout << message;
}
bool CopyFile(char* source, char *destionation)
{
	const int size = 65536;
	FILE* src, * dest;
	if (!(src = fopen(source, "rb")))
	{
		return false;
	}
	int handle=_fileno(src);
	char* data=new char[size];
		if (!data)
		{
			return false;
		}
	if (!(dest= fopen(destionation, "wb")))
	{
		delete[]data;
		return false;
	}
	int realsize;
	while (!feof(src))
	{
		realsize = fread(data, sizeof(char), size, src);
		fwrite(data, sizeof(char), realsize, dest);
	}
	fclose(src);
	fclose(dest);
	return true;
}
void main()
{
	char source[_MAX_PATH];
	char destionation[_MAX_PATH];
	char answer[20];
	RussianMessage("\n������� ���� � �������� ����������� �����:\n");
	cin.getline(source, _MAX_PATH);
	if (_access(source, 00) == -1)
	{
		RussianMessage("\n������ �������� ���� ��� �������� �����:\n");
		return;
	}
	RussianMessage("\n������� ���� � �������� ������ �����:\n");
	cin.getline(destionation, _MAX_PATH);
	if (_access(destionation, 00) == 0)
	{
		RussianMessage("\n������ ���� ��� ���������� ������������ ���(1-��/2-���)?\n");
		cin.getline(answer, 20);
		if (!strcmp(answer, "2"))
		{
			RussianMessage("\n�������� ������\n");
			return;
		}
		if (!strcmp(answer, "1"))
		{
			RussianMessage("\n������������ �����\n");
			return;
		}
		if (_access(destionation, 02) == 1)
		{
			RussianMessage("\n��� ������� � ������\n");
			return;
		}
		if (!CopyFile(source, destionation))
		{
			RussianMessage("\n������ ��� ������ � ������\n");
		}
	}
}