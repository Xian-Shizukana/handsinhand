#include <iostream>
#include <queue>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// In general: num = rand() % (how many numbers included in range) + (lowest number in the range)

int startingMenu();
void generateNewGame();
void displayCard(string card, char color = 'w');
void clearScreen();
void shoppingPhase();
void pickingPhase();
void listCards(vector<int> alreadyChosenCards, char cardsToDisplay);
void pressToContinue();
void arrangingPhase();
void arrangeEnemyHand();
void battlingPhase();
char didPlayerCardWin(char pCardType, char eCardType);
bool validateLoadFile();
string generateCard(int range, int lowest, int specialEffectChance = 0);

struct entityInfo{
    int hp;
    int gold;
    vector<string> hand;
    vector<string> deck;
    queue<string> handOrder;
} player, enemy;

struct gameInfo{
    int score;
    int level;
} game;

int main(){

    srand(time(0));
    bool skipToShop = false;

    while(true){
        switch(startingMenu()){
            case 1:
                clearScreen();
                generateNewGame();
                break;
            case 2:
                // if (validateLoadFile()) skipToShop = true;
                break;
            case 3:
                cout << "Exiting the game. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                clearScreen();
                continue;
        }

        clearScreen();
        break;
    }

    while(true){
        switch(skipToShop){
            case false:
                pickingPhase();
                cout << "Picking phase done.\n";
                while (player.hp > 0 || enemy.hp > 0){
                    arrangingPhase();
                    battlingPhase();
                }
            case true:
                // autoSave();
                // shoppingPhase();
                skipToShop = false;
                break;
        }
    }


    return 0;
}

int startingMenu(){
    int choice;
    cout << "HANDS IN HAND" << endl;
    cout << "1. Start New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Exit" << endl;
    cout << "Please enter your choice: ";
    cin >> choice;

    return choice;
}

void listCards(vector<int> alreadyChosenCards, char cardsToList){
    // Makes function reusable by allowing it to display
    // either the player's deck or the player's hand.
    vector<string> cards;
    if(cardsToList == 'd'){
        cards = player.deck;
    } else {
        cards = player.hand;
    }

    int counter = 0;

    for(string card : cards){

        cout << "\033[0m";
        for (int chosen : alreadyChosenCards){
            if (counter == chosen){
                cout << "\033[31m";
                break;
            }
        }

        string cardStats = to_string(counter) + " - ";
        string cardDamage;
        char cardType = card[0];
        char cardEffect = card[1];

        switch(cardType){
            case 'r':
                cardStats += "Rock - ";
                break;
            case 'p':
                cardStats += "Paper - ";
                break;
            case 's':
                cardStats += "Scissors - ";
                break;
        }

        for (int i = 2; i < card.length(); i ++){
            cardDamage += card[i];
        }
        cardStats += cardDamage + " Damage ";

        switch(cardEffect){
            case 'n':
                cardStats += "\n";
                break;
            case 'h':
                cardStats += "(Healing)\n";
                break;
        }

        cout << cardStats;
        counter += 1;
        cout << "\033[0m";
    }
}

void pickingPhase(){
    vector<int> counter;
    int choice;
    bool alreadyChosen;

    while(counter.size() < 5){
        alreadyChosen = false;
        clearScreen();
        listCards(counter, 'd');

        cout << "-----------------------------\n";
        cout << "Choose 5 cards from your deck (Current Hand Size: " << counter.size() << "/5): ";

        cin >> choice;

        // Shows an error if the choice isn't a number or outside of the
        // deck range.
        if (cin.fail() || choice < 0 || choice >= size(player.deck)){
            // cin.clear() fixes the error state of cin
            cin.clear();
            cout << "Invalid input.\n";
            pressToContinue();
            continue;
        }

        // If card is already chosen, throw an error
        for (int c : counter){
            if (c == choice){
                alreadyChosen = true;
                break;
            }
        }
        if (alreadyChosen) {
            cout << "Already chosen.\n";
            pressToContinue();
            continue;
        } else {
            // Add the card into the player's hand, and put
            // the card's index into the counter.
            player.hand.push_back(player.deck[choice]) ;
            displayCard(player.hand[counter.size()], 'b');
            counter.push_back(choice);
            pressToContinue();
        }
    }
}

void arrangingPhase(){
    vector<int> counter;
    int choice;
    bool alreadyChosen;

    arrangeEnemyHand();

    while(counter.size() < 5){
        alreadyChosen = false;
        clearScreen();
        listCards(counter, 'h');

        cout << "-----------------------------\n";
        cout << "Choose 5 cards from your hand ( Current Order: ";
        for (int cardNum : counter){
            cout << to_string(cardNum) << " ";
        }
        cout << ")\n";

        cin >> choice;

        // Shows an error if the choice isn't a number or outside of the
        // deck range.
        if (cin.fail() || choice < 0 || choice >= player.hand.size()){
            // cin.clear() fixes the error state of cin
            cin.clear();
            cout << "Invalid input.\n";
            pressToContinue();
            continue;
        }

        // If card is already chosen, throw an error
        for (int c : counter){
            if (c == choice){
                alreadyChosen = true;
                break;
            }
        }
        if (alreadyChosen) {
            cout << "Already chosen.\n";
            pressToContinue();
            continue;
        } else {
            // Add the card into the player's queue, and put
            // the card's index into the counter.
            player.handOrder.push(player.hand[choice]);
            displayCard(player.hand[counter.size()], 'b');
            counter.push_back(choice);
            pressToContinue();
        }
    }
}

void arrangeEnemyHand(){

    // Clear existing queue
    while(!enemy.handOrder.empty()){
        enemy.handOrder.pop();
    }

    // Copy hand
    vector<string> shuffledHand = enemy.hand;

    // Shuffle it
    random_shuffle(shuffledHand.begin(), shuffledHand.end());

    // Put cards into queue
    for(string card : shuffledHand){
        enemy.handOrder.push(card);
    }
}

void battlingPhase(){
    while(!player.handOrder.empty() && !enemy.handOrder.empty() && player.hp > 0 && enemy.hp > 0){

        string playerCard = player.handOrder.front();
        string enemyCard = enemy.handOrder.front();

        // stoi and substr gets the damage value from the cards 
        // and turns them into an integer.
        int playerCardVal = stoi(playerCard.substr(2));
        int enemyCardVal = stoi(enemyCard.substr(2));

        player.handOrder.pop();
        enemy.handOrder.pop();

        displayCard(playerCard, 'b');
        cout << "\nVS\n";
        displayCard(enemyCard, 'r');

        switch(didPlayerCardWin(playerCard[0], enemyCard[0])){
            case 'w':
                // Used switch case incase more effects get added
                switch(playerCard[1]){
                    case 'h':
                        player.hp += playerCardVal;
                        cout << "Player is healed for " << to_string(playerCardVal) << " HP!\n";
                        break;
                    case 'n':
                        enemy.hp -= playerCardVal;
                        cout << "Enemy is damaged for " << to_string(playerCardVal) << " HP!\n";
                        break;
                }
                break;
            case 'l':
                // Used switch case incase more effects get added
                switch(enemyCard[1]){
                    case 'h':
                        enemy.hp += enemyCardVal;
                        cout << "Enemy is healed for " << to_string(enemyCardVal) << " HP!\n";
                        break;
                    case 'n':
                        player.hp -= enemyCardVal;
                        cout << "Player is damaged for " << to_string(enemyCardVal) << " HP!\n";
                        break;
                }
                break;
            case 'd':
                cout << "It's a draw!\n";
                break;
        }

        pressToContinue();
        clearScreen();
    }
}

char didPlayerCardWin(char pCardType, char eCardType){
    if(pCardType == eCardType){
        return 'd';
    }

    // If the condition is true, return the first value
    // else, return the second value.
    switch(pCardType){
        case 'r':
            return (eCardType == 's') ? 'w' : 'l';
        case 'p':
            return (eCardType == 'r') ? 'w' : 'l';
        case 's':
            return (eCardType == 'p') ? 'w' : 'l';
        default:
            return 'd';
    }
}

void pressToContinue(){
    cout <<"Press any key to continue.";

    // Flushes out the value in cin in order for get to ask for a
    // new value instead of getting the leftovers from cin.
    cin.ignore(1000, '\n');
    cin.get();
}

void clearScreen(){
    // If the OS is Windows, use cls, else use clear.
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void generateNewGame(){
    game.score = 0;
    game.level = 1;

    player.hp = 30;
    player.gold = 0;

    enemy.hp = 20;
    
    for(int i = 0; i < 6; i++){
        string pCard;
        string eCard;
        pCard = generateCard(2, 5); 
        eCard = generateCard(2, 5);
        player.deck.push_back(pCard);
        enemy.hand.push_back(eCard);
    }
}

void displayCard(string card, char color){

    // For printing out the card

    char cardType = card[0];
    char cardEffect = card[1];
    string cardDamage = card.substr(2);

    switch (color){
        case 'w':
            cout << "\033[37m";
            break;
        case 'r':
            cout << "\033[31m";
            break;
        case 'g':
            cout << "\033[32m";
            break;
        case 'b':
            cout << "\033[34m";
            break;
    }

    cout << setw(3) << left << cardDamage << "-----+\n";
    switch(cardType){
        case 'r':
            cout << "|   _   |\n";
            cout << "| _( )_ |\n";
            cout << "|(_   _)|\n";
            cout << "|  (_)  |\n";
            cout << "|       |\n";
            break;
        case 'p':
            cout << "| _____ |\n";
            cout << "||     ||\n";
            cout << "||     ||\n";
            cout << "||_____||\n";
            cout << "|       |\n";
            break;
        case 's':
            cout << "|       |\n";
            cout << "|  \\ /  |\n";
            cout << "|   X   |\n";
            cout << "|  / \\  |\n";
            cout << "|       |\n";
            break;
    }

    switch (cardEffect){
        case 'h':
            cout << "HEAL ---+\n";
            break;
        case 'n':
            cout << "+-------+\n";
            break;
    }

    cout << "\033[0m";
}

string generateCard(int range, int startingValue, int specialEffectChance){
    // Generates a string containing the cards' type (rock, paper, or scissors),
    // if it's a heal card, and its damage/heal points

    string card = "";

    int cardType = rand() % 3;
    switch(cardType){
        case 0:
            card += "r";
            break;
        case 1:
            card += "p";
            break;
        case 2:
            card += "s";
            break;
    }

    if(rand() % 100 < specialEffectChance){
        card += "h"; // Heals
    } else {
        card += "n"; // No effect
    }

    int damage = rand() % range + startingValue;
    card += to_string(damage);
    return card;
}