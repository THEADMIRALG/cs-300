//Joseph Grzywinski
//cs-300
//04/21/2024

#include <iostream>
#include <fstream>
#include <string>
#include <vector>



using namespace std;


struct Course {
	string courseNumber;
	string courseName;
	vector<string> prerequisites;
	
};


struct Node {
	Course course;
	Node* left;
	Node* right;

	
	Node() {
		left = nullptr;
		right = nullptr;
	}

	
	Node(Course aCourse) :
		Node() {
		course = aCourse;
	}
};


class BinarySearchTree {

private:
	Node* root;

	void addNode(Node* node, Course course);
	void inOrder(Node* node);


public:
	BinarySearchTree();
	void InOrder();
	void LoadCourses(Course course);
	Course Search(string courseNumber);
};


// setting root node for BST
BinarySearchTree::BinarySearchTree() {
	root = nullptr;

}


void BinarySearchTree::InOrder() {
	inOrder(root);
}

//basic display function that displays course number, course name, and prerequisites
void display(Course course) {
	cout << "Course Number: " << course.courseNumber << endl;
	cout << "Course Name: " << course.courseName << endl;
	cout << "Prerequisites: " << endl;
	for (int i = 0; i < course.prerequisites.size(); i++) {
		cout << course.prerequisites[i] << " ";
	}
	cout << endl;
	cout << " =======================" << endl;
	cout << endl;
}

//the inorder method will traverse the tree in order so the printed list will be in alphanumeric order
void BinarySearchTree::inOrder(Node* node) {
	if (node != nullptr) {
		inOrder(node->left);
		cout << node->course.courseNumber << ": " << node->course.courseName << endl;
		
		if (node->course.prerequisites.size() == 0) {
			cout << "No prerequisites" << endl;
		}
		else{
			cout << "prerequisites: " << endl;
			for (int i = 0; i < node->course.prerequisites.size(); i++) {
				cout << node->course.prerequisites[i] << endl;
				}
			}
		cout << "=====================" << endl;
		inOrder(node->right);

	}
}

//search to compare inputted course number to the course number in the tree
Course BinarySearchTree::Search(string courseNumber) {
	Node* current = root;
	while (current != nullptr) {
		if (current->course.courseNumber.compare(courseNumber) == 0) {
			return current->course;
		}
		else {
			if (courseNumber.compare(current->course.courseNumber) < 0) {
				current = current->left;
			}
			else {
				current = current->right;
			}
		}

	}
	return Course();
}

//function sets the root node if root is null but will send the course to the addNode function if root is not null
void BinarySearchTree::LoadCourses(Course course) {
	if (root == nullptr) {
		root = new Node(course);
	}
	else {
		this->addNode(root, course);
	}
}

//add node function will check left node first and then right node if the course number is less than or greater than the current node
//to determine where to place it in the tree
void BinarySearchTree::addNode(Node* node, Course course) {

	if (node != nullptr) {
		if (node->left == nullptr && course.courseNumber.compare(node->course.courseNumber) < 0) {
			node->left = new Node(course);
		}
		else if (node->right == nullptr && course.courseNumber.compare(node->course.courseNumber) > 0) {
			node->right = new Node(course);
		}
		else if (course.courseNumber.compare(node->course.courseNumber) < 0) {
			addNode(node->left, course);
		}
		else {
			addNode(node->right, course);
		}
	}
}


//parser will read the file and separate the lines at each comma into a vector of strings. If the vector size is less than 2 then the input is invalid 
//and the vector is cleared if not, the vector is read to creat the course object out of each line.
void parser(string file, BinarySearchTree* bst)
{
	vector<string> substrings;
	ifstream inFS;	
	inFS.open(file);
	string line;
	string j = "";
	if (inFS.is_open()){
		while (getline(inFS, line)){
			for (int i = 0; i < line.length(); i++) {
				if (line[i] == ',') {
					substrings.push_back(j);
					j = "";
				}
				else {
					j += line[i];
				}
			}
			substrings.push_back(j);
			j = "";
			if (substrings.size() < 2) {
				cout << "Invalid input please enter a properly formatted file" << endl;
				substrings.clear();
				break;
			}
			
			Course course;
			course.courseNumber = substrings[0];	
			course.courseName = substrings[1];
			for (int i = 2; i < substrings.size(); i++) {
				course.prerequisites.push_back(substrings[i]);
			}
			bst->LoadCourses(course);
			substrings.clear();
		}
		cout << "Courses file loaded" << endl;
	}
	else
	{
		std::cout << "File not found" << std::endl;
	}
}


int main()
{

	BinarySearchTree* bst;
	bst = new BinarySearchTree();
	Course course;

	string fileName;
	int choice = 0;
	while (choice != 9) {
		cout << "Course System:" << endl;
		cout << "  1. Load Courses from a file" << endl;
		cout << "  2. Display All Courses" << endl;
		cout << "  3. Find a Course" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		if (choice == 1) {
			cout << "Enter file name: ";
			cin >> fileName;
			parser(fileName, bst);
		}
		else if (choice == 2) {
			bst->InOrder();
		}
		else if (choice == 3) {
			string courseNumber;
			cout << "Enter course number: ";
			cin >> courseNumber;
			for (char& i : courseNumber) {
				i = toupper(i);
			}
			Course course = bst->Search(courseNumber);
			if (!course.courseNumber.empty()) {
				display(course);
			}
			else {
				cout << "No course found." << endl;
			}
			
		}
		else if (choice == 9) {
			cout << "Exiting Application" << endl;
		}
		else {
			cout << "Invalid choice" << endl;
			break;
		}
	}
}


