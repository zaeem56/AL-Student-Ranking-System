#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> 
#include <cmath> 
#include <cctype> 
using namespace std;

class Student {
public:
    string name;
    string stream;
    int classNo;
    int marks[3]; 
    int totalMarks;
    int classRank;
    int schoolRank;
    double zScore;

    Student(string n, string s, int c, int m1, int m2, int m3) {
        name = n;
        stream = s;
        classNo = c;
        marks[0] = m1;
        marks[1] = m2;
        marks[2] = m3;
        totalMarks = m1 + m2 + m3;
    }
};


double calculateMean(const vector<Student>& students) {
    double sum = 0;
    for (const auto& student : students) {
        sum += student.totalMarks;
    }
    return sum / students.size();
}


double calculateStandardDeviation(const vector<Student>& students, double mean) {
    double variance = 0;
    for (const auto& student : students) {
        variance += pow(student.totalMarks - mean, 2);
    }
    variance /= students.size();
    return sqrt(variance);
}


void calculateZScores(vector<Student>& students) {
    double mean = calculateMean(students);
    double stddev = calculateStandardDeviation(students, mean);

    for (auto& student : students) {
        student.zScore = (student.totalMarks - mean) / stddev;
    }
}


void calculateRanks(vector<Student>& students) {
    
    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.totalMarks > b.totalMarks;
    });

    for (size_t i = 0; i < students.size(); ++i) {
        students[i].schoolRank = i + 1;
    }

   
    for (int classNo = 1; classNo <= 8; ++classNo) {
        vector<Student*> classStudents;
        for (auto& student : students) {
            if (student.classNo == classNo) {
                classStudents.push_back(&student);
            }
        }

      
        sort(classStudents.begin(), classStudents.end(), [](Student* a, Student* b) {
            return a->totalMarks > b->totalMarks;
        });

        for (size_t i = 0; i < classStudents.size(); ++i) {
            classStudents[i]->classRank = i + 1;
        }
    }
}


string toLowerCase(string str) {
    for (char& c : str) {
        c = tolower(c);
    }
    return str;
}

int main() {
    vector<Student> students;

    int n;
    cout << "Enter the number of students: ";
    cin >> n;
    cout << endl;

    
    for (int i = 0; i < n; ++i) {
        string name, stream;
        int classNo, m1, m2, m3;

        cout << "Enter details for Student " << i + 1 << ":" << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Stream (Bio/Math): ";
        cin >> stream;

       
        stream = toLowerCase(stream);

       
        if (stream == "bio") {
            cout << "Class Number (1-3): ";
            cin >> classNo;
            if (classNo < 1 || classNo > 3) {
                cout << "Invalid class number for Bio stream! Please enter a number between 1 and 3." << endl;
                return 1;
            }
        } else if (stream == "math") {
            cout << "Class Number (4-8): ";
            cin >> classNo;
            if (classNo < 4 || classNo > 8) {
                cout << "Invalid class number for Math stream! Please enter a number between 4 and 8." << endl;
                return 1;
            }
        } else {
            cout << "Invalid stream! Please enter either 'Bio' or 'Math'." << endl;
            return 1;
        }

        cout << "Enter marks for the 3 subjects (out of 100 each):" << endl;
        if (stream == "bio") {
            cout << " - Biology: ";
        } else {
            cout << " - Combined Maths: ";
        }
        cin >> m1;
        cout << " - Physics: ";
        cin >> m2;
        cout << " - Chemistry: ";
        cin >> m3;
        cout << endl;

        students.emplace_back(name, stream, classNo, m1, m2, m3);
    }

   
    calculateRanks(students);

 
    calculateZScores(students);

   
    cout << setw(15) << left << "Name"
         << setw(10) << "Stream"
         << setw(10) << "Class"
         << setw(15) << "Total Marks"
         << setw(15) << "Class Rank"
         << setw(15) << "School Rank"
         << setw(10) << "Z-Score" << endl;

    cout << "----------------------------------------------------------------------------------------" << endl;
    for (const auto& student : students) {
        cout << setw(15) << left << student.name
             << setw(10) << student.stream
             << setw(10) << student.classNo
             << setw(15) << student.totalMarks
             << setw(15) << student.classRank
             << setw(15) << student.schoolRank
             << setw(10) << fixed << setprecision(2) << student.zScore
             << endl;
    }

    return 0;
}
