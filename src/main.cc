#include <iostream>
#include "gameboard.h"
#include <fstream>
#include "helperF.h"
#include "player.h"
#include "human.h"
#include "ai1.h"
#include "ai2.h"
#include "ai3.h"
#include "ai4.h"
using namespace std;

int main(int argc, char *argv[]) {
	int currPlayer = 0;
	int startingPlayer = 0;
	double whiteScore = 0;
    double blackScore = 0;
	ifstream defaultBoard;
	bool firstLoop = true;

    //The program stays in the below while loop playing multiple games until
    //it terminates when ctrl-D is pressed
	while(true)
	{
		//Xwindow *w = &e;
		GameBoard *G = new GameBoard();
		Player *W = NULL;
		Player *B = NULL;
		Player *C = NULL; //Pointer to the current player
		string userIN;
		string token;
		
		//BOARD INITIALIZATION
		G->setReadingFile(true); //Supresses View from Printing while pieces are read to board
 		if(firstLoop == true) 
		{
			if (argc == 2) {
					defaultBoard.open(argv[1]);
				} else {
					defaultBoard.open("DBoard.txt");
				}
				startingPlayer = G->readFile(defaultBoard);
				currPlayer = startingPlayer;
				defaultBoard.close();
			firstLoop = false;
		} 
		else
		{
			defaultBoard.open("DBoard.txt");
			G->readFile(defaultBoard);
			startingPlayer = 1 - startingPlayer;
			currPlayer = startingPlayer;
			defaultBoard.close();
		}
		G->setReadingFile(false); //Release the supporession on the view class
		G->print();
		
		//GAME SETUP AND PLAYER INITIALIZATION
		while(getline(cin, userIN)) 
		{
			token = ""; //Protects from setupINIT returning with return character left on screen
			if (userIN == "")  
				getline(cin, userIN); 
			stringstream ss(userIN);
			ss >> token;
	
			if(token == "setup") {
				if(firstLoop && argc == 2) {
					defaultBoard.open("DBoard.txt");
					G->readFile(defaultBoard);
					defaultBoard.close();
				}
				GameBoard *GAlt = G;
				int *curr = &currPlayer;
				setupINIT(GAlt, curr);
			} else if(token == "game") {
				string playerW;
				string playerB;
				ss >> playerW >> playerB;
				if(((playerW == "human") || (playerW == "computer4") || (playerW == "computer1") || 
                                    (playerW == "computer2") || (playerW == "computer3")) &&
				   ((playerB == "human") || (playerB == "computer4") || (playerB == "computer1") || 
                                    (playerB == "computer2") || (playerB == "computer3"))) 
				{
					if (playerW == "human")
						W = new Human(G, 0);
					else if (playerW == "computer1")
						W = new AI1(G, 0);
					else if (playerW == "computer2")
						W = new AI2(G, 0);
					else if(playerW == "computer3")
						W = new AI3(G, 0);
					else
						W = new AI4(G, 0);

					if (playerB == "human") 
						B = new Human(G, 1);
					else if (playerB == "computer1") 
						B = new AI1(G, 1);
					else if (playerB == "computer2") 
						B = new AI2(G, 1);
					else if(playerB == "computer3") 
						B = new AI3(G, 1);
					else 
						B = new AI4(G, 1);
					if(currPlayer == 0)  C = W; 
                	else  C = B; 
					break;
				}
				else
					cerr << "Invalid Parameters: Valid paramaters to game are human, computer1, computer2" << endl;
			}
			else {
				stringstream ss(userIN);
				char checkEOF;
				ss >> checkEOF;
				if (checkEOF != EOF) 
					cerr << "Invalid Command: please enter setup or game" << endl;
			}
		}
		if (C == NULL)  
			break; //The above loop then exited because of a ctrl-D || Will need to dealocate memory here!
				


		//PLAYING THE GAME 
//		G.setPlayingGame(true);
		while (!G->gameOver(C)) {
	        	if(currPlayer == 0) {
				//REQUIRED: The below game message
				if(W->wouldPutInCheck(Coord(0,0),Coord(0,0))) { cout << "White is in check." << endl; }
				W->makeMove();

                                #ifdef DEBUG
                                cout << "White: Please take your turn." << endl;
                                #endif
			} else {
				//REQUIRED: The below game message
                                if(B->wouldPutInCheck(Coord(0,0),Coord(0,0))) { cout << "Black is in check." << endl; }
				B->makeMove();

                                #ifdef DEBUG
                                cout << "Black: Please take your turn." << endl;
                                #endif
			}
     	 	 	currPlayer = 1 - currPlayer;
			if(currPlayer == 0) { C = W; }
			else { C = B; }
       	        }
		//G.setPlayingGame(false);


                //ANALYZING AND OUTPUTTING RESULTS OF GAME
		int winner = G->getWinner(C, currPlayer);
                if (winner == -1) { //Draw
			whiteScore += .5;
			blackScore += .5;
			//REQUIRED: The below game message
			cout << "Stalemate!" << endl;
                } else if (winner == 0) {
			whiteScore += 1;
                        //REQUIRED: The below game messages
			if (G->isResigned()) {
                                cout << "White wins!" << endl;
                        } else {
                                cout << "Checkmate! White wins!" << endl;
                        }
		} else {
			blackScore += 1;
			//REQUIRED: The below game messages
			if (G->isResigned()) {
				cout << "Black wins!" << endl;
			} else {
				cout << "Checkmate! Black wins!" << endl;
			} 
		}
		delete W;
		delete B;
	}

	//REQUIRED: The end of program messages when ctrl-D is pressed
    cout << endl;
	cout << "Final Score:" << endl;
	cout << "White: " << whiteScore << endl;
	cout << "Black: " << blackScore << endl;
	return 0;
}
