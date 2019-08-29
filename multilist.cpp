/*
使用multilist存储学生选课信息
这是自研题目，没有太多测试用例
*/
#include <iostream>
#include <string>
using namespace std;
typedef struct information
{
	int row, column;
	struct information *row_ptr, *column_ptr;
}informationType;
typedef struct student
{
	string name_student, id_student;
	int age;
	informationType *row_ptr;
}studentType;
typedef struct course
{
	string name_course, id_course;
	informationType *column_ptr;
}courseType;
typedef struct multilist
{
	studentType *students;
	courseType *courses;
	int student_num, course_num;
}multilistType;


void searchCourse(multilistType *ML)
{
	cout << "Which course do you wnat search?\n";
	string name;
	cin >> name;
	informationType *infor = NULL;
	for (int i = 0; i < ML->course_num; ++i)
	{
		if (name == ML->courses[i].name_course)
		{
			infor = ML->courses[i].column_ptr;
			break;
		}
	}
	if (!infor)
	{
		cout << "No such student!";
	}
	else
	{
		int i = 1;
		while (infor)
		{
			studentType stu = ML->students[infor->column];
			cout << "NO." << i << endl;
			cout << "Name: " << stu.name_student << endl;
			cout << "ID:   " << stu.id_student << endl;
			cout << "Age:  " << stu.age << endl << endl << endl;
			infor = infor->column_ptr;
			i++;
		}
	}
	return;
}
void searchStudent(multilistType *ML)
{
	cout << "Which student do you wnat search?\n";
	string name;
	cin >> name;
	informationType *infor = NULL;
	for (int i = 0; i < ML->student_num; ++i)
	{
		if (name == ML->students[i].name_student)
		{
			infor = ML->students[i].row_ptr;
			break;
		}
	}
	if (!infor)
	{
		cout << "No such course!";
	}
	else
	{
		int i = 1;
		while (infor)
		{
			courseType cor = ML->courses[infor->row];
			cout << "NO." << i << endl;
			cout << "Name: " << cor.name_course << endl;
			cout << "ID:   " << cor.id_course << endl << endl << endl;
			infor = infor->row_ptr;
			i++;
		}
	}
	return;
}

int isContinue()
{
	char yes = getchar();
	while (yes != 'n' && yes != 'N' && yes != 'y' && yes != 'Y')
	{
		yes = getchar();
	}
	if (yes == 'n' || yes == 'N')
		return 0;
	if (yes == 'y' || yes == 'Y')
		return 1;
}
void query(multilistType *ML)
{
	cout << "Do you want to search?(y/n)\n";
	if (!isContinue())
		return;

	//cout << "What do you want to search?(s/c)\n";
	char tmp = getchar();
	while (tmp != 's' && tmp != 'S' && tmp != 'c' && tmp != 'C')
	{
		cout << "What do you want to search?(s/c)\n";
		tmp = getchar();
	}
	if (tmp == 'C' || tmp == 'c')
	{
		searchCourse(ML);
	}
	else
	{
		searchStudent(ML);
	}
	query(ML);
	return;
}
void selectCourse(multilistType* ML, int studentCur)
{
	cout << "Selected Course(input name of course):  ";
	string selected_course;
	cin >> selected_course;
	int j = 0;
	for (; j < ML->course_num && selected_course != ML->courses[j].name_course; j++);
	if (j >= ML->course_num)
	{
		cout << "Error! No such course.\n";
	}
	else
	{
		informationType *newNode = new informationType;
		newNode->row_ptr = ML->students[studentCur].row_ptr;
		newNode->column_ptr = ML->courses[j].column_ptr;
		ML->students[studentCur].row_ptr = newNode;
		ML->courses[j].column_ptr = newNode;
		newNode->row = j;
		newNode->column = studentCur;
	}


	cout << "Any courses?(y/n):  ";
	if (isContinue())
		selectCourse(ML, studentCur);
	return;
}
void getInformation(multilistType *ML)
{
	cout << "Please input the information of the " << ML->course_num << " courses:\n";
	//拿到课程信息
	for (int i = 0; i < ML->course_num; ++i)
	{
		ML->courses[i].column_ptr = NULL;
		cout << "NO." << i + 1 << ":\n";
		cout << "COURSE NAME:  ";
		cin >> ML->courses[i].name_course;
		cout << "COURSE ID:  ";
		cin >> ML->courses[i].id_course;
	}


	cout << "Please input the information of the " << ML->student_num << " students:\n";
	//拿到学生信息
	for (int i = 0; i < ML->student_num; ++i)
	{
		ML->students[i].row_ptr = NULL;
		cout << "NO." << i + 1 << ":\n";
		cout << "Student Name: ";
		cin >> ML->students[i].name_student;
		cout << "Student ID:  ";
		cin >> ML->students[i].id_student;
		cout << "Student Age:  ";
		cin >> ML->students[i].age;
		selectCourse(ML, i);//让学生选择课程
	}
	return;
}

multilistType* createMultilist(int student_num, int course_num)
{
	multilistType* ML = new multilistType;
	ML->course_num = course_num;
	ML->student_num = student_num;
	ML->courses = new courseType[course_num];
	ML->students = new studentType[student_num];
	return ML;
}
int main()
{
	int student_num, course_num;//NO. of students and courses
	cout << "Please enter the number of students and courses:\n";
	cout << "Students:  ";
	cin >> student_num;
	cout << "Courses:   ";
	cin >> course_num;
	multilistType *Multilist = createMultilist(student_num, course_num);
	getInformation(Multilist);
	query(Multilist);
	return 0;
}