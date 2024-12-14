#include<iostream>
#include<vector>
using namespace std;

class Result {
    private:
        string name;                
        vector<float> grades;      
    public:
        Result( string studentName, vector<float> studentGrades ) {
            name = studentName ;
            grades = studentGrades ;
        }

        double calculateGPA() {
            double totalGrades = 0 ;
            int subjectsEnrolled = grades.size() ;  
            for ( float grade : grades ) 
                totalGrades += grade ; // As all courses have same credit hour '3' so it will be cancelled both in num and denom
            
            return totalGrades / subjectsEnrolled; 
        }

        void displayResult() {
            cout << "Student Name: " << name << endl;
            cout << "GPA: " << calculateGPA() << endl;
        }
} ;

int main() {
    vector<Result> students;
    students.push_back( Result( "Ali", {3.66, 3.33, 4.0, 3.0, 2.66} ) ) ;   
    students.push_back( Result( "Hiba", {3.33, 3.0, 3.66, 3.0} ) ) ;
    students.push_back( Result( "Asma", {4.0, 3.66, 2.66} ) ) ;
    students.push_back( Result( "Zain", {2.66, 2.33, 4.0} ) ) ;
    students.push_back( Result( "Faisal", {3.33, 3.66, 4.0, 3.0, 3.33} ) ) ;

    for ( Result s : students ) {
        s.displayResult();
        cout << "------------------------" << endl;
    }

    return 0;
}