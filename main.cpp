#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Forward Declarations
void registration();
void login();

void manageStudents();

int main()
{
    // Infinite loop to continuously display the menu until the user exits
    while (true)
    {
        // Display the menu
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
            break;
        case 4:
            system("cls");
            cout << endl;
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

    cout << "\t\t Enter your username: ";
    cin >> userId;
    cout << "\t\t Enter your password: ";
    cin >> userPassword;
    cout << "\t\t Enter your email: ";
    cin >> userEmail;
    cout << "\t\t Enter a security question (e.g., Your pet's name?): ";
    cin.ignore();                   // Clear the input buffer
    getline(cin, securityQuestion); // Use getline to take the full input, including spaces
    cout << "\t\t Enter the answer to your security question: ";
    getline(cin, securityAnswer);

    ofstream write("credentials.txt", ios::app);
    write << userId << ' ' << userPassword << ' ' << userEmail << ' ' << securityQuestion << ' ' << securityAnswer << endl;
    write.close();
    system("cls");

    cout << endl;
    cout << "|******************************************************************|\n";
    cout << "|                  Registration is successful!                     |\n";
    cout << "|******************************************************************|\n\n\n";
}

void login()
{
    int count;
    string userId, userPassword, id, pass;
    cout << "__________________________________________________________________\n";
    cout << "|                           Login Page                            |\n";
    cout << "|_________________________________________________________________|\n\n";

    cout << "\t\t Enter your username: ";
    cin >> userId;
    cout << "\t\t Enter your password: ";
    cin >> userPassword;

    // Open the file where credentials are stored
    ifstream read("credentials.txt");
    // Check the file for matching username and password
    while (read >> id >> pass)
    {
        if (id == userId && pass == userPassword)
        {
            count = 1; // Successful login
            break;
        }
    }
    read.close();
    system("cls");

    // Output result based on the success or failure of the login attempt
    if (count == 1)
    {
        cout << "|******************************************************************|\n";
        cout << "                Login successful! Welcome " << userId << ".        \n";
        cout << "|******************************************************************|\n\n";
        // Call manageStudents function after successful login
        manageStudents();
    }
    else
    {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!          Login failed! Invalid username or password.             !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    }
}

void manageStudents()
{
    int choice;
    while (true)
    {
        cout << "__________________________________________________________________\n";
        cout << "|                     Student Management System                   |\n";
        cout << "|_________________________________________________________________|\n\n";

        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  1. Register New Student                         |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  2. Check Individual Student Result              |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  3. Display All Student Records                  |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  4. Modify Student Details                       |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  5. Delete Student Record                        |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  6. Logout                                       |\n";
        cout << "\t|--------------------------------------------------|\n";

        cout << "\nPlease enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            // registerStudent();
            break;
        case 2:
            system("cls");
            // individualResult();
            break;
        case 3:
            system("cls");
            // displayAllStudent();
            break;
        case 4:
            system("cls");
            // modifyStudent();
            break;
        case 5:
            system("cls");
            // deleteStudent();
            break;
        case 6:
            system("cls");
            cout << "|******************************************************************|\n";
            cout << "|                     Logging out...                               |\n";
            cout << "|******************************************************************|\n\n";
            return; // Return to the main menu
        default:
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
            cout << "!          Invalid choice. Please try again.                       !\n";
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        }
    }
}