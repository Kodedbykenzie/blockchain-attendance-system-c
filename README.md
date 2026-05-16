# 📘 README — Blockchain-Based Attendance System

## 📌 Project Title

**Design and Implementation of a Blockchain-Based Attendance Tracking System in C**

---

# 📖 Overview

This project implements a simple blockchain-based attendance system using the C programming language. It ensures secure and tamper-resistant attendance tracking using:

* SHA-256 cryptographic hashing
* ECDSA digital signatures
* Student registry validation
* File-based persistence

The system prevents unauthorized modification of attendance records by linking each block cryptographically.

---

# ⚙️ Features

* Load student registry from file (`students.txt`)
* Mark attendance (PRESENT / ABSENT / LATE)
* Blockchain-based storage of attendance records
* SHA-256 hash linking between blocks
* ECDSA digital signatures for authentication
* Blockchain validation and tamper detection
* File persistence using binary storage
* Command-line interface (CLI)

---

# 📁 Project Structure

```
attendance-blockchain/
│
├── main.c
├── blockchain.c
├── blockchain.h
├── registry.c
├── registry.h
├── crypto.c
├── crypto.h
├── storage.c
├── storage.h
├── students.txt
├── attendance.dat
└── README.md
```

---

# 🧩 Required Libraries and Dependencies

This project requires:

## 1. GCC Compiler

Used to compile the C program.

Install:

```bash
brew install gcc
```

---

## 2. OpenSSL Library (Required for SHA-256 & ECDSA)

Install OpenSSL:

```bash
brew install openssl@3
```

---

## 📌 OpenSSL Paths (Mac M1/M2/M3)

You may need to include these during compilation:

* Include path:

```
/opt/homebrew/opt/openssl@3/include
```

* Library path:

```
/opt/homebrew/opt/openssl@3/lib
```

---

# 🛠️ Compilation Instructions

Navigate to the project folder:

```bash
cd attendance-blockchain
```

Compile using GCC:

```bash
gcc main.c blockchain.c registry.c crypto.c storage.c \
-I/opt/homebrew/opt/openssl@3/include \
-L/opt/homebrew/opt/openssl@3/lib \
-o attendance -lssl -lcrypto
```

---

# ▶️ How to Run the Application

After successful compilation:

```bash
./attendance
```

---

# 📋 Menu Options

When the program runs, you will see:

```
===== Attendance Blockchain =====
1. Mark Attendance
2. View Records
3. Validate Blockchain
4. Tamper Block
5. Exit
```

---

## 🔹 Option 1: Mark Attendance

* Enter Student ID
* Enter status (PRESENT / ABSENT / LATE)
* System validates student and creates a blockchain record

---

## 🔹 Option 2: View Records

* Displays all attendance blocks stored in the blockchain

---

## 🔹 Option 3: Validate Blockchain

* Verifies:

  * SHA-256 hash integrity
  * Chain linkage
  * ECDSA digital signatures
* Output:

  * `Blockchain VALID` or `Blockchain TAMPERED`

---

## 🔹 Option 4: Tamper Block

* Simulates unauthorized modification of a block
* Used to demonstrate blockchain immutability

---

## 🔹 Option 5: Exit

* Safely exits the system

---

# 📄 Input File Format (students.txt)

Before running the program, ensure this file exists:

```
ALU001,John Doe,BLK101
ALU002,Jane Smith,BLK101
ALU003,Amara Diallo,BLK101
```

Format:

```
student_id, full_name, course_code
```

---

# 💾 Data Persistence

The blockchain is stored in:

```
attendance.dat
```

* Automatically saved after each attendance entry
* Loaded automatically at program startup

---

# 🔐 Security Features

This system implements:

### ✔ SHA-256 Hashing

Ensures data integrity and detects tampering.

### ✔ ECDSA Digital Signatures

Authenticates each block to prevent unauthorized record creation.

### ✔ Blockchain Linking

Each block contains the previous block’s hash.

---

# ⚠️ Notes

* Ensure OpenSSL is installed before compiling
* Do not modify `attendance.dat` manually
* Tampering with past blocks will cause validation failure

---

# 🚀 How to Clean & Rebuild

If you need to rebuild:

```bash
rm attendance
gcc main.c blockchain.c registry.c crypto.c storage.c \
-I/opt/homebrew/opt/openssl@3/include \
-L/opt/homebrew/opt/openssl@3/lib \
-o attendance -lssl -lcrypto
```

---


