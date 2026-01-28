/*-------------------------------------------
PROJECT 1 - ELEMENTARY CELLULAR AUTOMATION
WHAT IT DOES:
- Creates 65-cell world (wrapped ends) with single middle cell active
- User picks rule # (0-255) = 8-bit pattern controlling evolution  
- Each generation: every cell checks [left,self,right] 3-bit state
- Rule bit determines next active/inactive status ('o'/' ')
- Tracks how often each cell was active across all generations
- Displays evolution + final totals vertically (tens/units digits)
COURSE - CS 211 PROGRAMMING PRACTICUM SPRING 2026 UNIVERSITY OF ILLINOIS AT CHICAGO
AUTHOR - DAVINA TITUS
UIN - 652284919
------------------------------------------- */

#include <stdio.h>
#include <stdbool.h> 

const int WORLD_SIZE = 65;

typedef struct cell_struct{
    bool state[3]; //active status for [left, me, right] cells 
    bool active; //current status for me
    int total; //running accumulated count of this cell's active status for all generations
} cell;

//convert an 8-bit integer rule (0-255) to array of bits 
//(stored in reverse order)
//   ex: rule = 6  = 00000110 -> [01100000] 
//   ex: rule = 30 = 00011110 -> [01111000] 
//   ex: rule = 65 = 01000001 -> [10000010]
//return true if input rule is valid (0-255)
//return false if input rule is invalid
bool setBitArray(bool bitArray[8], int rule) {

    //TODO: Task 1 - write the setBitArray() function

    //VALIDATE RULE RANGE 0-255
    if (rule < 0 || rule > 255) {
        return false;
    }

    //EXTRACT 8 BITS: OUTER LOOP=BIT POSITION, INNER LOOP=2^i POWER
    for (int i = 0; i < 8; i++) {
        int power = 1;
        for (int j = 0; j < i; j++) {
            power *= 2;
        }

        //TEST BIT: (rule/power)%2 = 1 → TRUE, SET bitArray[i]
        if ((rule / power) % 2 == 1) {
            bitArray[i] = true;
        } else {
            bitArray[i] = false;
        }
    }

    return true;
}

//convert a 3-bit state array to its 
//associated index of the rule# bit array
//   ex: {0 0 0} -> 0
//   ex: {0 0 1} -> 1
//   ex: {1 0 1} -> 5
int stateToIndex(bool state[3]) {

    //TODO: Task 4 - write the stateToIndex() function

    int index = 0;

    //LEFT NEIGHBOR = 2^2 = 4
    if (state[0]){
        index+=4;
    }

    //MIDDLE CELL = 2^1 = 2 
    if (state[1]){
        index+=2;
    }

    //RIGHT NEIGHBOR = 2^0 = 1
    if (state[2]){
        index+=1;
    }

    return index;
}

//update the state array for each cell in the world array based on the
//current status of active for the nearby [left,me,right] cells
//note: world is assumed periodic/cyclic,
//with front-to-back and back-to-front wrapping 
void setStates(cell world[WORLD_SIZE]) {

    //TODO: Task 5 - write the setStates() function
    
    // FOR EACH CELL: COMPUTE WRAPPED NEIGHBOR INDICES
    for (int i =0; i < WORLD_SIZE;i++){
        int leftIndex, rightIndex;

        // WRAP LEFT: i-1 → if <0 then WORLD_SIZE-1 (64)
        leftIndex = i-1;
        if (leftIndex<0){
            leftIndex = WORLD_SIZE - 1;
        }

        // WRAP RIGHT: i+1 → if >=65 then 0 
        rightIndex = i+1;
        if (rightIndex>=WORLD_SIZE){
            rightIndex=0;
        }

        // SET 3-BIT STATE
        world[i].state[0] = world[leftIndex].active;
        world[i].state[1] = world[i].active;
        world[i].state[2] = world[rightIndex].active;
    }
}

//evolve each cell's active status to the next generation 
//  using its state array
//ruleBitArray contains the 8-bits for the rule#, 
//  stored in reverse order
//make sure to also update the total subitem for each cell
//return the number of active cells in the new generation
int evolveWorld(cell world[WORLD_SIZE], bool ruleBitArray[8]) {
    int totActive = 0;

    // FOR EACH CELL: EVOLVE USING 3-BIT STATE 
    for (int i = 0; i < WORLD_SIZE; i++) {
        int index = stateToIndex(world[i].state);
        bool next = ruleBitArray[index];

        // UPDATE GENERATION ACTIVE COUNT
        if (next) {
            world[i].total++;  
            totActive++;
        }
        world[i].active = next;  
    }

    // PREPARE NEXT GENERATION STATES WITH WRAPPED NEIGHBORS
    setStates(world);
    return totActive;
}


int main() {
    cell world[WORLD_SIZE];

    printf("Welcome to the Elementary Cellular Automaton!\n");

    //TODO: Task 2 - read in a valid rule# and
    //      generate the rule's 8-bit rule bit array 
    //      print the bit array in correct binary number order

    int rule;
    bool bitArray[8];
    bool validRule = false;

    // ASKING FOR RULE UNTIL VALID ONE IS ENTERED
    while (!validRule){
        printf("Enter the rule # (0-255): ");
        scanf("%d",&rule);

        validRule = setBitArray(bitArray, rule);
    }

    // DISPLAY BITS
    printf("\nThe bit array for rule #%d is ",rule);
    for (int i=7; i>=0; i--){
        printf("%d", bitArray[i] ? 1 : 0);
    }

    printf("\n\n");

    //TODO: Task 3 - use the rule bit array to report the evolution 
    //      step for all possible cell states.
    //      follow the format of the sample output exactly

    bool allStates[8][3]={
        {1,1,1},
        {1,1,0},
        {1,0,1},
        {1,0,0},
        {0,1,1},
        {0,1,0},
        {0,0,1},
        {0,0,0}
    };

    printf("The evolution of all possible states are as follows:\n");

    // PRINT TOP ROW: 8 STATES
    for (int i = 0; i < 8; i++) {
        printf("|");
        for (int j = 0; j < 3; j++) {
            printf("%c", allStates[i][j] ? 'o' : '\'');
        }

        printf("|");

        if (i < 7) {
            printf("   ");
        }
    }
    printf("\n");

    // PRINT BOTTOM ROW: RULE EVOLUTION
    printf(" ");
    for (int i = 0; i < 8; i++) {

        bool becomesActive = bitArray[7-i];
        printf(" |%c|",  becomesActive ? 'o' : '\'');

        if (i<7){
            printf("    ");
        }
    }
    printf("\n\n");    

    //TODO: Task 6 - read in the total number of generation evolution 
    //      steps from the user and initialize the world with ONLY the 
    //      middle cell active, all other cells should be inactive; 
    //      make sure to set the state array for each cell.
    int generations;
    bool validGens = false;

    // VALIDATE GENERATIONS INPUT 1-99 
    while (!validGens){
        printf("\nEnter the number of generations (1-99): ");
        scanf("%d", &generations);

        if (generations>=1 && generations <=99 ){
            validGens = true;
        }
    }
    
    printf("Initializing world & evolving...\n");

    // ZERO OUT ALL CELLS: active=false, total=0, state[3]={0,0,0}
    for (int i =0; i < WORLD_SIZE; i++) {
        world[i].active =false;
        world[i].total = 0;

        for (int j= 0; j <3; j++){
            world[i].state[j]= false;
        }
    }

    // ACTIVATE MIDDLE CELL ONLY: index 32 (WORLD_SIZE/2=65/2) 
    int middleIndex = WORLD_SIZE/2;

    world[middleIndex].active = true;
    world[middleIndex].total = 1;

    // COMPUTE INITIAL 3-BIT STATES FOR ALL CELLS
    setStates(world);

    // PRINT GENERATION 0: 32 '' + 'o' + 32 '' + "  1"
    for (int i = 0; i < WORLD_SIZE; i++) {
        printf("%c", world[i].active ? 'o' : '\'');
    }

    printf(" %d\n", 1);

    //TODO: Task 8 - evolve the world the user-specified number of generations,
    //      printing the world after each evolution step, where each active cell prints as
    //      the lower-case "oh"-letter, i.e. "o", and each inactive cell prints as an 
    //      aprostrophe, i.e. "'". After the world display, also print out the number of 
    //      active cells in that generation.
    //
    //      Ex: world = [00000000000000000010101111111001110011111110101000000000000000000]
    //          display->''''''''''''''''''o'o'ooooooo''ooo''ooooooo'o'o'''''''''''''''''' 21 <-display
    //
    //      At the end of ALL evolution steps, print a line under the last generation. 
    //      Ex: world = [01111110000111111111001111111001110011111110011111111100001111110]
    //          display->'oooooo''''ooooooooo''ooooooo''ooo''ooooooo''ooooooooo''''oooooo' 47 <-display
    //          display->_________________________________________________________________<-display


    for (int gen = 1; gen < generations; gen++) {
        // EVOLVE WORLD GET NEW ACTIVE COUNT
        int activeCount = evolveWorld(world, bitArray);

        // PRINT WORLD 'o'=ACTIVE, '\''=INACTIVE (65 CHARS TOTAL)
        for (int i = 0; i < WORLD_SIZE; i++) {
            printf("%c", world[i].active ? 'o' : '\'');
        }

        // PRINT RIGHT-ALIGNED ACTIVE COUNT
        printf(" %2d\n", activeCount);
    }

    // 65 UNDERSCORES - EXACT WORLD WIDTH SEPARATOR
    for (int i = 0; i < WORLD_SIZE; i++) {
        printf("_");
    }
    printf("\n");


    //TODO: Task 9 - after the line under the last generation, print the total active count
    //      for each cell throughout all evolution steps vertically. The cell total active 
    //      counts should be printed as two digit numbers across two lines. Single-digit 
    //      total counts should be represented as a whitespace on the top line, and the 
    //      single-digit on the lower line. For a zero total count, print both digits as whitespaces.
    //
    //      Ex: consider a world after many evolution steps with the following final generation:
    //          display->'oooooo''''ooooooooo''ooooooo''ooo''ooooooo''ooooooooo''''oooooo' 47 <-display
    //          display->_________________________________________________________________<-display
    //          display->            11111111122121222233233222212122111111111            <-display 
    //          display-> 243666698963456647182091851471191174158190281746654369896666342 <-display 
    //                   ^ ^                             ^
    //      note: the first cell was ALWAYS 0, so its total count is zero, and prints as two whitespaces
    //            the third cell has a total count of 4, so it prints as a whitespace above the digit 4
    //            the middle cell has a total count of 29, so it prints the digit 2 above the digit 9

    for (int i = 0; i < WORLD_SIZE; i++) {
        int tens = world[i].total / 10;
        // TENS DIGIT: SPACE FOR 0-9, '1'-'9' FOR 10-99
        printf("%c", tens > 0 ? '0' + tens : ' ');
    }

    printf("\n");

    for (int i = 0; i < WORLD_SIZE; i++) {
        int ones = world[i].total % 10;
        // UNITS DIGIT: SPACE FOR total=0, DIGIT FOR total>0 
        if (world[i].total == 0) {
            printf(" ");
        } else {
            printf("%d", ones);
        }
    }

    printf("\n");
}


