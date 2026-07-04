// ===================================
//          INCLUDED LIBRARIES
// ===================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include "functions.h" //header

// ==========================================
//        GLOBAL VARIABLES DEFINITIONS
// ==========================================
int v_index;
int i;
int vehicle_counter = 0;

// ===========================
//       HELPER FUNCTION
// ===========================

/**
 * @brief Searches for a vehicle's array index using its unique ID.
 * * This helper function iterates through the global vehicle array up to MAX_SLOTS(200).
 * It strictly filters and matches both the active occupancy status and the unique
 * tracking identification number.
 * * @param search_id The unique ID number of the vehicle to find.
 * @return int The exact array index if the vehicle is actively parked, otherwise -1.
 */
int find_vehicle_index(int search_id) {

    // Loop through the entire garage buffer to locate the target vehicle
    for (int i = 0; i < MAX_SLOTS; i++) {
        // Match only if the slot is occupied and the ID is identical
        if (v[i].status == 1 && v[i].id == search_id) {
            return i; // Target found, return memory tracking index
        }
    }

    return -1; // No such active ID exists in the system database
}

// ========================================
//        VEHICLE SEARCH OPERATIONS
// ========================================

/**
 * @brief Handles the UI and logic for searching a vehicle by either ID or Plate Number.
 * * This function provides a sub-menu allowing the user to select their search criteria.
 * Case 1 utilizes the centralized find_vehicle_index helper, while Case 2 performs
 * a string-comparison (strcmp) sequential scan over active garage records.
 */
void search_vehicle(){

    int exist=0;
    int choice;
    int search_id;
    char plate_num[15];
    clrscr();//clear screen

    printf(CYAN "\t\t\t\t          ...--> SEARCHING SECTION <--...          \n" RESET);
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);

    printf(YELLOW"\t\t\t\t   Searching by "BLUE"[1] "YELLOW"ID or "BLUE"[2] "YELLOW"Plate Number? ==> "BLUE);
    scanf("%d",&choice);

    switch(choice){
        // ---------------------------------------
        // [CASE 1] Search by unique Vehicle ID
        // ---------------------------------------
        case 1:
                printf(YELLOW"\n\t\t\t\t\t\t Enter ID ==> "BLUE);
                scanf("%d",&search_id);

                // Call helper function to acquire matching database index
                v_index = find_vehicle_index(search_id);

                if(v_index == -1){ //  ID  not found
                    printf(RED"\n\n\t\t\t\t\t\t ERROR!,NOT FOUND\n\n"RESET);
                    srch();
                }
                else{ // ID located, display comprehensive data profile
                    printf(GREEN"\n\t\t\t\t\t\t FOUND SUCCESSFULLY:)\n\n");
                    printf(YELLOW"\t\t\t\t\t\t Owner`s Name :"BLUE"  %s\n"RESET,v[v_index].owner_name);
                    printf(YELLOW"\t\t\t\t\t\t Plate Number :"BLUE"  %s\n"RESET,v[v_index].plate_number);
                    printf(YELLOW"\t\t\t\t\t\t Vehicle Type :"BLUE"  %s\n"RESET,v[v_index].vehicle_type);
                    printf(YELLOW"\t\t\t\t\t\t Slot Number  :"BLUE"  %d\n"RESET,v[v_index].slot_number);
                    printf(YELLOW"\t\t\t\t\t\t Entry Time   :"BLUE"  %d:%d\n\n"RESET,v[v_index].entry_hour,v[v_index].entry_min);
                    srch();
                }
                break;

        // ----------------------------------
        // [CASE 2] Search by Plate Number
        // ----------------------------------
        case 2:
                printf(YELLOW"\n\t\t\t\t\t    Enter Plate Number ==> "BLUE);
                scanf("%s",plate_num);

                // Sequential scanning for string token match
                for(int i=0;i<MAX_SLOTS;i++){
                    // Check if record is active and matches plate text
                    if(v[i].status==1 && strcmp(v[i].plate_number,plate_num)==0){

                        printf(GREEN"\n\t\t\t\t\t    FOUND SUCCESSFULLY:)\n\n");
                        printf(YELLOW"\t\t\t\t\t    Owner`s Name :"BLUE"  %s\n"RESET,v[i].owner_name);
                        printf(YELLOW"\t\t\t\t\t    Vehicle`s ID :"BLUE"  %d\n"RESET,v[i].id);
                        printf(YELLOW"\t\t\t\t\t    Vehicle Type :"BLUE"  %s\n"RESET,v[i].vehicle_type);
                        printf(YELLOW"\t\t\t\t\t    Slot Number  :"BLUE"  %d\n"RESET,v[i].slot_number);
                        printf(YELLOW"\t\t\t\t\t    Entry Time   :"BLUE"  %d:%d\n\n"RESET,v[i].entry_hour,v[i].entry_min);
                        exist = 1; // Flag successful discovery
                        srch();
                        break;
                    }
                }
                // Handle lookup failure boundary conditions
                if(exist == 0 ){//if plate number wrong or don`t exist
                  printf(RED"\n\t\t\t\t\t    ERROR!,NOT FOUND\n\n"RESET);
                  srch();
                }

                break;

        // ----------------------------------------------
        // [DEFAULT] Handle invalid sub-menu selections
        // ----------------------------------------------
        default:
                printf(RED"\t\t\t\t\t    INVALID CHOICE! , TRY AGAIN\n"RESET);
                sleep(1);
                search_vehicle(); // Recursive recovery invocation
                break;
    }
}

// ===================================
//      GARAGE SLOT RELEASE LOGIC
// ===================================

/**
 * @brief Logic function to clear an occupied parking slot from a vehicle record.
 * * This function tracks the vehicle's slot number, verifies that the slot is actively
 * occupied to prevent redundant releasing, clears the memory states (slot_number and status),
 * and returns the original slot identifier.
 * * @param i The array index of the vehicle checking out.
 * @return int The human-readable slot number that was successfully freed up.
 */
int release_slot(int i) {

    int current_slot = v[i].slot_number;

    // Check boundary conditions: verification if slot is already empty
    if (current_slot == 0 || v[i].status == 0) {
        printf(RED"\n\t\t\t\t\t    Slot is empty or is already released!\n"RESET);
        return 0; // Return zero as a safe exit
    }

    v[i].slot_number = 0; // Resetting slot assignment attributes
    v[i].status = 0;      // Set occupancy state to empty/inactive
    return current_slot;  // Return the original slot number for billing reference
}


// ========================================
//        VEHICLE REMOVAL OPERATIONS
// ========================================

/**
 * @brief Handles the UI screen and workflow for checking out and removing a vehicle.
 * * This function prompts the user for a vehicle tracking ID, runs a search index scan via
 * find_vehicle_index, computes outstanding checkout financial fees via calculate_fees,
 * triggers slot cleanups, and decrements the global counter tracking total garage occupancy.
 */
void remove_vehicle(){

    int search_id;
    clrscr();

    printf(CYAN"\t\t\t\t            ...--> REMOVING SECTION <--...          \n"RESET);
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);

    printf(BLUE"\n\t\t\t\t\t\t  Enter ID ==> "WHITE);
    scanf("%d",&search_id);

    // Call centralized search mechanism to capture localized tracking index
    v_index = find_vehicle_index(search_id);

    if(v_index == -1){ // Handle error scenario: ID not present in data tables
        printf(RED"\n\t\t\t\t\t\t  ERROR!,NOT FOUND\n\n"RESET);
        rmv();
        return;
    }
    else{ // Valid record target found: execute checkout and clearance routine
        printf(BLUE"\n\t\t\t\t\t    TOTAL PARKING FEE ==>"RESET" %.2f \n\n"RESET, calculate_fees(v_index));
        printf(GREEN"\n\t\t\t\t\t    VEHICLE REMOVED SUCCESSFULLY :)\n"RESET);
        printf(GREEN"\n\t\t\t\t\t    SLOT [%d] RELEASED SUCCESSFULLY :) \n\n"RESET, release_slot(v_index));
    }

    vehicle_counter--; // Safely decrement global live counter statistics
    rmv();             // Reload sub-menu UI frame structure
}

// =====================================
//        GARAGE SLOT ASSIGNMENT
// =====================================

/**
 * @brief Performs manual slot allocation logic and array memory shifting.
 * * This function prompts the operator to choose a target slot from 1 to 200, handles
 * out-of-bounds validations, checks availability, shifts data from the temporary
 * buffer slot to the selected slot, and updates global occupancy counters.
 * * @param v_index The temporary holding array index where vehicle data was loaded.
 * @return int The human-readable assigned slot number (1 to 200).
 */
int assign_slot(int v_index){

    int chosen_slot;
    int actual_slot;

    // Boundary confirmation loop for acquiring a valid, free garage slot
    while(1){

        printf(YELLOW"\n\t\t\t\t\tChoose A Slot [1:200] ==> "WHITE);
        scanf("%d",&actual_slot);

        chosen_slot = actual_slot-1; // Shift to zero-indexed array boundaries

        // Validate index boundaries
        if(chosen_slot < 0 || chosen_slot > (MAX_SLOTS-1)){
            printf(RED "\n\t\t\t\t\tInvalid Slot Number! Try Again.\n" RESET);
            continue;
        }

        // Verify slot occupancy status avoiding self-clashes
        if(v[chosen_slot].status==1 && chosen_slot!=v_index){
            printf(RED "\n\t\t\t\t\tError! Slot %d Is Already Occupied! Try another.\n" RESET, actual_slot);
            continue;
        }
        break;
    }

    // Shift structure payload to the newly chosen allocation index
    if (chosen_slot != v_index) {
        v[chosen_slot] = v[v_index];
        v[v_index].status = 0; // Wipe old temporary index flag state
    }

    v[chosen_slot].slot_number = chosen_slot+1; // Sync tracking parameter
    v[chosen_slot].status = 1;                  // Set active occupancy flag

    vehicle_counter++; // Safely register total active vehicle inventory

    return actual_slot;
}

// =================================
//       VEHICLE ADDITION
// =================================

/**
 * @brief Interfaces with the operator to register a new vehicle entering the garage.
 * * This function tests garage capacity boundaries, takes user inputs, validates
 * duplicate unique database keys (IDs and License Plates), captures systemic input time stamps
 * securely, and pipes the payload down into assign_slot.
 */
void add_vehicle () {

    int search_id;
    int check_id;
    char plate_num[15];
    int plate_exists=0;

    clrscr();

    printf(CYAN "\t\t\t\t            ...--> ADDING SECTION <--...          \n" RESET);
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);

    // Boundary overflow capacity verification check
    if (vehicle_counter == MAX_SLOTS) {
        printf(RED "\n\t\t\t\t\tERROR! Garage is full, No available slots.\n" RESET);
        sleep(2);
        clrscr();
    }

    printf(PURPLE "\n\t\t\t\t\tEnter the vehicle ID    ==> " WHITE);
    scanf("%d",&search_id);

    // Call helper interface execution module to enforce key uniqueness constraints
    check_id=find_vehicle_index(search_id);

    if (check_id!=-1) {
        printf(RED"\n\t\t\t\t\tError! This ID Already Exists\n"RESET);
        add();
        return;
    }

    // Locate first structurally unallocated placeholder slot in data buffer array
    for(int i = 0; i < MAX_SLOTS; i++) {
        if(v[i].status == 0) {
            v_index = i;
            break;
        }
    }

    v[v_index].id = search_id;

    printf(PURPLE "\t\t\t\t\tEnter The Owner Name    ==> " WHITE);
    scanf(" %[^\n]s", v[v_index].owner_name);

    printf(PURPLE "\t\t\t\t\tEnter The Plate Number  ==> " WHITE);
    scanf("%s", plate_num);

    // Scan table spaces to reject duplicated license tokens
    for(int j=0;j<MAX_SLOTS;j++){
        if(strcmp(plate_num,v[j].plate_number)== 0&&v[j].status == 1){
                plate_exists=1;
                break;
            }
    }
    if(plate_exists==1){
        printf(RED"\n\t\t\t\t\tError! This Plate Number Already Exists\n"RESET);
        add();
        return;
    }

    strcpy(v[v_index].plate_number,plate_num);

    printf(PURPLE "\t\t\t\t\tEnter the vehicle type  ==> " WHITE);
    scanf("%s", v[v_index].vehicle_type);

    // Input loop constraint block for sanitizing input human runtime formats
    while(1) {
        printf(PURPLE "\t\t\t\t\tEnter entry time (H:M)  ==> " WHITE);
        scanf("%d:%d", &v[v_index].entry_hour, &v[v_index].entry_min);

        // Boundaries tracking verification configuration guard
        if (v[v_index].entry_hour < 0 || v[v_index].entry_hour > 23 || v[v_index].entry_min < 0 || v[v_index].entry_min > 59) {
            printf(RED "\t\t\t\t\tInvalid Time Format! Hours [0-23] & Minutes [0-59]. Try Again.\n" RESET);
            continue;
        }
        break;
    }

    printf(GREEN "\n\t\t\t\t\tSuccessfully Assigned to Slot [%d] :)\n" RESET, assign_slot(v_index));
    add(); // menu callback invocation
}

// ======================================
//          VEHICLE DATA EDITING
// ======================================

/**
 * @brief Interfaces with the operator to edit sub-fields of a parked vehicle profile.
 * * This function captures a target vehicle's tracking ID, updates the localized reference
 * database pointer, presents a structural selection sub-menu, and executes safe overriding
 * operations ensuring system-wide identifier uniqueness constraints are never violated.
 */
void edit_vehicle() {

    int search_id;
    int new_id;
    char new_plate[15];
    int plate_exists=0;
    int check_id;

    clrscr();

    printf(CYAN "\t\t\t\t            ...--> EDITING SECTION <--...          \n" RESET);
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);

    printf(PURPLE "\t\t\t\t\t\t  Enter ID ==> " WHITE);
    scanf("%d", &search_id);

    // Call centralized scan search routine to capture current data block index
    v_index = find_vehicle_index(search_id);

    if(v_index == -1){ // Handle error scenario: targeted tracking ID not found
        printf(RED "\n\t\t\t\t\t\t  Error! ID Not Found.\n\n" RESET);
        edt();
    }
    else{ // Target matched successfully, load options configuration layout
            printf(GREEN"\n\t\t\t\t\t\t  FOUND SUCCESSFULLY :)\n\n"RESET);
            printf(WHITE"\t\t\t\t\t[1] "PURPLE"Edit Owner Name" RESET);
            printf(WHITE"\t   [2] "PURPLE"Edit Plate Number\n\n" RESET);
            printf(WHITE"\t\t\t\t\t\t  [3] "PURPLE"Edit Vehicle Type\n\n" RESET);
            printf(WHITE"\t\t\t\t\t[4] "PURPLE"Edit Vehicle ID" RESET);
            printf(WHITE"\t   [5] "PURPLE"Edit Entry Time\n\n" RESET);
            printf(CYAN "\t\t\t        ======================================================\n\n" RESET);

            printf(CYAN "\t\t\t\t\t\t  Enter your Choice ==> " );

            scanf("%d", &i);
            printf(CYAN "\n\t\t\t        ======================================================\n" RESET);

            switch (i) {
                // -----------------------------------------------
                // [CASE 1] Modify string value for Owner's Name
                // -----------------------------------------------
                case 1:
                    printf(PURPLE"\n\t\t\t\t\tEnter New Owner Name ==> "WHITE);
                    scanf(" %[^\n]s", v[v_index].owner_name);
                    printf(GREEN"\n\t\t\t\t\tOWNER NAME UPDATED SUCCESSFULLY :)\n\n"RESET);
                    edt();
                    break;

                // -----------------------------------------------------
                // [CASE 2] Modify License Plate (Uniqueness Enforced)
                // -----------------------------------------------------
                case 2:
                    printf(PURPLE"\n\t\t\t\t\tEnter New Plate Number ==> "WHITE);
                    scanf(" %s", new_plate);

                    // Cross-reference data tables to guarantee text token uniqueness
                    for(int j=0;j<MAX_SLOTS;j++){
                        if(strcmp(new_plate,v[j].plate_number)== 0&&v[j].status == 1&& j!=v_index){
                           plate_exists=1;
                           break;
                        }
                    }
                    if(plate_exists==1){ // Reject duplicated updates
                         printf(RED"\n\t\t\t\t\tError! This Plate Number Already Exists\n\n"RESET);
                         edt();
                         break;
                    }
                    else{ // Commit updates safely
                         strcpy(v[v_index].plate_number,new_plate);
                         printf(GREEN"\n\t\t\t\t\tPLATE NUMBER UPDATED SUCCESSFULLY :)\n\n"RESET);
                    }
                    edt();
                    break;

                // -----------------------------------------------
                // [CASE 3] Modify String value for Vehicle Type
                // -----------------------------------------------
                case 3:
                    printf(PURPLE"\n\t\t\t\t\tEnter New Vehicle Type ==> "WHITE);
                    scanf(" %s", v[v_index].vehicle_type);
                    printf(GREEN"\n\t\t\t\t\tVEHICLE TYPE UPDATED SUCCESSFULLY :)\n\n"RESET);
                    edt();
                    break;

                // ----------------------------------------------------------
                // [CASE 4] Modify Unique ID (Collision Protection Enforced)
                // ----------------------------------------------------------
                case 4:
                    printf(PURPLE"\n\t\t\t\t\tEnter New ID ==> "WHITE);
                    scanf("%d", &new_id);

                    check_id = find_vehicle_index(new_id);

                    // Block transaction if ID clashes with another parked node
                    if (check_id != -1 && check_id != v_index) {
                        printf(RED"\n\t\t\t\t\tError! This ID Already Exists\n\n"RESET);
                        edt();
                        break;
                    }
                    else{ // Apply transaction modifications
                        v[v_index].id = new_id;
                        printf(GREEN"\n\t\t\t\t\tID UPDATED SUCCESSFULLY :)\n\n"RESET);
                    }
                    edt();
                    break;

                // --------------------------------------------
                // [CASE 5] Override Entry Runtime Time Stamps
                // --------------------------------------------
                case 5:
                    while(1) {
                        printf(PURPLE"\n\t\t\t\t\tEnter New Entry Time (H:M) ==> "WHITE);
                        scanf("%d:%d", &v[v_index].entry_hour, &v[v_index].entry_min);

                        // Boundaries tracking verification configuration guard
                        if (v[v_index].entry_hour < 0 || v[v_index].entry_hour > 23 || v[v_index].entry_min < 0 || v[v_index].entry_min > 59) {
                            printf(RED "\t\t\t\t\tInvalid Time Format! Hours [0-23] & Minutes [0-59]. Try Again.\n" RESET);
                            continue;
                        }
                        break;
                    }
                    printf(GREEN"\n\t\t\t\t\tENTRY TIME UPDATED SUCCESSFULLY :)\n\n"RESET);
                    edt();
                    break;

                // --------------------------------------------
                // [DEFAULT] Recursive Recovery Handler Block
                // --------------------------------------------
                default:
                    printf(RED"\n\t\t\t\t\tInvalid choice!, Try Again\n"RESET);
                    sleep(1);
                    edit_vehicle();
                    break;
            }
        }
}

// =======================================
//       VEHICLE RECORDS OVERVIEW
// =======================================

/**
 * @brief Searches and outputs an extensive live data summary sheet for a target vehicle.
 * * This function queries the live database using localized find_vehicle_index mappings,
 * formats visual telemetry fields, and applies standardized padding parameters to
 * terminal screen outputs.
 */
void print_vehicle_data(){

    int search_id;
    clrscr();

    printf(CYAN"\t\t\t\t            ...--> VEHICLE INFO SECTION <--...          \n"RESET);
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);
    printf(RED"\t\t\t\t\t\t Enter ID ==> "GREEN);
    scanf("%d", &search_id);

    // Call helper scan framework utility to check for structural entry existence
    int v_index = find_vehicle_index(search_id);

    if (v_index == -1) { // Error logging sequence boundary check
        printf(RED"\n\n\t\t\t\t\t ERROR!, WRONG ID OR VEHICLE NOT PARKED\n\n"RESET);
        prnt();
        return;
    }

    // Display formatted record logs to standard output terminals
    printf(GREEN"\n\t\t\t\t\t\t FOUND SUCCESSFULLY :)\n\n"RESET);
    printf(RED"\t\t\t\t\t\t Vehicle ID   ==>"GREEN"  %d\n"RESET, v[v_index].id);
    printf(RED"\t\t\t\t\t\t Owner`s Name ==>"GREEN"  %s\n"RESET, v[v_index].owner_name);
    printf(RED"\t\t\t\t\t\t Entry Time   ==>"GREEN"  %02d:%02d\n"RESET, v[v_index].entry_hour, v[v_index].entry_min);
    printf(RED"\t\t\t\t\t\t Slot Number  ==>"GREEN"  %d\n"RESET, v[v_index].slot_number);
    printf(RED"\t\t\t\t\t\t Status       ==>"GREEN"  Parked\n\n"RESET);

    prnt(); // Invoke screen rendering layout callbacks
}

// ==========================================
// ===       PARKING OVERVIEW DISPLAY     ===
// ==========================================

/**
 * @brief Renders the visual status control board for total garage occupancy.
 * * This function computes live system metrics including real-time operational capacity,
 * absolute available vacant slots, and dynamically processes the global mathematical
 * volumetric occupancy percentage.
 */
void display_overview(){

    clrscr();

    printf(CYAN"\t\t\t\t            ...--> PARKING OVERVIEW <--...          \n"RESET);
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);

    // Core calculation block for live garage vacancy telemetry metrics
    int Available_slots = MAX_SLOTS - vehicle_counter;
    float occupancy_percentage = ((float)vehicle_counter / MAX_SLOTS) * 100;

    printf(YELLOW"\t\t\t\t\t    Total Slots          ==>"BLUE"  %d\n"RESET, MAX_SLOTS);
    printf(YELLOW"\t\t\t\t\t    Occupied Slots       ==>"RED"  %d\n"RESET, vehicle_counter);
    printf(YELLOW"\t\t\t\t\t    Available Slots      ==>"GREEN"  %d\n"RESET, Available_slots);
    printf(YELLOW"\t\t\t\t\t    Occupancy Percentage ==>"PURPLE"  %.2f%%\n\n"RESET, occupancy_percentage);

    view(); // Screen callback redirection layer
}

// =======================================
//       PARKING FEE CALCULATION
// =======================================

/**
 * @brief Dynamically computes outstanding transaction parking fees at checkout.
 * * This function tracks structural system runtime parameters, computes differential
 * runtime localized delta limits, addresses chronological overnight rollover boundary conditions
 * (1440 minute offset), enforces a specific 10-minute calculation grace threshold pattern,
 * and maps proportional scaling billing rates.
 * * @param v_index The integer array database memory block target pointer index.
 * @return float The computed precise outstanding financial payment balance fee.
 */
float calculate_fees(int v_index) {

    int entry_total_mins;
    int exit_total_mins;
    int diff_mins;
    int total_hours;
    float fees = 0.0;

    // Capture standard structural UNIX systemic clock metadata
    time_t current_time = time(NULL);
    struct tm *time_info;

    time_info = localtime(&current_time);
    // Convert chronological clock profiles down to raw minutes tracking matrix
    entry_total_mins = (v[v_index].entry_hour * 60) + v[v_index].entry_min;
    exit_total_mins = (time_info->tm_hour * 60) + time_info->tm_min;

    // Critical overnight runtime tracking overflow correction logic sequence (+24 hours)
    if (exit_total_mins < entry_total_mins) {
        exit_total_mins += 1440;
    }

    diff_mins = exit_total_mins - entry_total_mins;
    // Establish theoretical upper boundaries for operational time slots
    total_hours = (int)ceil((double)diff_mins / 60.0);

    int actual_hrs = diff_mins / 60;
    int actual_mins = diff_mins % 60;

    // Enforce custom 10-minute premium calculation grace threshold pattern rules
    if (actual_mins > 10) {
        total_hours = actual_hrs + 1;
    } else {
        total_hours = actual_hrs;
    }

    // Edge-case handler validation: safely capture minimum fractional slot runtimes
    if (total_hours == 0 && diff_mins > 0) {
        total_hours = 1;
    }

    // Apply strict flat scaling tiered billing table models
    if (total_hours <= 1) {
        fees = 10.0;// Base flat transaction fee index mapping

    } else {
        fees = 10.0 + ((total_hours - 1) * 5.0);// Iterative delta hourly rate updates
    }

    printf(BLUE"\n\t\t\t\t\t   %s Parked For "RESET"%d "BLUE"Hours And "RESET"%d "BLUE"Minutes\n"RESET,v[v_index].vehicle_type,actual_hrs,actual_mins);

    return fees; // Flush computational floating values to caller layers
}

// ======================================
//      UI NAVIGATION & SCREEN FLOW
// ======================================

/**
 * @brief Controls the post-removal navigation sub-menu.
 * * This function flushes structural character buffers and captures operator choices
 * to either recursively trigger another vehicle removal sequence or cleanly shift
 * back to the primary system dashboard menu interface.
 */
void rmv(){

    char choice = getchar(); // Clear layout buffer noise
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);
    printf(CYAN"\t\t\t\t[1] Remove Another Vehicle     [Any Key] Back To Menu ");

    scanf("%c",&choice);
    switch(choice){
        case '1':
            remove_vehicle(); // Re-invoke removal screen sequence
            break;
        default:
            clrscr(); // Clean viewport terminal screen to return safely
            break;
    }
}

/**
 * @brief Controls the post-search navigation sub-menu.
 * * This function prompts the user to either perform another consecutive database
 * search transaction or exit back into the main control program branch.
 */
void srch(){

    char choice = getchar(); // Consume trailing newline feed inputs
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);
    printf(CYAN"\t\t\t\t[1] Search Another Vehicle     [Any Key] Back To Menu ");

    scanf("%c",&choice);
    switch(choice){
        case '1':
            search_vehicle(); // Trigger database lookups iteratively
            break;
        default:
            clrscr(); // Redirect execution flow smoothly back to dashboard
            break;
       }
}

/**
 * @brief Controls the post-addition navigation sub-menu.
 * * This function captures runtime control choices following a successful vehicle data insertion,
 * branching execution flows based on terminal screen input criteria.
 */
void add(){

    char choice = getchar(); // Safe sanitation of character streams
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);
    printf(CYAN"\t\t\t\t [1] Add Another Vehicle     [Any Key] Back To Menu ");

    scanf("%c",&choice);
    switch(choice){
        case '1':
            add_vehicle(); // Re-open allocation channel entry vectors
            break;
        default:
            clrscr(); // Flush UI frames back to default menu state
            break;
       }
}

/**
 * @brief Controls the post-printing information summary navigation sub-menu.
 * * This function delays user workflow sequences to review structural log files,
 * allowing iterative individual data sheet printing views before backing out.
 */
void prnt(){

    char choice = getchar(); // Structural clearing of IO terminal pipes
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);
    printf(CYAN"\t\t\t\t [1] View Another Vehicle     [Any Key] Back To Menu ");

    scanf("%c",&choice);
    switch(choice){
        case '1':
            print_vehicle_data(); // Re-execute target indexing data visualizer
            break;
        default:
            clrscr(); // Refresh environment screens for main frames
            break;
        }
}

/**
 * @brief Delays program sequence to hold static overview statistics viewports active.
 * * This function acts as a structural screen-holding mechanism waiting for a random keystroke
 * to wipe frames and route control back into primary menu system stacks.
 */
void view(){

    char choice = getchar(); // Capture trailing frame buffer characters
    printf(CYAN   "\t\t\t\t  ==================================================\n" RESET);
    printf(CYAN"\n\t\t\t\t\t         [Any Key] Back To Menu ");

    scanf("%c",&choice);
    switch(choice){
        default:
            clrscr(); // Terminate viewing and sweep terminal workspaces clean
            break;
        }
}

/**
 * @brief Controls the post-editing navigation sub-menu flow vectors.
 * * This function handles user input flags to either repeat target profile field alterations
 * recursively or direct navigation structures back out to standard terminal control arrays.
 */
void edt(){

    char choice = getchar(); // Clean systemic string streams
    printf(CYAN "\t\t\t        ======================================================\n\n" RESET);
    printf(CYAN"\t\t\t\t [1] Edit Another Vehicle     [Any Key] Back To Menu ");

    scanf("%c",&choice);
    switch(choice){
        case '1':
            edit_vehicle(); // Invoke update transaction frames again
            break;
        default:
            clrscr(); // Reset UI layout view back into root paths
            break;
       }
}

// =======================================
//      SAVING & LOADING PROTOTYPES
// =======================================
/**
 * @brief Saves all current active parking records to an external text file.
 * * This function opens 'parking.txt' in write mode and iterates through the garage array.
 * It filters and writes data only for slots with an active status (status == 1) using
 * a pipe-separated format.
 */
void save_parking_data() {

    FILE *file = fopen("parking.txt", "w");
    if (file == NULL) {
        return;
    }

    for (int i = 0; i < MAX_SLOTS; i++) {
        // Only save slots that are currently occupied
        if (v[i].status == 1) {

            fprintf(file, "%d|%s|%s|%s|%d|%d|%d\n",v[i].id,v[i].owner_name,v[i].plate_number,v[i].vehicle_type,
                    v[i].slot_number,v[i].entry_hour,v[i].entry_min);
        }
    }

    fclose(file);
}

//===============================================================================================
/**
 * @brief Loads previously saved parking data from the text file into the system.
 * * This function reads 'parking.txt' line by line at system startup. It parses the
 * pipe-separated vehicle details, restores them into the global array, updates slot
 * statuses, and synchronizes the global vehicle counter.
 */
void load_parking_data() {
    FILE *file = fopen("parking.txt", "r");
    if (file == NULL) {
        return;
    }

    // Reset counter before reloading data from file
    vehicle_counter = 0;
    int i = 0;

    // Read delimited file tokens using scan sets until End Of File (EOF)
    while (fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%d|%d|%d\n", &v[i].id,v[i].owner_name,v[i].plate_number,
                  v[i].vehicle_type,&v[i].slot_number,&v[i].entry_hour,&v[i].entry_min) == 7) {

        v[i].status = 1;         // Mark slot as occupied
        vehicle_counter++;       // Increment total active vehicle count
        i++;

        // Prevent array index out of bounds (Buffer Overflow protection)
        if (i >= 200) break;
    }

    fclose(file);
}




