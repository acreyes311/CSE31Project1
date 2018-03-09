#include <stdio.h>
#define MAXSIZE 4096


/**
 * You can use this recommended helper function 
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {

  int i,j,count;
  
  i = j = count = 0;
  
  //Check for Null Terminator return 0
  while (pattern[j] == '\0'){
  	if (partial_line[j] == '\0'){
  		return 0;
  	}
  	
  	else if (partial_line[j] == '\n'){j++;} //if new-line increase j++ to jump line
  	
  	//Condition Checking
  	if (pattern[i+1] == '\\' && pattern[i] == '\\')
		{
			if (pattern[i+1] == partial_line[j])
			{
				i+=2; //next char of pattern
				j++; //next char of partial_line
			}
			else
			{
				i = 0; //Reset pattern 0
				j++; //Next partial_line
			}
		}
		
  	else if(pattern[i] == '\\' && pattern [i+1] = '+'){ // Move to next char on in both arrays
  		if(pattern[i] == partial_line[j]){  		
        	i++;
        	j++;
       		}       		
       		else {
        	i = 0; // Reset pattern back to 0
        	j++; // Move to next char in partial_line
        	}
        }
        
        else if (pattern[i] == '\\' && pattern[i+1] == '\\'){
        	if (pattern[i+1] == partial_line[j]){
        		j++; // Next char of Partial_line
        		i+=2; // next char of pattern.
        	}
        	else{ // Reset and Move
        		i = 0; //reset pattern
        		j++; // move partial_line
        	}
        }
        
        
  return 0;
}



/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {

  int i=0;
  
  //Performs error checking and makes call to matches_leading
  while(line[i] != '\0'){
  	if(matches_leading(line+i, pattern))
		return 1;
	i++;
  }

	if(pattern[0] == '\0')
		return 1;
    return 0;  
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
