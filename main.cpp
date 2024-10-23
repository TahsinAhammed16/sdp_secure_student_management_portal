#include <iostream>
#include <string>
#include <fstream>
#include <sstream> // For stringstream
using namespace std;

// Forward Declarations
void registration();

int main()
{
    // Infinite loop to continuously display the menu until the user exits
    while (true)
    {
        cout << "___________________________________________________________________\n";
        cout << "|                                                                  |\n";
        cout << "|                   Welcome to the Login Page                      |\n";
        cout << "|__________________________________________________________________|\n\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  1. LOGIN                                        |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  2. REGISTER                                     |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  3. FORGOT PASSWORD                              |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  4. EXIT                                         |\n";
        cout << "\t|--------------------------------------------------|\n\n";
        // Ask for the user's choice
        int choice;
        cout << "Please enter your choice: ";
        cin >> choice;
        // Handle the menu choice
        switch (choice)
        {
        case 1:
            system("cls");
            // login();
            break;
        case 2:
            system("cls");
            registration();
            break;
        case 3:
            system("cls");
            // forgotPassword();
            break;
        case 4:
            system("cls");
            cout << "|******************************************************************|\n";
            cout << "|          Thank you for using the system. Exiting...!             |\n";
            cout << "|******************************************************************|\n\n";
            return 0; // Exit the program
        default:
            system("cls");
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
            cout << "!    Invalid choice. Please select from the options given below.   !\n";
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        }
    }
    return 0;
}

void registration()
{
    string userId, userPassword, userEmail, securityQuestion, securityAnswer;
    cout << "__________________________________________________________________\n";
    cout << "|                       Registration Page                         |\n";
    cout << "|_________________________________________________________________|\n\n";
    // Collect user information
    cout << "\t\t Enter your username: ";
    cin.ignore(); // Clear buffer before getline
    getline(cin, userId);
    cout << "\t\t Enter your password: ";
    getline(cin, userPassword);
    cout << "\t\t Enter your email: ";
    getline(cin, userEmail);
    cout << "\t\t Enter a security question (e.g., Your pet's name?): ";
    getline(cin, securityQuestion);
    cout << "\t\t Enter the answer to your security question: ";
    getline(cin, securityAnswer);
    // Store user data in a file with '|' as a delimiter
    ofstream credentialWrite("credentials.txt", ios::app); // Append mode
    credentialWrite << userId << '|' << userPassword << '|' << userEmail << '|' << securityQuestion << '|' << securityAnswer << endl;
    credentialWrite.close(); // Close the file
    system("cls");
    cout << "|******************************************************************|\n";
    cout << "|                  Registration is successful!                     |\n";
    cout << "|******************************************************************|\n\n";
}