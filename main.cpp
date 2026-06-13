#include <iostream>
#include <queue>
#include <cstdlib>
#include <vector>
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
    player.gold = 50;

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

string generateCard(int range, int lowest, int specialEffectChance){
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
        card += "s"; // s for Special (to be replaced with actual special letters)
    } else {
        card += "n"; // n for None (no special effects)
    }

    int damage = rand() % range + lowest;
    card += to_string(damage);
    return card;
}