// ====================================
//         INCLUDED LIBRARIES
// ====================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include "functions.h"

// ==========================================
//        GLOBAL VARIABLES DEFINITIONS
// ==========================================
int i;

// =====================================
//        PRINTING A UI MESSAGE
// =====================================
/**
 * @brief Prints the static SPMS ASCII art banner message.
 * @return void
 */
void print_spms() {
    printf(CYAN"\t\t====================================================================================\n" RESET);
    printf(RED"\t\t         SMART               PARKING             MANAGEMENT             SYSTEM\n"RESET);
    printf(CYAN"\t\t====================================================================================\n" RESET);
    printf(RED);
    printf("\t\t  *****************   *****************   ****            ****   *****************\n");
    printf("\t\t  *****************   *****************   *****          *****   *****************\n");
    printf("\t\t  ****                ****         ****   ******        ******   ****             \n");
    printf("\t\t  ****                ****         ****   *******      *******   ****             \n");
    printf("\t\t  ****                ****         ****   **** **      ** ****   ****             \n");
    printf("\t\t  *****************   *****************   ****  **    **  ****   *****************\n");
    printf("\t\t  *****************   *****************   ****   **  **   ****   *****************\n");
    printf("\t\t               ****   ****                ****    ****    ****                ****\n");
    printf("\t\t               ****   ****                ****     **     ****                ****\n");
    printf("\t\t               ****   ****                ****            ****                ****\n");
    printf("\t\t  *****************   ****                ****            ****   *****************\n");
    printf("\t\t  *****************   ****                ****            ****   *****************\n");
    printf(CYAN"\t\t====================================================================================\n" RESET);
    printf("\033[0m");
}

// ===============================
//        PRINTING UI MAIN MENU
// ===============================
/**
 * @brief Prints the system interactive main selection menu panel.
 * @return void
 */
void menu(){
        printf(CYAN "\t\t\t\t        ...--> MAIN MENU SELECTIONS <--...          \n" RESET);
        printf(CYAN "\t\t\t\t  ===============================================\n" RESET);

        printf(YELLOW "\n\t\t\t\t      [1] "PURPLE "Add Vehicle."RESET);
        printf(YELLOW "\t    [2] "PURPLE "Edit Vehicle.\n\n" RESET);

        printf(YELLOW "\t\t\t\t      [3] "PURPLE "Remove Vehicle." RESET);
        printf(YELLOW "   [4] "PURPLE "Search Vehicle.\n\n" RESET);
        printf(YELLOW "\t\t\t\t\t     [5] "PURPLE "View Vehicle Information.\n\n" RESET);

        printf(YELLOW "\t\t\t\t\t     [6] "PURPLE "Total Parking Overview.\n\n" RESET);
        printf(YELLOW "\t\t\t\t\t\t      [7] "PURPLE "EXIT.\n\n" RESET);

        printf(CYAN "\t\t\t\t  ===============================================\n" RESET);
        printf(CYAN "\n\t\t\t\t\t      Enter your choice ==> " );
}

// ===================================================
//     CLEANING SCREAN AND REPRINTING A UI MESSAGE
// ===================================================
/**
 * @brief Utility terminal wrapper executing systemic screen flushes and banner re-renders.
 * @return void
 */
void clrscr(){
    system("cls"); // Execute native windows console screen clear routine
    print_spms();  // Re-display terminal app banner
}

// =======================================
//           MAIN FUNCTION
// =======================================

/**
 * @brief Primary application bootstrap orchestration entry vector.
 * @return int Status operational token sequence execution flags.
 */
int main() {
    load_parking_data(); // Pull state parameters from file structures upon boot

    // Core transactional infinite driver feedback loop execution
    do {
        clrscr();
        menu();
        scanf("%d", &i);

        // Core distribution routing execution tree handler block
        switch (i) {
            case 1:
                clrscr();
                add_vehicle(); // Redirect to registration operational workflow channels
                break;
            case 2:
                clrscr();
                edit_vehicle(); // Redirect to database node alteration channels
                break;
            case 3:
                clrscr();
                remove_vehicle(); // Redirect to checkout and checkout logic channels
                break;
            case 4:
                clrscr();
                search_vehicle(); // Redirect to structural scanning data workflows
                break;
            case 5:
                clrscr();
                print_vehicle_data(); // Redirect to single element layout visualizers
                break;
            case 6:
                clrscr();
                display_overview(); // Redirect to statistical overview telemetry control panels
                break;
            case 7:
                clrscr();
                printf(RED"\n\t\t\t\t\tThank You For Using Our Garage :)\n\n"RESET);
                printf(CYAN "\t\t\t\t  ===============================================\n" RESET);
                save_parking_data(); // Secure runtime memory maps to file tables upon exit trigger
                break;
            default:
                printf(RED"\t\t\t\t\tInvalid choice! Please try again.\n"RESET);
                sleep(1); // Hold screen view momentarily for error visibility
                break;
        }

    } while (i != 7); // Halt runtime processing only upon strict termination choice selection

    return 0; // Return memory buffers cleanly back to internal execution threads
}
