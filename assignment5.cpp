// ============================================================
// Name    : Sunny Rodrigues
// Course  : COSC 1437 - Programming Fundamentals II
// Date    : June 11, 2026
// Program : Chapter 5 Major Project
// Option  : A - Cookie Sales Tracker
// Purpose : Processes volunteer cookie sales data from a file,
// that calculates totals, averages, revenue, and top sellers.
// ============================================================

/*
============================================================
    SECTION 1: Pseudocode Design Block
============================================================

1. Open input file and output file.
2. If input file fails to open:
    Display error
    End program

3. Display success message

4. COUNTER-CONTROLLED LOOP
    Read cost per box
    Retry up to 3 times if cost <= 0

5. Print report header

6. EOF-CONTROLLED LOOP
    Read volunteer name and boxes sold until EOF

    IF boxes sold < MIN_VALID_BOXES
            Display warning
            continue
      ELSE
            Process record

      Accumulate:
            total volunteers
            total boxes
            total revenue

      Track maximum boxes sold

7. FLAG-CONTROLLED LOOP
    Scan stored data
    Determine top seller(s)

8. IF volunteer count > 0
      Calculate average
   ELSE
      Average = 0

9. FOR LOOP
    Print divider lines

10. BREAK DEMONSTRATION
    Verification loop
    Exit once sanity check passes

11. Display report summary

12. DO-WHILE LOOP
    Ask user if another file should be processed
    Continue asking until Y/N entered

13. End program

Loop Types:
a. Counter-controlled loop:
    Retry reading cost up to 3 attempts.
b. EOF-controlled loop:
    Process records until end of file.
c. Flag-controlled loop:
    Search for top seller(s).
d. For loop:
    Print divider lines.
e. Do-while loop:
    Validate Y/N response.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

int main()
{

// NAMED CONSTANTS
    const int MAX_RETRIES = 3;
    const int DIVIDER_LENGTH = 50;
    const int MIN_VALID_BOXES = 1;
    const double MIN_COST = 0.0;

// ============================================================
// Section 2: INPUT & VALIDATION
// ============================================================

    ifstream inFile("ch5_sales.txt");
    ofstream outFile("ch5_report.txt");

    if (!inFile)
    {
    cout << "ERROR: Unable to open ch5_sales.txt" << endl;
    return 1;
    }

    if (!outFile)
    {
    cout << "ERROR: Unable to create ch5_report.txt" << endl;
    return 1;
    }

    cout << "Input and output files opened successfully."
         << endl;

// ============================================================
// Section 3: LOOP TYPE SHOWCASE
// Counter-Controlled Loop
// ============================================================

    double costPerBox = 0.0;
    int attempts = 0;

    while (attempts < MAX_RETRIES && costPerBox <= MIN_COST)
    {
        inFile >> costPerBox;
        attempts++;
    }

    if (costPerBox <= MIN_COST)
    {
        cout << "Invalid cost per box." << endl;
        return 1;
    }

    vector<string> volunteerNames;
    vector<int> volunteerBoxes;

    string volunteerName;
    int boxesSold;

    int totalBoxes = 0;
    int volunteerCount = 0;

    double totalRevenue = 0.0;

    int maxBoxes = 0;

    outFile << fixed << setprecision(2);

// ============================================================
// Section 3: LOOP TYPE SHOWCASE
// For Loop
// ============================================================

    for (int i = 0; i < DIVIDER_LENGTH; i++)
        outFile << "-";

    outFile << endl;

    outFile << left
            << setw(20) << "Volunteer"
            << right
            << setw(10) << "Boxes Sold"
            << endl;

    for (int i = 0; i < DIVIDER_LENGTH; i++)
        outFile << "-";

    outFile << endl;

// ============================================================
// Section 4: CORE LOOP LOGIC
// EOF-Controlled Loop
// ============================================================

    while (inFile >> volunteerName >> boxesSold)
    {
// ============================================================
// Section 6: BREAK AND CONTINUE DEMONSTRATION
// Continue Statement
// ============================================================

        if (boxesSold < MIN_VALID_BOXES)
        {
            cout << "Skipping invalid record for "
                << volunteerName << endl;
            continue;
        }

        volunteerNames.push_back(volunteerName);
        volunteerBoxes.push_back(boxesSold);

        volunteerCount++;
        totalBoxes += boxesSold;

        totalRevenue += boxesSold * costPerBox;

        if (boxesSold > maxBoxes)
            maxBoxes = boxesSold;

        outFile << left
                << setw(20) << volunteerName
                << right
                << setw(10) << boxesSold
                << endl;

// ============================================================
// Section 5: NESTED CONTROL STRUCTURES
// ============================================================

        /*
        Skeleton code for daily totals verification.

        int dailyTotal = 0;
        int daySales;

        while(daySales != -999)
        {
            dailyTotal += daySales;
        }

        if(dailyTotal != boxesSold)
        {
            outFile << "Discrepancy found";
        }
        */
    }

// ============================================================
// Section 3: LOOP TYPE SHOWCASE
// Flag-Controlled Loop
// ============================================================
    bool foundTopSeller = false;

    vector<string> topSellers;

    size_t index = 0;

    while (index < volunteerBoxes.size())
    {
        foundTopSeller = false;

        if (volunteerBoxes[index] == maxBoxes)
        {
            foundTopSeller = true;
        }

        if (foundTopSeller)
        {
            topSellers.push_back(volunteerNames[index]);
        }

        index++;
    }

    double averageBoxes = 0.0;

    if (volunteerCount > 0)
    {
        averageBoxes =
            static_cast<double>(totalBoxes)
            / volunteerCount;
    }

// ============================================================
// Section 6: BREAK AND CONTINUE DEMONSTRATION
// Break Statement
// ============================================================

    while (true)
    {
        if (totalRevenue > 0)
        {
            break;
        }
    }

// ============================================================
// Section 9: FORMATTED OUTPUT
// ============================================================

    for (int i = 0; i < DIVIDER_LENGTH; i++)
        outFile << "-";

    outFile << endl;

    outFile << "Total Volunteers: "
            << volunteerCount << endl;

    outFile << "Total Boxes Sold: "
            << totalBoxes << endl;

    outFile << "Total Revenue: $"
            << totalRevenue << endl;

    outFile << "Average Boxes: "
            << averageBoxes << endl;

    outFile << endl;
    outFile << "Top Seller(s): ";

    for (size_t i = 0; i < topSellers.size(); i++)
    {
        outFile << topSellers[i];

        if (i < topSellers.size() - 1)
            outFile << ", ";
    }

    outFile << endl;

    for (int i = 0; i < DIVIDER_LENGTH; i++)
        outFile << "-";

    outFile << endl;

    inFile.close();
    outFile.close();

// ============================================================
//  SECTION 7: DO-WHILE INPUT VALIDATION
// ============================================================

    char answer;

    do
    {
        cout << "\nProcess another file? (Y/N): ";
        cin >> answer;

    } while (answer != 'Y' &&
             answer != 'y' &&
             answer != 'N' &&
             answer != 'n');

    if (answer == 'Y' || answer == 'y')
    {
        cout << "Program would restart here."
             << endl;
    }
    else
    {
        cout << "Thank you for using the Cookie "
             << "Sales Tracker." << endl;
    }

    return 0;
}

/*
============================================================
Section 8: BUG AVOIDANCE LOG
============================================================

1. Off-by-one Error
   The divider-line for loop prints exactly
   50 dashes using:
   for (int i = 0; i < 50; i++)

2. Infinite Loop Prevention
   The EOF-controlled loop terminates when
   file input fails at end-of-file.

3. Division by Zero
   Average boxes sold is calculated only when
   volunteerCount > 0.

4. Software Patches
   Instead of patching incorrect averages,
   the root cause was fixed by validating
   volunteerCount before division.

5. Semicolon After Loop Header
   Accidentally writing:
   while (inFile >> volunteerName >> boxesSold);

   would create an empty loop and prevent
   records from being processed correctly.
============================================================
*/