#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Employee {
public:
    Employee(const std::string& name) : name(name), busy(false) {}

    void receiveTask(int taskId) {
        busy = true;
        std::cout << name << " received task " << taskId << std::endl;
    }

    bool isBusy() const { return busy; }
    void completeTask() { busy = false; }

private:
    std::string name;
    bool busy;
};

class Manager : public Employee {
public:
    Manager(const std::string& name) : Employee(name) {}

    void assignTasks(int taskId, std::vector<Employee>& workers) {
        std::srand(taskId + 1);
        int tasksCount = std::rand() % (workers.size() + 1);
        std::cout << "Manager is assigning " << tasksCount << " tasks." << std::endl;

        std::vector<Employee*> availableWorkers;
        for (int i = 0; i < workers.size(); ++i) {
            if (!workers[i].isBusy()) {
                availableWorkers.push_back(&workers[i]);
            }
        }

        std::random_shuffle(availableWorkers.begin(), availableWorkers.end());
        for (int i = 0; i < tasksCount && i < availableWorkers.size(); ++i) {
            availableWorkers[i]->receiveTask(taskId + i);
        }
    }

    std::vector<Employee>& getWorkers() {
        return workers;
    }

private:
    std::vector<Employee> workers;
};

class CEO : public Employee {
public:
    CEO(const std::string& name) : Employee(name) {}

    void giveInstructions(int instructionId, std::vector<Manager>& managers) {
        std::srand(instructionId);
        for (Manager& manager : managers) {
            manager.assignTasks(instructionId, manager.getWorkers());
        }
    }

    void addTeam(const std::vector<Employee>& team) {
        workers = team;
    }

private:
    std::vector<Employee> workers;
};

class Team {
public:
    Team(const std::string& managerName, int workerCount)
        : manager(managerName) {
        for (int i = 0; i < workerCount; ++i) {
            workers.push_back(Employee("Worker " + std::to_string(i + 1)));
        }
    }

    Manager& getManager() {
        return manager;
    }

    std::vector<Employee>& getWorkers() {
        return workers;
    }

private:
    Manager manager;
    std::vector<Employee> workers;
};

int main() {
    int teamCount, workersPerTeam;
    std::cout << "Enter number of teams and workers per team: ";
    std::cin >> teamCount >> workersPerTeam;

    std::vector<Team> teams;
    std::vector<Manager> managers;

    for (int i = 0; i < teamCount; ++i) {
        std::string managerName = "Manager " + std::to_string(i + 1);
        Team team(managerName, workersPerTeam);
        teams.push_back(team);
        managers.push_back(team.getManager());
    }

    CEO ceo("CEO");
    for (Team& team : teams) {
        ceo.addTeam(team.getWorkers());
    }

    int instructionId;
    while (true) {
        std::cout << "Enter instruction ID (or -1 to exit): ";
        std::cin >> instructionId;
        if (instructionId == -1) break;

        ceo.giveInstructions(instructionId, managers);

        bool allBusy = true;
        for (Team& team : teams) {
            for (Employee& worker : team.getWorkers()) {
                if (!worker.isBusy()) {
                    allBusy = false;
                    break;
                }
            }
            if (!allBusy) break;
        }

        if (allBusy) {
            std::cout << "All workers are busy. No more tasks can be assigned." << std::endl;
        }
    }

    return 0;
}