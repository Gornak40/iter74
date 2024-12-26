#pragma once

#include <regex.h>
#include <stdint.h>

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

	kNum,  // integer constant (228)

	kId,   // identifier (var)
	kPId,  // pointer identifier (Var)
	kTId,  // typed itentifier (type_Var)

	kSetId,	   // a=
	kSetPId,   // A=
	kSetTId,   // T_A=
	kSetNull,  // null=
	kSetFunc,  // func=

	kStorePId,	// A<-

	kCall,	 // function call (.function)
	kPCall,	 // pointer function call (.Function)
	kTCall,	 // typed function call (.type_Function)

	kSunc,	// any other token
} token_typ_t;

typedef uint64_t token_mask_t;

static const token_mask_t kMaskAll = -1;

static const token_mask_t kMaskIdExpr =
	(1 << kNull) | (1 << kTrue) | (1 << kNum) | (1 << kId) | (1 << kCall) | (1 << kSunc);

static const token_mask_t kMaskPIdExpr =
	(1 << kNull) | (1 << kPId) | (1 << kPCall) | (1 << kSunc);

static const token_mask_t kMaskTIdExpr =
	(1 << kNull) | (1 << kTId) | (1 << kTCall) | (1 << kSunc);

static const token_mask_t kMaskExpr = kMaskIdExpr | kMaskPIdExpr | kMaskTIdExpr;

static const token_mask_t kMaskVar = (1 << kId) | (1 << kPId) | (1 << kTId);

static const token_mask_t kMaskCall = (1 << kCall) | (1 << kPCall) | (1 << kTCall);

static const token_mask_t kMaskConst = (1 << kNull) | (1 << kTrue) | (1 << kNum);

static const token_mask_t kMaskStrP = kMaskVar | kMaskCall | (1 << kSunc) |
									  (1 << kSetId) | (1 << kSetPId) | (1 << kSetTId) |
									  (1 << kStorePId);

typedef struct {
	token_typ_t type;
	int b_off;	// byte offset
	union {
		long long num;
		char* str;
	};
} token_t;

void debug_token(const token_t* t, const char* s);

#define TOKENIZER_INI_CAP 2

typedef struct {
	token_t* v_tok;
	regex_t reg_id;
	regex_t reg_pid;
	regex_t reg_tid;
} tokenizer_t;

tokenizer_t* tokenizer_new();

void tokenizer_feed(tokenizer_t* t, const char* source);

token_t tokenizer_token(tokenizer_t* t, const char* stoken);

void tokenizer_free(tokenizer_t* t);
