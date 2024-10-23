#include <iostream>
using namespace std;
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
            // registration();
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