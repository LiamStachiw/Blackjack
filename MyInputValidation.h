/** MyInputValidation.h
 *	
 *	A re-useable library of input validation functions.
 *	   
 *	@author		Thom MacDonald
 *	@author		Your name goes here.
 *	@version	2014.02
 *	@since		11 Feb 2014
 *	@see 		Bronson, G. (2012).  Chapter 6 Modularity Using Functions. 
 *					In A First Book of C++ (4th ed.). 
 *					Boston, MA: Course Technology.
*/

#ifndef _MY_INPUT_VALIDATION

#define _MY_INPUT_VALIDATION

#include <iostream>
#include <cstdio> 	
#include <cstdlib>
#include <iomanip>
#include <climits> // for limits of a int INT_MIN and INT_MAX
#include <cfloat>  // for limits of a double DBL_MIN and DBL_MAX

using namespace std;

namespace myValidation
{
	/**	GetValidInteger function
	 * Gets a valid int value from the console with range checking
	 *
	 * @param  MIN the minimum value the user may enter; defaults to the minimum double.
	 * @param  MIN the minimum value the user may enter; defaults to the maximum double.
	 * @return A validated int input by the user.
	*/
	int GetValidInteger(const int MIN = INT_MIN, const int MAX = INT_MAX);
	
	/**	GetValidDouble function
	 * Gets a valid double value from the console with range checking
	 *
	 * @param  MIN the minimum value the user may enter; defaults to the minimum double.
	 * @param  MIN the minimum value the user may enter; defaults to the maximum double.
	 * @return A validated double input by the user.
	*/
	double GetValidDouble(const double MIN = -DBL_MAX, const double MAX = DBL_MAX);
	
	/**	ClearInputBuffer function
	 *	Clears the input buffer and resets the fail state of an istream object. 
	 *
	 *	@param		in (istream object by ref) - the object to clear & reset; defaults to cin.
	 *	@return		none.
	*/
	void ClearInputBuffer(istream &in = cin); // function prototype
	
	// GetValidInteger function definition
	int GetValidInteger(const int MIN, const int MAX)
	{
	       
	       double validNumber = 0.0; // holds the user input
	       
	       validNumber = GetValidDouble(MIN, MAX); // Get user input as a double
		   
	       if(validNumber > (int)validNumber)       // If user input is not a whole number
	       {
	           // report the problem to the user.
	           cerr << "\nInvalid input. Please try again and enter whole number.\n";
	           validNumber = GetValidInteger(MIN, MAX); // try again using recursion.
	       }
	       return (int) validNumber; // returns a valid value to the calling function.
	}
	
	// GetValidDouble function definition
	double GetValidDouble(const double MIN, const double MAX)
	{
	       
	       double validNumber = 0.0; // holds the user input
	       
		   cin >> validNumber;       // try to get input
	       if(cin.fail())            // if user input fails...
	       {
	           // reset the cin object and clear the buffer.
			   ClearInputBuffer();
	           // report the problem to the user.
	           cerr << "\nInvalid input. Please try again and enter a numeric value.\n";
	           // Try again by calling the function again (recursion)
	           validNumber = GetValidDouble(MIN, MAX);
	       } 
	       else if(validNumber < MIN || validNumber > MAX)// if value is outside range...
	       {
	           // report the problem to the user.
	           cerr << "\nInvalid input. Please try again and enter a value between "
	                << MIN << " and " << MAX << ".\n";
	           // Try again by call the function again (recursion)
	           validNumber = GetValidDouble(MIN, MAX);
	       }
	       return validNumber; // returns a valid value to the calling function.
	}
	
	// ClearInputBuffer function definition
	void ClearInputBuffer(istream &in) 
	{
		char characterFromBuffer; // a char variable to hold input from the buffer
		// if the in object has failed...
		if(in.fail())
	  	{
			in.clear(); // clear the fail state of the object
			characterFromBuffer = in.get(); // attempt to read a character 
		  	// while the character read is not new-line or not end-of-file
		  	while (characterFromBuffer != '\n' && characterFromBuffer != EOF) 
		  	{
			  	// therefore something was read from the buffer
			  	// attempt to read another character
				characterFromBuffer = in.get();
			} // end of while
		}// end of if	
	
	} // end of ClearInputBuffer
}
#endif
