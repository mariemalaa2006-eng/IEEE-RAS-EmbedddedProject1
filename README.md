# Smart Parking Management System (SPMS)

An embedded-style C application designed to efficiently manage garage slots, automate check-ins, record vehicle timestamps, and dynamically calculate parking fees with a custom grace period.

## Team Members & Contributors
* **Mariam Alaa** (@mariemalaa2006-eng) - Team Leader, Core Architecture & UI Workflows & Testing
* **Kolod Fahmy** - Database Management 

## System Features
* **Dynamic Slot Allocation:** Efficiently assigns or moves vehicles within available parking slots.
* **Collision Prevention:** Multi-layered verification ensuring unique IDs and License Plates.
* **Automated Financial Engine:** Computes exact garage fees based on stay duration with an integrated **10-minute grace period**.
* **Visual Telemetry Dashboard:** Live terminal statistics showing overall vacancy, occupancy numbers, and capacity percentages.

## Tech Stack
* **Language:** C (Standard C11)
* **IDE Tools:** Code::Blocks / GCC Compiler
* **Environment:** Windows Terminal / PowerShell (ANSI Color codes enabled)

## How to run the Project:
1. Clone the repository
2. Compile the project: `gcc main.c functions.c -o smart_parking`
3. Run the program: `./smart_parking`
4. Use the CLI to interact with the system
5. Make sure all files (main.c, functions.c, functions.h) are in the same directory.
