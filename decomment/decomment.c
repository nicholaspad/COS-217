#include <stdio.h>
#include <ctype.h>

enum State {NORMAL, ESC_IN_NORMAL,
	        HALF_OPEN_COMMENT, OPEN_COMMENT, HALF_CLOSED_COMMENT,
	        DOUBLE_QUOTE_OPEN, ESC_IN_DOUBLE_QUOTE,
	        SINGLE_QUOTE_OPEN, ESC_IN_SINGLE_QUOTE};

/**********************************************************************/

/* Corresponds to state NORMAL (i.e. not within a comment or quote
   block). Takes input character c. Returns state HALF_OPEN_COMMENT if
   c is a forward slash. Returns state ESC_IN_NORMAL if c is a back
   slash. Returns state DOUBLE_QUOTE_OPEN if c is a double quote.
   Returns state SINGLE_QUOTE_OPEN if c is a single quote. Returns
   state NORMAL (same state) if c is any other character. Prints c if it
   is not a forward slash. */
enum State handleNormal(int c) {
	enum State state;

	switch (c) {
	case '/': /* forward slash */
		state = HALF_OPEN_COMMENT;
		break;
	case '\\': /* back slash */
		putchar(c);
		state = ESC_IN_NORMAL;
		break;
	case '"': /* double quote */
		putchar(c);
		state = DOUBLE_QUOTE_OPEN;
		break;
	case '\'': /* single quote */
		putchar(c);
		state = SINGLE_QUOTE_OPEN;
		break;
	default: /* any other character */
		putchar(c);
		state = NORMAL;
	}

	return state;
}


/* Corresponds to state ESC_IN_NORMAL (i.e. immediately succeeding a
   back slash not inside a comment or quote block). Takes input
   character c. Returns state NORMAL. Prints c. */
enum State handleNormalEsc(int c) {
	enum State state = NORMAL;
	putchar(c);
	return state;
}

/* Corresponds to state HALF_OPEN_COMMENT (i.e. immediately succeeding a
   forward slash not inside a comment or quote block). Takes input
   character c, current line number currLine, and current comment block
   line number comStart. Returns state HALF_OPEN_COMMENT (same state) if
   c is a forward slash. Prints a space and returns state OPEN_COMMENT
   if c is an asterisk, and updates comStart. Returns state NORMAL if c
   is any other character. Prints c if it is not an asterisk. */
enum State handleHalfOpenComment(int c, int currLine, int *comStart) {
	enum State state;

	switch (c) {
	case '/': /* forward slash */
		putchar(c);
		state = HALF_OPEN_COMMENT;
		break;
	case '*': /* asterisk */
		putchar(' ');
		state = OPEN_COMMENT;
		*comStart = currLine;
		break;
	default: /* any other character */
		putchar('/');
		putchar(c);
		state = NORMAL;
	}

	return state;
}

/* Corresponds to state OPEN_COMMENT (i.e. within a comment block).
   Takes input character c. Returns state HALF_CLOSED_COMMENT if c is an
   asterisk. Returns state OPEN_COMMENT if c is any other character.
   Prints c if it is a newline character. */
enum State handleOpenComment(int c) {
	enum State state;

	switch (c) {
	case '*': /* asterisk */
		state = HALF_CLOSED_COMMENT;
		break;
	default: /* any other character */
		if (c == '\n') {
			putchar(c);
		}
		state = OPEN_COMMENT;
	}

	return state;
}

/* Corresponds to state HALF_CLOSED_COMMENT (i.e. immediately
   succeeding a forward slash inside a comment block). Takes input
   character c. Returns state HALF_CLOSED_COMMENT if c is an asterisk.
   Returns state NORMAL if c is a forward slash. Returns state
   OPEN_COMMENT if c is any other character. Prints c if it is a newline
   character. */
enum State handleHalfClosedComment(int c) {
	enum State state;

	switch (c) {
	case '*': /* asterisk */
		state = HALF_CLOSED_COMMENT;
		break;
	case '/': /* forward slash */
		state = NORMAL;
		break;
	default: /* any other character */
		if (c == '\n') {
			putchar(c);
		}
		state = OPEN_COMMENT;
	}

	return state;
}

/* Corresponds to state DOUBLE_QUOTE_OPEN (i.e. inside a double quote
   block). Takes input character c. Returns state ESC_IN_DOUBLE_QUOTE if
   c is a back slash. Returns state NORMAL if c is a double quote.
   Returns state DOUBLE_QUOTE_OPEN if c is any other character. Prints
   c. */
enum State handleDoubleQuoteOpen(int c) {
	enum State state;

	switch (c) {
	case '\\': /* back slash */
		putchar(c);
		state = ESC_IN_DOUBLE_QUOTE;
		break;
	case '"': /* double quote */
		putchar(c);
		state = NORMAL;
		break;
	default: /* any other character */
		putchar(c);
		state = DOUBLE_QUOTE_OPEN;
	}

	return state;
}


/* Corresponds to state ESC_IN_DOUBLE_QUOTE (i.e. immediately succeeding
   a back slash inside a double quote block). Takes input character c.
   Returns state DOUBLE_QUOTE_OPEN. Prints c. */
enum State handleDoubleQuoteEsc(int c) {
	enum State state = DOUBLE_QUOTE_OPEN;
	putchar(c);
	return state;
}

/* Corresponds to state SINGLE_QUOTE_OPEN (i.e. inside a single quote
   block). Takes input character c. Returns state ESC_IN_SINGLE_QUOTE if
   c is a back slash. Returns state NORMAL if c is a single quote.
   Returns state SINGLE_QUOTE_OPEN if c is any other character. Prints
   c. */
enum State handleSingleQuoteOpen(int c) {
	enum State state;

	switch (c) {
	case '\\': /* back slash */
		putchar(c);
		state = ESC_IN_SINGLE_QUOTE;
		break;
	case '\'': /* single quote */
		putchar(c);
		state = NORMAL;
		break;
	default: /* any other character */
		putchar(c);
		state = SINGLE_QUOTE_OPEN;
	}

	return state;
}

/* Corresponds to state ESC_IN_SINGLE_QUOTE (i.e. immediately succeeding
   a back slash inside a single quote block). Takes input character c.
   Returns state SINGLE_QUOTE_OPEN. Prints c. */
enum State handleSingleQuoteEsc(int c) {
	enum State state = SINGLE_QUOTE_OPEN;
	putchar(c);
	return state;
}

/**********************************************************************/

int main(void) {
	int c; /* Latest character from standard input */
	int comStart; /* Line number of most recent comment block */
	int currLine = 1; /* Current line number */
	enum State state = NORMAL; /* Start in state NORMAL */

	/* Exhaustively read characters one-by-one from standard input. */
	while((c = getchar()) != EOF) {
		if (c == '\n') {
			currLine++;
		}

		switch (state) {
		case NORMAL:
			state = handleNormal(c);
			break;
		case ESC_IN_NORMAL:
			state = handleNormalEsc(c);
			break;
		case HALF_OPEN_COMMENT:
			state = handleHalfOpenComment(c, currLine, &comStart);
			break;
		case OPEN_COMMENT:
			state = handleOpenComment(c);
			break;
		case HALF_CLOSED_COMMENT:
			state = handleHalfClosedComment(c);
			break;
		case DOUBLE_QUOTE_OPEN:
			state = handleDoubleQuoteOpen(c);
			break;
		case ESC_IN_DOUBLE_QUOTE:
			state = handleDoubleQuoteEsc(c);
			break;
		case SINGLE_QUOTE_OPEN:
			state = handleSingleQuoteOpen(c);
			break;
		case ESC_IN_SINGLE_QUOTE:
			state = handleSingleQuoteEsc(c);
			break;
		}
	}

	/* States OPEN_COMMENT and HALF_CLOSED_COMMENT mean that a comment
	   block has not been closed: EXIT_FAILURE. */
	if (state == OPEN_COMMENT || state == HALF_CLOSED_COMMENT) {
		fprintf(stderr, "Error: line %d: unterminated comment\n", comStart);
		return 1;
	}

	/* All other states mean that all comment blocks have been closed:
	   EXIT_SUCCESS. */
	return 0;
}
