#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

// =======================================
//          COLORS DEFINITIONS
// =======================================

#define BLACK   "\033[1;30m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define PURPLE  "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define RESET   "\033[0m"

// =======================================
//         FINAL VALUES
// =======================================

#define MAX_SLOTS 200

// ======================================
//          DATA STRUCTURES
// ======================================
/**
 * @brief Structure to store comprehensive vehicle and parking slot details.
 */
typedef struct {
    int id;                 /**< Unique identification number for the vehicle(id) */
    char owner_name[50];    /**< Name of the vehicle owner */
    char plate_number[15];  /**< Unique vehicle plate number */
    char vehicle_type[10];  /**< Type of vehicle ( car, bicycle, bus, motorcycle, tricycle) */
    int slot_number;        /**< Assigned garage slot number (1 to MAX_SLOTS) */
    int status;             /**< Slot status: 0 => Empty, 1 => Occupied */
    int entry_hour;         /**< Hour of vehicle entry (24-hour format) */
    int entry_min;          /**< Minute of vehicle entry */
} vehicle;

// Global struct array to hold garage data and vehicles
 vehicle v[MAX_SLOTS];

// =======================================
//        BASIC FUNCTIONS PROTOTYPES
// =======================================

/**
 * @brief Searches for a vehicle's array index using its unique ID & helper function to avoid repeating code
 * @param search_id The ID of the vehicle to find.
 * @return int The index of the vehicle in the array if found, otherwise -1.
 */
int find_vehicle_index(int search_id);

/**
 * @brief Releases a slot after removing a vehicle
 * @param vehicle index  of the vehicle to find.
 * @return int The number of slot released
 */
int  release_slot(int i);
/**
 * @brief Handles the UI and logic for searching a vehicle and printing its details.
 */
void search_vehicle();

/**
 * @brief Handles removing a vehicle from a slot and freeing up the space.
 */
void remove_vehicle();

/**
 * @brief Assigns a slot after checking i it is occupied or not
 * @param vehicle index  of the vehicle to find.
 * @return int The number of slot assigned
 */
int assign_slot(int v_index);

/**
 * @brief Calculates the parking fees based on duration spent in the garage & apeares when removing a car
 * @param v_index The array index of the vehicle checking out.
 * @return float The total parking fee
 */
float calculate_fees(int v_index);

/**
 * @brief Handles taking user input to add a new vehicle to the system
 */
void add_vehicle();

/**
 * @brief Handles editing existing vehicle information (Owner, Plate, ID, Time, Type)
 */
void edit_vehicle();

/**
 * @brief Prints the full list of formatted vehicle data.(ID,Slot,Owner,Time,Status)
 */
void print_vehicle_data();

/**
 * @brief Displays an overview of total, occupied, and available slots in the garage
 */
void display_overview();


// =======================================
//      SAVING & LOADING PROTOTYPES
// =======================================

/**
 * @brief Saves all current parking data from the array into an external file.
 */
void save_parking_data();

/**
 * @brief Loads previously saved parking data from the external file into the system array at startup.
 */
void load_parking_data();


// =========================================
//        UI PRINTING MENUS PROTOTYPES
// =========================================

/**
 * @brief Displays the interactive screen menu for the vehicle removal section.
 */
void rmv();

/**
 * @brief Displays the interactive screen menu for the vehicle search section.
 */
void srch();

/**
 * @brief Displays the interactive screen menu for the vehicle addition section.
 */
void add();

/**
 * @brief Displays the interactive screen menu for printing/displaying vehicle data.
 */
void prnt();

/**
 * @brief Displays the interactive screen menu for the total parking overview layout.
 */
void view();

/**
 * @brief Displays the interactive screen menu for the vehicle editing section.
 */
void edt();

#endif // FUNCTIONS_H_INCLUDED
