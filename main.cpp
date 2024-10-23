#include <iostream>
#include <string>
#include <fstream>
#include <sstream> // For stringstream
#include <iomanip> // For formatting decimal points
using namespace std;

// Forward Declarations
void registration();
void forgotPassword();
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
    // Function to calculate CGPA
    float calculateCGPA(float sGPA[], int completedSemesters)
    {
        float totalSGPA = 0.0;
        for (int i = 0; i < completedSemesters; i++)
        {
            totalSGPA = totalSGPA + sGPA[i];
        }
        if (completedSemesters > 0)
        {
            return totalSGPA / completedSemesters;
        }
        else
        {
            return 0.0; // Return 0 if no semesters completed
        }
    }
    // Function to convert marks to grade point
    float getGradePoint(float marks)
    {
        if (marks >= 80.0)
            return 4.00;
        else if (marks >= 75.0)
            return 3.75;
        else if (marks >= 70.0)
            return 3.50;
        else if (marks >= 65.0)
            return 3.25;
        else if (marks >= 60.0)
            return 3.00;
        else if (marks >= 55.0)
            return 2.75;
        else if (marks >= 50.0)
            return 2.50;
        else if (marks >= 45.0)
            return 2.25;
        else if (marks >= 40.0)
            return 2.00;
        else
            return 0.00;
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
        // Sequential Flow Operations
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
                totalCredits = totalCredits + credit;
                totalGradePoints = totalGradePoints + credit * gradePoint;
            }
            // sGPA is an array that stores the SGPA values for each semester
            sGPA[completedSemesters] = calculateSGPA(totalCredits, totalGradePoints); // Calculate SGPA for the current semester
            completedSemesters++;                                                     // Increment completed semesters
        }
        studentsWrite << endl;
        studentsWrite.close();
        // Calculate CGPA
        float cgpa = calculateCGPA(sGPA, completedSemesters);
        system("cls");
        cout << endl;
        cout << "|******************************************************************|\n";
        cout << "|    Registration successful! Student details have been saved.     |\n";
        cout << "     *Current Semester SGPA: " << sGPA[completedSemesters - 1] << " \n";
        cout << "     *CGPA: " << cgpa << "                                          \n";
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
                // Calculate CGPA using the existing function
                float CGPA = calculateCGPA(tempSGPA, tempCompletedSemesters);
                cout << "\nCGPA: " << CGPA << endl
                     << endl;
                // Display SGPA values
                cout << "Number of Semesters Completed: " << tempCompletedSemesters << endl;
                for (int i = 0; i < tempCompletedSemesters; i++)
                {
                    cout << "SGPA for Semester " << i + 1 << ": " << tempSGPA[i] << endl;
                }
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
    }

    // Function to display all student result
    void displayAllStudent()
    {
        ifstream readStudents("students.txt");
        if (!readStudents)
        {
            cout << "Error: Unable to open the file!\n";
            return;
        }
        cout << "______________________________________________________________________\n";
        cout << "|                      All Student Records                            |\n";
        cout << "|---------------------------------------------------------------------|\n";
        cout << "| Name                   | ID           | Semesters Completed  | CGPA |\n";
        cout << "|------------------------|--------------|----------------------|------|\n";
        string line;
        while (getline(readStudents, line)) // Read the entire line
        {
            if (line != "") // Check if the line is not empty
            {
                stringstream ss(line); // Create a stringstream
                string name, id;
                int completedSemesters;
                float sGPA[8];
                getline(ss, name, '|');   // Read name
                getline(ss, id, '|');     // Read ID
                ss >> completedSemesters; // Read completed semesters
                ss.ignore();              // Ignore the delimiter after semesters
                float totalSGPA = 0;
                for (int i = 0; i < completedSemesters; i++)
                {
                    ss >> sGPA[i];
                    ss.ignore();                     // Ignore delimiter after each SGPA value
                    totalSGPA = totalSGPA + sGPA[i]; // Add SGPA for CGPA calculation
                }
                float CGPA;
                if (completedSemesters > 0)
                {
                    CGPA = totalSGPA / completedSemesters; // Calculate CGPA when there are completed semesters
                }
                else
                {
                    CGPA = 0.0; // Set CGPA to 0 if no semesters are completed
                }
                // Display the student's information with formatted output
                cout << "| " << setw(23) << left << name               // Align name to the left with a width of 22
                     << "| " << setw(13) << left << id                 // Align ID to the left with a width of 12
                     << "| " << setw(21) << left << completedSemesters // Align completed semesters
                     << "| " << fixed << setprecision(2) << CGPA       // Fixed precision for CGPA
                     << " |\n";                                        // Display CGPA
            }
        }
        cout << "|---------------------------------------------------------------------|\n";
        readStudents.close(); // Close the file
    }
};

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
        system("cls");
        cout << "\n|******************************************************************|\n";
        cout << "|                           Login Successful!                      |\n";
        cout << "|******************************************************************|\n\n";

        // Call manageStudents function after successful login
        manageStudents();
    }
    else
    {
        cout << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
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
            student.registerStudent();
            break;
        case 2:
            system("cls");
            student.individualResult();
            break;
        case 3:
            system("cls");
            student.displayAllStudent();
            break;
        case 4:
            system("cls");
            // modifyStudent();
            break;
        case 5:
            system("cls");
            // student.deleteStudent();
            break;
        case 6:
            system("cls");
            cout << "|******************************************************************|\n";
            cout << "|                          Logging out.                            |\n";
            cout << "|******************************************************************|\n\n";
            return; // Return to the main menu
        default:
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
            cout << "!               Invalid choice. Please try again.                  !\n";
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        }
    }
}