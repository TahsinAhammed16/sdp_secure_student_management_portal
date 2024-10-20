#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Forward Declarations
void registration();
void login();
void manageStudents();

class Students
{
public:
    string name, id;
    int completedSemesters;
    float sGPA[8];

    // Function to calculate SGPA for the current semester
    float calculateSGPA(float totalCredits, float totalGradePoints)
    {
        if (totalCredits == 0)
            return 0; // Prevent division by zero
        return totalGradePoints / totalCredits;
    }

    // Function to convert marks to grade point
    float getGradePoint(float marks)
    {
        if (marks >= 80.0)
            return 4.00; // A+
        else if (marks >= 75.0)
            return 3.75; // A
        else if (marks >= 70.0)
            return 3.50; // A-
        else if (marks >= 65.0)
            return 3.25; // B+
        else if (marks >= 60.0)
            return 3.00; // B
        else if (marks >= 55.0)
            return 2.75; // B-
        else if (marks >= 50.0)
            return 2.50; // C+
        else if (marks >= 45.0)
            return 2.25; // C
        else if (marks >= 40.0)
            return 2.00; // D
        else
            return 0.00; // F
    }

    // Function to register a new student
    void registerStudent()
    {
        ofstream studentsWrite("students.txt", ios::app);

        // Input student details
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter student ID: ";
        cin >> id;

        cout << "  |\n";
        cout << "  |How many previous semesters has the student completed? ";
        cin >> completedSemesters;

        // Input SGPA for each completed semester
        for (int i = 0; i < completedSemesters; i++)
        {
            cout << "\t|> Enter SGPA for semester " << i + 1 << ": ";
            cin >> sGPA[i];
        }

        // Check if the current semester is complete
        char semesterComplete;
        cout << "  |\n";
        cout << "  |Is the current semester complete? (Y/N): ";
        cin >> semesterComplete;

        // Store student data in the file
        studentsWrite << name << "|" << id << "|" << completedSemesters;

        // Store SGPA for each completed semester
        for (int i = 0; i < completedSemesters; i++)
        {
            studentsWrite << "|" << sGPA[i];
        }

        if (semesterComplete == 'Y' || semesterComplete == 'y')
        {
            int subjects;
            cout << "\t|> How many subjects in the current semester? ";
            cin >> subjects;

            // Store number of subjects
            studentsWrite << "|" << subjects;

            // Loop to input subject details
            float totalCredits = 0, totalGradePoints = 0;
            for (int i = 0; i < subjects; i++)
            {
                string subjectName;
                float credit, marks, gradePoint;

                cout << endl;
                cout << "\t\t---------------------------------------------------\n";
                cout << "\t\t  >> Enter the name for subject " << i + 1 << ": ";
                cin.ignore();
                getline(cin, subjectName);

                cout << "\t\t       |Enter credit for " << subjectName << ": ";
                cin >> credit;
                cout << "\t\t       |Enter marks for " << subjectName << "(out of 100): ";
                cin >> marks;

                // Function call to convert marks to grade point
                gradePoint = getGradePoint(marks);
                cout << "\t\t          **Grade Point for subject " << subjectName << ": " << gradePoint << endl;

                // Write subject details to the file
                // Use '|' as the delimiter to separate fields
                studentsWrite << "|" << subjectName << "|" << credit << "|" << marks << "|" << gradePoint;

                totalCredits += credit;
                totalGradePoints += credit * gradePoint;
            }

            sGPA[completedSemesters] = calculateSGPA(totalCredits, totalGradePoints); // Calculate SGPA for the current semester
            completedSemesters++;                                                     // Increment completed semesters
        }

        studentsWrite << endl;
        studentsWrite.close();
        system("cls");

        cout << endl;
        cout << "|******************************************************************|\n";
        cout << "|     Registration successful! Student details have been saved.    |\n";
        cout << "|******************************************************************|\n\n\n";
    }

    // Function to display individual student result
    void individualResult()
    {
        ifstream readStudents("students.txt");
        if (!readStudents)
        {
            cout << "Error: Unable to open the file!\n";
            return;
        }

        string searchId;
        cout << "\nEnter student ID to search: ";
        cin >> searchId;

        string tempName, tempId, line;
        int tempCompletedSemesters, subjects;
        float tempSGPA[8];
        bool found = false;

        // Read each line as a full student record
        while (getline(readStudents, line))
        {
            // Create a string stream to parse the line
            stringstream ss(line);

            // Read the student data separated by '|'
            getline(ss, tempName, '|');
            getline(ss, tempId, '|');
            ss >> tempCompletedSemesters;
            ss.ignore(); // Ignore delimiter after completed semesters

            // Read SGPA values for completed semesters
            for (int i = 0; i < tempCompletedSemesters; i++)
            {
                ss >> tempSGPA[i];
                ss.ignore(); // Ignore delimiter after each SGPA value
            }

            // Check if the ID matches the searched ID
            if (tempId == searchId)
            {
                found = true;

                // Display student details
                cout << "__________________________________________________________________\n";
                cout << "|                           Marksheet                             |\n";
                cout << "|_________________________________________________________________|\n\n";
                cout << "Student Name: " << tempName << endl;
                cout << "Student ID: " << tempId << endl;
                cout << "\nNumber of Semesters Completed: " << tempCompletedSemesters << endl;

                float totalSGPA = 0;
                for (int i = 0; i < tempCompletedSemesters; i++)
                {
                    cout << "SGPA for Semester " << i + 1 << ": " << tempSGPA[i] << endl;
                    totalSGPA += tempSGPA[i];
                }

                // Calculate CGPA
                float CGPA = totalSGPA / tempCompletedSemesters;
                cout << "\nCGPA: " << CGPA << endl;

                // Check if there are subject details for the current semester
                if (ss >> subjects) // Read number of subjects
                {
                    ss.ignore(); // Ignore delimiter after subjects count
                    cout << "\nMarksheet for Current Semester:\n";
                    cout << "Subject\t\tCredit\tMarks\tGrade Point\n";
                    cout << "------------------------------------------------\n";

                    // Loop to read subject details
                    for (int i = 0; i < subjects; i++)
                    {
                        string subjectName;
                        float credit, marks, gradePoint;

                        getline(ss, subjectName, '|'); // Read subject name
                        ss >> credit;
                        ss.ignore(); // Ignore delimiter after credit
                        ss >> marks;
                        ss.ignore();
                        ss >> gradePoint;
                        ss.ignore();

                        cout << subjectName << "\t\t" << credit << "\t" << marks << "\t" << gradePoint << endl;
                    }
                    cout << "------------------------------------------------\n";
                }
                break; // Exit loop if student is found
            }
        }

        if (!found)
        {
            cout << "Student ID not found.\n";
        }
        readStudents.close(); // Close the file

        // Prompt user to press Enter to return to the main menu
        cout << "\nPress Enter to return to the main menu...";
        cin.ignore(); // To consume any leftover newline character
        cin.get();    // Wait for the user to press Enter
        system("cls");
    }
};

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
    Students student;
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
            cout << "__________________________________________________________________\n";
            cout << "|                    Register New Student Page                    |\n";
            cout << "|_________________________________________________________________|\n\n";
            student.registerStudent();
            break;
        case 2:
            system("cls");
            student.individualResult();
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