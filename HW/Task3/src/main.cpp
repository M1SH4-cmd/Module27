#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Branch {
public:
    Branch(Branch* parent = nullptr) : parent(parent), elfName("None") {
        if (parent) {
            parent->addChild(this);
        }
    }

    void addChild(Branch* child) {
        children.push_back(child);
    }

    void addElf(const std::string& name) {
        if (name != "None") {
            elfName = name;
        }
    }

    Branch* getTopBranch() {
        if (parent == nullptr) return nullptr;
        if (parent->parent == nullptr) return parent;
        return parent->getTopBranch();
    }

    bool findElf(const std::string& name) {
        if (elfName == name) {
            return true;
        }
        for (Branch* child : children) {
            if (child->findElf(name)) {
                return true;
            }
        }
        return false;
    }

    int countNeighbors() {
        int count = 0;
        if (elfName != "None") {
            count++;
        }
        for (Branch* child : children) {
            if (child->elfName != "None") {
                count++;
            }
        }
        return count;
    }

    const std::string& getElfName() const {
        return elfName;
    }

    const std::vector<Branch*>& getChildren() const {
        return children;
    }

    void printTree(int level = 0) const {
        std::cout << std::string(level * 2, ' ') << (parent ? "Middle " : "Big ") << elfName << std::endl;
        for (Branch* child : children) {
            child->printTree(level + 1);
        }
    }

private:
    Branch* parent;
    std::vector<Branch*> children;
    std::string elfName;
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

    std::cout << "Forest structure:" << std::endl;
    for (Branch& tree : trees) {
        tree.printTree();
    }

    for (Branch& tree : trees) {
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

    for (Branch& tree : trees) {
        for (Branch* branch : tree.getChildren()) {
            if (branch->findElf(searchName)) {
                int neighbors = branch->countNeighbors();
                std::cout << "Total neighbors for " << searchName << ": " << neighbors - 1 << std::endl;
                return 0;
            }
        }
    }

    std::cout << "Elf " << searchName << " not found." << std::endl;
    return 0;
}