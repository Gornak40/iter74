#pragma once

#include "tokenizer.h"

typedef enum {
	kScnOk,		   // no errors
	kScnNegBal,	   // negative balance
	kScnPosBal,	   // positive balance
	kScnOutFunc,   // outside func
	kScnNestFunc,  // nested func
	kScnBadPass,   // pass without once
} scn_err_t;

scn_err_t scan_tokens(const token_t* v_tok);

const char* scan_error(scn_err_t err);
