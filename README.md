Memory Management Simulator
Overview
This is a C++-based memory management simulator that emulates how an operating system allocates and deallocates memory for processes using the First-Fit allocation strategy. The simulator represents memory as a list of blocks, each either free or allocated to a process, and supports allocation, deallocation, and visualization of memory status. It also handles external fragmentation by merging adjacent free blocks.
Features

First-Fit Allocation: Allocates memory to a process in the first free block that is large enough.
Dynamic Block Splitting: Splits oversized free blocks during allocation to minimize wasted space.
Deallocation: Frees memory by process ID and merges adjacent free blocks to reduce fragmentation.
Memory Visualization: Displays the current state of memory, showing allocated and free blocks.
Console-Based Interface: Allows users to allocate/deallocate memory and view memory status interactively.

Requirements

C++ compiler (e.g., g++, supporting C++11 or later)
Standard C++ library (included with most compilers)

Installation

Clone or Download the Project:
Download the source code or clone the repository (if hosted).


Compile the Code:
Open a terminal in the project directory.
Run: g++ simulator.cpp -o simulator


Run the Program:
Execute: ./simulator (on Linux/Mac) or simulator.exe (on Windows).



Usage

Start the Program:
Run the compiled executable.
Enter the total memory size when prompted (e.g., 100 for 100 units).


Menu Options:
1. Allocate memory: Enter a process ID and memory size to allocate memory.
2. Deallocate memory: Enter a process ID to free its allocated memory.
3. Display memory: View the current memory status.
4. Exit: Quit the program.


Example Run:Enter total memory size: 100
Memory initialized with 100 units.

1. Allocate memory
2. Deallocate memory
3. Display memory
4. Exit
Choose an option: 1
Enter process ID: 1
Enter memory size: 30
Allocated 30 units for Process 1
----------------------------------------
[Process 1, Size: 30] [Free, Size: 70]
----------------------------------------



Code Structure

simulator.cpp: The main source file containing:
MemoryBlock struct: Represents a memory block with size, status, and process ID.
MemoryManager class: Manages memory allocation, deallocation, and display.
main function: Provides the console-based user interface.



Extending the Simulator
You can enhance the simulator by adding:

Other Allocation Strategies:
Best-Fit: Allocate the smallest free block that fits.
Worst-Fit: Allocate the largest free block.
Modify the allocate function in MemoryManager to implement these.


Paging Simulation:
Divide memory into fixed-size pages and allocate processes to pages.


Fragmentation Metrics:
Calculate external fragmentation (sum of unusable free blocks) or internal fragmentation (unused space within allocated blocks).


Graphical Visualization:
Integrate a library like SFML for a graphical memory display or use ASCII art.


Compaction:
Add a function to move allocated blocks together, consolidating free space.



Example Extension: Best-Fit Allocation
To implement Best-Fit, modify the allocate function to select the smallest free block that can accommodate the process:
bool allocate(int processID, int size) {
    int bestIndex = -1;
    int minSize = totalMemory + 1;
    for (int i = 0; i < memory.size(); i++) {
        if (memory[i].isFree && memory[i].size >= size && memory[i].size < minSize) {
            minSize = memory[i].size;
            bestIndex = i;
        }
    }
    // ... (rest of the allocation logic)
}

Limitations

No input validation for negative sizes or duplicate process IDs.
Supports only First-Fit allocation by default.
No graphical interface (console-based only).
Does not simulate paging or segmentation.

Future Improvements

Add input validation for robust error handling.
Implement additional allocation strategies (Best-Fit, Worst-Fit).
Support paging or segmentation for more realistic OS simulation.
Add a graphical interface using a library like SFML or SDL.
Include metrics for fragmentation analysis.

Contributing
Feel free to fork the project, add features, or fix bugs. Submit pull requests or open issues for suggestions.
License
This project is unlicensed and free to use or modify for educational purposes.
