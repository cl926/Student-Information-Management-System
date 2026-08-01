#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
using namespace std;

class Student {
private:
	string name;
	int id;
	int score;
public:
	Student(string n = "", int i = 0, int s = 0) : name(n), id(i), score(s) {}
	void display() {
		cout << "姓名：" << name << "   " << "学号：" << id << "   " << "成绩：" << score << endl;
	}
	string getName() {
		return name;
	}
	int getID() {
		return id;
	}
	int getScore() {
		return score;
	}
	bool isName(string n) {
		return name == n;
	}
	bool isID(int i) {
		return id == i;
	}
	bool isScore(int s) {
		return score == s;
	}
	void setName(string n) {
		name = n;
	}
	void setID(int i) {
		id = i;
	}
	void setScore(int s) {
		score = s;
	}
};

class StudentManager {
	vector<Student>v;
public:
	void addStudent();
	void deleteStudent();
	void showAll();
	void modifyStudent();
	void searchStudent();
	void saveToFile();
	void loadFromFile();
};
void StudentManager::addStudent() {
	int id, score;
	string name;
	cout << "请输入学生姓名" << endl;
	cin >> name;
	cout << "请输入学生学号" << endl;
	cin >> id;
	cout << "请输入学生成绩" << endl;
	cin >> score;
	v.push_back(Student(name, id, score));
}
void showStudent(Student& s) {
	s.display();
}
void StudentManager::deleteStudent() {
	if (v.begin() == v.end()) {
		cout << "没有学生信息" << endl;
		return;
	}
	showAll();
	cout << "请输要删除的学生姓名" << endl;
	string n;
	cin >> n;
	int count = 0;
	for (vector<Student>::iterator it = v.begin();it != v.end();) {
		if ((*it).getName() == n)  it=v.erase(it);
		else it++;
	}
}
void StudentManager::showAll() {
	if (v.begin() == v.end()) {
		cout << "没有学生信息" << endl;
		return;
	}
	for_each(v.begin(), v.end(), showStudent);
}
void StudentManager::modifyStudent() {
	if (v.size() == 0) {
		cout << "没有学生信息" << endl;
		return;
	}
	showAll();
	string na, t;
	int I, s, target=0;
	cout << "请输入要修改的学生姓名" << endl;
	cin >> t;
	for (int i = 0;i < v.size();i++) {
		if (v[i].isName(t)) {
			cout << "请输入修改后的学生信息，" << endl;
			cout << "姓名:(如果无改动请按回车)";
			cin.ignore( 100,'\n');
			getline(cin, na);
			if (!na.empty()) v[i].setName(na);
			cout << "学号:(如果无改动请输入0)";
			cin >> I;
			if (I != 0)v[i].setID(I);
			cout << "成绩:(如果无改动请输入0)";
			cin >> s;
			if (s != 0) v[i].setScore(s);
			target = 1;
			break;
		}
	}
	if (target == 0) {
		cout << "没有找到该学生" << endl;
	}
}
void StudentManager::searchStudent() {
	if (v.size() == 0) {
		cout << "没有学生信息" << endl;
		return;
	}
	string n;
	int t=0;
	cout << "请输入要查询的学生姓名" << endl;
	cin.ignore(100,'\n');
	getline(cin, n);
	for (int i = 0;i < v.size();i++) {
		if (v[i].isName(n)) {
			t = 1;
			cout << "姓名：" << v[i].getName() << '\t' << "学号：" << v[i].getID() << '\t' << "成绩：" << v[i].getScore() << endl;
			
		}
	}
	if (t == 0) {
		cout << "没有该学生信息" << endl;
	}
}
void StudentManager::saveToFile() {
	ofstream outfile("student.dat", ios::out);
	if (!outfile) {
		cout << "打开文件student.dat失败";
		return;
	}
	for (int i = 0;i < v.size();i++) {
		outfile << v[i].getName() << " " << v[i].getID() << " " << v[i].getScore() << endl;
	}
	outfile.close();
	cout << "保存成功" << endl;
}
void StudentManager::loadFromFile() {
	ifstream infile("student.dat", ios::in);
	if (!infile) {
		cout << "打开文件student.dat失败" << endl;
		return;
	}
	string name;
	int id, score;
	while (infile >> name >> id >> score) {
		v.push_back(Student(name, id, score));
	}
	infile.close();
	cout << "加载成功" << endl;
}

int main() {
	StudentManager sm;
	sm.loadFromFile();
	int choice;
	do {
		cout << "1.添加学生信息" << endl;
		cout << "2.删除学生信息" << endl;
		cout << "3.修改学生信息" << endl;
		cout << "4.查询学生信息" << endl;
		cout << "5.展示学生信息" << endl;
		cout << "0.退出" << endl;
		cout << "请输入你的选项" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			sm.addStudent();
			break;
		case 2:
			sm.deleteStudent();
			break;
		case 3:
			sm.modifyStudent();
			break;
		case 4:
			sm.searchStudent();
			break;
		case 5:
			sm.showAll();
			break;
		case 0:
			sm.saveToFile();
			cout << "退出系统" << endl;
			break;
		default:
			cout << "无效的选项，请重新输入" << endl;

		}
	} while (choice != 0);
	return 0;
}
