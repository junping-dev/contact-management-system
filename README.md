
# Personal Contact Management System

This is a C++ Qt-based project for managing personal contact information, developed as a course assignment for *Advanced Programming Language II*. The system supports management of different categories of contacts, including classmates, colleagues, friends, and relatives, with features for database integration and birthday reminders.

## 🧠 Features

* **Object-Oriented Design**: Core contact types (`Classmate`, `Colleague`, `Friend`, `Relative`) inherit from a base class `Contact` with polymorphic methods like `show()` and `saveToDB()`.
* **Database Integration**: Uses MySQL for persistent storage, with dynamic loading and saving via `QSqlDatabase`.
* **Comprehensive Operations**:

  * Add, delete, update contacts
  * Search contacts by name
  * Sort contacts by name or birthday
  * Find contacts with upcoming birthdays in 5 days
  * Count the number of birthdays in a given month
  * Export birthday wishes to a text file
* **Extensible Architecture**: Template functions in `ContactManager` allow generalized operations across different contact categories with minimal code duplication.

## 💻 Technologies Used

* **Language**: C++
* **Framework**: Qt 5 (for GUI and database operations)
* **Database**: MySQL
* **Build System**: qmake

## 📁 Project Structure

* `main.cpp`: Entry point with Qt application setup
* `Contact.h/.cpp`: Base class for all contact types
* `Classmate/Colleague/Friend/Relative.cpp`: Derived classes with extra info fields
* `ContactManager.cpp`: Core logic handling CRUD and search/sort
* `connection.cpp`: Database connection setup
* `Date.cpp`: Utility for handling date comparison, validation, and weekday computation
* `mainwindow.cpp`: The implementation of GUI operations

## 🗂️ Data Model

Each contact includes:

* `Name`, `Phone`, `Email`
* `Birthday` (with leap year and weekday support)
* A custom field depending on contact type:

  * **Classmate**: School name
  * **Colleague**: Enterprise
  * **Friend**: Meeting place
  * **Relative**: Relationship title

## 🛠️ How to Run

1. **Dependencies**:

   * Qt 5 or 6 with Qt SQL module
   * MySQL running locally (`localhost:3306`), with a database named `addressbook`

2. **Build**:

   ```bash
   qmake
   make
   ./project
   ```

3. **MySQL Setup**: Create tables named `classmates`, `colleagues`, `friends`, `relatives` with schema:

   ```sql
   CREATE TABLE classmates (
     id INT PRIMARY KEY AUTO_INCREMENT,
     name VARCHAR(50),
     year INT, mon INT, day INT,
     tel VARCHAR(20), email VARCHAR(50),
     extra VARCHAR(100)
   );
   -- Repeat for other tables with same fields
   ```

## 📌 Highlights

* Clean separation of GUI, logic, and data layers
* Template-based data loading to reduce redundancy
* Use of `virtual` functions for polymorphic DB save/update
* Automatically generates birthday greetings as `.txt` files

## 📜 License

This project is developed for educational purposes. No formal license is attached.
