#pragma once //防止头文件重复包含
#include<iostream>
#include "worker.h"
#include"manager.h"
#include"employee.h"
#include"boss.h"
#include<fstream>
#define filename "empfile.txt"
using namespace std;

class WorkerManager
{
public:
	WorkerManager();

	void Show_Menu();
	void ExitSystem();
	
	int m_EmpNum;
	Worker** m_EmpArray;
	void Add_Emp(); 
	void save();

	bool m_FileIsEmpty;

	int get_EmpNum();

	void init_Emp();
	void show_Emp();

	void Del_Emp();
	void Mod_Emp();
	void Find_Emp();
	int IsExist(int id);
	void Sort_Emp();
	void Clean_File();
	~WorkerManager();
};