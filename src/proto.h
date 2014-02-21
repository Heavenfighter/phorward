/*
 * This is a generated file - manual editing is not recommended!
 */

/* base/dbg.c */
void _dbg_trace( char* file, int line, char* type, char* format, ... );

/* base/llist.c */
LIST* list_push( LIST* list, void* ptr );
LIST* list_pop( LIST* list, void** ptr );
LIST* list_remove( LIST* list, void* ptr );
LIST* list_free( LIST* list );
void list_print( LIST* list, void (*callback)( void* ) );
LIST* list_dup( LIST* src );
int list_find( LIST* list, void* ptr );
void* list_getptr( LIST* list, int cnt );
int list_diff( LIST* first, LIST* second );
LIST* list_union( LIST* first, LIST* second );
int list_count( LIST* list );
pboolean list_subset( LIST* list, LIST* subset );
LIST* list_sort( LIST* list, int (*sf)( void*, void* ) );

/* base/plist.c */
pboolean plist_init( plist* list, psize size, pbyte flags );
plist* plist_create( psize size, pbyte flags );
plist* plist_dup( plist* list );
pboolean plist_erase( plist* list );
pboolean plist_clear( plist* list );
plist* plist_free( plist* list );
plistel* plist_insert( plist* list, plistel* pos, char* key, void* src );
plistel* plist_push( plist* list, void* src );
void* plist_malloc( plist* list );
pboolean plist_remove( plist* list, plistel* e );
pboolean plist_pop( plist* list, void* dest );
plistel* plist_get( plist* list, int n );
plistel* plist_get_by_key( plist* list, char* key );
plistel* plist_get_by_ptr( plist* list, void* ptr );
int plist_union( plist* all, plist* from );
int plist_diff( plist* left, plist* right );
pboolean plist_subsort( plist* list, plistel* from, plistel* to );
pboolean plist_sort( plist* list );
pboolean plist_set_comparefn( plist* list, int (*comparefn)( plist*, plistel*, plistel* ) );
pboolean plist_set_sortfn( plist* list, int (*sortfn)( plist*, plistel*, plistel* ) );
void* plist_access( plistel* e );
char* plist_key( plistel* e );
plistel* plist_next( plistel* u );
plistel* plist_prev( plistel* u );
int plist_offset( plistel* u );
pboolean plist_swap( plistel* a, plistel* b );
plistel* plist_first( plist* l );
plistel* plist_last( plist* l );
int plist_size( plist* l );
int plist_count( plist* l );

/* base/memory.c */
void* pmalloc( psize size );
void* prealloc( void* oldptr, psize size );
void* pfree( void* ptr );
void* pmemdup( void* ptr, psize size );

/* base/stack.c */
pboolean pstack_init( pstack* stack, size_t size, size_t step );
pstack* pstack_create( size_t size, size_t step );
pboolean pstack_erase( pstack* stack );
pstack* pstack_free( pstack* stack );
void* pstack_push( pstack* stack, void* item );
void* pstack_pop( pstack* stack );
void* pstack_access( pstack* stack, size_t offset );
void* pstack_top( pstack* stack );
void* pstack_bottom( pstack* stack );
int pstack_count( pstack* stack );

/* regex/ccl.c */
pregex_ccl* pregex_ccl_create( int min, int max, char* ccldef );
pboolean pregex_ccl_compat( pregex_ccl* l, pregex_ccl* r );
int pregex_ccl_size( pregex_ccl* ccl );
int pregex_ccl_count( pregex_ccl* ccl );
pregex_ccl* pregex_ccl_dup( pregex_ccl* ccl );
pboolean pregex_ccl_testrange( pregex_ccl* ccl, pchar begin, pchar end );
pboolean pregex_ccl_test( pregex_ccl* ccl, pchar ch );
pboolean pregex_ccl_instest( pregex_ccl* ccl, pchar ch );
pboolean pregex_ccl_addrange( pregex_ccl* ccl, pchar begin, pchar end );
pboolean pregex_ccl_add( pregex_ccl* ccl, pchar ch );
pboolean pregex_ccl_delrange( pregex_ccl* ccl, pchar begin, pchar end );
pboolean pregex_ccl_del( pregex_ccl* ccl, pchar ch );
pboolean pregex_ccl_negate( pregex_ccl* ccl );
pregex_ccl* pregex_ccl_union( pregex_ccl* ccl, pregex_ccl* add );
pregex_ccl* pregex_ccl_diff( pregex_ccl* ccl, pregex_ccl* rem );
int pregex_ccl_compare( pregex_ccl* left, pregex_ccl* right );
pregex_ccl* pregex_ccl_intersect( pregex_ccl* ccl, pregex_ccl* within );
pboolean pregex_ccl_get( pchar* from, pchar* to, pregex_ccl* ccl, int offset );
pboolean pregex_ccl_parse( pregex_ccl* ccl, char* ccldef, pboolean extend );
pboolean pregex_ccl_erase( pregex_ccl* ccl );
pregex_ccl* pregex_ccl_free( pregex_ccl* ccl );
char* pregex_ccl_to_str( pregex_ccl* ccl, pboolean escape );
void pregex_ccl_print( FILE* stream, pregex_ccl* ccl, int break_after );

/* regex/dfa.c */
void pregex_dfa_print( pregex_dfa* dfa );
pregex_dfa* pregex_dfa_create( void );
pboolean pregex_dfa_reset( pregex_dfa* dfa );
pregex_dfa* pregex_dfa_free( pregex_dfa* dfa );
int pregex_dfa_from_nfa( pregex_dfa* dfa, pregex_nfa* nfa );
int pregex_dfa_minimize( pregex_dfa* dfa );
int pregex_dfa_match( pregex_dfa* dfa, char* str, size_t* len, int* anchors, pregex_range** ref, int* ref_count, int flags );
int pregex_dfa_to_matrix( pchar*** matrix, pregex_dfa* dfa );

/* regex/direct.c */
int pregex_qmatch( char* regex, char* str, int flags, pregex_range** results );
int pregex_qsplit( char* regex, char* str, int flags, pregex_range** results );
char* pregex_qreplace( char* regex, char* str, char* replace, int flags );

/* regex/misc.c */
pregex_accept* pregex_accept_init( pregex_accept* accept );
pboolean pregex_check_anchors( char* all, char* str, psize len, int anchors, int flags );

/* regex/nfa.c */
pregex_nfa_st* pregex_nfa_create_state( pregex_nfa* nfa, char* chardef, int flags );
void pregex_nfa_print( pregex_nfa* nfa );
pregex_nfa* pregex_nfa_create( void );
pboolean pregex_nfa_reset( pregex_nfa* nfa );
pregex_nfa* pregex_nfa_free( pregex_nfa* nfa );
int pregex_nfa_move( pregex_nfa* nfa, plist* hits, pchar from, pchar to );
int pregex_nfa_epsilon_closure( pregex_nfa* nfa, plist* closure, pregex_accept* accept );
int pregex_nfa_match( pregex_nfa* nfa, char* str, psize* len, int* anchors, pregex_range** ref, int* ref_count, int flags );
int pregex_nfa_from_string( pregex_nfa* nfa, char* str, int flags, int acc );

/* regex/pattern.c */
pregex_ptn* pregex_ptn_create_char( pregex_ccl* ccl );
pregex_ptn* pregex_ptn_create_string( char* str, int flags );
pregex_ptn* pregex_ptn_create_sub( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_alt( pregex_ptn* left, ... );
pregex_ptn* pregex_ptn_create_kle( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_pos( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_opt( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_seq( pregex_ptn* first, ... );
pregex_ptn* pregex_ptn_free( pregex_ptn* ptn );
void pregex_ptn_print( pregex_ptn* ptn, int rec );
int pregex_ptn_to_regex( char** regex, pregex_ptn* ptn );
int pregex_ptn_to_nfa( pregex_nfa* nfa, pregex_ptn* pattern );
int pregex_ptn_parse( pregex_ptn** ptn, char* str, int flags );

/* regex/pregex.c */
pregex* pregex_create( void );
pregex* pregex_free( pregex* regex );
pregex* pregex_reset( pregex* regex );
int pregex_compile( pregex* regex, char* pattern, int accept );
int pregex_finalize( pregex* regex );
pregex_range* pregex_match_next( pregex* regex, char* str );
int pregex_match( pregex* regex, char* str, pregex_range** results );
pregex_range* pregex_split_next( pregex* regex, char* str );
int pregex_split( pregex* regex, char* str, pregex_range** results );
char* pregex_replace( pregex* regex, char* str, char* replacement );
pregex_range* pregex_get_range( pregex* regex );
pregex_range* pregex_get_split( pregex* regex );
pregex_range* pregex_get_ref( pregex* regex, int offset );
int pregex_get_match_count( pregex* regex );
int pregex_get_flags( pregex* regex );
pboolean pregex_set_flags( pregex* regex, int flags );
pregex_fn pregex_get_match_fn( pregex* regex );
pboolean pregex_set_match_fn( pregex* regex, pregex_fn match_fn );

/* regex/range.c */
char* pregex_range_to_string( pregex_range* range );

/* regex/ref.c */
int pregex_ref_init( pregex_range** ref, int* ref_count, int ref_all, int flags );
void pregex_ref_update( pregex_range* ref, char* strp, psize off );

/* string/convert.c */
char* wchar_to_u8( pchar* str, pboolean freestr );
pchar* u8_to_wchar( char* str, pboolean freestr );
char* plong_to_uchar( plong l );
pchar* plong_to_pchar( plong l );
char* pulong_to_uchar( pulong ul );
pchar* pulong_to_pchar( pulong ul );
char* pdouble_to_uchar( pdouble d );
pchar* pdouble_to_pchar( pdouble d );

/* string/string.c */
char* pstrcatchar( char* str, wchar chr );
char* pstrcatstr( char* dest, char* src, boolean freesrc );
char* pstrncatstr( char* str, char* append, psize n );
char* pstrreplace( char* str, char* find, char* replace );
char* pstrdup( char* str );
char* pstrndup( char* str, psize len );
psize pstrlen( char* str );
int psprintf( char* res, char* fmt, ... );
int pvasprintf( char** str, char* fmt, va_list ap );
char* pasprintf( char* fmt, ... );
char* psetstr( char** str, char* val );
char* pgetstr( char* str );
char* pstrrender( char* tpl, ... );
char* pstrltrim( char* s );
char* pstrrtrim( char* s );
char* pstrtrim( char* s );
int pstrsplit( char*** tokens, char* str, char* sep, int limit );
char* pstrupr( char* s );
char* pstrlwr( char* s );
int pstrcasecmp( char* s1, char* s2 );
int pstrncasecmp( char* s1, char* s2, pint n );
int pstrparsechar( wchar* retc, char *str, pboolean escapeseq );
#ifdef UNICODE
pchar* pwcsdup( pchar* str );
int pwcsprintf( pchar* res, pchar* fmt, ... );
int pvawcsprintf( pchar** str, pchar* fmt, va_list ap );
pchar* pawcsprintf( pchar* fmt, ... );
pchar* pwcscatchar( pchar* str, wchar chr );
pchar* pwcscatstr( pchar* dest, pchar* src, boolean freesrc );
pchar* pwcsncatstr( pchar* str, pchar* append, psize num );
psize pwcslen( pchar* str );
#endif

/* string/utf8.c */
pboolean u8_isutf( pbyte c );
int u8_seqlen(char *s);
wchar u8_char( char* str );
char* u8_move( char* str, int count );
wchar u8_parse_char( char** ch );
int u8_toucs(wchar *dest, int sz, char *src, int srcsz);
int u8_toutf8(char *dest, int sz, wchar *src, int srcsz);
int u8_wc_toutf8(char *dest, wchar ch);
int u8_offset(char *str, int charnum);
int u8_charnum(char *s, int offset);
int u8_strlen(char *s);
wchar u8_nextchar(char *s, int *i);
void u8_inc(char *s, int *i);
void u8_dec(char *s, int *i);
int octal_digit(char c);
int hex_digit(char c);
int u8_read_escape_sequence(char *str, wchar *dest);
int u8_unescape(char *buf, int sz, char *src);
int u8_escape_wchar(char *buf, int sz, wchar ch);
int u8_escape(char *buf, int sz, char *src, int escape_quotes);
char *u8_strchr(char *s, wchar ch, int *charn);
char *u8_memchr(char *s, wchar ch, size_t sz, int *charn);
int u8_is_locale_utf8(char *locale);

/* util/system.c */
char* pwhich( char* filename, char* directories );
char* pbasename( char* path );
pboolean pfileexists( char* filename );
int map_file( char** cont, char* filename );
pint pgetopt( char* opt, char** param, pint* next, pint argc, char** argv, char* optstr, char* loptstr, pint idx );

/* union/union.c */
pboolean punion_init( punion* var );
punion* punion_create( void );
pboolean punion_reset( punion* var );
punion* punion_free( punion* u );

/* union/union.conv.c */
pbyte punion_to_byte( punion* var );
char punion_to_char( punion* var );
pint punion_to_int( punion* var );
plong punion_to_long( punion* var );
pulong punion_to_ulong( punion* var );
pfloat punion_to_float( punion* var );
pdouble punion_to_double( punion* var );
char* punion_to_string( punion* var );
pchar* punion_to_wstring( punion* var );
pint punion_convert( punion* var, pbyte type );

/* union/union.get.c */
pbyte punion_get_byte( punion* var );
char punion_get_char( punion* var );
pint punion_get_int( punion* var );
plong punion_get_long( punion* var );
pulong punion_get_ulong( punion* var );
pfloat punion_get_float( punion* var );
pdouble punion_get_double( punion* var );
char* punion_get_cstring( punion* var );
char* punion_get_string( punion* var );
pchar* punion_get_wcstring( punion* var );
pchar* punion_get_wstring( punion* var );

/* union/union.set.c */
pbyte punion_set_byte( punion* var, pbyte b );
char punion_set_char( punion* var, char c );
pint punion_set_int( punion* var, pint i );
plong punion_set_long( punion* var, plong l );
pulong punion_set_ulong( punion* var, pulong ul );
pfloat punion_set_float( punion* var, pfloat f );
pdouble punion_set_double( punion* var, pdouble d );
char* punion_set_cstring( punion* var, char* s );
char* punion_set_string( punion* var, char* s );
pchar* punion_set_wcstring( punion* var, pchar* ws );
pchar* punion_set_wstring( punion* var, pchar* ws );

/* xml/xml.c */
XML_T xml_child( XML_T xml, char* name );
XML_T xml_idx( XML_T xml, int idx );
char* xml_attr( XML_T xml, char* attr );
plong xml_int_attr( XML_T xml, char* attr );
pdouble xml_float_attr( XML_T xml, char* attr );
XML_T xml_vget( XML_T xml, va_list ap );
XML_T xml_get( XML_T xml, ... );
char ** xml_pi( XML_T xml, char* target );
char* xml_decode( char* s, char ** ent, char t );
char* xml_str2utf8( char ** s, size_t* len );
void xml_free_attr( char ** attr );
XML_T xml_parse_str( char* s, size_t len );
XML_T xml_parse_fp( FILE* fp );
XML_T xml_parse_file( char* file );
char* xml_ampencode( char* s, size_t len, char ** dst, size_t* dlen, size_t* max, short a );
char* xml_toxml( XML_T xml );
void xml_free( XML_T xml );
char* xml_error( XML_T xml );
XML_T xml_new( char* name );
XML_T xml_insert( XML_T xml, XML_T dest, size_t off );
XML_T xml_add_child( XML_T xml, char* name, size_t off );
XML_T xml_set_txt( XML_T xml, char* txt );
XML_T xml_set_attr( XML_T xml, char* name, char* value );
XML_T xml_set_int_attr( XML_T xml, char* name, plong value );
XML_T xml_set_float_attr( XML_T xml, char* name, pdouble value );
XML_T xml_set_flag( XML_T xml, short flag );
int xml_count( XML_T xml );
int xml_count_all( XML_T xml );
XML_T xml_cut( XML_T xml );

/* grammar/astnode.c */
pgastnode* pg_astnode_create( pgasttype* type );
pgastnode* pg_astnode_free( pgastnode* node );
void pg_astnode_print( pgastnode* node, FILE* stream );
pgasttype* pg_astnode_get_type( pgastnode* node );
pgsymbol* pg_astnode_get_symbol( pgastnode* node );
pboolean pg_astnode_set_symbol( pgastnode* node, pgsymbol* symbol );
pgtoken* pg_astnode_get_token( pgastnode* node );
pboolean pg_astnode_set_token( pgastnode* node, pgtoken* token );

/* grammar/asttype.c */
pgasttype* pg_asttype_create( pggrammar* g, char* name );
pgasttype* pg_asttype_get_by_name( pggrammar* g, char* name );
char* pg_asttype_get_name( pgasttype* asttype );
size_t pg_asttype_get_size( pgasttype* asttype );
pboolean pg_asttype_set_size( pgasttype* asttype, size_t size );
pgastfn pg_asttype_get_topdown( pgasttype* asttype );
pboolean pg_asttype_set_topdown( pgasttype* asttype, pgastfn topdown );
pboolean pg_asttype_call_topdown( pgasttype* asttype, pgastnode* node );
pgastfn pg_asttype_get_passover( pgasttype* asttype );
pboolean pg_asttype_set_passover( pgasttype* asttype, pgastfn passover );
pboolean pg_asttype_call_passover( pgasttype* asttype, pgastnode* node );
pgastfn pg_asttype_get_bottomup( pgasttype* asttype );
pboolean pg_asttype_set_bottomup( pgasttype* asttype, pgastfn bottomup );
pboolean pg_asttype_call_bottomup( pgasttype* asttype, pgastnode* node );

/* grammar/bnf.c */
void pg_grammar_from_bnf( void );

/* grammar/error.c */
void PGERR( pggrammar* g, char* file, int line, char* fmt, ... );

/* grammar/grammar.c */
pggrammar* pg_grammar_create( void );
pggrammar* pg_grammar_free( pggrammar* g );
void pg_grammar_print( pggrammar* g );
BOOLEAN pg_grammar_compute_first( pggrammar* g );
BOOLEAN pg_grammar_compute_follow( pggrammar* g );
BOOLEAN pg_grammar_compute_select( pggrammar* g );
pgterminal* pg_grammar_get_goal( pggrammar* g );
BOOLEAN pg_grammar_set_goal( pggrammar* g, pgnonterminal* goal );
pgterminal* pg_grammar_get_eoi( pggrammar* g );
BOOLEAN pg_grammar_set_eoi( pggrammar* g, pgterminal* eoi );
BOOLEAN pg_grammar_parse_whitespace( pggrammar* grammar, char* str );
BOOLEAN pg_grammar_set_whitespace( pggrammar* grammar, pregex_ptn* whitespace );
pregex_ptn* pg_grammar_get_whitespace( pggrammar* grammar );

/* grammar/nonterm.c */
pgnonterminal* pg_nonterminal_create( pggrammar* grammar, char* name );
pgnonterminal* pg_nonterminal_drop( pgterminal* nonterminal );
pgnonterminal* pg_nonterminal_get( pggrammar* g, int offset );

/* grammar/production.c */
pgproduction* pg_production_create( pgnonterminal* lhs, ... );
pgproduction* pg_production_drop( pgproduction* p );
char* pg_production_to_string( pgproduction* p );
void pg_production_print( pgproduction* p, FILE* f );
pboolean pg_production_append( pgproduction* p, pgsymbol* sym );
pboolean pg_production_append_with_key( pgproduction* p, char* key, pgsymbol* sym );
pgproduction* pg_production_get( pggrammar* grammar, int i );
pgproduction* pg_production_get_by_lhs( pgnonterminal* lhs, int i );
pgsymbol* pg_production_get_rhs( pgproduction* p, int i );
pgsymbol* pg_production_get_rhs_by_key( pgproduction* p, char* key );
int pg_production_get_id( pgproduction* p );
pggrammar* pg_production_get_grammar( pgproduction* p );
pgnonterminal* pg_production_get_lhs( pgproduction* p );
int pg_production_get_rhs_length( pgproduction* p );
pgasttype* pg_production_get_asttype( pgproduction* p );
pboolean pg_production_set_asttype( pgproduction* p, pgasttype* type );

/* grammar/symbol.c */
pgsymbol* pg_symbol_create( pggrammar* grammar, pgsymtype type, char* name );
pgsymbol* pg_symbol_free( pgsymbol* symbol );
BOOLEAN pg_symbol_reset( pgsymbol* s );
void pg_symbol_print( pgsymbol* symbol, FILE* f );
BOOLEAN pg_symbol_is_terminal( pgsymbol* symbol );
BOOLEAN pg_symbol_is_nonterminal( pgsymbol* symbol );
pgsymbol* pg_symbol_get( pggrammar* g, int i );
pgsymbol* pg_symbol_get_by_id( pggrammar* g, int id );
int pg_symbol_get_id( pgsymbol* s );
pgsymtype pg_symbol_get_type( pgsymbol* s );
pggrammar* pg_symbol_get_grammar( pgsymbol* s );
char* pg_symbol_get_name( pgsymbol* s );

/* grammar/terminal.c */
pgterminal* pg_terminal_create( pggrammar* grammar, char* name, char* pattern );
pgterminal* pg_terminal_drop( pgterminal* terminal );
pgterminal* pg_terminal_get( pggrammar* g, int offset );
BOOLEAN pg_terminal_parse_pattern( pgterminal* terminal, char* pattern );
BOOLEAN pg_terminal_set_pattern( pgterminal* terminal, pregex_ptn* ptn );
pregex_ptn* pg_terminal_get_pattern( pgterminal* terminal );

/* grammar/token.c */
pgtoken* pg_token_create( pgsymbol* sym, char* lexem );
pboolean pg_token_reset( pgtoken* tok );
pgtoken* pg_token_free( pgtoken* tok );
void pg_token_print( pgtoken* tok );
pboolean pg_token_set_symbol( pgtoken* tok, pgsymbol* symbol );
pgsymbol* pg_token_get_symbol( pgtoken* tok );
pboolean pg_token_set_lexem( pgtoken* tok, char* lexem );
char* pg_token_get_lexem( pgtoken* tok );
pboolean pg_token_set_wlexem( pgtoken* tok, pchar* lexem );
pchar* pg_token_get_wlexem( pgtoken* tok );

/* lexer/lexer.c */
pglexer* pg_lexer_create( pgparser* parser );
pboolean pg_lexer_reset( pglexer* lex );
pglexer* pg_lexer_free( pglexer* lex );
pboolean pg_lexer_set_source( pglexer* lex, int type, void* ptr );
char* pg_lexer_isolate( pglexer* lex );
pgtoken* pg_lexer_fetch( pglexer* lex );

/* parser/lr.gen.c */
BOOLEAN pg_parser_lr_closure( pgparser* parser );
BOOLEAN pg_parser_lr_reset( pgparser* parser );

/* parser/lr.parse.c */
pboolean pg_parser_lr_parse( pgparser* parser );

/* parser/parser.c */
pgparser* pg_parser_create( pggrammar* grammar, pgparadigm paradigm );
pgparser* pg_parser_free( pgparser* parser );
BOOLEAN pg_parser_generate( pgparser* p );
BOOLEAN pg_parser_parse( pgparser* p );
BOOLEAN pg_parser_is_lr( pgparser* p );
BOOLEAN pg_parser_is_ll( pgparser* p );
pggrammar* pg_parser_get_grammar( pgparser* p );
pboolean pg_parser_get_optimize( pgparser* p );
pboolean pg_parser_set_optimize( pgparser* p, pboolean optimize );
char* pg_parser_get_source( pgparser* p );
pboolean pg_parser_set_source( pgparser* p, char* source );

