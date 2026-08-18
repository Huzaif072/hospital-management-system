# Hospital Management System

A graphical hospital patient management application built with C++ and SFML 2. It provides a full-screen GUI for managing patient records through a linked-list-based data structure.

---

## Features

- Loading screen on startup
- Login screen with credential validation
- Main menu with keyboard and mouse navigation
- Add a new patient record
- Edit an existing patient record
- Search for a patient by serial number
- Delete a patient record
- Display all patient records
- Doubly linked list used as the core data structure

---

## Requirements

| Dependency | Version |
|---|---|
| C++ compiler | C++17 or later |
| SFML | 2.x |

### macOS

Install SFML via Homebrew:

```bash
brew install sfml@2
```

---

## Building

### macOS

```bash
make
```

This compiles all source files from the `coding/` directory and links against the system-installed SFML@2 libraries.

To clean build artifacts:

```bash
make clean
```

---

## Running

```bash
./HospitalManagement
```

The application launches in fullscreen mode. If the requested video mode is unavailable, SFML will automatically switch to a valid mode.

---

## Login Credentials

The following accounts are available by default:

| Username | Password   |
|----------|------------|
| admin    | admin1234  |
| huzaif   | huzaif1234 |

---

## Project Structure

```
.
├── Makefile               # Build configuration for macOS
├── README.md
├── coding/                # All C++ source and header files
│   ├── main.cpp
│   ├── Menu.cpp / Menu.h
│   ├── PatientList.cpp / PatientList.h
│   ├── LoadingScreen.cpp / LoadingScreen.h
│   ├── LoginScreen.cpp / LoginScreen.h
│   ├── AddRecord.cpp / AddRecord.h
│   ├── EditRecord.cpp / EditRecord.h
│   ├── SearchRecord.cpp / SearchRecord.h
│   ├── DeleteRecord.cpp / DeleteRecord.h
│   └── DisplayRecord.cpp / DisplayRecord.h
├── font/                  # Font files (Poppins, Arial, Montserrat, Verdana)
└── img/                   # Background images used in the GUI
```

---

## Data Structure

Patient records are stored in a **doubly linked list**. Each node holds:

- Serial number
- Patient name and father's name
- Date of birth
- Ward
- Patient ID
- Number of days admitted

This structure allows efficient sequential traversal in both directions, supporting display, search, edit, and delete operations.

---

## Controls

**Menu navigation:**
- Arrow keys (Up / Down) to move between options
- Enter to select
- Mouse hover and click also work

**Login screen:**
- Click a text field to select it
- Type to enter credentials
- Press Enter to move from username to password field, then Enter again to log in
- Or click the Login button

---

## Platform

This project was originally developed on Windows and has been ported to macOS. The build system uses the Homebrew-installed SFML@2 dylibs. Windows `.dll` files and the Windows-targeted Makefile have been removed.

---

## Authors

Developed as a Data Structures semester project.
