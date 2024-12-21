#include "tokenizer.h"

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void debug_token(const token_t* t, const char* s) {
	fprintf(stderr, "DBG(token): %s (%d:%d) [%d]:", s, t->b_off,
			t->b_off + (int)strlen(s), t->type);
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

token_t tokenizer_token(tokenizer_t* t, const char* stoken) {
	switch (strlen(stoken)) {  // perfomance trick
		case 1:
			// operators
			if (!strcmp(stoken, "=")) {
				return (token_t){.type = kSet};
			}
		case 2:
			// operators
			if (!strcmp(stoken, "<-")) {
				return (token_t){.type = kStore};
			}
		case 4:
			// keywords
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
			if (!strcmp(stoken, "type")) {
				return (token_t){.type = kType};
			}
			// literals
			if (!strcmp(stoken, "null")) {
				return (token_t){.type = kNull};
			}
			if (!strcmp(stoken, "true")) {
				return (token_t){.type = kTrue};
			}
	}
	{  // number constant
		char* end;
		long long num = strtoll(stoken, &end, 0);
		if (*end == '\0') {
			return (token_t){.type = kNum, num = num};
		}
	}
	{  // identifier and function call
		if (!regexec(&t->reg_id, stoken, 0, NULL, 0)) {
			return (token_t){.type = kId, .str = strdup(stoken)};
		}
		if (*stoken == '.' && !regexec(&t->reg_id, stoken + 1, 0, NULL, 0)) {
			return (token_t){.type = kCall, .str = strdup(stoken + 1)};
		}
	}
	{  // pointer identifier and pointer function call
		if (!regexec(&t->reg_pid, stoken, 0, NULL, 0)) {
			return (token_t){.type = kPId, .str = strdup(stoken)};
		}
		if (*stoken == '.' && !regexec(&t->reg_pid, stoken + 1, 0, NULL, 0)) {
			return (token_t){.type = kPCall, .str = strdup(stoken + 1)};
		}
	}
	{  // typed identifier and typed function call
		if (!regexec(&t->reg_tid, stoken, 0, NULL, 0)) {
			return (token_t){.type = kTId, .str = strdup(stoken)};
		}
		if (*stoken == '.' && !regexec(&t->reg_tid, stoken + 1, 0, NULL, 0)) {
			return (token_t){.type = kTCall, .str = strdup(stoken + 1)};
		}
	}
	return (token_t){.type = kSunc, .str = strdup(stoken)};
}

tokenizer_t* tokenizer_new() {
	tokenizer_t* t = malloc(sizeof(*t));
	vec_new(&t->v_tok, TOKENIZER_INI_CAP);
	if (regcomp(&t->reg_id, "^[a-z][a-zA-Z0-9]*$", REG_EXTENDED | REG_NOSUB)) {
		FAIL("Invalid id regex in tokenizer");
	}
	if (regcomp(&t->reg_pid, "^[A-Z][a-zA-Z0-9]*$", REG_EXTENDED | REG_NOSUB)) {
		FAIL("Invalid pid regex in tokenizer");
	}
	if (regcomp(&t->reg_tid, "^[a-z]+_[A-Z][a-zA-Z0-9]*$", REG_EXTENDED | REG_NOSUB)) {
		FAIL("Invalid tid regex in tokenizer");
	}
	return t;
}

void tokenizer_feed(tokenizer_t* t, const char* source) {
	const char* itl = source;
	const char* itr = source;
	for (;;) {
		if (*itr != '\0' && !isspace(*itr)) {  // normal symbol
			++itr;
			continue;
		}
		if (itl != itr) {  // non empty token
			char* tok = strndup(itl, itr - itl);
			token_t token = tokenizer_token(t, tok);
			token.b_off = itl - source;
			vec_push(&t->v_tok, token);
			debug_token(&token, tok);
			free(tok);
		}
		if (*itr == '\0') {
			break;
		}
		itl = ++itr;
	}
}

void tokenizer_free(tokenizer_t* t) {
	for (token_t* it = t->v_tok; it != t->v_tok + vec_len(t->v_tok); ++it) {
		switch (it->type) {
			case kId:
			case kPId:
			case kTId:
			case kCall:
			case kPCall:
			case kTCall:
			case kSunc:
				free(it->str);
				break;
			default:
				break;
		}
	}
	vec_free(t->v_tok);
	regfree(&t->reg_id);
	regfree(&t->reg_pid);
	regfree(&t->reg_tid);
	free(t);
}
