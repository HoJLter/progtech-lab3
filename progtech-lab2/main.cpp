#include <vector>
#include <iostream>
#include <fstream>

struct Node {
	Node* left;
	Node* right;
	int value;
};

class BST {
	Node* root;

private:
	Node* createNode(int value) {
		Node* node = new Node();
		node->left = nullptr;
		node->right = nullptr;
		node->value = value;

		return node;
	}

	void insertRecursive(Node*& localRoot, int value) {
		if (localRoot == nullptr) {
			localRoot = createNode(value);
			return;
		}
		if (value > localRoot->value)
			insertRecursive(localRoot->right, value);
		else {
			insertRecursive(localRoot->left, value);
		}
	}

	static void printRecursive(Node* localRoot) {
		if (localRoot == nullptr) {
			return;
		}
		printRecursive(localRoot->left);
		std::cout << localRoot->value << " ";
		printRecursive(localRoot->right);
	}

	bool isSubtreeHasNodes(Node* localRoot, const std::vector<int>& values) {
		if (localRoot == nullptr) {
			return false;
		}

		bool flag = false;
		for (auto x : values) {
			if (localRoot->value == x) {
				flag = true;
				break;
			}
		}
		flag = flag || 
			isSubtreeHasNodes(localRoot->left, values) || 
			isSubtreeHasNodes(localRoot->right, values);
		return flag;
	}

	void findSubtreesNotIncludesNodesRecursive(
		Node* localRoot, 
		const std::vector<int>& nodes, 
		std::vector<Node*>& result
	) 
	{
		if (localRoot == nullptr) {
			return;
		}

		if (!isSubtreeHasNodes(localRoot, nodes)) {
			result.push_back(localRoot);
			return;
		}

		findSubtreesNotIncludesNodesRecursive(localRoot->left, nodes, result);
		findSubtreesNotIncludesNodesRecursive(localRoot->right, nodes, result);
	}

	void deleteRecursive(Node* localRoot) {
		if (localRoot == nullptr) {
			return;
		}

		deleteRecursive(localRoot->left);
		deleteRecursive(localRoot->right);

		delete localRoot;
	}

public:
	BST() {
		root = nullptr;
	}
	
	~BST() {
		deleteRecursive(root);
	}

	static void print(Node* localRoot) {
		printRecursive(localRoot);
	}

	void insert(int value) {
		insertRecursive(root, value);
	}

	void print() {
		printRecursive(root);
	}

	void printRoot() {
		std::cout << root->value;
	}

	std::vector<Node*> findSubtreesNotIncludesNodes(const std::vector<int>& nodes) {
		std::vector<Node*> result;

		findSubtreesNotIncludesNodesRecursive(root, nodes, result);

		return result;
	}
};

void readValuesFromConsole(std::vector<int>& values, int count) {
	for (int i = 0; i < count; i++) {
		int value;
		std::cin >> value;
		values.push_back(value);
	}
}

void readValuesFromFile(std::vector<int>& values, std::string filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Can't open the file");
	}

	int count;
	file >> count;

	for (int i = 0; i < count; i++) {
		int value;
		file >> value;
		values.push_back(value);
	}
}


int main() {
	while (true) {
		BST tree;
		std::cout << "Where do I get the tree? \n1 - console\n2 - file\n0 - exit\n\nEnter: ";
		int switchValue;
		std::cin >> switchValue;
		std::vector<int> values;
		switch (switchValue) {
			case 1:
			{
				int count;
				std::cout << "Enter the number of tree elements: ";
				std::cin >> count;
				std::cout << "Enter the elements of tree: ";
				readValuesFromConsole(values, count);
				break;
			}
			case 2: {
				std::string filename;
				std::cout << "Enter the filename: ";
				std::cin >> filename;
				readValuesFromFile(values, filename);
				break;
			}
			case 0: {
				return 0;
			}
		}
		for (auto x : values) {
			tree.insert(x);
		}


		std::cout << "Enter the count of values that must not be in the subtree: ";
		int count;
		std::cin >> count;
		std::cout << "Enter a values that must not be in the subtree: ";
		std::vector<int> valuesToNotInclude;
		readValuesFromConsole(valuesToNotInclude, count);

		std::vector<Node*> subtrees = tree.findSubtreesNotIncludesNodes(valuesToNotInclude);
		
		std::cout << "FOUND SUBTREES:";
		std::cout << std::endl;
		for (int i = 0; i < subtrees.size(); i++) {
			std::cout << i << "." << " Root: " << subtrees[i]->value << " Subtree: ";
			BST::print(subtrees[i]);
			std::cout << std::endl;
		}

		std::cout << "WHOLE TREE: ";
		std::cout << std::endl;
		std::cout << "Root: ";
		tree.printRoot();
		std::cout << " Tree : ";
		tree.print();

		std::cout << std::endl;
		std::cout << "\nPress Enter to continue...\n";
		std::cin.ignore(30, '\n');
		std::cin.get();
		system("cls");
	}
}

