#include"workermanager.h"


WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
	
}
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			delete this->m_EmpArray[i];
			this->m_EmpArray[i] = NULL;
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
void WorkerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()
{
	cout << "������Ҫ��ӵ�ְ������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = this->m_EmpNum + addNum;
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int j = 0; j < addNum; j++)
		{
			int id;
			string name;
			int did;
			cout << "������� "<<j + 1 << " ����ְ���ı�ţ�" << endl;
			cin >> id;
			cout << "������� "<<j + 1 << " ����ְ����������" << endl;
			cin >> name;
			cout << "������� "<<j + 1 << " ����ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> did;
			Worker* worker = NULL;
			switch (did)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			newSpace[this->m_EmpNum + j] = worker;
		}
		delete[]this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		cout << "�ɹ������ " << addNum << " ����ְ����" << endl;
		this->m_FileIsEmpty = false;
		this->save();
	}
	else
		cout << "���������Ա����С�ڵ���0��" << endl;
	system("pause");
	system("cls");

}

void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(filename, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << " "
			<< endl;
	}
	ofs.close();
	cout << "д���ļ��ɹ���" << endl;
}

int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(filename, ios::in);
	int id;
	int dId;
	int index = 0;
	string name;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
			worker = new Employee(id, name, dId);
		else if(dId ==2 )
			worker = new Manager(id, name, dId);
		else
			worker = new Boss(id, name, dId);
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
	
}

void WorkerManager::show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
		
	}
	system("pause");
	system("cls");
}
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�";
	}
	else
	{
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
		}
		else
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ����" << endl;
	}
	system("pause");
	system("cls");
}


int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "�ļ������ڻ�Ϊ�գ�" << endl;
	else
	{
		cout << "������ҪҪ�޸ĵ�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newid = 0;
			string newname = "";
			int newdid = 0;
			cout << "���ҵ�idΪ " << id << " ��ְ�����������µ�ְ���ţ�" << endl;
			cin >> newid;
			cout << "�������µ�������" << endl;
			cin >> newname;
			cout << "�������µĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> newdid;
			Worker* worker = NULL;
			switch (newdid)
			{
			case 1:
				worker = new Employee(newid, newname, newdid);
				break;
			case 2:
				worker = new Manager(newid, newname, newdid);
				break;
			case 3:
				worker = new Boss(newid, newname, newdid);
				break;
			default:
				break;
			}
			this->m_EmpArray[ret] = worker;
			cout << "ְ����Ϣ�޸ĳɹ���" << endl;
			this->save();
		}
		else
			cout << "���޴��ˣ�" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cin >> id;
			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "���޴��ˣ�" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "������Ҫ���ҵ�ְ����������" << endl;
			cin >> name;
			bool flag = false;  //���ҵ��ı�־
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ�,ְ�����Ϊ��"
						<< m_EmpArray[i]->m_Id
						<< " �ŵ���Ϣ���£�" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ķ�ʽ��" << endl;
		cout << "1������" << endl;
		cout << "2������" << endl;
		int select;
		cin >> select;
		
		for (int i = 0; i < m_EmpNum; i++)
		{
			int minormax = i;
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[minormax]->m_Id > this->m_EmpArray[j]->m_Id)
						minormax = j;
				}
					
				else
					if (this->m_EmpArray[minormax]->m_Id < this->m_EmpArray[j]->m_Id)
						minormax = j;
			}
			if (i != minormax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minormax];
				this->m_EmpArray[minormax] = temp;

			}
		}
		cout << "����ɹ��������Ľ��Ϊ��" << endl;
		this->save();
		this->show_Emp();
		


	}
}

void WorkerManager::Clean_File()
{
	cout << "ȷ��Ҫ�����" << endl;
	cout << "1��ȷ��" << endl;
	cout << "����" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(filename, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			delete[] this->m_EmpArray;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}