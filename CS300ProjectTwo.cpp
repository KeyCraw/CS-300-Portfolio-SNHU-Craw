/*
CS 300 Project Two – Course Planner
Author: Kenya Craw
Date: 12/14/2025
Description: This program allows users to load course data from a CSV file,
print all courses in alphanumeric order, and look up individual courses and their prerequisites.
The program uses a vector of Course objects and provides a simple menu-driven interface.

Runtime and Memory Analysis:

Data Structure Used: Vector<Course>

1. Loading Courses:
   - Time Complexity: O(n*m), where n = number of courses, m = average number of prerequisites per course.
     The program reads the file line by line and validates each prerequisite.
   - Memory Complexity: O(n + p), where n = number of courses, p = total number of prerequisite entries.
     Each course object stores courseNumber, title, and a vector of prerequisite strings.

2. Printing Course List:
   - Time Complexity: O(n log n) due to sorting the vector by courseNumber.
   - Memory Complexity: O(n) extra memory for the sorted copy of the course vector.

3. Searching for a Course:
   - Time Complexity: O(n*m), because in the worst case it scans all courses and for each prerequisite,
     may scan the vector again to find the course title.
   - Memory Complexity: O(1) extra memory beyond existing course data.

Pros and Cons:

Pros:
- Simple and easy-to-read implementation.
- Easy to load, sort, and display courses.
- Maintains prerequisite validation.

Cons:
- Lookup is slower than using a hash table or BST for larger datasets.
- Sorting creates an extra copy of the vector.

Recommendation:
- For this dataset, the vector implementation is sufficient and easy to maintain.
- For larger datasets or production systems, a hash table or BST would reduce lookup time.

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

// Structure to store course information
struct Course {
    string courseNumber;             // Course code (e.g., CSCI100)
    string title;                    // Course title
    vector<string> prerequisites;    // List of course numbers that are prerequisites
};

// Function to trim whitespace from a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

// Function to convert string to uppercase (for consistent search)
string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Function to load courses from a CSV file into a vector
bool loadCourses(const string& fileName, vector<Course>& courses) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return false;
    }

    courses.clear();  // Clear any existing data

    string line;
    vector<string> allCourseNumbers;

    // First pass: collect all course numbers
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        if (tokens.size() < 2) {
            cout << "Error: Invalid line format: " << line << endl;
            continue;
        }

        allCourseNumbers.push_back(tokens[0]);
    }

    file.clear();
    file.seekg(0); // Reset file pointer for second pass

    // Second pass: create Course objects and validate prerequisites
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        if (tokens.size() < 2) continue;

        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];

        for (size_t i = 2; i < tokens.size(); ++i) {
            if (!tokens[i].empty()) {
                // Validate prerequisite exists
                if (find(allCourseNumbers.begin(), allCourseNumbers.end(), tokens[i]) == allCourseNumbers.end()) {
                    cout << "Warning: Prerequisite " << tokens[i] << " does not exist for course " << course.courseNumber << endl;
                }
                course.prerequisites.push_back(tokens[i]);
            }
        }

        courses.push_back(course);
    }

    file.close();
    cout << "Courses loaded successfully!" << endl;
    return true;
}

// Function to print the full course list alphanumerically
void printCourseList(const vector<Course>& courses) {
    if (courses.empty()) {
        cout << "No courses loaded. Please load data first." << endl;
        return;
    }

    // Create a copy and sort by course number
    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(),
         [](const Course& a, const Course& b) {
             return a.courseNumber < b.courseNumber;
         });

    cout << "Course List:" << endl;
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.title << endl;
    }
}

// Function to find and print a specific course and its prerequisites
void printCourseInfo(const vector<Course>& courses, const string& inputNumber) {
    if (courses.empty()) {
        cout << "No courses loaded. Please load data first." << endl;
        return;
    }

    string searchNumber = toUpper(inputNumber);

    for (const auto& course : courses) {
        if (toUpper(course.courseNumber) == searchNumber) {
            cout << course.courseNumber << ", " << course.title << endl;
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    // Find prerequisite title
                    auto it = find_if(courses.begin(), courses.end(),
                                      [&](const Course& c) { return c.courseNumber == course.prerequisites[i]; });
                    if (it != courses.end()) {
                        cout << it->courseNumber << ", " << it->title;
                        if (i < course.prerequisites.size() - 1) cout << "; ";
                    }
                }
                cout << endl;
            } else {
                cout << "Prerequisites: None" << endl;
            }
            return;
        }
    }

    cout << "Course " << inputNumber << " not found." << endl;
}

// Main menu function
void displayMenu(vector<Course>& courses) {
    int choice;
    string input;

    do {
        cout << "\n1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit\n";
        cout << "What would you like to do? ";
        getline(cin, input);

        // Validate input is numeric
        try {
            choice = stoi(input);
        } catch (...) {
            choice = -1;
        }

        switch (choice) {
            case 1: {
                string fileName;
                cout << "Enter the CSV file name: ";
                getline(cin, fileName);
                loadCourses(fileName, courses);
                break;
            }
            case 2:
                printCourseList(courses);
                break;
            case 3:
                cout << "What course do you want to know about? ";
                getline(cin, input);
                printCourseInfo(courses, input);
                break;
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;
            default:
                cout << input << " is not a valid option." << endl;
                break;
        }

    } while (choice != 9);
}

// Main function
int main() {
    vector<Course> courses;
    cout << "Welcome to the course planner." << endl;
    displayMenu(courses);
    return 0;
}
