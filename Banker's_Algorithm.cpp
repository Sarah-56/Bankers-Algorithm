#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

int n, m; //n is the number of processes & m is the number of resources type
vector <int> available; //of size m
vector <vector <int>> max_;
vector <vector <int>> allocation;
vector <vector <int>> need;
vector <int> request;
int in;
int choice;
int process;
int x;
int y;
int z;



void input();
void calNeed();
bool isSafe();
bool isGranted();
void asBefore();


int main()
{
    do {
        input();
        calNeed();
        cout << "1: Safe state check\n2: Request Resources\nChoose a number: ";
        cin >> choice;
        cout << "\n";
        while (choice < 1 || choice > 2) {
            cout << "Choose 1 or 2 only: ";
            cin >> choice;
            cout << "\n";
        }

        switch (choice)
        {
        case 1:
            isSafe();
            cout << "Request Resources ? Yes: 1, No: 0\n";
            cin >> z;
            cout << "\n";
            while (z < 0 || z > 1) {
                cout << "Choose 0 or 1 only: ";
                cin >> z;
                cout << "\n";
            }
            if (z == 0) {
                break;
            }
            else {
                choice = 2;
            }
        case 2:
            do {
                cout << "The request is from process: ";
                cin >> process;
                cout << "\n";
                while (process < 0 || process > 4) {
                    cout << "Choose a number from 0 to " << n << ": ";
                    cin >> process;
                    cout << "\n";
                }
                cout << "Enter the request vector of P" << process << ":\n";
                for (int i = 0; i < m; i++) {
                    cin >> in;
                    request.push_back(in);
                }
                isGranted();
                
                cout << "Make another request ? Yes: 1, No:0\n";
                cin >> x;
                cout << "\n";
                while (x < 0 || x > 1) {
                    cout << "Choose 0 or 1 only: ";
                    cin >> x;
                    cout << "\n";
                }
                if (x == 0)
                    break;
            } while (1);
            break;
        }
        cout << "1: Enter new input\n2: Exit\nChoose a number: ";
        cin >> y;
        cout << "\n";
        while (y < 1 || y > 2) {
            cout << "Choose 1 or 2 only: ";
            cin >> y;
            cout << "\n";
        }
        if (y == 2) {
            system("pause");
            return 0;
        }
        allocation.clear();
        max_.clear();
        need.clear();
        available.clear();
        system("CLS");
    } while (1);
    return 0;
}


//Takes the number of processes, resources types, allocation matrix, max matrix and available vector
void input() {
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "\n" << "Enter number of resources types: ";
    cin >> m;
    cout << "\n" << "Enter the allocated resources: " << "\n";
    for (int i = 0; i < n; i++) {
        vector<int> row;
        cout << "P" << i << " ";
        for (int j = 0; j < m; j++) {
            cin >> in;
            row.push_back(in);
        }
        allocation.push_back(row);
    }
    cout << "\n" << "Enter the max resources: " << "\n";
    for (int i = 0; i < n; i++) {
        vector<int> row;
        cout << "P" << i << " ";
        for (int j = 0; j < m; j++) {
            cin >> in;
            row.push_back(in);
        }
        max_.push_back(row);
    }
    int error = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (allocation[i][j] > max_[i][j]) {
                error = 1;
            }
        }
    }
    cout << "\n" << "Enter the available resources: " << "\n";
    for (int i = 0; i < m; i++) {
        cin >> in;
        available.push_back(in);
    }
    cout << "\n";
    
}
// Calculate need matrix need = max - allocation and print it
void calNeed() {
    cout << "The need matrix is: \n     ";
    for (int i = 0; i < m; i++) {
        cout << "R" << i << "   ";
    }
    cout << "\n";
    for (int i = 0; i < n; i++) {
        vector<int> row;
        cout << "P" << i << "   ";
        for (int j = 0; j < m; j++) {
            in = max_[i][j] - allocation[i][j];
            row.push_back(in);
            cout << row[j] << "    ";
        }
        need.push_back(row);
        cout << "\n";
    }
}

bool isSafe() {
    //Initialization
    vector <int> work; //of size m
    vector <bool> finish; //of size n 
    vector <int> answer(n, 0); //of size n
    int index = 0;
    for (int i = 0; i < m; i++) {
        work.push_back(available[i]);
    }
    for (int i = 0; i < n; i++) {
        finish.push_back(false);
    }
    //safe algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (finish[i] == false) {

                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    answer.insert(answer.begin() + index, i);
                    index++;
                    for (int y = 0; y < m; y++)
                        work[y] += allocation[i][y];
                    finish[i] = true;
                }
            }
        }
    }
    //print the safe sequence 
    for (int i = 0; i < n; i++) {
        if (finish[i] == true) {
            if (choice == 1) {
                cout << "YES, Safe state <P" << answer[0] <<",";
                for (int i = 1; i < n - 1; i++)
                    cout << " P" << answer[i] << ",";
                cout << " P" << answer[n - 1] << ">\n";
            }
            else if (choice == 2) {
                cout << "YES, Safe state <P" << process << "req,";
                for (int i = 0; i < n - 1; i++)
                    cout << " P" << answer[i] << ",";
                cout << " P" << answer[n - 1] << ">\n";
                
            }
            
            return true;
        }
            
    }
    
    cout << "NO\n";
    return false;
}
bool isGranted() {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            cout << "NO\nError! process has exceeded it's maximum claim.\n";
            request.clear();
            return false;
        }
    }
    for (int i = 0; i < m; i++) {
        if (request[i] > available[i]) {
            cout << "NO\nResources are not available.\n";
            request.clear();
            return false;
        }
    }
    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }
    isSafe();
    asBefore();
    return true;
}
void asBefore() {
    for (int i = 0; i < m; i++) {
        available[i] += request[i];
        allocation[process][i] -= request[i];
        need[process][i] += request[i];
    }
    request.clear();
}