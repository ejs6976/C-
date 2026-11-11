#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

struct Task {
    string name;
    string dueDate;
    int priority;
    bool completed;
};

void addTask(vector<Task>& tasks) {
    Task task;
    cout << "Enter task name: ";
    getline(cin, task.name);

    cout << "Enter due date (for example, 2026-11-05): ";
    getline(cin, task.dueDate);
    
    cout<<"Enter priority level for this task(1, 2 or 3)\n 1. High\n 2. Medium\n 3. Low\n";
    cin>>task.priority;

    task.completed = false;
    tasks.push_back(task);
    cout << "Task added successfully.\n";
}

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks found.\n";
        return;
    }

    cout << "\n--- Your Tasks ---\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". " << tasks[i].name
             << " | Due: " << tasks[i].dueDate
             << " | Status: " << (tasks[i].completed ? "Completed" : "Incomplete")
             << '\n';
    }
}

void markTaskComplete(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    viewTasks(tasks);
    cout << "Enter the task number to mark as complete: ";

    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice < 1 || choice > static_cast<int>(tasks.size())) {
        cout << "Invalid task number.\n";
        return;
    }

    tasks[choice - 1].completed = true;
    cout << "Task marked as complete.\n";
}

void removeTask(vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    viewTasks(tasks);
    cout << "Enter the task number to remove: ";

    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice < 1 || choice > static_cast<int>(tasks.size())) {
        cout << "Invalid task number.\n";
        return;
    }

    tasks.erase(tasks.begin() + (choice - 1));
    cout << "Task removed successfully.\n";
}

void showList(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks found.\n";
        return;
    }

    cout << "\n--- Your To-Do List ---\n";
    vector<Task> sortedTasks = tasks;   // make a copy

    sort(sortedTasks.begin(), sortedTasks.end(),
         [](const Task& a, const Task& b) {
             return a.priority < b.priority;
         });

    cout << "\nTo-Do List by Importance:\n";
    for (const Task& task : sortedTasks) {
        cout << "Task: " << task.name << " | Priority: ";

        if (task.priority == 1) {
            cout << "High";
        } else if (task.priority == 2) {
            cout << "Medium";
        } else {
            cout << "Low";
        }

        cout << endl;
    }
    
    
}


void saveTasks(const vector<Task>& tasks, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error saving file.\n";
        return;
    }

    for (const Task& task : tasks) {
        outFile << task.name << '\n'
                << task.dueDate << '\n'
                << task.completed << '\n';
    }

    cout << "Tasks saved to file.\n";
}

void loadTasks(vector<Task>& tasks, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        return;
    }

    tasks.clear();
    Task task;
    while (getline(inFile, task.name)) {
        getline(inFile, task.dueDate);
        inFile >> task.completed;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');
        tasks.push_back(task);
    }
}

int main() {
    vector<Task> tasks;
    string filename = "tasks.txt";

    loadTasks(tasks, filename);

    int choice;
    do {
        cout << "\n=== Student Planner ===\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Complete\n";
        cout << "4. Remove Task\n";
        cout << "5. View To-Do List\n";
        cout << "6. Save and Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskComplete(tasks);
                break;
            case 4:
                removeTask(tasks);
                break;
            case 5:
                showList(tasks);
                break;
            case 6:
                saveTasks(tasks, filename);
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}