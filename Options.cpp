#include "Options.h"

using namespace std;

// include options in the game
void Options::includeOptions(Deck& deck, vector<Player*>& plist){
	bool arg_d=false; // is option -d included?
	bool arg_p=false; // is option -p included?
	bool arg_s=false; // is option -s included?

	// read each argument until the end of the argument
	for(unsigned int arg_count=0; arg_count<this->size(); arg_count++){
		// if the option -r is included
		if((string)this->at(arg_count)=="-r"){
			arg_count++;
			// if -d is already included, then produce an error meassage and exit
			if(arg_d){
				cerr<<"Aborting; -r must occur before -d on command line if both flags are used."<<endl;
				exit(1);
			}
			// if -r is the last argument(seed is not specified), produce an error message and exit
			else if(arg_count==this->size()){
				cerr<<"Error, -r requires another argument. Aborting."<<endl;
				exit(1);
			}
			// set the seed value for the given deck
			else deck.setRandomSeed(atoi(this->at(arg_count)));
		}

		// if the option -s is included
		else if((string)this->at(arg_count)=="-s"){
			arg_count++;
			arg_s=true; // -s is included now
			// if -s is the last argument(maxScore is not specified), produce an error message and exit
			if(arg_count==this->size()){
				cerr<<"Error, -s requires another argument. Aborting."<<endl;
				exit(1);
			}
			// if the given maxScore value is negative or 0, produce an error message and exit		
			else if(atoi(this->at(arg_count))<=0){
				cerr<<"Error, maxScore must be positive."<<endl;
				exit(1);
			}

			// set the new MaxPoints for the game
			else this->MaxPoints=(unsigned int)atoi(this->at(arg_count));
		}

		// if the option -d is included
		else if((string)this->at(arg_count)=="-d"){
			arg_count++;
			arg_d=true; // -d is included now
			string inputfile=this->at(arg_count); // store the name of the file in "inputfile"
			// if -d is the last argument(the name of the file is not specified), produce an error message and exit
			if(arg_count==this->size()){
				cerr<<"Error, -d requires another argument. Aborting."<<endl;
				exit(1);
			}
			// read the file
			ifstream in(inputfile.c_str());
			// if the given filename is not in the current directory, produce an error message and exit
			if(in.fail()){
				cerr<<"Error, couldn't open card deck input\""<<inputfile<<"\""<<endl;
				exit(1);
			}
			// read each line in the given file, and store them in a given deck
			Card* c;
			for(int i=0; i<52; i++){
				c=new Card();
				in>>*c;
				deck.push_back(c);
			}
		}

		// if the option -p is specified
		else if((string)this->at(arg_count)=="-p"){
			string pname;
			arg_p=true; // -p is included now
			// if -p is the last argument(player info is not specified), produce an error message and exit
			if(arg_count+1==this->size()){
				cerr<<"Error, -p requires another argument. Aborting."<<endl;
				exit(1);
			}

			// takes players info until we have all 4 players' info
			while(1){
				arg_count++; // move on to the next argument
				// if we have all 4 players' info, break
				if(plist.size()==4)
					break;

				// if the player type "S" is in the argument
				else if((string)this->at(arg_count+1)=="S"){
					// mark the corresponding player's name as smart player by appending "S" in front of the player's name
					pname="s"+(string)this->at(arg_count);
					// allocate a memory space for a smart player and store its address in the given plist
					plist.push_back(new SmartPlayer(pname));
					arg_count+=1; // jump to the next argument
				}

				// if the player type "H" is in the argument
				else if((string)this->at(arg_count+1)=="H"){
					// mark the correspoding player's name as human player by appending "H" in front of the player's name
					pname="h"+(string)this->at(arg_count);
					// allocate a memory space for a human player and store its address in the given plist
					plist.push_back(new HumanPlayer(pname));
					arg_count+=1; // jump to the next argument
		 		}

				// if the player type "R" is in the argument
				else if((string)this->at(arg_count+1)=="R"){
					// mark the corresponding player's name as random player by appending "R" in front of the player's name
					pname="r"+(string)this->at(arg_count);
					// if the seed value of the random player is not specified, produce an error message and exit
					if(arg_count+2==this->size()){
						cerr<<"Error, -p requires another argument. Aborting."<<endl;
						exit(1);
					}
					// allocate a memory space for a random player and store its address in the given plist
					plist.push_back(new RandomPlayer(pname,(unsigned int)atoi(this->at(arg_count+2))));
					arg_count+=2; // jump to the next argument(note that +=2 because "R" takes 3 arguments(name type seed)
				}

				// if the next argument is not "S" nor "H" nor "R", produce an error message and exit
				else if((string)this->at(arg_count+1)!="S" ||(string)this->at(arg_count+1)!="H" || (string)this->at(arg_count+1)!="R"){
					cerr<<"Illegal player kind: \""<<(string)this->at(arg_count+1)<<"\""<<endl;
					exit(1);
				}
				// if -p has no other arguments, produce an error and exit
				else{
					cerr<<"Error, -p requires another argument. Aborting."<<endl;
					exit(1);
				}
			}
		}
		// if the given arugment is irrelevant, move on to the next argument
		else arg_count++;
	}

	// if the option -d was not specified, then set the deck to default
	if(!arg_d)	deck.generate();

	// if the option -p was not specified, then set the players to default
	if(!arg_p){
		plist.push_back(new SmartPlayer("sAlice"));
		plist.push_back(new SmartPlayer("sBob"));
		plist.push_back(new SmartPlayer("sCarole"));
		plist.push_back(new SmartPlayer("sTed"));
	}

	// if the option -s was not specified, then set the Maxpoints to default
	if(!arg_s) this->MaxPoints=40;

	// shuffle the deck so that we are now ready to play
	deck.shuffle();
}

// return MaxPoints
int Options::getMaxPoints(){
	return MaxPoints;
}
