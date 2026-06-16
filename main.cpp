#include <iostream>
#include <queue>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;

// In general: num = rand() % (how many numbers included in range) + (lowest number in the range)


int startingMenu();
void newGame();
void displayCard(string card);
string generateCard(int range, int lowest, int specialEffectChance = 0);

struct entityInfo{
    int hp;
    int gold;
    string hand[5];
    vector<string> deck;
    queue<string> handOrder;
} player, enemy;

struct gameInfo{
    int score;
    int level;
} game;

int main(){

    while(true){
        switch(startingMenu()){
            case 1:
                newGame();
                break;
            case 2:
                cout << "Loading game..." << endl;
                // Code to load a game goes here
                break;
            case 3:
                cout << "Exiting the game. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
                continue;
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

void newGame(){
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
        enemy.deck.push_back(eCard);
    }
}

void displayCard(string card){
    char cardType = card[0];
    char cardEffect = card[1];
    string cardDamage = "";

    for (int i = 2; i < card.length(); i ++){
        cardDamage += card[i];
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
}

string generateCard(int range, int startingValue, int specialEffectChance){
    srand(time(0));

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
        card += "h"; // s for Special
    } else {
        card += "n"; // n for None (no special effects)
    }

    int damage = rand() % range + startingValue;
    card += to_string(damage);
    return card;
}