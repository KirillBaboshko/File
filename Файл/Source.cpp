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
	RussianMessage("\nВведите путь и название копируемого файла:\n");
	cin.getline(source, _MAX_PATH);
	if (_access(source, 00) == -1)
	{
		RussianMessage("\nУказан неверный путь или название файла:\n");
		return;
	}
	RussianMessage("\nВведите путь и название нового файла:\n");
	cin.getline(destionation, _MAX_PATH);
	if (_access(destionation, 00) == 0)
	{
		RussianMessage("\nТакого файл уже существует перезаписать его(1-Да/2-Нет)?\n");
		cin.getline(answer, 20);
		if (!strcmp(answer, "2"))
		{
			RussianMessage("\nОперация отмены\n");
			return;
		}
		if (!strcmp(answer, "1"))
		{
			RussianMessage("\nНеправильный вывод\n");
			return;
		}
		if (_access(destionation, 02) == 1)
		{
			RussianMessage("\nНет доступа к записи\n");
			return;
		}
		if (!CopyFile(source, destionation))
		{
			RussianMessage("\nОшибка при работе с файлом\n");
		}
	}
}