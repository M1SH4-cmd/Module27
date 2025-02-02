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
    std::string getName() const { return name; }

private:
    std::string name;
    bool busy;
};

class Manager : public Employee {
public:
    Manager(const std::string& name) : Employee(name) {}

    void assignTasks(int taskId, std::vector<Employee*>& workers) {
        int tasksCount = std::rand() % (workers.size() + 1);
        std::cout << "Manager " << getName() << " is assigning " << tasksCount << " tasks." << std::endl;

        std::vector<Employee*> availableWorkers;
        for (Employee* worker : workers) {
            if (!worker->isBusy()) {
                availableWorkers.push_back(worker);
            }
        }

        std::random_shuffle(availableWorkers.begin(), availableWorkers.end());
        for (int i = 0; i < tasksCount && i < availableWorkers.size(); ++i) {
            availableWorkers[i]->receiveTask(taskId + i);
        }
    }

    void addWorker(Employee* worker) {
        workers.push_back(worker);
    }

    std::vector<Employee*>& getWorkers() {
        return workers;
    }

private:
    std::vector<Employee*> workers;
};

class CEO : public Employee {
public:
    CEO(const std::string& name) : Employee(name) {}

    void giveInstructions(int instructionId, std::vector<Manager>& managers) {
        for (Manager& manager : managers) {
            manager.assignTasks(instructionId, manager.getWorkers());
        }
    }

    void addTeam(const std::vector<Employee*>& team) {
        workers = team;
    }

private:
    std::vector<Employee*> workers;
};

class Team {
public:
    Team(const std::string& managerName, int workerCount)
            : manager(managerName) {
        for (int i = 0; i < workerCount; ++i) {
            Employee* worker = new Employee("Worker " + std::to_string(i + 1));
            workers.push_back(worker);
            manager.addWorker(worker);
        }
    }

    Manager& getManager() {
        return manager;
    }

    std::vector<Employee*>& getWorkers() {
        return workers;
    }

private:
    Manager manager;
    std::vector<Employee*> workers;
};

void printCompanyState(const std::vector<Team>& teams) {
    std::cout << "Current state of the company:" << std::endl;
    for (Team team : teams) {
        std::cout << "Team managed by " << team.getManager().getName() << ":" << std::endl;
        for (const Employee* worker : team.getWorkers()) {
            std::cout << " - " << worker->getName() << (worker->isBusy() ? " (Busy)" : " (Available)") << std::endl;
        }
    }
}

int main() {
    std::srand(std::time(0));

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
        printCompanyState(teams);

        bool allBusy = true;
        for (Team& team : teams) {
            for (Employee* worker : team.getWorkers()) {
                if (!worker->isBusy()) {
                    allBusy = false;
                    break;
                }
            }
            if (!allBusy) break;
        }

        if (allBusy) {
            std::cout << "All workers are busy. Waiting for tasks to complete..." << std::endl;
            for (Team& team : teams) {
                for (Employee* worker : team.getWorkers()) {
                    worker->completeTask();
                }
            }
        }
    }

    for (Team& team : teams) {
        for (Employee* worker : team.getWorkers()) {
            delete worker;
        }
    }

    return 0;
}
