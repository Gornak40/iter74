#pragma once

typedef enum {
	kFunc,	// func (function declaration)
	kStop,	// stop (})
	kIter,	// iter (while)
	kHalt,	// halt (break/return)
	kOnce,	// once (if)
	kPass,	// pass (elif)

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

token_t parse_token(const char* stoken);

// Lifetime of source must be longer than result's.
token_t* tokenize(char* source);
