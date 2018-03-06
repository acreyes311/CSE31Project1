#include <stdio.h>
#define MAXSIZE 4096

//nextChar returns the next character in string
char nextChar(char *str) {
  return *(str + sizeof(char));
}

//prevChar return the previous char in string
char prevChar(char *str) {
  return *(str - sizeof(char));
}

/**
 TODO
 int isOperator(char pattern)
 switch function to return type of operator.
 .,+,?,\\
 
 
/*
  plus function returns true if char = + symbol
  uses nextChar to cycle through string
*/
int plus(char *pattern) {
  if (nextChar(pattern) == '+')
  	return 1;
  return 0;
}

/*
  question Function returns true if char = ? symbol
  uses nextchar to cycle through
*/
int question(char *pattern) {
  if (nextChar(pattern) == '\?')
  	return 1;
  return 0;
}

/*
  escape function returns true if char = //
  uses prevchar to cycle through
*/
int escape (char *pattern) {
  if (prevChar(pattern) == '\\')
  	return 1;
  return 0;
}

/**
 * You can use this recommended helper function 
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
  // Implement if desire 
  if(*partial_line == *pattern)
  	return 1;
  	/*
  if (*pattern == '.' && !escape(pattern))
  	return 1;
  if (*pattern == '.' && !escape(pattern))
  	return 1; 
  if (*pattern == '\\')
  	return matches_leading(partial_line, pattern + sizeof(char));
  if (question(pattern))
  	return 1;
  
*/
  return 0;
}



/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {

    //
    // Implement me 
    //

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
