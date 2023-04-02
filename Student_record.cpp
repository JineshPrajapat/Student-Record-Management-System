/***********************     Student record management system using file handling.       *****************************/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//--------------------------------------------class "student" starts here-------------------------
class student
{
    int rollno;
    char name[30];
    int DBMS_marks, math_marks, cprogramming_marks, python_marks, DCN_marks;
    double percentage;
    char grade;

public:
    void getdata();
    void showdata() const;                         // const -  function does not modify any member variables of the class.
    void calculate();
    int retrollno() const;
};

void student::calculate()
{
    percentage = (DBMS_marks + math_marks + cprogramming_marks + python_marks + DCN_marks) / 5;
    if (percentage >= 90)
        grade = 'A';
    else if (percentage >= 75)
        grade = 'B';
    else if (percentage >= 50)
        grade = 'C';
    else
        grade = 'F';
}

void student::getdata()
{
    cout << "\nEnter student's roll number: ";
    cin >> rollno;
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(name, 30);
    cout << "\n\nAll marks should be out of 100.";
    cout << "\n\nEnter marks in DBMS : ";
    cin >> DBMS_marks;
    cout << "Enter marks in Mathematics : ";
    cin >> math_marks;
    cout << "Enter marks in C programming ";
    cin >> cprogramming_marks;
    cout << "Enter marks in Python : ";
    cin >> python_marks;
    cout << "Enter marks in DCN : ";
    cin >> DCN_marks;
    calculate();
}

void student::showdata() const
{
    cout << "\n Roll number of student : " << rollno;
    cout << "\n Name of student : " << name;
    cout << "\n DBMS : " << DBMS_marks;
    cout << "\n Mathematics : " << math_marks;
    cout << "\n C programming : " << cprogramming_marks;
    cout << "\n Python : " << python_marks;
    cout << "\n DCN : " << DCN_marks;

    cout << "\n\n Percentage : " << percentage << " %";
    cout << "\n Grade : " << grade;
}

int student::retrollno() const
{
    return rollno;
}

//-------------------------------- Function declaration------------------------------------------

void create_student();
void display_p(int);
void display_all();
void delete_student(int);
void change_student_record(int);

//-------------------------------------- MAIN-----------------------------------------------------

int main()
{
    char ch;
    cout << setprecision(2);
    do
    {
        int num;
        system("cls");                                       // used to clear console screen
        cout << "\n\n\n MENU ";
        cout << "\n\n\t 1. Create student record";
        cout << "\n\t 2. Display all student record";
        cout << "\n\t 3. Search student record";
        cout << "\n\t 4. Delete student record";
        cout << "\n\t 5. Modify student record";
        cout << "\n\t 6. Exit";

        cout << "\n\n What is  your choice (1/2/3/4/5/6) ?\n";
        cin >> ch;

        system("cls");

        switch (ch)
        {
        case '1':
            create_student();
            break;
        case '2':
            display_all();
            break;
        case '3':
            cout << "\nEnter the roll number :";
            cin >> num;
            display_p(num);
            break;
        case '4':
            cout << "\nEnter the roll number :";
            cin >> num;
            delete_student(num);
            break;
        case '5':
            cout << "\nEnter the roll number :";
            cin >> num;
            change_student_record(num);
            break;
        case '6':
            cout << "\n Exiting, Thank you !";
            exit(0);
        }
    } while (ch != 6);
    return 0;
}

//----------------------Write student details to file--------------------------------------------
void create_student()
{
    student stud;
    ofstream oFile;
    oFile.open("Student.dat", ios::binary | ios::app);                    // ios::app - allowing new data to be appended to the existing file content instead of overwriting it.
    stud.getdata();
    oFile.write(reinterpret_cast<char*>(&stud), sizeof(student));
    oFile.close();

    cout << "\n Student record has been created ";
    cin.ignore();
    cin.get();
}

//-----------------------Read file record------------------------------------------------------
void display_all()
{
    student stud;
    ifstream iFile;
    iFile.open("Student.dat", ios::binary);
    if (!iFile)
    {
        cout << "\nFile could not be opened !! Press any key to exit.";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n DISPLAYING ALL RECORD\n\n";
    while (iFile.read(reinterpret_cast<char*> (&stud), sizeof(student)))
    {
        stud.showdata();
        cout << "\n=================================================================================\n";
    }
    iFile.close();
    cin.ignore();
    cin.get();
}

//---------------------------Read particular record on the basis of roll no.--------------------------
void display_p(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("Student.dat", ios::binary);
    if (!iFile)
    {
        cout << "File could not be opened !! Press any key to exit. ";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(student)))
    {
        if (stud.retrollno() == n)
        {
            stud.showdata();
            flag = true;
        }
    }
    iFile.close();
    if (flag == false)
    {
        cout << "\n Record does not exist. ";
    }
    cin.ignore();
    cin.get();
}

//-------------------------------Modify record for particular roll number ---------------------------
void change_student_record(int n)
{
    bool found = false;
    student stud;
    fstream f1;
    f1.open("student.dat", ios::binary | ios::in | ios::out);                // Opening the file with ios::in and ios::out modes together allows us to perform both read and write operations on the file.
    if (!f1)
    {
        cout << "File could not be opened !! Press any key to exit. ";
        cin.ignore();
        cin.get();
        return;
    }
    while (!f1.eof() && found == false)
    {
        f1.read(reinterpret_cast<char *>(&stud), sizeof(student));
        if (stud.retrollno() == n)
        {
            stud.showdata();
            cout << "\n Enter new student details :" << endl;
            stud.getdata();
            int pos = (-1) * static_cast<int>(sizeof(stud));
            f1.seekp(pos, ios::cur);
            f1.write(reinterpret_cast<char *>(&stud), sizeof(student));
            cout << "\n\n Record Updated ";
            found = true;
        }
    }
    f1.close();
    if (found == false)
        cout << "\n Record not found ";
    cin.ignore();
    cin.get();
}

//-----------------------delete record with particular roll number-----------------------------------
void delete_student(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("Student.dat", ios::binary);
    if (!iFile)
    {
        cout << "File could not be opned... Press any key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("temp.dat", ios::out);                                       // temporary file created.
    iFile.seekg(0, ios::beg);                                               // sets the read pointer to the beginning of the file.
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(student)))
    {
        if (stud.retrollno() != n)
            oFile.write(reinterpret_cast<char *>(&stud), sizeof(student));
    }
    oFile.close();
    iFile.close();
    remove("Student.dat");
    rename("temp.dat", "Student.dat");
    cout << "\n\n Record deleted... ";
    cin.ignore();
    cin.get();
}




// oFile.write: This is a member function of the ofstream class that is used to write binary data to the file. It takes two arguments - a pointer to the data to be written and the number of bytes to write.

// reinterpret_cast<char*>: This is a C++ cast operator that is used to convert a pointer of one type to a pointer of another type. Here, it is used to convert a pointer to the stud object to a pointer of type char*. This is necessary because the write function expects a pointer to a character array.

// &stud: This is the address of the stud object, which is passed as the first argument to the write function. This is the data that will be written to the binary file.

// sizeof(student): This is the number of bytes to write to the file. It is calculated using the sizeof operator, which returns the size in bytes of the student object.

// cin.get(): This does not discard any extraneous characters from the input stream buffer. Therefore, if you use cin.get() after using cin to read user input, any newline characters ('\n') left in the input buffer will be read by cin.get(). To avoid this, you can call cin.ignore() before calling cin.get().

// ios::binary: This mode specifies that the file should be opened in binary mode, which means the file is read or written in binary format rather than in text format.

// ios::in: This mode specifies that the file should be opened for reading.

// ios::out: This mode specifies that the file should be opened for writing.

// f1.eof(): This is a member function of the fstream class. This return true when the end file is reached.

// f1.seekp(pos, ios::cur):This is used to set the write position in the file to a specific position relative to the current write position.

// iFile.seekg(0, ios::beg); sets the read pointer of the input file stream to the beginning of the file, so that data can be read from the start. This is typically done before reading or writing data from a file.