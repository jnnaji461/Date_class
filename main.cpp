/*
Program name:
Author:
Date:
Purpose:
*/

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Date {
private:
    int month;
    int day;
    int year;

    // Helper method to return the number of days in a given month
    int daysInMonth(int m) const {
        switch (m) {
        case 2: return 28; // ignoring leap years
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
        }
    }

    // Helper method to return month name
    string monthName(int m) const {
        const string names[] = { "January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December" };
        return names[m - 1];
    }

public:
    // 3-parameter constructor - throws invalid_argument for invalid values
    Date(int m, int d, int y) {
        // Validate month
        if (m < 1 || m > 12) {
            throw invalid_argument("There are only 12 months in the year");
        }

        // Validate year
        if (y < 1900 || y > 2020) {
            throw invalid_argument("The year must be between 1900 and 2020");
        }

        // Validate day based on month
        int maxDay = daysInMonth(m);
        if (d < 1 || d > maxDay) {
            throw invalid_argument("Invalid Value - there are only " + to_string(maxDay) +
                " days in " + monthName(m));
        }

        month = m;
        day = d;
        year = y;
    }

    // Mutator methods that also throw exceptions for invalid parameters
    void setMonth(int m) {
        if (m < 1 || m > 12) {
            throw invalid_argument("There are only 12 months in the year");
        }
        month = m;
    }

    void setDay(int d) {
        int maxDay = daysInMonth(month);
        if (d < 1 || d > maxDay) {
            throw invalid_argument("Invalid Value - there are only " + to_string(maxDay) +
                " days in " + monthName(month));
        }
        day = d;
    }

    void setYear(int y) {
        if (y < 1900 || y > 2020) {
            throw invalid_argument("The year must be between 1900 and 2020");
        }
        year = y;
    }

    // toString method that returns date in "Month DD, YYYY" format
    string toString() const {
        return monthName(month) + " " + to_string(day) + ", " + to_string(year);
    }
};

// Function to get validated integer input with error handling
int getValidatedInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear(); // Clear error flags
            cin.ignore(10000, '\n'); // Clear the input buffer
            cout << "Invalid input. Please enter a numeric value.\n";
        }
        else {
            cin.ignore(10000, '\n'); // Clear any extra input including newline
            return value;
        }
    }
}

int main() {
    cout << "=== Date Creation Program ===" << endl;

    // Create initial date with exception handling
    Date* userDate = nullptr;
    bool dateCreated = false;

    while (!dateCreated) {
        try {
            cout << "\nPlease enter initial date values:" << endl;
            int month = getValidatedInt("Enter month (1-12): ");
            int day = getValidatedInt("Enter day: ");
            int year = getValidatedInt("Enter year (1900-2020): ");

            userDate = new Date(month, day, year);
            dateCreated = true;
            cout << "Date created successfully: " << userDate->toString() << endl;

        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            cout << "Please try again." << endl;
        }
    }

    // Demonstrate changing month with exception handling
    cout << "\n--- Change the Month ---" << endl;
    bool monthUpdated = false;
    while (!monthUpdated) {
        try {
            int newMonth = getValidatedInt("Enter new month (1-12): ");
            userDate->setMonth(newMonth);
            monthUpdated = true;
            cout << "Month updated successfully: " << userDate->toString() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            cout << "Please try again." << endl;
        }
    }

    // Demonstrate changing day with exception handling
    cout << "\n--- Change the Day ---" << endl;
    bool dayUpdated = false;
    while (!dayUpdated) {
        try {
            int newDay = getValidatedInt("Enter new day: ");
            userDate->setDay(newDay);
            dayUpdated = true;
            cout << "Day updated successfully: " << userDate->toString() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            cout << "Please try again." << endl;
        }
    }

    // Demonstrate changing year with exception handling
    cout << "\n--- Change the Year ---" << endl;
    bool yearUpdated = false;
    while (!yearUpdated) {
        try {
            int newYear = getValidatedInt("Enter new year (1900-2020): ");
            userDate->setYear(newYear);
            yearUpdated = true;
            cout << "Year updated successfully: " << userDate->toString() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            cout << "Please try again." << endl;
        }
    }

    // Final display
    cout << "\n=== Final Date ===" << endl;
    cout << "Your final date is: " << userDate->toString() << endl;

    delete userDate;
    return 0;
}
