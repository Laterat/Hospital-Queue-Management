# Hospital Queue Management System

A C++ console application for managing a small hospital patient queue. The system supports role-based login for administrators, receptionists, and doctors, and uses basic data structures to manage staff accounts and waiting patients.

## Features

- Role-based authentication for Admin, Receptionist, and Doctor users
- Default admin account created at startup
- Admin tools to add staff, remove staff, list users, reset credentials, and update profile details
- Receptionist tools to register patients, search patients, view waiting time, display the queue, and update profile details
- Doctor tools to view the next patient, consult the next patient, display the queue, and update profile details
- Emergency patients are prioritized ahead of normal patients
- Input validation for names, ages, and Ethiopian phone numbers
- Auto-generated patient IDs, usernames, and passwords

## Data Structures Used

- **Singly linked list**: stores staff user accounts in `UserManager`
- **Circular queue**: stores waiting patients in `CircularQueue`
- **Structs and enums**: model users, patients, roles, and patient priority

## Project Structure

```text
.
|-- Auth.cpp / Auth.h              # Login prompt and authentication bridge
|-- CircularQueue.cpp / .h         # Patient queue implementation
|-- Patient.h                      # Patient model and priority enum
|-- User.h                         # User model and role enum
|-- UserManager.cpp / .h           # Staff account linked-list management
|-- Utils.cpp / Utils.h            # ID generation, credential generation, validation helpers
|-- main.cpp                       # Program entry point and role menus
`-- README.md
```

## Requirements

- A C++ compiler that supports C++11 or newer
- Windows PowerShell, Command Prompt, or any terminal that can run `g++`

If you are on Windows, MinGW-w64 is a common way to get `g++`.

## Build

From the project directory, compile all source files:

```powershell
g++ main.cpp Auth.cpp CircularQueue.cpp UserManager.cpp Utils.cpp -o main.exe
```

On Linux or macOS, you can build the same program with:

```bash
g++ main.cpp Auth.cpp CircularQueue.cpp UserManager.cpp Utils.cpp -o main
```

## Run

On Windows:

```powershell
.\main.exe
```

On Linux or macOS:

```bash
./main
```

## Default Login

The application initializes one default administrator account when it starts:

```text
Username: admin
Password: admin123
```

Use this account first to add receptionist and doctor users.

## How It Works

1. The program asks for the maximum queue capacity.
2. Users log in with a username and password.
3. The menu shown depends on the logged-in user's role.
4. Receptionists register patients into the queue.
5. Emergency patients are inserted before normal-priority patients.
6. Doctors consult patients from the front of the queue.

## User Roles

### Admin

- Add receptionist or doctor accounts
- Remove staff accounts
- List all staff users
- Reset staff credentials
- Update own profile

### Receptionist

- Register patients
- Search patients by ID
- Check estimated waiting time
- Display the current patient queue
- Update own profile

### Doctor

- Peek at the next patient
- Consult the next patient
- Display the current patient queue
- Update own profile

## Validation Rules

- Names must contain letters and spaces only
- Ages must be within the allowed range requested by the current form
- Phone numbers must use the Ethiopian format `09XXXXXXXX`
- Passwords created manually must be at least 6 characters long

## Notes

- Data is stored in memory only. Users and patients are lost when the program exits.
- Generated files such as `.o`, `.exe`, `.out`, and `.log` are ignored by Git.
- The queue capacity is selected at startup and must be between `1` and `500`.
