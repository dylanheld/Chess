#include "human.h"
#include "pieces.h"
#include "player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

Human::Human(GameBoard* gb, int colour): Player(gb, colour) {} 

//Human::makeMove()
//Will read input from user to execute "move" and "resign" commands.
//Checks: (1) Calls Method to Check if player owns starting peice
//        (2) Checks that end location is a avaliable move for the piece 
//        (3) Calls Method that proposed move wont put their own king in check
//        (4) Above methods indirectly confirm starting and ending locations are on board
void Human::makeMove() {
  bool validRequest = false;
  while(!validRequest) {
    bool makeTheMove = false;
    string cmdLine;
    string cmd_type;
    Coord stc, endc;

    getline(cin, cmdLine);
    if (cmdLine == "") getline(cin, cmdLine);
    istringstream cmd(cmdLine);
    cmd >> cmd_type;
   
    //This code block preforms the 4 checks
    if (cmd_type == "move") {
	stc >> cmd;
	//      in >> stc;
	endc >> cmd;
        //cmd >> endc;
        #ifdef DEBUG
	//cout << "Hello" << stc.getX() << " " << stc.getY() << endl;
        //cout << endc.getX() << " " << endc.getY() << endl;
       
	//cout << gb->getPiece(stc)->getPiece() << endl;
        //cout << "getcolor: " << gb->getPiece(stc)->getColour() << endl;
        //cout << "color " << colour << endl;
      	#endif
	if(isMyPiece(gb->getPiece(stc))) {
        vector <Coord> v;
        v = gb->getPiece(stc)->potentialMoves(stc); //Change potentialMoves to return a vector
      
        for(vector<Coord>::iterator it = v.begin(); it != v.end(); ++it) {
          #ifdef DEBUG
	  //cout << "potential: " << it->getX() << " " << it->getY() << endl; 
	  #endif
	  bool same = ((it->getX() == endc.getX()) && (it->getY() == endc.getY()));
          if (same && !(wouldPutInCheck(stc,endc))) makeTheMove = true;
        }
      }
    }
    // Add pawn promotion!
    string apple;
    bool canPP = false;
    //cout << "got here" << endl;
    if(makeTheMove && ((colour == 0 && endc.getY() == 7 && gb->getPiece(stc)->getPiece() == 'P') ||
	(colour == 1 && endc.getY() == 0 && gb->getPiece(stc)->getPiece() == 'p'))) {
#ifdef DEBUG
		cout << "Pawn Promotion occured!" << endl;
#endif
		bool whichState = false;
		//canPP = false;
		//char checkState = gb->getPiece(stc)->getPiece()
		if(isupper(gb->getPiece(stc)->getPiece())) { whichState = true; }
		cmd >> apple;
			if(whichState && (apple == "Q" || apple == "R" || apple == "N" || apple == "B")) {
				//makeTheMove = true;
				canPP = true;	
			}
			else if(!whichState && (apple == "q" || apple == "r" || apple == "n" || apple == "b")) {
                                //makeTheMove = true;
                        	canPP = true;
			}
			else {
				makeTheMove = false;
				cerr << "Invalid Promotion piece" << endl;
			}
	}
    if (makeTheMove) {
      gb->commitMove(stc, endc); //Need to add this function to our GameBoard Class
      if(canPP) {
		gb->promotePawn(endc, apple);
      }
      validRequest = true;
    } else if (cmd_type == "resign") {
      gb->setResigned(true);
      validRequest = true;
    } else {
      cerr << "Invalid Request: no change occured." << endl;
    }

  } //Exit upon valid command read
}
