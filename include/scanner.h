#pragma once

#include "tokenizer.h"

typedef enum {
	kScnOk,		   // no errors
	kScnPosBal,	   // positive balance
	kScnOutFunc,   // outside func (negative balance)
	kScnNestFunc,  // nested func
	kScnBadPass,   // pass without once
	kScnNoExpr,	   // expected expression
	kScnNoVar,	   // expected variable
} scn_err_t;

scn_err_t scan_tokens(const token_t* v_tok);

const char* scan_error(scn_err_t err);
