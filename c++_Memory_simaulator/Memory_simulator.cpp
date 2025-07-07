#include <iostream>
#include <vector>
using namespace std;

// Structure to represent a memory block
struct MemoryBlock {
    int size;           // Size of the block
    bool isFree;        // Is the block free?
    int processID;      // ID of the process occupying the block (-1 if free)
};

// Class to manage memory
class MemoryManager {
private:
    vector<MemoryBlock> memory; // List of memory blocks
    int totalMemory;            // Total memory size

public:
    // Constructor to initialize memory with one large free block
    MemoryManager(int totalSize) {
        totalMemory = totalSize;
        MemoryBlock initialBlock = {totalSize, true, -1};
        memory.push_back(initialBlock);
        cout << "Memory initialized with " << totalSize << " units.\n";
    }

    // Allocate memory using First-Fit
    bool allocate(int processID, int size) {
        // Scan for the first free block that's large enough
        for (int i = 0; i < memory.size(); i++) {
            if (memory[i].isFree && memory[i].size >= size) {
                // If the block is larger than needed, split it
                if (memory[i].size > size) {
                    MemoryBlock newBlock = {memory[i].size - size, true, -1};
                    memory.insert(memory.begin() + i + 1, newBlock);
                    memory[i].size = size;
                }
                // Allocate the block
                memory[i].isFree = false;
                memory[i].processID = processID;
                cout << "Allocated " << size << " units for Process " << processID << "\n";
                displayMemory();
                return true;
            }
        }
        cout << "No suitable block found for Process " << processID << "\n";
        return false;
    }

    // Deallocate memory for a process
    void deallocate(int processID) {
        bool found = false;
        for (int i = 0; i < memory.size(); i++) {
            if (!memory[i].isFree && memory[i].processID == processID) {
                memory[i].isFree = true;
                memory[i].processID = -1;
                found = true;
                cout << "Deallocated memory for Process " << processID << "\n";
            }
        }
        if (!found) {
            cout << "Process " << processID << " not found.\n";
            return;
        }
        // Merge adjacent free blocks
        mergeFreeBlocks();
        displayMemory();
    }

    // Merge adjacent free blocks to reduce fragmentation
    void mergeFreeBlocks() {
        for (int i = 0; i < memory.size() - 1; i++) {
            if (memory[i].isFree && memory[i + 1].isFree) {
                memory[i].size += memory[i + 1].size;
                memory.erase(memory.begin() + i + 1);
                i--; // Check the same index again after merging
            }
        }
    }

    // Display memory status
    void displayMemory() {
        cout << "\nMemory Status:\n";
        cout << "----------------------------------------\n";
        for (const auto& block : memory) {
            if (block.isFree) {
                cout << "[Free, Size: " << block.size << "] ";
            } else {
                cout << "[Process " << block.processID << ", Size: " << block.size << "] ";
            }
        }
        cout << "\n----------------------------------------\n";
    }
};

// Main function with a simple interface
int main() {
    int totalMemory;
    cout << "Enter total memory size: ";
    cin >> totalMemory;

    MemoryManager manager(totalMemory);

    while (true) {
        cout << "\n1. Allocate memory\n2. Deallocate memory\n3. Display memory\n4. Exit\n";
        cout << "Choose an option: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int processID, size;
            cout << "Enter process ID: ";
            cin >> processID;
            cout << "Enter memory size: ";
            cin >> size;
            manager.allocate(processID, size);
        } else if (choice == 2) {
            int processID;
            cout << "Enter process ID to deallocate: ";
            cin >> processID;
            manager.deallocate(processID);
        } else if (choice == 3) {
            manager.displayMemory();
        } else if (choice == 4) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid option!\n";
        }
    }

    return 0;
}