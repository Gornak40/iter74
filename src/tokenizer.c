#include "tokenizer.h"

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void debug_token(const token_t* t, const char* s) {
	fprintf(stderr, "DBG(token): %s [%d]:", s, t->type);
	switch (t->type) {
		case kNum:
			fprintf(stderr, " %lld\n", t->num);
			break;
		case kId:
		case kPId:
		case kTId:
		case kCall:
		case kPCall:
		case kTCall:
		case kSunc:
			fprintf(stderr, " %s\n", t->str);
			break;
		default:
			putc('\n', stderr);
			break;
	}
}

token_t parse_token(const char* stoken) {
	switch (strlen(stoken)) {  // perfomance trick
		case 1:
			// Operators
			if (!strcmp(stoken, "=")) {
				return (token_t){.type = kSet};
			}
		case 2:
			// Operators
			if (!strcmp(stoken, "<-")) {
				return (token_t){.type = kStore};
			}
		case 4:
			// Keywords
			if (!strcmp(stoken, "func")) {
				return (token_t){.type = kFunc};
			}
			if (!strcmp(stoken, "stop")) {
				return (token_t){.type = kStop};
			}
			if (!strcmp(stoken, "iter")) {
				return (token_t){.type = kIter};
			}
			if (!strcmp(stoken, "halt")) {
				return (token_t){.type = kHalt};
			}
			if (!strcmp(stoken, "once")) {
				return (token_t){.type = kOnce};
			}
			if (!strcmp(stoken, "pass")) {
				return (token_t){.type = kPass};
			}
			// Literals
			if (!strcmp(stoken, "null")) {
				return (token_t){.type = kNull};
			}
			if (!strcmp(stoken, "true")) {
				return (token_t){.type = kTrue};
			}
	}
	{  // Number constant
		char* end;
		long long num = strtoll(stoken, &end, 0);
		if (*end == '\0') {
			return (token_t){.type = kNum, num = num};
		}
	}
	{  // Identifier and Function call
		regex_t pat_id;
		if (regcomp(&pat_id, "^[a-z][a-zA-Z0-9]*$", REG_EXTENDED | REG_NOSUB)) {
			FAIL("Failed parse token");
		}
		if (!regexec(&pat_id, stoken, 0, NULL, 0)) {
			regfree(&pat_id);
			return (token_t){.type = kId, .str = stoken};
		}
		if (*stoken == '.' && !regexec(&pat_id, stoken + 1, 0, NULL, 0)) {
			regfree(&pat_id);
			return (token_t){.type = kCall, .str = stoken};
		}
		regfree(&pat_id);
	}
	// TODO: resolve other
	return (token_t){.type = kSunc, .str = stoken};
}

token_t* tokenize(char* source) {
	int sz = 0;
	int cap = 4;
	token_t* tokens = malloc(cap * sizeof(*tokens));
	const char* itl = source;
	char* itr = source;
	for (;;) {
		if (*itr != '\0' && !isspace(*itr)) {  // normal symbol
			++itr;
			continue;
		}
		int brk = *itr == '\0';
		if (itl != itr) {  // non empty token
			*itr = '\0';
			token_t token = parse_token(itl);
			if (sz == cap) {
				tokens = realloc(tokens, (cap <<= 1) * sizeof(*tokens));
			}
			tokens[sz++] = token;
			debug_token(&token, itl);
		}
		if (brk) {
			break;
		}
		itl = ++itr;
	}
	return tokens;
}
