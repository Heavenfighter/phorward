#include <phorward.h>

PG_AST_FUNC( tadd )
{
	switch( astpass )
	{
		case PGASTPASS_RECOGNIZE:
			break;
		case PGASTPASS_TOPDOWN:
			break;
		case PGASTPASS_PASSOVER:
			break;
		case PGASTPASS_BOTTOMUP:
			fprintf( stderr, "ADD\n" );
			break;

		default:
			MISSINGCASE;
			break;
	}
}

PG_AST_FUNC( tsub )
{
	switch( astpass )
	{
		case PGASTPASS_RECOGNIZE:
			break;
		case PGASTPASS_TOPDOWN:
			break;
		case PGASTPASS_PASSOVER:
			break;
		case PGASTPASS_BOTTOMUP:
			fprintf( stderr, "SUB\n" );
			break;

		default:
			MISSINGCASE;
			break;
	}
}

PG_AST_FUNC( tmul )
{
	switch( astpass )
	{
		case PGASTPASS_RECOGNIZE:
			break;
		case PGASTPASS_TOPDOWN:
			break;
		case PGASTPASS_PASSOVER:
			break;
		case PGASTPASS_BOTTOMUP:
			fprintf( stderr, "MUL\n" );
			break;

		default:
			MISSINGCASE;
			break;
	}
}

PG_AST_FUNC( tdiv )
{
	switch( astpass )
	{
		case PGASTPASS_RECOGNIZE:
			break;
		case PGASTPASS_TOPDOWN:
			break;
		case PGASTPASS_PASSOVER:
			break;
		case PGASTPASS_BOTTOMUP:
			fprintf( stderr, "DIV\n" );
			break;

		default:
			MISSINGCASE;
			break;
	}
}

int main()
{
	pggrammar*		g;
	pgparser*		p;
	pgparser*		p2;

	pgterminal*		i;
	pgterminal*		op_a;
	pgterminal*		op_s;
	pgterminal*		op_d;
	pgterminal*		op_m;
	pgterminal*		br_op;
	pgterminal*		br_cl;

	pgnonterminal*	start;
	pgnonterminal*	expr;
	pgnonterminal*	term;
	pgnonterminal*	factor;

	pgtoken*		tok;

	g = pg_grammar_create();

	i = pg_terminal_create( g, "@INTEGER", "[0-9]+" );
	op_a = pg_terminal_create( g, "+", "\\+" );
	op_s = pg_terminal_create( g, "-", "-" );
	op_d = pg_terminal_create( g, "/", "/" );
	op_m = pg_terminal_create( g, "*", "\\*" );
	br_op = pg_terminal_create( g, "(", "\\(" );
	br_cl = pg_terminal_create( g, ")", "\\)" );

	start = pg_nonterminal_create( g, "start" );
	expr = pg_nonterminal_create( g, "expr" );
	term = pg_nonterminal_create( g, "term" );
	factor = pg_nonterminal_create( g, "factor" );

	/*
	pg_production_create( start, expr, (pgsymbol*)NULL );
	pg_production_create( expr, expr, op_a, term, (pgsymbol*)NULL );
	pg_production_create( expr, expr, op_s, term, (pgsymbol*)NULL );
	pg_production_create( expr, term, (pgsymbol*)NULL );
	pg_production_create( term, term, op_m, factor, (pgsymbol*)NULL );
	pg_production_create( term, term, op_d, factor, (pgsymbol*)NULL );
	pg_production_create( term, factor, (pgsymbol*)NULL );
	pg_production_create( factor, br_op, expr, br_cl, (pgsymbol*)NULL );
	pg_production_create( factor, i, (pgsymbol*)NULL );
	*/

	/* start */
	pg_production_create( start, expr, (pgsymbol*)NULL );

	/* expr */
	pg_production_create_as_node( expr, "add", tadd,
		expr, op_a, term, (pgsymbol*)NULL );
	pg_production_create_as_node( expr, "sub", tsub,
		expr, op_s, term, (pgsymbol*)NULL );
	pg_production_create( expr, term, (pgsymbol*)NULL );

	/* term */
	pg_production_create_as_node( term, "mul", tmul,
		term, op_m, factor, (pgsymbol*)NULL );
	pg_production_create_as_node( term, "div", tdiv,
		term, op_d, factor, (pgsymbol*)NULL );
	pg_production_create( term, factor, (pgsymbol*)NULL );

	/* factor */
	pg_production_create( factor, br_op, expr, br_cl, (pgsymbol*)NULL );
	pg_production_create( factor, i, (pgsymbol*)NULL );

	pg_grammar_print( g );

	/*
	pgterminal*		test;
	pgterminal*		test2;

	g = pg_grammar_create();
	test = pg_terminal_create( g, "INTEGER", "[0-9]+" );
	test2 = pg_terminal_create( g, "NAME", "[A-Za-z_!]+" );
	start = pg_nonterminal_create( g, "start" );
	pg_production_create( start, test, test2, (pgsymbol*)NULL );
	pg_grammar_print( g );
	*/

	p = pg_parser_create( g, PGPARADIGM_LALR1 );

	pg_lexer_set_source( p->lexer, PG_LEX_SRCTYPE_STRING, "1*2+3" );
	pg_parser_parse( p );

	getchar();
	fprintf( stderr, "------------------------------\n" );

	pg_lexer_set_source( p->lexer, PG_LEX_SRCTYPE_STRING, "(7+3)*2-5" );
	pg_parser_parse( p );

	return 0;
}
