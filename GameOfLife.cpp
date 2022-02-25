#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

#define RESETTEXT  "\x1B[0m" // Set all colors back to normal.
#define FOREBLK  "\x1B[30m" // Black
#define FORERED  "\x1B[31m" // Red
#define FOREGRN  "\x1B[32m" // Green
#define FOREYEL  "\x1B[33m" // Yellow
#define FOREBLU  "\x1B[34m" // Blue
#define FOREMAG  "\x1B[35m" // Magenta
#define FORECYN  "\x1B[36m" // Cyan
#define FOREWHT  "\x1B[37m" // White

#define BACKBLK "\x1B[40m"
#define BACKRED "\x1B[41m"
#define BACKGRN "\x1B[42m"
#define BACKYEL "\x1B[43m"
#define BACKBLU "\x1B[44m"
#define BACKMAG "\x1B[45m"
#define BACKCYN "\x1B[46m"
#define BACKWHT "\x1B[47m"

class Board {
private:
  int l, w;
  vector<vector<int> > squares, currentSquares;
public:
  bool nothingHappened;


  Board(){}

  Board(int length, int width) {
    l = length;
    w = width;
    vector<int> tempTB, temp;
    for (int i=0; i<width+2; i++) {
      tempTB.push_back(6);
    }
    squares.push_back(tempTB);
    currentSquares.push_back(tempTB);
    for (int i=1; i<length+1; i++) {
      while(temp.size() > 0) {
        temp.erase(temp.begin());
      }
      temp.push_back(6);
      for (int i=1; i<width+1; i++) {
        //this controls ur numbers
        int random = (int)(rand() % 2);
        if (random == 0) {
          temp.push_back(1);
        } else {
          temp.push_back(0);
        }
      }
      temp.push_back(6);
      //
      squares.push_back(temp);
      currentSquares.push_back(temp);
    }
    squares.push_back(tempTB);
    currentSquares.push_back(tempTB);
  }

  void setVal(vector<int> a, int index, int val) {
    a.erase(a.begin()+index);
    a.insert(a.begin()+index, val);
  }

  void setStoC(int i, int j) { //why do u not exist already
    int temp = currentSquares[i][j];
    squares[i].erase(squares[i].begin()+j);
    squares[i].insert(squares[i].begin()+j, temp);
  }

  //this thing sets up currentSquares for one val
  void swapUno(int rCor, int cCor) {
    int neighborCtr = 0;
    for (int i=rCor-1; i<rCor+2; i++) {
      for (int j=cCor-1; j<cCor+2; j++) {
        if (i != rCor || j != cCor) {
          if (squares[i][j] == 1) {
            neighborCtr++;
          }
        }
      }
    }
    //cout << "neighbors ea" << rCor << cCor << neighborCtr << endl;

    bool isOne = squares[rCor][cCor] == 1;
    bool isZero = squares[rCor][cCor] == 0;
    currentSquares[rCor].erase(currentSquares[rCor].begin()+cCor);
    if (isOne && (neighborCtr < 2 || neighborCtr > 3)) {
      currentSquares[rCor].insert(currentSquares[rCor].begin()+cCor, 0);
    } else if (isOne) {
      currentSquares[rCor].insert(currentSquares[rCor].begin()+cCor, 1);
    } else if (isZero && neighborCtr == 2) {
      currentSquares[rCor].insert(currentSquares[rCor].begin()+cCor, 1);
    } else if (isZero) {
      currentSquares[rCor].insert(currentSquares[rCor].begin()+cCor, 0);
    } else {}
  }

  //bam
  void swappyswap(){
    for(int i=1; i<l+1; i++) {
      for (int j=1; j<w+1; j++) {
        swapUno(i, j);
      }
    }
    //submethod
    int diffCtr = 0;
    for (int i=1; i<l+1; i++) {
      for (int j=1; j<l+1; j++) {
        if (squares[i][j] != currentSquares[i][j]) {
          diffCtr++;
        }
      }
    }
    nothingHappened = diffCtr == 0;
    //
    for (int i=1; i<l+1; i++) {
      for (int j=1; j<w+1; j++) {
        setStoC(i, j);
      }
    }
  }

  void printBoard(){
    for (int i=1; i<l+1; i++) {
      for (int j=1; j<w+1; j++) {
        if (this->squares[i][j] == 1) {
          cout << BACKWHT << "  " << RESETTEXT;
        } else {
          cout << BACKBLK << "  " << RESETTEXT;
        }
      }
      cout << endl;
    }
  }

};

int main() {

  string input;
  int l, w;
  cout << "Length of board?: ";
  cin >> input;
  try {
    l = stoi(input);
  } catch (exception &err) {
    l = 40;
  }

  cout << "Width of board?: ";
  cin >> input;
  try {
    w = stoi(input);
  } catch (exception &err) {
    w = 40;
  }

  Board b(l, w);

  do {
    b.printBoard();
    cout << endl;
    b.swappyswap();
    this_thread::sleep_for(chrono::milliseconds(125));
  } while (!b.nothingHappened);
  return 0;
}
