#include <iostream>
#include <vector>
#include <string>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::seconds

using namespace std;

// Structure to represent a Task
struct Task {
    string description;
    string dueDate;
    int priority;
    bool completed;

    Task(string desc, string date, int prio) 
        : description(desc), dueDate(date), priority(prio), completed(false) {}
};

// Function to display the welcome page
void displayWelcomePage() {
    cout << "--------------------------------------\n";
    cout << "|                                    |\n";
    cout << "|      WELCOME TO THE TO-DO LIST     |\n";
    cout << "|                                    |\n";
    cout << "--------------------------------------\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Pause for 2 seconds
}

// Function to display the main menu
void displayMenu() {
    cout << "\nTo-Do List Application\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Mark Task as Completed\n";
    cout << "4. Delete Task\n";
    cout << "5. Search Task\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

// Function to add a task
void addTask(vector<Task>& tasks) {
    string description, dueDate;
    int priority;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, description);
    cout << "Enter due date (YYYY-MM-DD): ";
    cin >> dueDate;
    cout << "Enter priority (1-5): ";
    cin >> priority;
    tasks.emplace_back(description, dueDate, priority);
    cout << "Task added successfully.\n";
}

// Function to view tasks
void viewTasks(const vector<Task>& tasks) {
    cout << "\nTo-Do List:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". " << tasks[i].description 
             << " [Due: " << tasks[i].dueDate 
             << ", Priority: " << tasks[i].priority 
             << ", Completed: " << (tasks[i].completed ? "Yes" : "No") << "]\n";
    }
}

// Function to mark a task as completed
void markTaskCompleted(vector<Task>& tasks) {
    int taskIndex;
    cout << "Enter task number to mark as completed: ";
    cin >> taskIndex;
    if (taskIndex > 0 && taskIndex <= tasks.size()) {
        tasks[taskIndex - 1].completed = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

// Function to delete a task
void deleteTask(vector<Task>& tasks) {
    int taskIndex;
    cout << "Enter task number to delete: ";
    cin >> taskIndex;
    if (taskIndex > 0 && taskIndex <= tasks.size()) {
        tasks.erase(tasks.begin() + taskIndex - 1);
        cout << "Task deleted successfully.\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

// Function to search tasks by keyword
void searchTask(const vector<Task>& tasks) {
    string keyword;
    cout << "Enter keyword to search for: ";
    cin.ignore();
    getline(cin, keyword);

    cout << "\nSearch Results:\n";
    bool found = false;
    for (const auto& task : tasks) {
        if (task.description.find(keyword) != string::npos) {
            cout << "Description: " << task.description 
                 << " [Due: " << task.dueDate 
                 << ", Priority: " << task.priority 
                 << ", Completed: " << (task.completed ? "Yes" : "No") << "]\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No tasks found with the keyword: " << keyword << "\n";
    }
}

// Main function
int main() {
    // Display welcome page
    displayWelcomePage();

    vector<Task> tasks;
    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskCompleted(tasks);
                break;
            case 4:
                deleteTask(tasks);
                break;
            case 5:
                searchTask(tasks);
                break;
            case 6:
                cout << "Exiting application.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
