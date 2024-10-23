#include <iostream>
#include <string>
#include <fstream>
#include <sstream> // For stringstream
using namespace std;

// Forward Declarations
void registration();
void forgotPassword();
void login();

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
            login();
            break;
        case 2:
            system("cls");
            registration();
            break;
        case 3:
            system("cls");
            forgotPassword();
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

void forgotPassword()
{
    string inputUserId, inputSecurityAnswerOrEmail;
    string userId, userPassword, userEmail, securityQuestion, securityAnswer;
    cout << "__________________________________________________________________\n";
    cout << "|                      Forgot Password Page                       |\n";
    cout << "|_________________________________________________________________|\n\n";
    cout << "Enter your username: ";
    cin.ignore(); // Clear the input buffer before the first getline
    getline(cin, inputUserId);
    ifstream credentialRead("credentials.txt");
    bool userFound = false;
    string line;
    // Check for matching username and fetch the security question or email
    while (getline(credentialRead, line))
    {
        stringstream ss(line); // String stream for reading the line
        getline(ss, userId, '|');
        getline(ss, userPassword, '|');
        getline(ss, userEmail, '|');
        getline(ss, securityQuestion, '|');
        getline(ss, securityAnswer); // Read the last part after '|'
        if (userId == inputUserId)
        {
            userFound = true;
            cout << "You can either answer the security question or provide your email for verification.\n";
            cout << "__________________________________________________________________\n\n";
            cout << "Security Question: " << securityQuestion << endl;
            break; // User found, exit the loop
        }
    }
    credentialRead.close();
    if (!userFound)
    {
        cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!             User not found! Please check your username.          !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        return;
    }
    cout << "Enter the answer to your security question or your registered email: ";
    getline(cin, inputSecurityAnswerOrEmail); // Capture the answer or email
    // Validate the security answer or email
    if (inputSecurityAnswerOrEmail == securityAnswer || inputSecurityAnswerOrEmail == userEmail)
    {
        // Display the current password
        cout << "\n__________________________________________________________________\n";
        cout << "Your current password is: " << userPassword << "\n";
        // Ask if the user wants to change the password
        string changeChoice;
        cout << "\t Do you want to change your password? (Y/N): ";
        cin >> changeChoice;
        if (changeChoice == "y" || changeChoice == "Y")
        {
            string newPassword;
            cout << "\t\t Enter your new password: ";
            cin.ignore();
            getline(cin, newPassword);
            // Read all data to a temporary file
            ifstream tempRead("credentials.txt");
            ofstream tempWrite("temp_credentials.txt");
            // Update user password
            while (getline(tempRead, line))
            {
                stringstream ss(line); // String stream for reading the line
                getline(ss, userId, '|');
                getline(ss, userPassword, '|');
                getline(ss, userEmail, '|');
                getline(ss, securityQuestion, '|');
                getline(ss, securityAnswer); // Read the last part after '|'
                if (userId == inputUserId)
                {
                    // Write updated user data with new password
                    tempWrite << userId << '|' << newPassword << '|' << userEmail << '|'
                              << securityQuestion << '|' << securityAnswer << endl;
                }
                else
                {
                    // Write unchanged user data
                    tempWrite << userId << '|' << userPassword << '|' << userEmail << '|'
                              << securityQuestion << '|' << securityAnswer << endl;
                }
            }
            tempRead.close();
            tempWrite.close();
            // Replace the original file with the updated file
            remove("credentials.txt");
            rename("temp_credentials.txt", "credentials.txt");
            cout << "\n|******************************************************************|\n";
            cout << "|                     Password successfully updated!               |\n";
            cout << "|******************************************************************|\n\n";
        }
        else
        {
            cout << "\n|******************************************************************|\n";
            cout << "|                  You choose not to change your password.            |\n";
            cout << "|********************************************************************|\n\n";
        }
    }
    else
    {
        cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!                  Incorrect answer or email!                      !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    }
}

void login()
{
    string inputUserId, inputUserPassword;
    string userId, userPassword;
    cout << "__________________________________________________________________\n";
    cout << "|                           Login Page                            |\n";
    cout << "|_________________________________________________________________|\n\n";
    cout << "Enter your username: ";
    cin.ignore(); // Clear the input buffer before the first getline
    getline(cin, inputUserId);
    cout << "Enter your password: ";
    getline(cin, inputUserPassword);
    ifstream credentialRead("credentials.txt");
    bool loginSuccessful = false;
    string line;
    // Check for matching username and password
    while (getline(credentialRead, line))
    {
        stringstream ss(line); // String stream for reading the line
        getline(ss, userId, '|');
        getline(ss, userPassword, '|');
        if (userId == inputUserId && userPassword == inputUserPassword)
        {
            loginSuccessful = true;
            break; // User found and password matches
        }
    }
    credentialRead.close();
    if (loginSuccessful)
    {
        cout << "\n|******************************************************************|\n";
        cout << "|                           Login Successful!                      |\n";
        cout << "|******************************************************************|\n\n";
    }
    else
    {
        cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!          Login failed! Invalid username or password.             !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    }
}