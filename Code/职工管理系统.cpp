#include "workermanager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;



int main()
{
	
	//��̬����
	/*Worker* worker = new Employee(1, "����", 1);
	worker->showInfo();
	delete worker;
	
	worker = new Manager(2, "����", 2);
	worker->showInfo();
	delete worker;

	worker = new Boss(3, "����", 3);
	worker->showInfo();
	delete worker;*/


	/*Employee* employee = new Employee(1, "����", 1);
	employee->showInfo();
	delete employee;

	Manager* manager = new Manager(2, "����", 2);
	manager->showInfo();
	delete manager;

	Boss* boss = new Boss(3, "����", 3);
	boss->showInfo();
	delete boss;*/


	WorkerManager wm;
	int choice;
	while (true)
	{
		wm.Show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> choice; 
		switch (choice)
		{
		case 0:
			wm.ExitSystem();
			break;
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}


	system("pause");
	return 0;
}