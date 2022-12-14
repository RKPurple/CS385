/*******************************************************************************
 * Filename: student.cpp 
 * Author  :  Rohan Kallur
 * Version : 1.0 
 * Date    :  9/16/22
 * Description: 
 * Pledge  :  I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Student {
public:
    // Constructor that uses an initializer list
    Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} { }

    string full_name() const {
        return first_ + " " + last_;
    }

    float gpa() const {
        cout << fixed;
        cout << setprecision(2);
        return gpa_;
    }

    int id() const {
        return id_;
    }

    void print_info () const {
        cout << full_name() << ", GPA: " << gpa() << ", ID: " << id() << endl;
    }

private:
    string first_, last_;
    float gpa_;
    int id_;
};

/**
 * Takes a vector of Student objects, and returns a new vector
 * with all Students whose GPA is < 1.0
 */
vector<Student> find_failing_students(const vector<Student> &students) {
    vector<Student> failing_students;
    for (Student x : students) {
        if (x.gpa() < 1.0) {
            failing_students.push_back(x);
        }
    }
    return failing_students;
}

/**
 * Takes a vector of Student objects and prints them to a screen.
 */
void print_students(const vector<Student> &students) {
    for (Student x : students) {
        x.print_info();
    }
}

/** 
*  Allows the user to enter information for multiple students, then 
*  find those students whose GPA is below 1.0 and prints them to the 
*  screen. */ 
int main() { 
    string first_name, last_name; 
    float gpa; 
    int id; 
    char repeat; 
    vector<Student> students; 
 
    do { 
        cout << "Enter student's first name: "; 
        cin >> first_name; 
        cout << "Enter student's last name: "; 
        cin >> last_name; 
        gpa = -1; 
        while (gpa < 0 || gpa > 4) { 
            cout << "Enter student's GPA (0.0-4.0): "; 
            cin >> gpa; 
            
        } 
        cout << "Enter student's ID: "; 
        cin >> id; 
        students.push_back(Student(first_name, last_name, gpa, id)); 
        cout << "Add another student to database (Y/N)? "; 
        cin >> repeat; 
    } while (repeat == 'Y' || repeat == 'y'); 
 
    cout << endl << "All students:" << endl; 
    print_students(students); 
    vector<Student> failing = find_failing_students(students);
    if (failing.size() == 0) {
        cout << endl << "Failing students: None";
        return 0;
    }
    cout << endl << "Failing students:" << endl; 
        print_students(failing);

 
    return 0; 
}