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
} token_typ_t;

typedef struct {
	token_typ_t type;
} token_t;

token_t* tokenize(const char* source);
