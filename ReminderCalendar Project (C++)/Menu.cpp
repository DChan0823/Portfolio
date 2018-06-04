#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::start() {
	int choice;

	cout << "MENU\n1. Create New Event\n2. Edit Saved Event\n3. Delete Saved Event\n4. Quit\n";

	if (choice == 1) {
		string title, description;
		int hour, minute, month, day, year;

		cout << "Enter title: ";
		cin >> title;
		cout << "\nEnter description: ";
		cin >> description;
		cout << "\nEnter hour: ";
		cin >> hour;
		cout << "\nEnter minute: ";
		cin >> minute;
		cout << "\nEnter month: ";
		cin >> month;
		cout << "\nEnter day: ";
		cin >> day;
		cout << "\nEnter year: ";
		cin >> year;

		container.input(title, description, hour, minute, month, day, year);
	}
	else if (choice == 2) {
		string title4edit;
		Event *event4edit;
		int choice2;

		cout << "\nWhat is title of event to edit?\n";
		cin >> title4edit;

		event4edit = container.search(title4edit);

		if (event4edit == NULL) {
			cout << "CANNOT FIND EVENT WITH THAT TITLE" << endl;
		}
		else {
			cout << "1. Edit Title\n2. Edit Description\n3. Edit Date\n";
			cin >> choice2;

			if (choice2 == 1) {
				string newTitle;

				cout << "\nNew Title: ";
				cin >> newTitle;

				event4edit->editTitle(newTitle);
			}
			else if (choice2 == 2) {
				string newDescript;

				cout << "\nNew Description: ";
				cin >> newDescript;

				event4edit->editDescript(newDescript);
			}
			else {
				int newHour, newMinute, newMonth, newDay, newYear;

				cout << "\nEnter hour: ";
				cin >> newHour;
				cout << "\nEnter minute: ";
				cin >> newMinute;
				cout << "\nEnter month: ";
				cin >> newMonth;
				cout << "\nEnter day: ";
				cin >> newDay;
				cout << "\nEnter year: ";
				cin >> newYear;

				event4edit->editDate(newDay, MONTH(newMonth), newYear, newHour, newMinute);
			}
		}
	}
	else if(choice == 3) {
		string title4edit;
		Event *event4edit;
		int choice2;

		cout << "\nWhat is title of event to delete?\n";
		cin >> title4edit;

		container.delete(title4edit);
	}
	else {

	}
}
