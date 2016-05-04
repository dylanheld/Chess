# Friday 5:00am
God why.
Anyways, see your email for link to doc I made
Still to do: finish doc, finish uml, comment out any uneccessary cout statements

# if have trouble getting email then go to link :
https://docs.google.com/document/d/1y9X6ZgiaVAp7TqC6c-kb0SXIHMMF_U7sSYPw39m5roY/edit?usp=sharing



# Thursday 12:00

Working on textdisplay Messages "White is in Check", "Stalemate!",...
Also working on AI 3.5

# Thursday 3:40am
Done for now... I can't remember 100% what I updated right now... everything
# Main note: Can not just do g++ \*.cc ... refer to page 9 of assignment 3... I compile as g++ \*.cc -lX11 ... you may have to do something else 
<br />
<br />

# Wednesday 7:00pm
Editing main.cc gamebaord.cc gamebaord.h right now please no touchy.

#Wednesday Morning - had date messed up before
Done programming until later this evening
I was working on main a lot 
Need to put #ifdef DEBUG around a lot of cout statements because its getting too cluttered, started doing that
Ran AI2 vs AI2 king got killed by R
When piece gets killed display prints twice
Not sure if it is recording the right winner

Guess, AI3 has to wait, too many bugs to fix and code to cleanup :P

#Tues night
Would put in check fixed and now also takes care of knights
 - this function will be the template for #attacking and #defending that can be used for AI3
AI2 done
The board now has while and black tiles
Had to undo change to main2.cc because changes to setup got overwritten


# MON RECAP
On monday I did the following: <br />
(1) Implemented history class with *working* add function, canCastle function, canEnpassant function <br />
(2) revised gameboard.cc commitmove to encorporate castling and enpassant functionality <br />
(3) implemented AI1, tested slightly human vs. AI1, AI1 vs. AI1 <br />
# NOTES: 
(1) AI1 vs AI1 runs indefinately because it keeps moving kings at end of game, never reaches checkmate since gameOver is not coded yet.
(2) Need to implement gameOver :) <br />
Done for Human (3) Need to implement Pawn promotion <br />
(4) after this done, revise perhaps then on to further AIs. <br />
(5) I'm going to bed at ~4:15am, so i probably won't be awake prior to class at 2:30, until then. Happy holidays <br />

# More important update: Stepping out now (7:00pm), currently working on castling ability using history class I made, please if read don't alter canCastle in history.cc, or potentialmoves in king.cc
# Will continue to work and finish these when i return in a couple hours
# MON 7:00pm


# The new version is already in there - 4:57pm
# working on files: gameboard.cc gameboard.h history.h history.cc

# Done Queen Monday 4:00pm - queen.cc queen.h gameboard.cc
# One change to gameboard as queen was being made with Rook ctor
# I think you need to push new version of would put in check


 Fixed wouldputincheck, problems were (1) checking against the original gamebaord instead of temporary one (2) incremented mag twice each time instead of once, thus loop skipped over a location every call
 Sun: 6:00pm
 Can now move Bishops and Knights
 Mun: 2:13am

Andrew - Checking out for the day 5:00pm
Unfortunately, failed to get what I wanted done done. Will try to call.

 Can move rook now
sun 2:18pm

Sunday 10:30
I FREAKEN JUST PUSHED SOME PAWN :D
To do this I made some changes to:
main2
helperF
gameboard
textdisplay
pawn
human
I think thats all.

Pushed to GIT everthing up to this point.

Now will work on the king piece and functions related to checking if the king is in check. These will be the same functionsused in the AI. Please keep me updated on what sections you are working on.

#Updated main2.cc to use helper functions to setup game so code is less dense
#Sat 12:30pm

#SAT 11:00am
# I finished the movements of the pawn pieces -> Please look at those files
# I changed game.h/cc to gameboard.h/cc and made edits in there
# I forgot to override the >> operator for Coord and also Coord.getString() I think will be useful

# I don't really understand the view UML part, I don't think we need to create a seperate copy of
# where the peices are in the view, as in the observer patter we should have a pointer to the 
# gameboard, but I'll leave this to you to do and explain to me after.

# After the view is and main is done, I will be able to compile to test the 100 bugs I expect to 
# find in my code :P 

# We should meed to clean the code after we can compile a game that can just move pawns.

# I'm going to take the afternoon off and then program again in the evening.


#FRI-10:30pm
# I finished the Player Class and Human Class -> Please read comments in their .h and .cc files
# The next thing I want to work on is the Peices Class and Pawn Class starting Sat Morning (Unless of course you do it)
#
# Other Notes:
# - We don't need custructors for individual peices, the abstract class one should be sufficient
# - GameBoard class being called game.h is driving me crasy :P
# - You wrote in comment: What if player had a array of peices? Too complicated to write, but that would mess up quite a few things now.
# - char apple; lol
