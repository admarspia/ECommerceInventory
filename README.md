# E-Commerce Inventory Management System  
**Data Structures & Algorithms – C++ Project**

---

## 1. Project Overview

This project is a **console-based E-Commerce Inventory Management System** implemented in **C++**, focusing on the practical application of **Data Structures and Algorithms (DSA)**.

The system manages products, stock levels, categories, and order history efficiently using in-memory data structures, without relying on any external database. This design choice ensures the project remains academically focused on DSA concepts.

---

## 2. Objectives

- Apply core data structures to a real-world problem
- Implement efficient searching, insertion, and traversal algorithms
- Understand how multiple data structures interact in a system
- Design a modular and maintainable C++ project

---

## 3. Features

- Product database management
- Efficient product search by **ID** and **Name**
- Stock level tracking and availability checks
- Category-based filtering and sorting
- Order history management
- Menu-driven console interface

---

## 4. Data Structures Used

### 4.1 Binary Search Tree (BST)

- Stores products ordered by **Product ID**
- Supports:
  - Insertion
  - Deletion
  - In-order traversal for sorted output

**Time Complexity:**
- Average case: `O(log n)`
- Worst case: `O(n)`

---

### 4.2 Hash Table

- Maps **product names** to **product IDs**
- Enables fast lookup by name

**Time Complexity:**
- Average case: `O(1)`

---

### 4.3 Vector (`std::vector`)

- Stores order history
- Used to collect and display all products

---

## 5. Project Structure
---

```
ECommerceInventory/
│
├── include/
│ ├── Product.h
│ ├── BST.h
│ ├── HashTable.h
│ ├── Inventory.h
│ └── Order.h
│
├── src/
│ ├── BST.cpp
│ ├── HashTable.cpp
│ ├── Inventory.cpp
│ ├── Order.cpp
│ └── main.cpp
│
├── Makefile
└── README.md
```

## 6. Core Components

### Product
A plain data structure containing:
- Product ID
- Name
- Category
- Price
- Stock quantity

---

### Inventory
Acts as the central controller:
- Manages the BST and Hash Table
- Handles all product-related operations

---

### Order
- Records purchase details
- Updates product stock levels
- Maintains order history

---

## 7. System Workflow (High-Level)

1. User selects an operation from the menu
2. The Inventory module processes the request
3. The appropriate data structure is used:
   - BST for ordered operations
   - Hash Table for fast name-based search
4. Results are displayed to the user

---

## 8. Compilation and Execution

### Requirements

- C++17 or later
- `g++` compiler
- `make` utility

---

### Build the Project

``` bash
make

```

## Run the Program 
```
./inventory
```

## Clean Build Files

```
make clean
```
