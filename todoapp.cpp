#include<iostream>
#include<vector>
#include<fstream>

class Task{
    public:
        std::string name;
        bool completed;

        Task(const std::string& taskname) : name(taskname), completed(false){}

        Task(const std::string& taskname, const bool done) : name(taskname), completed(done){}

        void markAsCompleted(){
            completed = true;
        }

};

class TodoList{
    private:
        std::vector<Task> tasks;

    public:
        void addTask(const std::string& taskname){
            tasks.emplace_back(taskname);
            std::cout<<"Task added Successfully...\n";
        }

        void viewTasks() const{
            if(tasks.empty()){
                std::cout<<"No task for now...\n";
                return;
            }
            int i = 1;
            for(const auto& task: tasks){
                std::cout<<i<<". "<<(task.completed ? "[X]":"[ ]") <<task.name<<std::endl;
                i++;
            }
        }
        void markTaskAsCompleted(int index){
            index--;
            if(index>=0 && index < tasks.size()){
                tasks[index].markAsCompleted();
                std::cout<<"task is marked as done...";
            }
        }
        void removeTask(int index){
            index--;
            if(index>=0 && index < tasks.size()){
                tasks.erase(tasks.begin()+index);
                std::cout <<"task removed successfully...";
            }
        }
        const std::vector<Task>& getTasks(){
            return tasks;
        }

        void fillTasks(const std::string taskname,const bool done){
            tasks.emplace_back(taskname,done);
        }

};

void saveToFile(TodoList& todoList, const std::string& filename){
    std::ofstream outFile(filename);

    for(const auto& task : todoList.getTasks()){
        outFile << task.name <<","<<task.completed<<std::endl;
    }
    outFile.close();

}

void loadFromFile(TodoList& todoList, const std::string filename){
    std::ifstream inFile(filename);

    if(!inFile.is_open()){
        std::cout<< "Error: Could not open file."<<std::endl;
    }

    std::string line;
    

    while(std::getline(inFile,line)){

        if(line.empty()){
            continue;
        }
        size_t delimiterPos = line.find(',');
        if(delimiterPos !=std::string::npos){
            std::string name = line.substr(0,delimiterPos);
            bool done = line.substr(delimiterPos+1)=="1"?true:false;
            todoList.fillTasks(name,done);
        }
    }
    inFile.close();
}

void displayMenu() {
    std::cout << "Todo List Menu:\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Mark Task as Completed\n";
    std::cout << "4. Remove Task\n";
    std::cout << "q. Quit\n";
    std::cout << "Enter your choice: ";
}

void processUserInput(TodoList& todoList, char choice) {
    

    switch (choice) {
        case '1': {
            std::string taskName;
            std::cout << "Enter task name: ";
            std::cin.ignore(); // Ignore newline character
            std::getline(std::cin, taskName);
            todoList.addTask(taskName);
            break;
        }
        case '2':
            todoList.viewTasks();
            break;
        case '3': {
            int index;
            std::cout << "Enter the index of the task to mark as completed: ";
            std::cin >> index;
            todoList.markTaskAsCompleted(index);
            
            break;
        }
        case '4': {
            int index;
            std::cout << "Enter the index of the task to remove: ";
            std::cin >> index;
            todoList.removeTask(index);
            
            break;
        }
        // Handle additional cases as needed
        case 'q':
            std::cout << "Quitting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}

int main() {
    TodoList todoList;
    loadFromFile(todoList, "todolist.txt");

    char choice;
    do {
        displayMenu();
        std::cin >> choice;
        processUserInput(todoList, choice);
    } while (choice != 'q');

    saveToFile(todoList, "todolist.txt");
    
    return 0;
}
