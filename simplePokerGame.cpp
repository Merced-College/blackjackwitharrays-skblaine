/*
Skylee Blaine
Kirsten Richards
Andrew Doumas

1/21/25
Reviewing Procedural Programming
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// creating strings for each type of suit and rank of card in a deck
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
int DECK[52];
int currentCardIndex = 0;
int wins = 0;
int losses = 0;
int ties = 0;
int chips = 100;
int player_bet = 0;

//increases win count
void add_win(){
    wins++;
}
//increases loss count
void add_losses(){
    losses++;
}
//increases tie count
void add_tie(){
    ties++;
}
// creates deck, populates array with numbers 0-51
void initializeDeck() {
    for (int i = 0; i < 52; i++) {
        DECK[i] = i;
    }
}

void add_chips(){
    chips += player_bet*1.5;
}

void remove_chips(){
    chips -= player_bet;
}

void betting(){
    
    bool betting = true;

    while(betting){
        cout<<"how many chips would you like to bet?"<<endl;
        cin>> player_bet;

        if(player_bet < 1){
            cout<<"please enter an amount greater than 0" ;
            betting = false;
        }
        else{
            betting = false;
        }
    }

    cout<< "you bet: "<<player_bet <<"chip(s)"<<endl;
}

// shuffels the deck to be in a random order
void shuffleDeck() {
    //seeded randomization to prevent game from being repetetive
    srand(time(0));
    for (int i = 0; i < 52; i++) {
        int index = rand() % 52;
        int temp = DECK[i];
        DECK[i] = DECK[index];
        DECK[index] = temp;
    }
}

//deals card to player/dealer 
int dealCard() {
    return DECK[currentCardIndex++] % 13;
}

// determines card value
int cardValue(int card) {
    return card < 9 ? card + 2 : 10;
}

// identifies and prints 2 of the player's cards (rank and suit)
int dealInitialPlayerCards() {
    int card1 = dealCard();
    int card2 = dealCard();
    cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
    return cardValue(card1) + cardValue(card2);
}

// identifies and prints the dealer's card (rank and suit)
int dealInitialDealerCards() {
    int card1 = dealCard();
    cout << "Dealer's card: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << endl;
    return cardValue(card1);
}

// begins player turn (hit or stand)
int playerTurn(int playerTotal) {
    cout << "Your total is " << playerTotal << endl;
    betting();


    while (true) {
        cout << "Your total is " << playerTotal<<"." << endl;
        cout<<"Do you want to hit or stand?" << endl;
        string action;
        getline(cin, action); //user input (only takes hit or stand)
        if (action == "hit") {
            int newCard = dealCard();
            playerTotal += cardValue(newCard);
            cout << "You drew a " << RANKS[newCard % 13] << " of " << SUITS[newCard / 13] << endl; //return random card
            if (playerTotal > 21) {
                break;
            }
        } else if (action == "stand") {
            break;
        } else {
            cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
        }
    }
    return playerTotal;
}

// dealers turn, draws new card, adds to dealerTotal
// algorithm for dealer's turn
int dealerTurn(int dealerTotal) {
    while (dealerTotal < 17) { // dealer draws if total is less than 17
        int newCard = dealCard();
        dealerTotal += cardValue(newCard);
    }
    cout << "Dealer's total is " << dealerTotal << endl;
    return dealerTotal;
}

// compares playerTotal and dealerTotal
// prints win, tie, or dealer win
// determines who wins 
void determineWinner(int playerTotal, int dealerTotal) {
    if (dealerTotal > 21 || playerTotal > dealerTotal) {
        cout << "You win!" << endl;
        add_win();
        add_chips();
    } else if (dealerTotal == playerTotal) {
        cout << "It's a tie!" << endl;
        add_tie();
    } else {
        cout << "Dealer wins!" << endl;
        add_losses();
        remove_chips();
    }
}

int main() {

    //calls functions to create and shuffle the deck of cards 
    initializeDeck();
    shuffleDeck();
  
    //deals initial cards to player/dealer 
    int playerTotal;
    int dealerTotal;
   

    bool play_game = true;
    bool player_choice = true;
    bool player_bust = false;
    string play_again;


while(play_game){
       playerTotal = dealInitialPlayerCards();
       dealerTotal = dealInitialDealerCards();

    player_bust = false;
    // if player total is greater than 21, results in a bust
    // player turn happens here
    playerTotal = playerTurn(playerTotal);
    //checks if player total is greater than 21
    if (playerTotal > 21) {
      cout << "You busted! Dealer wins." << endl;
      add_losses();
      remove_chips();
      player_bust = true;
    }

    //dealers turn happens here, calls dealerTurn function
    dealerTotal = dealerTurn(dealerTotal);

    if(player_bust == false){
    //checks who wins the game
    determineWinner(playerTotal, dealerTotal);
    }


    cout<<"you have "<< chips<<" chips."<<endl;
    cout<<endl;

    // asks the player if they would like to play again
    player_choice = true;

    if(chips<=0){
        cout<<"You have run out of chips, good bye."<<endl;
        player_choice = false;
        play_game = false;
    }

    while(player_choice){
      cout<<'\n'<< "Would you like to play again?"<<'\n'<<"Please enter either yes or no"<<endl;

      // gets player choice and converts string to lowercase
      play_again = "";
      cin>> play_again;
      std::transform(play_again.begin(), play_again.end(), play_again.begin(), ::tolower); 

      
      
      if(play_again == "yes" || play_again == "no"){
        cout<< play_again<<endl;
        player_choice = false;
        if(play_again == "no"){
          player_choice = false;
          play_game = false;
        }
      }
      else{
        cout<<"Something went wrong..."<<endl;

      
      }
    }

}
  
    //outputs chips, win, loss, and tie stats
    cout<<"you walked away with "<<chips<<" chip(s)."<<endl;
    cout<<"You won: "<< wins<<" time(s)." <<endl;
    cout<<"You lost: "<< losses<<" time(s)."<<endl;
    cout<<"You tied: "<< ties<<" time(s)." <<endl;

    return 0;
}



