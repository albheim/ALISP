#include <editline/readline.h>

#include "mpc.h"


long eval_op(int x, char* op, int y) {
	if (strcmp(op, "+") == 0) return x + y;
	if (strcmp(op, "-") == 0) return x - y;
	if (strcmp(op, "*") == 0) return x * y;
	if (strcmp(op, "/") == 0) return x / y;
	return 0;
}


long eval(mpc_ast_t* t)
{
	if (strstr(t->tag, "number")) {
		if (strstr(t->tag, "integer")) {
			return atoi(t->contents);
		}
		else {
			return atof(t->contents);
		}
	}

	char* op = t->children[1]->contents;
	printf("%s ", op);

	long x = eval(t->children[2]); // only supports integers so far
	printf("%l ", x);

	int i = 3;
	while (strstr(t->children[i]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[i]));
		printf("%l ", x);
		i++;
	}

	return x;
}

int main()
{
	mpc_parser_t* integer = mpc_new("integer");
	mpc_parser_t* decimal = mpc_new("decimal");
	mpc_parser_t* number = mpc_new("number");
	mpc_parser_t* operator = mpc_new("operator");
	mpc_parser_t* expr = mpc_new("expr");
	mpc_parser_t* alisp = mpc_new("alisp");

	mpca_lang(MPCA_LANG_DEFAULT,
			"							\
			integer	 : /-?[0-9]+/ ;					\
			decimal  : /-?[0-9]+(\\.[0-9]+)/ ;           \
			number   : <decimal> | <integer> ;          \
			operator : '+' | '-' | '*' | '/' ;			\
			expr     : <number> | '(' <operator> <expr>+ ')' ;	\
			alisp    : /^/ <operator> <expr>+ /$/ ;			\
			",
			integer, decimal, number, operator, expr, alisp);


	printf("ALISP interactive prompt version 0.0.1c\n");
	printf("Press Ctrl-C to exit\n");

	while (1) {
		char* input = readline("alisp> ");

		add_history(input);

		mpc_result_t r;
		if (mpc_parse("<stdin>", input, alisp, &r)) {
			long result = eval(r.output);
			printf("%li\n", result);
			mpc_ast_print(r.output);
			mpc_ast_delete(r.output);
		} else {
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}

		free(input);
	}

	mpc_cleanup(6, integer, decimal, number, operator, expr, alisp);

	return 0;
}


