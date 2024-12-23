#include "scanner.h"

#include <stdbool.h>
#include <stdlib.h>

#include "tokenizer.h"
#include "utils.h"

typedef struct {
	token_typ_t* v_st;	 // global balance stack
	token_typ_t prv;	 // previous token type
	token_mask_t allow;	 // allowed token types mask
	scn_err_t prom_err;	 // error if token type is not allowed
} scn_state_t;

scn_state_t* scn_state_new() {
	scn_state_t* s = malloc(sizeof(*s));
	vec_new(&s->v_st, 1);
	s->prv = -1;
	s->allow = 1 << kFunc;
	s->prom_err = kScnOutFunc;
	return s;
}

void scn_state_free(scn_state_t* s) {
	vec_free(s->v_st);
	free(s);
}

static scn_err_t scan_momentum(token_typ_t cur, scn_state_t* s) {
	if ((s->allow & (1 << cur)) == 0) {
		return s->prom_err;
	}
	if (vec_len(s->v_st) == 0 && cur != kFunc) {
		return kScnOutFunc;
	}
	s->prv = cur;
	s->allow = kMaskAll;
	switch (cur) {
		case kFunc:	 // TODO: fix nested
			if (vec_len(s->v_st) == 0) {
				vec_push(&s->v_st, cur);
				s->allow = kMaskVar;
				s->prom_err = kScnNoVar;
			} else {
				s->allow = (1 << kSet);
				s->prom_err = kScnNestFunc;
			}
			break;
		case kStop:
			vec_pop(s->v_st);
			break;
		case kIter:
		case kOnce:
			vec_push(&s->v_st, cur);
			s->allow = kMaskExpr;
			s->prom_err = kScnNoExpr;
			break;
		case kPass:
			if (vec_len(s->v_st) == 0 || s->v_st[vec_len(s->v_st) - 1] != kOnce) {
				return kScnBadPass;
			}
			s->allow = kMaskExpr;
			s->prom_err = kScnNoExpr;
			break;
		case kSet:
		case kStore:
			s->allow = kMaskExpr;
			s->prom_err = kScnNoExpr;
			break;
		default:  // TODO: better checks
			break;
	}
	return kScnOk;
}

// TODO: scan for easy errors and store functions
scn_err_t scan_tokens(const token_t* v_tok) {
	scn_state_t* stat = scn_state_new();
	for (int i = 0; i < vec_len(v_tok); ++i) {
		scn_err_t err = scan_momentum(v_tok[i].type, stat);
		if (err != kScnOk) {
			scn_state_free(stat);
			return err;
		}
	}
	if (vec_len(stat->v_st) != 0) {
		scn_state_free(stat);
		return kScnPosBal;
	}
	scn_state_free(stat);
	return kScnOk;
}

const char* scan_error(scn_err_t err) {
	switch (err) {
		case kScnOk:
			return "OK";
		case kScnPosBal:
			return "Missing stop";
		case kScnOutFunc:
			return "Out of func declaration";
		case kScnNestFunc:
			return "Nested func declaration";
		case kScnBadPass:
			return "Pass not paired with once";
		case kScnNoExpr:
			return "Expected expression";
		case kScnNoVar:
			return "Expected variable parameter";
	}
	return "Unknown error";
}
