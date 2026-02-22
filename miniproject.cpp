#include <iostream>
using namespace std;

struct Expense
{
	char date[12];
	char category[20];
	double amount;
	char note[64];
};

const int MAX_EXPENSES = 1000;
Expense expenses[MAX_EXPENSES];
int expense_count = 0;

double cat_totals[4] = {0.0, 0.0, 0.0, 0.0};

void print_amount(double v)
{
	if (v < 0)
	{
		cout << '-';
		v = -v;
	}
	long long cents = (long long)(v * 100.0 + 0.5);
	cout << (cents / 100) << '.';
	int rem = (int)(cents % 100);
	if (rem < 10)
		cout << '0';
	cout << rem;
}

int category_index_from_choice(int choice)
{
	if (choice == 1)
		return 0;
	if (choice == 2)
		return 1;
	if (choice == 3)
		return 2;
	return 3;
}

void add_expense()
{
	if (expense_count >= MAX_EXPENSES)
	{
		cout << "Storage full.\n";
		return;
	}
	Expense &e = expenses[expense_count];
	cout << "Enter amount (e.g. 12.50): ";
	double amt = 0.0;
	if (!(cin >> amt))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid amount.\n";
		return;
	}
	e.amount = amt;
	cin.ignore(1000, '\n');

	cout << "Choose category: 1) food 2) travel 3) shopping 4) other\n";
	cout << "Enter choice (1-4): ";
	int c = 4;
	if (!(cin >> c))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		c = 4;
	}
	cin.ignore(1000, '\n');
	int idx = category_index_from_choice(c);
	if (idx == 0)
		strcpy(e.category, "food");
	else if (idx == 1)
		strcpy(e.category, "travel");
	else if (idx == 2)
		strcpy(e.category, "shopping");
	else
	{
		cout << "Enter category name (max 19 chars): ";
		cin.getline(e.category, sizeof(e.category));
		if (e.category[0] == '\0')
			strcpy(e.category, "other");
	}

	cout << "Enter note (optional, up to 63 chars): ";
	cin.getline(e.note, sizeof(e.note));

	cout << "Enter date (YYYY-MM-DD) or leave empty: ";
	cin.getline(e.date, sizeof(e.date));
	if (e.date[0] == '\0')
		strcpy(e.date, "-");

	cat_totals[idx] += e.amount;
	expense_count++;
	cout << "Added ";
	print_amount(e.amount);
	cout << " to " << e.category << " on " << e.date << "\n";
}

void show_totals()
{
	double total = 0.0;
	for (int i = 0; i < 4; ++i)
		total += cat_totals[i];
	cout << "\nTotal spending: ";
	print_amount(total);
	cout << "\n";
	cout << "By category:\n";
	cout << "  food     : ";
	print_amount(cat_totals[0]);
	cout << "\n";
	cout << "  travel   : ";
	print_amount(cat_totals[1]);
	cout << "\n";
	cout << "  shopping : ";
	print_amount(cat_totals[2]);
	cout << "\n";
	cout << "  other    : ";
	print_amount(cat_totals[3]);
	cout << "\n\n";
}

void list_expenses()
{
	cout << "\nAll expenses:\n";
	if (expense_count == 0)
	{
		cout << "  (none)\n\n";
		return;
	}
	for (int i = 0; i < expense_count; ++i)
	{
		Expense &e = expenses[i];
		cout << i + 1 << ") " << e.date << " " << e.category << " ";
		print_amount(e.amount);
		if (e.note[0] != '\0')
			cout << "  - " << e.note;
		cout << "\n";
	}
	cout << "\n";
}

int main()
{
	cout << "Simple Expense Tracker (iostream only)\n";
	while (true)
	{
		cout << "\nMenu:\n";
		cout << " 1) Add expense\n";
		cout << " 2) Show totals\n";
		cout << " 3) List all expenses\n";
		cout << " 0) Exit\n";
		cout << "Choose: ";
		int choice = -1;
		if (!(cin >> choice))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input\n";
			continue;
		}
		cin.ignore(1000, '\n');
		if (choice == 0)
		{
			cout << "Exiting.\n";
			break;
		}
		else if (choice == 1)
			add_expense();
		else if (choice == 2)
			show_totals();
		else if (choice == 3)
			list_expenses();
		else
			cout << "Unknown choice.\n";
	}
	return 0;
}