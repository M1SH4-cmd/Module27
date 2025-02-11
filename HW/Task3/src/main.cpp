#include <iostream>
#include <vector>
#include <string>
#include <ctime>

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

    void setElfName(const std::string& name) {
        elfName = name;
    }

    const std::string& getElfName() const {
        return elfName;
    }

    std::vector<Branch*> getChildren() const {
        return children;
    }

    Branch* getTopBranch() {
        if (parent == nullptr) return nullptr;
        if (parent->parent == nullptr) return parent;
        return parent->getTopBranch();
    }

    Branch* findElf(const std::string& name) {
        if (elfName == name) {
            return this;
        }
        for (Branch* child : children) {
            Branch* result = child->findElf(name);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    int countNeighbors() {
        int count = 0;
        Branch* topBranch = getTopBranch();
        if (topBranch) {
            if (topBranch->elfName != "None") {
                count++;
            }
            for (Branch* child : topBranch->children) {
                if (child->elfName != "None") {
                    count++;
                }
            }
        }
        return count - 1;
    }

    void printTree(int level = 0, const std::string& prefix = "") const {
        std::cout << std::string(level * 2, ' ') << prefix << elfName << std::endl;
        for (size_t i = 0; i < children.size(); ++i) {
            std::string childPrefix = (level == 0) ? "Big " + std::to_string(i + 1) + " - " : "Middle " + std::to_string(i + 1) + " - ";
            children[i]->printTree(level + 1, childPrefix);
        }
    }

private:
    Branch* parent;
    std::vector<Branch*> children;
    std::string elfName;
};

void deleteTree(Branch* branch) {
    for (Branch* child : branch->getChildren()) {
        deleteTree(child);
    }
    delete branch;
}

void generateForest(std::vector<Branch*>& trees) {
    for (int i = 0; i < 5; ++i) {
        Branch* tree = new Branch();
        int numBigBranches = 3 + rand() % 3;
        for (int j = 0; j < numBigBranches; ++j) {
            Branch* bigBranch = new Branch(tree);
            bigBranch->setElfName("Big " + std::to_string(i + 1) + "." + std::to_string(j + 1));
            int numMediumBranches = 2 + rand() % 2;
            for (int k = 0; k < numMediumBranches; ++k) {
                Branch* mediumBranch = new Branch(bigBranch);
                mediumBranch->setElfName("Middle " + std::to_string(i + 1) + "." + std::to_string(j + 1) + "." + std::to_string(k + 1));
            }
        }
        trees.push_back(tree);
    }
}

int main() {
    std::srand(std::time(nullptr));
    std::vector<Branch*> trees;

    generateForest(trees);

    for (size_t i = 0; i < trees.size(); ++i) {
        std::cout << "Tree " << (i + 1) << ":" << std::endl;
        for (Branch* bigBranch : trees[i]->getChildren()) {
            std::string elfName;
            std::cout << "Enter elf name for " << bigBranch->getElfName() << ": ";
            std::cin >> elfName;
            bigBranch->setElfName(elfName);

            for (Branch* mediumBranch : bigBranch->getChildren()) {
                std::cout << "Enter elf name for " << mediumBranch->getElfName() << ": ";
                std::cin >> elfName;
                mediumBranch->setElfName(elfName);
            }
        }
    }

    std::cout << "Forest structure:" << std::endl;
    for (size_t i = 0; i < trees.size(); ++i) {
        std::cout << "Tree " << (i + 1) << ":" << std::endl;
        trees[i]->printTree();
    }

    std::string searchName;
    std::cout << "Enter the name of the elf to search: ";
    std::cin >> searchName;

    for (Branch* tree : trees) {
        Branch* foundBranch = tree->findElf(searchName);
        if (foundBranch) {
            int neighbors = foundBranch->countNeighbors();
            std::cout << "Total neighbors for " << searchName << ": " << neighbors << std::endl;
            deleteTree(tree);
            return 0;
        }
    }

    std::cout << "Elf " << searchName << " not found." << std::endl;
    for (Branch* tree : trees) {
        deleteTree(tree);
    }
    return 0;
}
