#include "scanner.h"

// TODO: scan for easy errors and store functions
scn_err_t scan_tokens(const token_t* v_tok) { return kScnOk; }

const char* scan_error(scn_err_t err) {
	switch (err) {
		case kScnOk:
			return "OK";
	}
}
