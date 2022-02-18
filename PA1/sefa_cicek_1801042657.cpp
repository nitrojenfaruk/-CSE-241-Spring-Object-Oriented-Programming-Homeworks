#include <iostream>
#include <ctime>
#include <string>

using namespace std;

bool is_it_unique(string input);

int main(int argc, char *argv[])
{
	const int limit = 100;   
	string entered_num, secret_num , argv_1, argv_2;
	int  exact=0, misplaced=0, turn=1, check=0;
	bool no_error = false;

	srand(time(NULL));

	/* Command-line arguments transfer */
	if(argc == 3){
		argv_1 += argv[1]; /* "-r" OR "-u" */
		argv_2 += argv[2]; 
		no_error = true;
	}

	/* Checking digits of the number followed by "-u" or "-r" */
    for (int i = 0 ; i < argv_2.length() && no_error ; ++i)
    {
    	if ( !isdigit(argv_2[i]) || argv_2[0] == '0' || argv_2[0]  == '-'){  
    		no_error = false; 
    	}
    }

    /* E0 - ERROR PART */
	if ( !(no_error) || 
	     !(argv_1 == "-r" || argv_1 == "-u") ||   
	     (argv_1 == "-r" && argv_2.length() > 1) ||
	     (argv_1 == "-u" && !is_it_unique(argv_2))
	   )
	{
		cout << "E0" << endl;
		no_error = false;
	}

	/* There is no error in program call..*/
	if(no_error){

		if(argv_1 == "-u"){
			secret_num = argv_2;     // ./mastermind -u 128 -> 128 is the secret number.
			check = 1;    // It is used for error checking later. 
		}

		/* argv_1 == "-r" */
		else{
			
			int length = stoi(argv_2);   

			for (int j = 0; j < length; ++j){

				/* Assigning first digit of number */
				if(j == 0){
					int first_digit = (rand() % 9 + 1);
					secret_num += (first_digit + '0');
				}

				/* Assigning digits of number excluding first digit */
				else{
						/* Unique Digit Generator */
				     	int temp, count;
				     	count = 0; 
					
						temp = rand() % 10;    // Generating random digit

						/* Comparing generated digit with existing digits */
						for (int n = j-1; n >= 0; --n){
			
							if(temp + '0' != secret_num[n] && count != j){
								count++;    
								continue;
							}

						}
						/* Generated digit is not equal to existing digits */
						if(count == j)
							secret_num.push_back(temp + '0');    // Digit is appending to the end
						else
							--j;    // Digit is not unique, generating new random digit again..

				}	
			}
		}


		do{

			cin >> entered_num;

			/* E2 - ERROR PART -> User enters something but not an integer */
			for (int k = 0 ; k < entered_num.length() && no_error; ++k){

    			if ( !isdigit(entered_num[k]) ){  
    				cout << "E2" << endl;
    				no_error = false; 
    				break;
    			}

   			}

   			/* E1 - ERROR PART -> User enters a number which has more or less than argv_2 */
			if(entered_num.length() != stoi(argv_2) && no_error && !check ||
			   entered_num[0] == '0' || !is_it_unique(entered_num))
			{
				cout << "E1" << endl;
				no_error = false;
			}

			/* Program provides two counts -> exact, misplaced */
			for (int l = 0; l < entered_num.length() && no_error; ++l){

				if(entered_num[l] == secret_num[l]){    // Digit was matched on right place..
					exact++;
					continue;
				}

				for (int m = 0; m < entered_num.length() && no_error; ++m)
				{
					if(entered_num[l] == secret_num[m]){   // Digit was misplaced..
						misplaced++;
						break;
					}

				}
			}
			
			/* Secret number is found! */
			if(entered_num == secret_num && no_error){   
				cout << "FOUND " << turn << endl;
				no_error = false; 
			}
			
			/* Secret number is not found. */
			else if(no_error){
				cout << exact << ' ' << misplaced << endl;
			}

			/* Guess limit is exceed! */
			if((turn == limit) && no_error){
				cout << "FAILED" << endl;
				no_error = false;
			}

			/* For the next number predictions */
			exact = misplaced = 0;
			turn++;

		} while(no_error);
    
	}

	return 0;
		
}

/* To find the entered number is unique or not unique */
bool is_it_unique(string input){

	bool unique = true;

	/* It is not unique..Size exceeding or first digit is 0 */
	if(input.length() > 9 || (input.length() == 1 && input[0] == '0')){
		unique = false;
	}
	
	for (int i = 0; i < input.length() && unique ; ++i)
	{
		for (int j = i+1; j < input.length(); ++j)    
		{	
			/* Digit is matched with another digit so that it is not unique number.*/
			if(input[i] == input[j])
				unique = false;
		}
	}

	return unique;
	
}
