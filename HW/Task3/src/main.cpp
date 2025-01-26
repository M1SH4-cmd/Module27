#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Branch {
public:
    Branch(Branch* parent = nullptr) : parent(parent) {
        if (parent) {
            parent->addChild(this);
        }
    }

    void addChild(Branch* child) {
        children.push_back(child);
    }

    void addElf(const std::string& name) {
        if (name != "None") {
            elves.push_back(name);
        }
    }

    Branch* getTopBranch() {
        if (parent == nullptr) return nullptr;
        if (parent->parent == nullptr) return parent;
        return parent->getTopBranch();
    }

    bool findElf(const std::string& name) {
        if (std::find(elves.begin(), elves.end(), name) != elves.end()) {
            return true;
        }
        for (auto child : children) {
            if (child->findElf(name)) {
                return true;
            }
        }
        return false;
    }

    int countNeighbors() {
        return elves.size();
    }

    const std::vector<std::string>& getElves() const {
        return elves;
    }

    const std::vector<Branch*>& getChildren() const {
        return children;
    }

private:
    Branch* parent;
    std::vector<Branch*> children;
    std::vector<std::string> elves;
};

void generateForest(std::vector<Branch>& trees) {
    for (int i = 0; i < 5; ++i) {
        Branch* tree = new Branch();
        int numBigBranches = 3 + rand() % 3;
        for (int j = 0; j < numBigBranches; ++j) {
            Branch* bigBranch = new Branch(tree);
            int numMediumBranches = 2 + rand() % 2;
            for (int k = 0; k < numMediumBranches; ++k) {
                new Branch(bigBranch);
            }
        }
        trees.push_back(*tree);
    }
}

int main() {
    std::srand(std::time(nullptr));
    std::vector<Branch> trees;

    generateForest(trees);

    for (Branch tree : trees) {
        for (Branch* branch : tree.getChildren()) {
            std::string elfName;
            std::cout << "Enter elf name for branch: ";
            std::cin >> elfName;
            branch->addElf(elfName);
        }
    }

    std::string searchName;
    std::cout << "Enter the name of the elf to search: ";
    std::cin >> searchName;

    for (Branch tree : trees) {
        for (Branch* branch : tree.getChildren()) {
            if (branch->findElf(searchName)) {
                int neighbors = branch->countNeighbors();
                std::cout << "Total neighbors for " << searchName << ": " << neighbors << std::endl;
                return 0;
            }
        }
    }

    std::cout << "Elf " << searchName << " not found." << std::endl;
    return 0;
}