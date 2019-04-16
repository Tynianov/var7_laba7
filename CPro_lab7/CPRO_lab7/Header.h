#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<windows.h>
#include<chrono>
#include<ctime>
#include<fstream>
#include<string>
#include <Commdlg.h>
#include<atlstr.h>
#pragma comment(lib, "Dll1.lib")


#ifdef L7_2_API
#else 
#define L7_2_API __declspec(dllimport)
#endif

struct ReadData {
	std::string text;
	std::string readTime;
	std::string fileName;

	ReadData(std::string t, std::string rt, std::string name) : 
		text(t), readTime(rt), fileName(name)
	{
	}
};

L7_2_API ReadData * readFromFile(OPENFILENAME &);
L7_2_API void display(ReadData *, HWND *);
