#include <stdio.h>
#include <string.h>
#define MAXSIZE 4096


/**
 * You can use this recommended helper function 
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {

  int i,j,count;  // Index's to traverse partial_line and pattern seperately  
  i = j = count = 0;
  
  //Check for Null Terminator return 0
  while (pattern[i] == '\0') {
  	if (partial_line[j] == '\0'){
  		return 0;  // No match
  	}
  	
  	else if (partial_line[j] == '\n'){j++;} //if new-line increase j++ to jump line
  	
  	//Condition Checking
  	else if (pattern[i+1] == '\\' && pattern[i] == '\\')  // check '\\'
		{
			if (pattern[i+1] == partial_line[j]) {
				i+= 2; //next char of pattern
				j++; //next char of partial_line
			}
			else {
				i = 0; //Reset pattern 0
				j++; //Next partial_line
			}
		}
		
  	else if(pattern[i-1] == '\\' && pattern [i] == '+'){ //check '\+'
  		if(pattern[i] == partial_line[j]){  		
        		i++;
        		j++;
       		}       		
       		else {
        		i = 0; // Reset pattern back to 0
        		j++; // Move to next char in partial_line
        	}
        }
        
        else if (pattern[i] == '?' && pattern[i-1] == '\\') { // check '\?'
        	if (pattern[i] == partial_line[j]){
        		i++; // next char in pattern
        		j++; // next char in parial_line
        	}
        	else{
        		i = 0;  // reset pattern to 0
        		j++;  // increase partial_line
        	}		
        }
        else if (pattern[i] == '.' && pattern [i-1] == '\\') { // check '\.'
        	if (pattern[i] == partial_line[j]) {
        		i++; // next char in pattern
        		j++;  // next char in partial_line
        	}
        	else {
        		i = 0; // reset pattern
        		j++; // inscrease partial
        	}
        }	
        	// check for '\' only
        else if(pattern[i] == '\\' && (pattern[i+1] != '\\' || pattern [i+1] != '+' || pattern[i+1] != '?'|| pattern[i+1] != '.')) {
        	if  (pattern [i+1] == partial_line[j]) {
        		i += 2;  // Jump 2 Chars of pattern
        		j++;  // Increase Partial
        	}		
        	else {
        		i = 0; // reset
        		j++;
        	}
        }
        	
        else if((pattern[i] == '+') && (pattern[i-1] !='\\')) { // check for '+' only
        	count++;
        	char temp = pattern[i-1]; // sets temp to char before '+' symbol.
        	// '.' special case
        	if (temp == '.') // if previous char is '.'
        		temp = partial_line[j];  // Sets temp to current char
        		
        	while (temp == partial_line[j])// Go through all matches.
        		j++;
        		
        	i++; // next char in pattern
        	int patternLength = strlen(pattern);
        	int lineLength = strlen(partial_line);
        	
        	while((pattern[i] == temp) &&((patternLength - count) < (lineLength))) {
        		i++;
        	}	
        		         	
        }
        
        else
        	return 0; // no matches found	
  }
        	
  return 1;
}



/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {

  //int i=0;  
  /*
  //Performs error checking and makes call to matches_leading
  while(line[i] != '\0'){
  	if(matches_leading(line+i, pattern))
		return 1;
	i++;
  }

	if(pattern[0] == '\0')
		return 1;
		*/
		
  int i = 0;
  int res = 0; // return value
  int flag = 1; // condition flag
  
  //Test for symbol chars "? and \"
  while (pattern [i] != '\0') {  // While not null
  	if (pattern[i] == '\\' || pattern[i] == '?') { // Check for the chars and set flag 1
  		flag = 0;
  	}
  		
  	i++; // Increment i to loop through pattern
  }
    
 
  
  if (flag == 1) {
	res = matches_leading(line,pattern);
  }
  	
  if (pattern[i] == '?' && pattern[i-1] == '\\')  {
  	res = matches_leading(line,pattern);
  }	
  		
// Find symbols		
  else{
  	i = 0;
  	if (pattern [i] == '?' || pattern [i-1] != '\\'){
  		
  		char symbols[strlen(pattern)-2];  // without char
  		char fullstr[strlen(pattern)-1];  // Full string
  		int s1, s2;
  		s1 = s2 = 0;
  		
  		
  		// Will Loop Through to assign pattern to fullstr 
  		while (pattern[s1] != '\0'){
  			if (pattern[s1] == '?')
  				s1++;
  				
  			fullstr[s2] = pattern[s1];
  			s1++;
  			s2++;
  			
  		}
  		s1 = s2 = 0;
  		// Will Loop Through to assign pattern without '?' 
  		while (pattern [s1] != '\0') {
  			if (pattern [s1+1] == '?')  // check for double '?'
  				s1 += 2; // skip both
  			symbols[s2] = pattern[s1];	
  			s1++;
  			s2++;
  		}	
  		
  		int return_with_char = 0; 
		int return_without_char = 0;
		return_without_char = matches_leading(line, symbols);
		return_with_char = matches_leading(line, fullstr);
			
		if (return_without_char || return_with_char)
		{
			res = 1;
		}
  		// If either true return true;
  		//if ((matches_leading(line, symbols) == 1) || (matches_leading(line, fullstr) == 1))		
  			//return 1;
  	}
  	
  }		
    return res;  
}


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
