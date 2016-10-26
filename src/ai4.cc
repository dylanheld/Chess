#include <stdlib.h>
#include <iostream>
#include "ai4.h"
#include "player.h"
#include <map>
#include <vector>
#include "pieces.h"
#include <ctime>
//#include <algorithm>
using namespace std;


AI4::AI4(GameBoard* gb, int colour): AI(gb, colour) {}

void AI4::makeMove() {
  //AI4 aso Does 3 loops, first loop narrows down to attack moves, second loop runs if impossible to attack try any move
  srand (time(NULL));
  bool aggression[2] = {true, false};
  string canMove;
  while(cin >> canMove) 
  {
    map<Coord*, vector<Coord> > opponentMoves;
    map<Coord*, vector<Coord> > allMoves;
    
    if (canMove == "move") 
    {
      //STEP1: First read in all opponents potential moves
      for(int i = 0; i < 8; ++i) 
      {
        for(int j = 0; j < 8; ++j) 
        {
          Coord temp(i, j);
          vector<Coord> v;
          if(!(gb->getPiece(temp) == NULL) && !isMyPiece(gb->getPiece(temp))) 
            v = gb->getPiece(temp)->potentialMoves(temp);
          if (!(v.empty())) 
          {
            Coord* temp2 = new Coord(i,j);
            opponentMoves[temp2] = v;
          }
        }
      }
      if (!allMoves.empty()) { cerr << "DEBUG::impossible situaiton occured"; }
      bool ChooseAggretion = aggression[rand() % 2];
      // Now iterate 5 times depending on aggression level chosen, if true then do exactly as AI3 does, otherwise do an additional check that
      // piece in question can capture the attacker
      for(int Attack = 2; Attack >= -3; Attack--) 
      {
        for(int i = 0; i < 8; ++i) 
        {
          for(int j = 0; j < 8; ++j) 
          {
            Coord temp(i, j);
            vector<Coord> v;
            if(isMyPiece(gb->getPiece(temp)) && ChooseAggretion == false) 
            {
              //CODE FOR ATTACK = 2
              if(Attack == 2) 
              { //AKA we are defending
                //SEE IF CURRENT LOCATION IS BEING ATTACKED
                bool isAttacked = false;
                typedef map<Coord*, vector<Coord> >::iterator it_type;
                for(it_type iteratorA = opponentMoves.begin(); iteratorA != opponentMoves.end(); iteratorA++) 
                {
                  //iterator->first = key, iterator->second = value
                  for(vector<Coord>::iterator it = iteratorA->second.begin(); it != iteratorA->second.end(); it++) 
                  {
                    if ((temp.getX() == it->getX()) && (temp.getY() == it->getY())) 
                    { 
                      isAttacked = true;
                      break;
                    }
                  }
                }
                //SEE IF ANY POTENTIAL MOVES ARE NOT ON ATTACKED SQUARES
		            if(isAttacked) 
                {
	                v = gb->getPiece(temp)->potentialMoves(temp);
                  for(vector<Coord>::iterator it = v.begin(); it != v.end();) 
                  {
                    bool unsafe = wouldPutInCheck(temp, *it, false, false);
                    if(wouldPutInCheck(temp, *it)) 
                      it = v.erase(it);
                    else if (unsafe)
                      it = v.erase(it);
		                else
                      ++it;
                  }
                }

              //CODE FOR ATTACK = 1, ATTACK = 0      
	            } 
              else 
              {
                v = gb->getPiece(temp)->potentialMoves(temp);
                for(vector<Coord>::iterator it = v.begin(); it != v.end();) 
                {
                  bool isAttacked = wouldPutInCheck(temp, *it, false, false);
                  if(wouldPutInCheck(temp, *it))
                    it = v.erase(it);
                  else if ((Attack == 1 || Attack == -1) && 
                    (gb->getPiece(*it) == NULL) && 
                    !(wouldPutInCheck(temp, *it, true))) 
                    it = v.erase(it);   
                  else if ((Attack == 1 || Attack == 0) && isAttacked)
                    it = v.erase(it);
                  else
                    ++it; 
                }
              }
            }
            else if (isMyPiece(gb->getPiece(temp))) 
            {
              if(Attack == 2) 
              { //AKA we are defending
                //SEE IF CURRENT LOCATION IS BEING ATTACKED
                bool isAttacked = false;
                typedef map<Coord*, vector<Coord> >::iterator it_type;
                Coord Attacker;
  		          for(it_type iteratorA = opponentMoves.begin(); iteratorA != opponentMoves.end(); iteratorA++) 
                {
                  for(vector<Coord>::iterator it = iteratorA->second.begin(); it != iteratorA->second.end(); it++) 
                  {
                    if ((temp.getX() == it->getX()) && (temp.getY() == it->getY())) 
                    {
                        isAttacked = true;
                        Attacker = *(iteratorA->first);
  		                  break;
                    }
                  }
                }
		
                //SEE IF ANY POTENTIAL MOVES ARE NOT ON ATTACKED SQUARES
                if(isAttacked) 
                {
        	  	    v = gb->getPiece(temp)->potentialMoves(temp);
                  for(vector<Coord>::iterator it = v.begin(); it != v.end();) 
                  {
                    bool unsafe = wouldPutInCheck(temp, *it, false, false);
                    if(wouldPutInCheck(temp, *it)) 
                    {
                      it = v.erase(it);
                    } 
                    else if (unsafe) 
                    {	
				              if(it->getX() == Attacker.getX() && it->getY() == Attacker.getY()) 
                      {
                        char myP = gb->getPiece(temp)->getPiece();
                        char tp = gb->getPiece(*it)->getPiece();
					              if(isupper(myP)) 
                          myP = myP + 32;
              					if(isupper(tp))
                          tp = tp + 32;
              					if ((myP == 'q' && tp == 'q') || 
                          (myP == 'r' && (tp == 'r' || 
                            tp == 'q')) || (myP == 'b' && 
                          (tp == 'b' || tp == 'r' || tp == 'q')) || 
                            (myP == 'n' && (tp == 'n' || tp == 'b' || 
                              tp == 'r' || tp == 'q')) || myP == 'p')
                          ++it;
              					else 
              						it = v.erase(it);          			
				              }
              				else 
              					it = v.erase(it);
                    }   //else if (wouldPutInCheck(temp, *it, false, false)) { it = v.erase(it); }
                    else
                      ++it;
                  }
                }
              }
		          else if(Attack == 1) 
              { //AKA we are defending
                //SEE IF CURRENT LOCATION IS BEING ATTACKED
                bool isAttacked = false;
                typedef map<Coord*, vector<Coord> >::iterator it_type;
                for(it_type iteratorA = opponentMoves.begin(); iteratorA != opponentMoves.end(); iteratorA++) 
                {
                  //iterator->first = key, iterator->second = value
                  for(vector<Coord>::iterator it = iteratorA->second.begin(); it != iteratorA->second.end(); it++) 
                  {
                    if ((temp.getX() == it->getX()) && (temp.getY() == it->getY())) 
                    {
                      isAttacked = true;
                      break;
                      //cout << "In Attack Loop Interation one" << temp.getX() << " " << temp.getY() << endl;
                    }
                  }
                }
                //SEE IF ANY POTENTIAL MOVES ARE NOT ON ATTACKED SQUARES
                if(isAttacked) 
                {
                  v = gb->getPiece(temp)->potentialMoves(temp);
                  //v = gb->getPiece(stc)->potentialMoves(stc);
                  for(vector<Coord>::iterator it = v.begin(); it != v.end();) 
                  {
                    bool unsafe = wouldPutInCheck(temp, *it, false, false);
                    if(wouldPutInCheck(temp, *it)) 
                      it = v.erase(it);
                    else if (unsafe) 
                      it = v.erase(it);
                     else 
                      ++it;
                  }
                }
              }
              //CODE FOR ATTACK = 1, ATTACK = 0      
              else 
              {
                v = gb->getPiece(temp)->potentialMoves(temp);
                for(vector<Coord>::iterator it = v.begin(); it != v.end();) 
                {
                  bool isAttacked = wouldPutInCheck(temp, *it, false, false);
                  if(wouldPutInCheck(temp, *it)) 
                      it = v.erase(it);
                  else if ((Attack == 0 || Attack == -2) && 
                    (gb->getPiece(*it) == NULL) && 
                    !(wouldPutInCheck(temp, *it, true))) 
                      it = v.erase(it);
                  else if ((Attack == 0 || Attack == -1) && isAttacked) 
  			            it = v.erase(it);
                  else
                    ++it;
                }
              }
            }		
            if (!(v.empty())) 
            {
              Coord* temp2 = new Coord(i,j);
              allMoves[temp2] = v;		
            }
          }
        }
        if (!allMoves.empty()) 
          break; 
      }
      map<Coord*, vector<Coord> >::iterator it = allMoves.begin();
      std::advance(it, rand() % allMoves.size());
      Coord* randKey = it->first;
      vector<Coord>::iterator et = allMoves[randKey].begin();
      std::advance(et, rand() % allMoves[randKey].size());
      Coord randVal = *et;
      string promotedPiece;
      bool canPP = false;
      if (colour == 0 && randVal.getY() == 7 && gb->getPiece(*randKey)->getPiece() == 'P') 
      {
        string possiblePromotions[4] = {"R", "N", "B", "Q"};
        promotedPiece = possiblePromotions[rand() % 4];
        canPP = true;
      }
      else if(!(canPP) && colour == 1 && randVal.getY() == 0 && gb->getPiece(*randKey)->getPiece() == 'p') 
      {
        string possiblePromotions[4] = {"r", "n", "b", "q"};
        promotedPiece = possiblePromotions[rand() % 4];
        canPP = true;
      }
      gb->commitMove(*randKey, randVal);
      if(canPP)
        gb->promotePawn(randVal, promotedPiece);
      for(map<Coord*, vector<Coord> >::iterator it = allMoves.begin(); it != allMoves.end(); ++it)
        delete it->first;
      for(map<Coord*, vector<Coord> >::iterator it = opponentMoves.begin(); it != opponentMoves.end(); ++it)
        delete it->first;
      break;
    } 
    else if (canMove == "resign") 
    { 
      gb->setResigned(true); 
      break; 
    } 
    else
      cerr << "Invalid input request, please enter either move or resign" << endl;
  }
}