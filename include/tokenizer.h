#pragma once

#include <regex.h>
typedef enum {
	kFunc,	// func (function declaration)
	kStop,	// stop (})
	kIter,	// iter (while)
	kHalt,	// halt (break/return)
	kOnce,	// once (if)
	kPass,	// pass (elif)
	kType,	// struct syntax sugar (type)

	kNull,	// null (read/write 0)
	kTrue,	// true (read -1)

	kSet,	 // =
	kStore,	 // <-

	kNum,  // integer constant (228)

	kId,   // identifier (var)
	kPId,  // pointer identifier (Var)
	kTId,  // typed itentifier (type_Var)

	kCall,	 // function call (.function)
	kPCall,	 // pointer function call (.Function)
	kTCall,	 // typed function call (.type_Function)

	kSunc,	// any other token
} token_typ_t;

typedef struct {
	token_typ_t type;
	union {
		long long num;
		const char* str;
	};
} token_t;

void debug_token(const token_t* t, const char* s);

typedef struct {
	int len;
	int cap;
	token_t* tokens;
	regex_t reg_id;
	regex_t reg_pid;
	regex_t reg_tid;
} tokenizer_t;

tokenizer_t* tokenizer_new();

// Lifetime of source must be longer than result's.
void tokenizer_feed(tokenizer_t* t, char* source);

token_t tokenizer_token(tokenizer_t* t, const char* stoken);

void tokenizer_free(tokenizer_t* t);
