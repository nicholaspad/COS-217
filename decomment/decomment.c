#include <stdio.h>
#include <ctype.h>

enum State {NORMAL, ESC_IN_NORMAL,
	        HALF_OPEN_COMMENT, OPEN_COMMENT, HALF_CLOSED_COMMENT,
	        DOUBLE_QUOTE_OPEN, ESC_IN_DOUBLE_QUOTE,
	        SINGLE_QUOTE_OPEN, ESC_IN_SINGLE_QUOTE};

/*********************************************************************/

enum State handleNormal(int c) {
	enum State state;

	switch (c) {
	case '/':
		state = HALF_OPEN_COMMENT;
		break;
	case '\\':
		putchar(c);
		state = ESC_IN_NORMAL;
		break;
	case '"':
		putchar(c);
		state = DOUBLE_QUOTE_OPEN;
		break;
	case '\'':
		putchar(c);
		state = SINGLE_QUOTE_OPEN;
		break;
	default:
		putchar(c);
		state = NORMAL;
	}

	return state;
}

enum State handleNormalEsc(int c) {
	enum State state = NORMAL;
	putchar(c);
	return state;
}

enum State handleHalfOpenComment(int c) {
	enum State state;

	switch (c) {
	case '/':
		putchar(c);
		state = HALF_OPEN_COMMENT;
		break;
	case '*':
		state = OPEN_COMMENT;
		break;
	default:
		putchar('/');
		putchar(c);
		state = NORMAL;
	}

	return state;
}

enum State handleOpenComment(int c) {
	enum State state;

	switch (c) {
	case '*':
		state = HALF_CLOSED_COMMENT;
		break;
	default:
		if (c == '\n') {
			putchar(c);
		}
		state = OPEN_COMMENT;
	}

	return state;
}

enum State handleHalfClosedComment(int c) {
	enum State state;

	switch (c) {
	case '*':
		state = HALF_CLOSED_COMMENT;
		break;
	case '/':
		putchar(' ');
		state = NORMAL;
		break;
	default:
		if (c == '\n') {
			putchar(c);
		}
		state = OPEN_COMMENT;
	}

	return state;
}

enum State handleDoubleQuoteOpen(int c) {
	enum State state;

	switch (c) {
	case '\\':
		putchar(c);
		state = ESC_IN_DOUBLE_QUOTE;
		break;
	case '"':
		putchar(c);
		state = NORMAL;
		break;
	default:
		putchar(c);
		state = DOUBLE_QUOTE_OPEN;
	}

	return state;
}

enum State handleDoubleQuoteEsc(int c) {
	enum State state = DOUBLE_QUOTE_OPEN;
	putchar(c);
	return state;
}

enum State handleSingleQuoteOpen(int c) {
	enum State state;

	switch (c) {
	case '\\':
		putchar(c);
		state = ESC_IN_SINGLE_QUOTE;
		break;
	case '\'':
		putchar(c);
		state = NORMAL;
		break;
	default:
		putchar(c);
		state = SINGLE_QUOTE_OPEN;
	}

	return state;
}

enum State handleSingleQuoteEsc(int c) {
	enum State state = SINGLE_QUOTE_OPEN;
	putchar(c);
	return state;
}

/*********************************************************************/

int main(void) {
	int c;
	enum State state = NORMAL;

	while((c = getchar()) != EOF) {
		switch (state) {
		case NORMAL:
			state = handleNormal(c);
			break;
		case ESC_IN_NORMAL:
			state = handleNormalEsc(c);
			break;
		case HALF_OPEN_COMMENT:
			state = handleHalfOpenComment(c);
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

	if (state == OPEN_COMMENT || state == HALF_CLOSED_COMMENT) {
		return 1;
	}

	return 0;
}
