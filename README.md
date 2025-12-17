# Welcome to my CS 300 portfolio!

Welcome to my CS 300 portfolio! This repository contains my coursework and projects from **CS 300: Analysis and Design**, showcasing my work with data structures, algorithms, and software design principles.

## About This Course
CS 300 focuses on software analysis, design principles, and object-oriented programming. Throughout the course, I completed assignments, labs, and projects that strengthened my understanding of efficient data handling, algorithm design, and writing maintainable, scalable software.

## Repository Contents
- **Assignments:** Exercises covering data structures, algorithm analysis, UML diagrams, and software evaluation.  
- **Lab Activities:** Hands-on labs reinforcing object-oriented design, software architecture, and algorithm implementation.  
- **Projects:** Major projects demonstrating practical application of analysis and design concepts, including run-time and memory analysis, pseudocode development, and fully working implementations.

## Project One – Run-Time and Memory Analysis

### Vector Data Structure
- **Loading Courses:** O(n) time; O(n) memory.  
- **Searching Courses:** O(n) time; O(1) extra memory.  
- Vectors are simple and easy to implement but slower for large datasets.

### Hash Table Data Structure
- **Insertion/Search:** O(1) average time; O(n) memory.  
- Fast lookup compared to vectors, with additional memory overhead for buckets and linked nodes.  
- Worst-case search can degrade to O(n) if many collisions occur.

### Binary Search Tree (BST)
- **Insertion/Search:** O(log n) average time for a balanced tree; O(n) worst case.  
- **Printing All Courses:** O(n) time via in-order traversal.  
- BSTs maintain sorted order and efficient searches if balanced.  
- Memory usage: O(n).

### Summary
Each structure has trade-offs. Vectors are simple but slow for searching, hash tables provide fast lookups, and BSTs allow sorted traversal with efficient search. Selecting the right structure depends on program requirements and dataset size.

## Project Two – Course Planner

### Overview
Project Two is a C++ program that:
- Loads course data from a CSV file
- Prints all courses in alphanumeric order
- Allows users to search for individual courses and view prerequisites
- Uses a menu-driven interface

### Data Structure
- **Vector<Course>** storing course number, title, and prerequisites.  
- Chosen for simplicity, easy iteration, and suitability for the dataset size.

### Run-Time and Memory
- **Loading Courses:** O(n·m) time; O(n + p) memory (n = courses, m = avg prerequisites, p = total prerequisites).  
- **Printing Course List:** O(n log n) time for sorting; O(n) extra memory for sorted copy.  
- **Searching Courses:** O(n·m) worst-case time; O(1) extra memory.  

### Design Trade-Offs
- Easy to maintain and read.  
- Slower lookups than hash tables or BSTs for larger datasets.  
- Suitable for current dataset; larger datasets would benefit from hash tables or BSTs.

### Learning Outcomes
- Reinforced the importance of choosing appropriate data structures.  
- Strengthened understanding of sorting, searching, input validation, and writing maintainable C++ code.

## How to Use
Browse through the folders to view source code, UML diagrams, pseudocode, and project documentation. Each file contains comments to clarify logic and design decisions.

## Conclusion
This portfolio reflects my growth in data structures, algorithms, and software design through CS 300. Included artifacts demonstrate my ability to analyze performance, design efficient solutions, and implement maintainable code ready for future scalability.

