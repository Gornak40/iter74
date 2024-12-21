#pragma once

#include "tokenizer.h"

typedef enum {
	kScnOk,
} scn_err_t;

scn_err_t scan_tokens(const token_t* v_tok);

const char* scan_error(scn_err_t err);
