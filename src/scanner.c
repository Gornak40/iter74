#include "scanner.h"

#include <stdbool.h>
#include <stdlib.h>

#include "tokenizer.h"
#include "utils.h"

typedef struct {
	token_typ_t* v_st;
	token_typ_t prv;
	int func_cnt;
} scn_state_t;

scn_state_t* scn_state_new() {
	scn_state_t* s = malloc(sizeof(*s));
	vec_new(&s->v_st, 1);
	s->prv = -1;
	s->func_cnt = 0;
	return s;
}

void scn_state_free(scn_state_t* s) {
	vec_free(s->v_st);
	free(s);
}

static scn_err_t scan_momentum(token_typ_t cur, scn_state_t* s) {
	if (!s->func_cnt && cur != kFunc) {
		return kScnOutFunc;
	}
	if (s->func_cnt && cur == kFunc) {
		return kScnNestFunc;
	}
	token_typ_t old = s->prv;
	s->prv = cur;
	switch (cur) {
		case kFunc:	 // TODO: fix nested
			s->func_cnt++;
			vec_push(&s->v_st, cur);
			break;
		case kStop:
			if (s->v_st[vec_len(s->v_st) - 1] == kFunc) {
				s->func_cnt--;
			}
			vec_pop(s->v_st);
			break;
		case kIter:
			vec_push(&s->v_st, cur);
			break;
		case kOnce:
			vec_push(&s->v_st, cur);
			break;
		case kPass:
			if (vec_len(s->v_st) == 0 || s->v_st[vec_len(s->v_st) - 1] != kOnce) {
				return kScnBadPass;
			}
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
	}
	return "Unknown error";
}
