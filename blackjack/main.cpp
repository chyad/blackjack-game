#include <iostream>

#include <vector>

#include <algorithm>
#include <random>

using namespace std;

/*
void killscreen();
*/

int p_ace, d_ace =0;  // ace counter



void init_card(vector<int>& pool, vector<int>& d, vector<int>& p);

bool ask_player();

bool check21(int count, int ace);

void draw(vector<int>& pool, vector<int>& p, int n=1);  // 1 for player atm

int point_count(vector<int> card);   // ace always counting as 1 in here.

void print_card(int n);             // print big card

void print_hand(vector<int> n);     // print small card

void print_point(int count);

bool five_card(int s, int count);       // reach five cards and not busted

char print_end(int n);

bool rematch();


int main() {

  string cushion;
  
  std::random_device rd;
  auto rng = std::default_random_engine { rd() };

  std::vector <int> card_pool;

  p_ace = 0;
  d_ace = 0;

  int deck_size =1;

  while(true){
    cout << "choose deck size (preferably 1-8):" << "\n";
    cout << "your input: ";
    cin >> deck_size;
    if(deck_size>0 && deck_size<9){

      if (system("CLS")) system("clear");

      break;
    }
  }
  
  
  for(int i=0; i<deck_size;i++){
    for(int j=0; j<52; j++){
      card_pool.push_back((j)%13+1);
    }
  }
  std::shuffle(std::begin(card_pool), std::end(card_pool), rng);


  while(true){

  p_ace = 0;
  d_ace = 0;
  cout << "-----------------------" << "\n";
  cout << "deck size: " << deck_size << "\n";
  cout << "-----------------------" << "\n"; 
  cout << "card pool: " << card_pool.size() << "\n";
  cout << "-----------------------" << "\n"; 

  /*                                          // debug
  for(int i : card_pool){
    cout << i << " ";
  }
  cout << "-----------------------" << "\n"; 
  */


  std::vector< int > dc; // cards on hand
  std::vector< int > pc;

  init_card(card_pool, dc, pc);   // giving first 3 cards
  

  int count = point_count(pc);
  bool player_round = true;
  
  cout << "- Your round -" << "\n"; 
  cout << "-----------------------" << "\n"; 

  if(check21(count, p_ace)){                  // blackjack check
    cout << "You reached 21 points" << "\n";
    cout << "blackjack!" << "\n";
    player_round = false;
    count = 21;

    cout << "\n";
    cout <<"input something to resume: ";     // cushion
    cin >> cushion;
    if (system("CLS")) system("clear");
  }


  while(player_round){          // player round

    count = point_count(pc);

    if(five_card(pc.size(), count)){  // straight win when five cards
      cout << "five card trick!" << "\n";
      print_hand(pc);
      cout << "\n";
      player_round = false;

      cout << "\n";
      cout <<"input something to resume: ";     // cushion
      cin >> cushion;
      if (system("CLS")) system("clear");
      break;
    }
    
    print_point(count);
    print_hand(pc);
    cout << "\n\n";

    if(count > 21){               // escape
      cout << "Busted" << "\n";
      count = 0;

      cout << "\n";
      cout <<"input something to resume: ";     // cushion
      cin >> cushion;
      if (system("CLS")) system("clear");
      break;
    }
    if(check21(count, p_ace)){
      cout << "You reached 21 points" << "\n";
      count = 21;

      cout << "\n";
      cout <<"input something to resume: ";     // cushion
      cin >> cushion;
      if (system("CLS")) system("clear");
      break;
    }
    if(!ask_player()){

      if(p_ace){          // update highest point
        if(count+10 < 21){
          count+=10;
        }
      }

      if (system("CLS")) system("clear");

      break;
    }                             // escape

    if (system("CLS")) system("clear");
    cout << "-----------------------" << "\n";
    draw(card_pool, pc, 1);
    cout << "-----------------------" << "\n";
    
  }


  cout << "-----------------------" << "\n"; 
  cout << "- Dealer's round -" << "\n"; 

  if(! player_round){
    cout << "\n" << "..." << "\n";
    cout << "\n" << "... ..." << "\n\n";
    cout << "-----------------------" << "\n";
    cout << ":  may I have a card? :" << "\n";
    cout << ":   maybe next time?  :" << "\n";
    cout << "-----------------------" << "\n\n";
  }
  if(!count){
    cout << "\n" << "..." << "\n";
    cout << "\n" << "... ..." << "\n\n";
    cout << "-----------------------" << "\n";
    cout << ":       no worry      :" << "\n";
    cout << ":we can have a rematch:" << "\n";
    cout << "-----------------------" << "\n\n";
  }

  
  int d_count = point_count(dc);

  while(count && player_round){          // if player is not busted or blackjack

    d_count = point_count(dc);

    if(d_count > 21){
      cout << "\n";
      cout << "-----------------------" << "\n";
      cout << "dealer busted" << "\n"; 
      cout << "-----------------------" << "\n";
      cout << "\n";
      d_count = 0;
      break;
    }
    if(d_count > 16){   // stand when above 17
      cout << "\n";
      cout << "-----------------------" << "\n";
      cout << "dealer stands at " << d_count << "\n"; 
      cout << "-----------------------" << "\n";
      cout << "\n";
      break;
    }
    if(d_ace){          // checking points
      if(d_count+10 > count && d_count+10 < 22 && d_count+10 > 16){
        cout << "\n";
        cout << "-----------------------" << "\n";
        cout << "dealer stands at " << d_count+10 << "\n"; 
        cout << "-----------------------" << "\n";
        cout << "\n";
        d_count += 10;
        break;
      }
    }

    draw(card_pool, dc, 0);
    
  }

                         
  cout <<"input something to see result: ";     // cushion
  cin >> cushion;
  if (system("CLS")) system("clear");


  // printing hands
  cout << "\n" << "*-+*-+*-+*-+*-+*-+*-+*-" << "\n";
  cout << "\n" << ":    hands  rewind    :" << "\n";
  cout << "\n" << "*-+*-+*-+*-+*-+*-+*-+*-" << "\n";
  cout << "- dealer's card -" << "\n\n";
  print_hand(dc);
  cout << "\n\n" << "*-+*-+*-+*-+*-+*-+*-+*-" << "\n";

  cout << "- player's card -" << "\n\n";
  print_hand(pc);
  cout << "\n\n" << "*-+*-+*-+*-+*-+*-+*-+*-" << "\n";

  /*
  for(int i : card_pool){ // debug
    cout << i << " ";
  }
  cout << "\n" << "-----------------------" << "\n";
  */

  cout << "\n";
  cout << "dealer: " << d_count << " points\n";
  cout << "player: " << count << " points\n";
  cout << "\n";

  if(d_count == count){
    cout << "-----------------------" << "\n";
    cout << ": seems like we tied  :" << "\n";
    cout << "-----------------------" << "\n";
  }else if(d_count > count){
    cout << "-----------------------" << "\n";
    cout << ":  seems like I won   :" << "\n";
    cout << "-----------------------" << "\n";
  }else{
    cout << "-----------------------" << "\n";
    cout << ": seems like you won  :" << "\n";
    cout << "-----------------------" << "\n";
  }
  

  cout << "\n";
  if(card_pool.size() < 26){
    cout << "-----------------------" << "\n";
    cout << ":  card pool ran out  :" << "\n";
    cout << ":  see you next time  :" << "\n";
    cout << "-----------------------" << "\n";
    break;
  }

  if(rematch()){
    cout << "-----------------------" << "\n";
    cout << ":  see you next time  :" << "\n";
    cout << "-----------------------" << "\n";
    break;
  }

  if (system("CLS")) system("clear");

  }

  return 0;
}


/* ----------------------------------------------------------------------- */


void init_card(vector<int>& pool, vector<int>& d, vector<int>& p){

  d.push_back(pool[0]);
  
  cout << "dealer card:" << "\n";
  print_card(pool[0]);

  cout << "-----------------------" << "\n";
  if(pool[0]==1) {
    d_ace += 1;
  }

  pool.erase(pool.begin());

  cout << "player card:" << "\n";
  for(int i=0; i<2; i++){
    p.push_back(pool[0]);
    
    print_card(pool[0]);

    if(pool[0]==1) {
      p_ace += 1;
    }

    pool.erase(pool.begin());
  }
  cout << "-----------------------" << "\n";

  return;
}


void draw(vector<int>& pool, vector<int>& p, int n){

  p.push_back(pool[0]);

  if(pool[0]==1){
    if(n==1){
      p_ace += 1;
    }else{
      d_ace +=1;
    }
  }

  cout << "Drawing... ..." << "\n";
  
  string temp = (n == 1) ? "player card:" : "dealer card:";

  cout << temp << "\n";
  print_card(pool[0]);

  pool.erase(pool.begin());

}


bool ask_player(){
  char n = '0';

  while(!(n == 'y' || n == 'n')){
    cout << "Take a card? (y/n):";
    cin >> n;
  }

  return (n == 'y') ? true : false;
}


int point_count(vector<int> card){

  int count =0;

  for(int i : card){

    if(i>=10){
      count += 10;
    }else{
      count += i;
    }
  }
  return count;
}


void print_point(int count){

  if(count+10 > 21){
    cout << "Your points is currecntly "  << count << "\n";
    return;
  }

  if(p_ace > 0){

    cout << "Your points could be " << count+10 << " or ";

    }else{
      cout << "Your points is currecntly " ;
    }
    cout << count << "\n";

    return;
}


bool check21(int count, int ace){
  if(count == 21) return true;

  if(ace == 0) return (count == 21);

  return (count+10 == 21);
}


void print_card(int n){
  cout << "-------" << "\n";
  cout << "|     |" << "\n";

  switch(n){
    case 13:
      cout << "|  " << "K" << "  |"<< "\n";
      break;
    case 12:
      cout << "|  " << "Q" << "  |"<< "\n";
      break;
    case 11:
      cout << "|  " << "J" << "  |"<< "\n";
      break;
    case 10:
      cout << "| 10  |"<< "\n";
      break;
    case 1:
      cout << "|  " << "A" << "  |"<< "\n";
      break;
    default:
      cout << "|  " << n << "  |"<< "\n";
      break;
  }

  cout << "|     |" << "\n";
  cout << "-------" << "\n";

  return;
}


bool five_card(int s, int count){
  return (s==5 && count<22);
}


char print_end(int n){
  switch(n){
    case 13:
      return 'K';
    case 12:
      return 'Q';
    case 11:
      return 'J';
    case 1:
      return 'A';
  }
  return '=';
}


void print_hand(vector<int> n){

  for(int i : n){
    if(i==1 || i >10){
      cout << "[" << print_end(i) << "] ";
    }else{
      cout << "[" << i << "] ";
    }  
  }
}


bool rematch(){
  char n = '0';

  while(!(n == 'y' || n == 'n')){
    cout << "another round? (y/n):";
    cin >> n;
  }

  return (n == 'y') ? false : true;
}
