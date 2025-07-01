# Graph Theory and Shortest Path Algorithms

This project focuses on graph theory, graph connectivity, and algorithms for finding the shortest path and shortest circuit. It is an assignment for the Discrete Mathematics for Computer Science course at Ho Chi Minh City University of Technology (HCMUT) in the 242 semester.

## Project Overview
This project implements algorithms to:
- Find the shortest path using the **Bellman-Ford algorithm**.
- Solve the **Travelling Salesman Problem (TSP)** using the **Held-Karp** and **Ant Colony Optimization** algorithms.
- Generate random graphs represented by adjacency matrices with 5 to 25 vertices.

## File Descriptions
1. **`bellman.cpp`**
   - **`BF()`**: Calculates one step of the Bellman-Ford algorithm when called from `main.cpp`.
   - **`BF_Path()`**: Provides the shortest path from the start vertex to the goal vertex using the Bellman-Ford algorithm.

2. **`tsm.cpp`**
   - **`Travelling()`**: Solves the Travelling Salesman Problem (TSP), assuming the graph always has a Halminton cycle. It uses two algorithms:
     - **Held-Karp algorithm**: Finds the optimal solution for graphs with fewer than 20 vertices.
     - **Ant Colony Optimization**: Provides an approximate solution for graphs with more than 20 vertices.

3. **`main.cpp`**
   - Randomly generates a graph represented by an adjacency matrix with 5 to 25 vertices.
   - Calls the functions `BF()`, `BF_Path()`, and `Travelling()` and prints their results.

4. **`tsm.pdf`**
   - Explains the approach and algorithms used to solve the Travelling Salesman Problem.

## Requirements
- Language: C++.
- No external libraries are required.

## Usage
1. Clone the repository:
   git clone https://github.com/NghiaTran-Billy/Discrete-Mathematics-Assignment.git

## Author
- Name: Tran Trung Nghia (GitHub: NghiaTran-Billy)
- Student ID: 2412278
- Institution: Ho Chi Minh City University of Technology (HCMUT)
- Course: Discrete Mathematics for Computer Science, 242 semester