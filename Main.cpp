#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class User {
public:
    int id;
    std::string name;
    std::string email;
    std::string password;

    // Default constructor
    User() : id(0), name(""), email(""), password("") {}

    // Constructor with parameters
    User(int _id, std::string _name, std::string _email, std::string _password) 
        : id(_id), name(_name), email(_email), password(_password) {}

    // Display user info
    void display() const {
        std::cout << "ID: " << id << ", Name: " << name << ", Email: " << email << std::endl;
    }

    // Display profile (more detailed)
    void displayProfile() const {
        std::cout << "\n=== User Profile ===" << std::endl;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "===================" << std::endl;
    }
};

class SocialMediaApp {
private:
    std::vector<User> users;
    int nextUserId;
    int currentUserId; // -1 means no one is logged in

public:
    SocialMediaApp() : nextUserId(1), currentUserId(-1) {}

    // Register a new user
    void registerUser() {
        std::string name, email, password;

        std::cout << "=== Register New User ===" << std::endl;
        std::cout << "Enter name: ";
        std::cin >> name;
        std::cout << "Enter email: ";
        std::cin >> email;
        std::cout << "Enter password: ";
        std::cin >> password;

        for (const User& user : users) {
            if (user.email == email) {
                std::cout << "Email already exists! Please use a different email." << std::endl;
                return ;
            }
        }

        User newUser(nextUserId, name, email, password);
        users.push_back(newUser);

        std::cout << "User registered successfully with ID: " << nextUserId << std::endl;
        nextUserId++;
    }

    // Login user
    bool loginUser() {
        std::string email, password;

        std::cout << "=== Login ===" << std::endl;
        std::cout << "Enter email: ";
        std::cin >> email;
        std::cout << "Enter password: ";
        std::cin >> password;

        for (const User& user : users) {
            if (user.email == email && user.password == password) {
                currentUserId = user.id;
                std::cout << "Login successful! Welcome, " << user.name << "!" << std::endl;
                return true;
            }
        }

        std::cout << "Invalid email or password!" << std::endl;
        return false;
    }

    // Logout user
    void logoutUser() {
        if (currentUserId != -1) {
            std::cout << "Logged out successfully!" << std::endl;
            currentUserId = -1;
        } else {
            std::cout << "No user is currently logged in!" << std::endl;
        }
    }

    // Check if user is logged in
    bool isLoggedIn() {
        return currentUserId != -1;
    }

    // Get current user
    User* getCurrentUser() {
        if (currentUserId == -1) return nullptr;

        for (User& user : users) {
            if (user.id == currentUserId) {
                return &user;
            }
        }
        return nullptr;
    }

    // View current user's profile
    void viewProfile() {
        if (!isLoggedIn()) {
            std::cout << "Please login first!" << std::endl;
            return;
        }

        User* currentUser = getCurrentUser();
        if (currentUser) {
            currentUser->displayProfile();
        }
    }

    // Edit profile
    void editProfile() {
        if (!isLoggedIn()) {
            std::cout << "Please login first!" << std::endl;
            return;
        }

        User* currentUser = getCurrentUser();
        if (!currentUser) return;

        std::cout << "=== Edit Profile ===" << std::endl;
        std::cout << "Current name: " << currentUser->name << std::endl;
        std::cout << "Enter new name (or press Enter to keep current): ";

        std::string newName;
        std::cin.ignore();
        std::getline(std::cin, newName);

        if (!newName.empty()) {
            currentUser->name = newName;
            std::cout << "Name updated successfully!" << std::endl;
        }
    }

    // Show all users
    void showAllUsers() {
        std::cout << "\n=== All Users ===" << std::endl;
        if (users.empty()) {
            std::cout << "No users registered yet." << std::endl;
            return;
        }

        for (const User& user : users) {
            user.display();
        }
    }

    // Save users to file
    void saveUsers() {
        std::ofstream file("users.txt");
        if (!file.is_open()) {
            std::cout << "Error: Could not open file for saving!" << std::endl;
            return;
        }

        for (const User& user : users) {
            file << user.id << "," << user.name << "," << user.email << "," << user.password << std::endl;
        }

        file.close();
        std::cout << "Users saved successfully!" << std::endl;
    }

    // Load users from file
    void loadUsers() {
        std::ifstream file("users.txt");
        if (!file.is_open()) {
            std::cout << "No existing user file found. Starting fresh." << std::endl;
            return;
        }

        users.clear();
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;

            std::getline(ss, item, ',');
            int id = std::stoi(item);

            std::getline(ss, item, ',');
            std::string name = item;

            std::getline(ss, item, ',');
            std::string email = item;

            std::getline(ss, item, ',');
            std::string password = item;

            users.push_back(User(id, name, email, password));

            if (id >= nextUserId) {
                nextUserId = id + 1;
            }
        }

        file.close();
        std::cout << "Users loaded successfully! (" << users.size() << " users)" << std::endl;
    }
};

// Show main menu
void showMainMenu() {
    std::cout << "\n=== Social Media Simulation ===" << std::endl;
    std::cout << "1. Register" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Show All Users" << std::endl;
    std::cout << "4. Save Data" << std::endl;
    std::cout << "5. Load Data" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choice: ";
}

// Show user menu
void showUserMenu() {
    std::cout << "\n=== User Menu ===" << std::endl;
    std::cout << "1. View Profile" << std::endl;
    std::cout << "2. Edit Profile" << std::endl;
    std::cout << "3. Show All Users" << std::endl;
    std::cout << "4. Save Data" << std::endl;
    std::cout << "5. Logout" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choice: ";
}

int main() {
    SocialMediaApp app;
    int choice;

    app.loadUsers();

    while (true) {
        if (!app.isLoggedIn()) {
            showMainMenu();
            std::cin >> choice;

            switch (choice) {
                case 1:
                    app.registerUser();
                    break;
                case 2:
                    app.loginUser();
                    break;
                case 3:
                    app.showAllUsers();
                    break;
                case 4:
                    app.saveUsers();
                    break;
                case 5:
                    app.loadUsers();
                    break;
                case 0:
                    std::cout << "Goodbye!" << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice!" << std::endl;
            }
        } else {
            showUserMenu();
            std::cin >> choice;

            switch (choice) {
                case 1:
                    app.viewProfile();
                    break;
                case 2:
                    app.editProfile();
                    break;
                case 3:
                    app.showAllUsers();
                    break;
                case 4:
                    app.saveUsers();
                    break;
                case 5:
                    app.logoutUser();
                    break;
                case 0:
                    std::cout << "Goodbye!" << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice!" << std::endl;
            }
        }
    }

    return 0;
}
