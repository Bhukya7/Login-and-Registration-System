#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User
{
private:
    string username;
    string password;

public:
    User() {}

    User(string user, string pass) : username(user), password(pass) {}

    string getUsername() const
    {
        return username;
    }

    string getPassword() const
    {
        return password;
    }
};

class UserManager
{
private:
    const string filename = "users.txt";

public:
    void registerUser()
    {
        string username, password;

        cout << "Enter a username: ";
        cin >> username;
        cout << "Enter a password: ";
        cin >> password;

        if (isUsernameTaken(username))
        {
            cout << "Username already taken. Please choose another one.\n";
            return;
        }

        ofstream outFile(filename, ios::app);
        if (outFile.is_open())
        {
            outFile << username << "\n"
                    << password << "\n";
            outFile.close();
            cout << "Registration successful!\n";
        }
        else
        {
            cout << "Error saving user data.\n";
        }
    }

    void loginUser()
    {
        string username, password;

        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        if (validateUser(username, password))
        {
            cout << "Login successful! Welcome, " << username << "!\n";
        }
        else
        {
            cout << "Invalid username or password.\n";
        }
    }

private:
    bool isUsernameTaken(const string &username)
    {
        string line;
        ifstream inFile(filename);

        while (getline(inFile, line) && !line.empty())
        {
            if (line == username)
            {
                inFile.close();
                return true;
            }
            getline(inFile, line);
        }

        inFile.close();
        return false;
    }

    bool validateUser(const string &username, const string &password)
    {
        string line;
        ifstream inFile(filename);

        while (getline(inFile, line) && !line.empty())
        {
            if (line == username)
            {
                getline(inFile, line);
                if (line == password)
                {
                    inFile.close();
                    return true;
                }
            }
        }

        inFile.close();
        return false;
    }
};

int main()
{
    UserManager userManager;
    int choice;

    do
    {
        cout << "\nLogin and Registration System\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            userManager.registerUser();
            break;
        case 2:
            userManager.loginUser();
            break;
        case 3:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}
