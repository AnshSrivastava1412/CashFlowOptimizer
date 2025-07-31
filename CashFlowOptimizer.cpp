#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Structure for a person and the amount owed/owed to
struct Person {
    int id;
    int amount;
    Person(int id, int amount) : id(id), amount(amount) {}
};

// Comparator for max-heap based on amount
struct Compare {
    bool operator()(Person const& p1, Person const& p2) {
        return p1.amount < p2.amount; // max heap, biggest amount first
    }
};

// Function to minimize cash flow among friends
void minimizeCashFlow(int amount[], int n) {
    priority_queue<Person, vector<Person>, Compare> creditors;
    priority_queue<Person, vector<Person>, Compare> debtors;

    for (int i = 0; i < n; i++) {
        if (amount[i] > 0)
            creditors.push(Person(i, amount[i]));
        else if (amount[i] < 0)
            debtors.push(Person(i, -amount[i]));
    }

    while (!creditors.empty() && !debtors.empty()) {
        Person creditor = creditors.top();
        Person debtor = debtors.top();

        creditors.pop();
        debtors.pop();

        int minAmount = min(creditor.amount, debtor.amount);

        cout << "Person " << debtor.id << " pays " << minAmount << " to Person " << creditor.id << endl;

        creditor.amount -= minAmount;
        debtor.amount -= minAmount;

        if (creditor.amount > 0)
            creditors.push(creditor);
        if (debtor.amount > 0)
            debtors.push(debtor);
    }
}

int main() {
    // Number of friends
    int n;
    cout << "Enter number of people: ";
    cin >> n;

    // Transactions: For simplicity, we read net amounts for each person
    // Positive amount means that person should receive money, negative means person owes money
    int amount[n];
    cout << "Enter net amounts (-ve means owes money, +ve means to receive money) for each person: " << endl;

    for (int i = 0; i < n; i++) {
        cout << "Person " << i << ": ";
        cin >> amount[i];
    }

    cout << "\nOptimized minimal transactions:\n";
    minimizeCashFlow(amount, n);

    return 0;
}
