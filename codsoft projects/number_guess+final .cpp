#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int randomNumberGenerator(int start, int end) {
    return rand() % (end - start + 1) + start;
}

void numberGuessingGame() {
    int attempts = 5;
    int start = 1;
    int end = 100;
    int target;

    int randomNumber = randomNumberGenerator(start, end);

    cout << "\n=============================================\n";
    cout << "🎮  WELCOME TO THE NUMBER GUESSING GAME  🎯\n";
    cout << "=============================================\n";
    cout << "🔢 Range: " << start << " to " << end << "\n";
    cout << "❤️ You have " << attempts << " attempts to guess the number!\n";
    cout << "=============================================\n\n";

    while (attempts) {
        cout << "👉 Enter your guess: ";
        cin >> target;

        if (target == randomNumber) {
            cout << "\n✅✅✅----------------------------------✅✅✅\n";
            cout << "🎉 HURRAY! You guessed it right!\n";
            cout << "🎯 The number was: " << randomNumber << "\n";
            cout << "✅✅✅----------------------------------✅✅✅\n\n";
            return;
        } else if (target > randomNumber && attempts > 1) {
            cout << "📉 Too High! Try a smaller number.\n";
        } else if (target < randomNumber && attempts > 1) {
            cout << "📈 Too Low! Try a larger number.\n";
        }

        attempts--;
        if (attempts > 0) {
            cout << "⏳ Remaining Attempts: " << attempts << "\n\n";
        }
    }

    cout << "\n❌❌❌----------------------------------❌❌❌\n";
    cout << "😢 Oops! You've used all your attempts.\n";
    cout << "🎯 The correct number was: " << randomNumber << "\n";
    cout << "❌❌❌----------------------------------❌❌❌\n\n";
}

int main() {
    srand(time(0));
    int choice;

    do {
        cout << "=============================================\n";
        cout << "📋 MENU:\n";
        cout << "1️⃣  Start Game\n";
        cout << "2️⃣  Exit\n";
        cout << "=============================================\n";
        cout << "👉 Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                numberGuessingGame();
                break;
            case 2:
                cout << "👋 Exiting the game. See you soon!\n";
                break;
            default:
                cout << "❌ Invalid choice! Please enter 1 or 2.\n";
        }

        if (choice == 1) {
            char again;
            cout << "🔁 Do you want to play again? (y/n): ";
            cin >> again;
            if (again == 'y' || again == 'Y') {
                choice = 1;
            } else {
                cout << "👋 Thanks for playing! Goodbye!\n";
                break;
            }
        }

    } while (choice != 2);

    return 0;
}
