/*
	This file was automatically generated by pinclude.
	Source files: phorward.tpl.h
*/



#ifndef _PHORWARD_H
#define _PHORWARD_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <stdarg.h>

#ifndef va_copy
#define va_copy( a, b )	(a) = (b)
#endif

#include <limits.h>
#include <time.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>

#ifdef UNICODE
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#endif

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#endif




#ifdef UNICODE
typedef wchar_t					wchar;
#else
typedef unsigned int			wchar;
#endif


typedef unsigned char			pbyte;		
typedef wchar					pchar;		
typedef char					uchar;		
typedef	int						pint;		
typedef	float					pfloat;		
typedef double					pdouble;	
typedef long					plong;		
typedef size_t					pulong;		
typedef size_t					psize;		



typedef char 					pboolean;	
#define BOOLEAN					pboolean
#define boolean 				pboolean

#ifndef TRUE
#define TRUE					1
#endif

#ifndef FALSE
#define FALSE					0
#endif

#define BOOLEAN_STR( b ) 		( ( b ) ? "TRUE" : "FALSE" )
#define TRUEBOOLEAN( b ) 		( ( b ) ? TRUE : FALSE )


#define ERR_OK					0		
#define ERR_FAILURE				-1		
#define ERR_PARMS				-2		
#define ERR_MEM					-3		
#define ERR_SYSTEM				-4		
#define ERR_UNIMPL				-5		
#define ERR_OTHER				-6		


#define OUTOFMEM				fprintf( stderr, \
									"%s, %d: Ran out of memory\n", \
										__FILE__, __LINE__ ), exit( 1 )

#define WRONGPARAM				fprintf( stderr, \
									"%s, %d: Function called with wrong or " \
									"incomplete parameters, fix your call!\n", \
										__FILE__, __LINE__ )

#define MISSINGCASE				fprintf( stderr, \
									"%s, %d: Missing case enganged, " \
									"please check for correctness.", \
									__FILE__, __LINE__ )

#define TODO					fprintf( stderr, \
									"%s, %d: TODO alert! The program ran into "\
									"a module that is not finished yet!\n", \
											__FILE__, __LINE__ )


#ifndef _WIN32
#define PDIRSEP					':'
#define PPATHSEP				'/'
#else
#define PDIRSEP					';'
#define PPATHSEP				'\\'
#endif


#define bit_set( val, bit )			( (val) |= (bit) )
#define bit_unset( val, bit )		( (val) &= ~(bit) )
#define bit_is_set( val, bit )		( ( (val) & (bit) ) == (bit) )
#define bit_is_unset( val, bit )	( ( (val) & (bit) ) == 0 )






#ifndef BITSET_H
#define BITSET_H


typedef uchar byte;
typedef byte* bitset;


#define bitset_free( set ) 		free( set )

#endif



#ifndef _DBG_H
#define _DBG_H


#ifdef DEBUG
	#define PROC( name ) \
		static char*	_dbg_proc_name	= name; \
		_dbg_trace( __FILE__, __LINE__, "ENTRY", "%s", _dbg_proc_name )
#else
	#define PROC( name )
#endif


#ifdef DEBUG
	#define RETURN( val ) \
		do \
		{ \
			_dbg_trace( __FILE__, __LINE__, \
				"RETURN", "%s", _dbg_proc_name ); \
			return val; \
		} \
		while( 0 )
#else
	#define RETURN( val ) return val
#endif


#ifdef DEBUG
	#define VOIDRET \
		do \
		{ \
			_dbg_trace( __FILE__, __LINE__, \
				"RETURN", "%s", _dbg_proc_name ); \
			return; \
		} \
		while( 0 )
#else
	#define VOIDRET return
#endif


#ifdef DEBUG
	#define MSG( text ) \
		_dbg_trace( __FILE__, __LINE__, "MSG", "%s", text )
#else
	#define MSG( text )
#endif


#ifdef DEBUG
	#define VARS( name, format, val ) \
		_dbg_trace( __FILE__, __LINE__, "VARS", "%s = >" format "<", name, val )
#else
	#define VARS( name, format, val )
#endif


#ifdef DEBUG
	#define PARMS( name, format, val ) \
		_dbg_trace( __FILE__, __LINE__, "PARMS", \
			"%s = >" format "<", name, val )
#else
	#define PARMS( name, format, val )
#endif


#ifdef DEBUG
	#define TIMEDUMP \
		_dbg_time( __FILE__, __LINE__ )
#else
	#define TIMEDUMP
#endif

#endif



#ifndef LLIST_H
#define LLIST_H


typedef struct llist
{
	void*			pptr;
	struct llist*	next;
} LIST;


#define list_access( ll )		( (ll) ? (ll)->pptr : (void*)NULL )
#define list_next( ll )			( (ll) ? (ll)->next : (LIST*)NULL )
#define list_replace( ll, ptr )	( (ll) ? (ll)->pptr = (ptr) : 0 )

#define LISTFOR( ll, cc )		for( (cc) = (ll); (cc); (cc) = list_next(cc) )

#endif




#ifndef PLIST_H
#define PLIST_H


#define PLIST_MOD_NONE		0
#define PLIST_MOD_RECYCLE	1
#define PLIST_MOD_EXTKEYS	2
#define PLIST_MOD_UNIQUE	4
#define PLIST_MOD_WCHAR		8


typedef struct Pelem		punit;
typedef struct Plist		plist;

typedef	pboolean			(*punit_fn)( pbyte* e );
#define PELEM_FN_NULL		( (punit_fn)NULL )


struct Pelem
{
	uchar*					key;

	plist*					list;

	punit*					prev;
	punit*					next;

	punit*					hashnext;
	punit*					hashprev;
};


struct Plist
{
	int						flags;
	int						size;
	int						count;
	int						hashsize;

	punit_fn				destruct_fn;

	punit*					unused;

	punit*					first;
	punit*					last;
	punit**					hash;
};

#endif 



#ifndef __HASHTAB_H
#define __HASHTAB_H


#define HASHTAB_MOD_NONE		0	
#define HASHTAB_MOD_EXTKEYS		1	
#define HASHTAB_MOD_WCHAR		2	
#define HASHTAB_MOD_LIST		4	
#define HASHTAB_MOD_NO_COLL		8	

#define HASHTAB_CALLBACK		void(*) ( void* )
#define HASHTAB_NO_CALLBACK		( (HASHTAB_CALLBACK) NULL )


typedef struct _hashtab 	HASHTAB;
typedef struct _bucket		HASHBUCKET;
typedef struct _hashelem	HASHELEM;


struct _hashtab
{
	int			flags;					
	int			size;					
	HASHBUCKET*	buckets;				
	HASHELEM*	discarded;				
	LIST*		list;					
};

#define hashtab_list( ht )				(ht)->list

struct _bucket
{
	HASHELEM*	start;					
	HASHELEM*	end;					
};

struct _hashelem
{
	uchar*		key;					
	void*		data;					
	HASHELEM*	prev;					
	HASHELEM*	next;					
};

#endif




#ifndef STACK_H
#define STACK_H

typedef struct
{
	pbyte*	stack;
	psize	size;
	psize	top;
	psize	count;
	psize	step;
} STACK;

#define STACK_CALLBACK		void(*) ( pbyte* )
#define STACK_NO_CALLBACK	( (STACK_CALLBACK)NULL )

#define stack_count( s )	( s )->top

#endif



#ifndef CCL_H
#define CCL_H


#define CCL_MIN			0x0
#define CCL_MAX			ccl_max()


typedef struct _crange	CRANGE;
typedef struct _crange*	CCL;

struct _crange
{
	pchar	begin;
	pchar	end;
};


#define ccl_free( ccl )				pfree( ccl )
#define ccl_replace( ccl, nccl )	ccl_free( ccl ), ccl = nccl
#define ccl_end( ccl )				( (ccl)->begin == CCL_MAX )

#endif




#define PREGEX_ACCEPT_NONE		-1

#define PREGEX_ALLOC_STEP		16


#define PREGEX_STAT_NONE		0
#define PREGEX_STAT_NFA			1
#define PREGEX_STAT_DFA			2


#define PREGEX_MOD_NONE			0		
#define PREGEX_MOD_WCHAR		1		
#define PREGEX_MOD_INSENSITIVE	2		
#define PREGEX_MOD_GLOBAL		4		
#define PREGEX_MOD_STATIC		8		
#define PREGEX_MOD_NO_REF		16		
#define PREGEX_MOD_NO_ERRORS	32		
#define PREGEX_MOD_NO_ANCHORS	64		
#define PREGEX_MOD_GREEDY		128		
#define PREGEX_MOD_NONGREEDY	256		
#define PREGEX_MOD_DEBUG		1024 	


#define PREGEX_ANCHOR_NONE		0	
#define PREGEX_ANCHOR_BOL		1	
#define PREGEX_ANCHOR_EOL		2	
#define PREGEX_ANCHOR_BOW		4	
#define PREGEX_ANCHOR_EOW		8	


typedef CCL						pregex_ccl;

typedef struct	_regex_accept	pregex_accept;

typedef struct	_regex_nfa_st	pregex_nfa_st;
typedef struct	_regex_dfa_tr	pregex_dfa_tr;
typedef struct	_regex_dfa_st	pregex_dfa_st;
typedef struct	_regex_nfa		pregex_nfa;
typedef struct	_regex_dfa		pregex_dfa;

typedef enum 	_regex_ptntype	pregex_ptntype;
typedef struct	_regex_ptn		pregex_ptn;
typedef struct	_regex_ptndef	pregex_ptndef;

typedef struct	_regex			pregex;
typedef	struct	_pregex_range	pregex_range;


typedef	int 					(*pregex_fn)( pregex*, pregex_range* );
#define PREGEX_FN_NULL			( (pregex_fn)NULL )


struct _regex_accept
{
	int				accept;		
	pboolean		greedy;		
	int				anchors;	
};


struct _regex_nfa_st
{
	pregex_ccl		ccl;		
	pregex_nfa_st*	next;		
	pregex_nfa_st*	next2;		

	int				ref;		

	pregex_accept	accept;		
};


struct _regex_nfa
{
	LIST*			states;		
	LIST*			empty;		
	int				modifiers;	

	int				ref_count;	
	int				ref_cur;	
};


struct _regex_dfa_tr
{
	pregex_ccl		ccl;		
	unsigned int	go_to;		
};


struct _regex_dfa_st
{
	LIST*			trans;		
	pregex_dfa_tr*	def_trans;	
	int*			ref;		
	int				ref_cnt;	

	pregex_accept	accept;		

	pboolean		done;		
	LIST*			nfa_set;	
};


struct _regex_dfa
{
	LIST*			states;		
	int				ref_count;	
};



enum _regex_ptntype
{
	PREGEX_PTN_NULL,
	PREGEX_PTN_CHAR,
	PREGEX_PTN_SUB,
	PREGEX_PTN_ALT,
	PREGEX_PTN_KLE,
	PREGEX_PTN_POS,
	PREGEX_PTN_OPT
};

struct _regex_ptn
{
	pregex_ptntype	type;		
	CCL				ccl;		

	pregex_ptn*		child[ 2 ];	
	pregex_ptn*		next;		
};

struct _regex_ptndef
{
	pregex_ptn*		pattern;	
	pregex_accept	accept;		
};

struct _pregex_range
{
	uchar*			begin;		
	pchar*			pbegin;		
	uchar*			end;		
	pchar*			pend;		
	psize			pos;		
	psize			len;		
	int				accept;		
	pbyte*			user;		
};


struct _regex
{
	

	pbyte			stat;		
	int				flags;		

	LIST*			defs;		
	union
	{
		pregex_nfa	nfa;		
		pregex_dfa	dfa;		
	} machine;

	

	int				age;		

	pregex_fn		match_fn;	

	
	int				last_err;	
	int				match_count;
	int				last_age;	

	uchar*			last_str;	
	uchar*			last_pos;	

	pregex_range	range;		
	pregex_range	split;		

	pregex_range*	refs;		
	int				refs_cnt;	

	uchar*			tmp_str;	
};



#ifndef PHORWARD_STRING_H
#define PHORWARD_STRING_H


#ifdef UNICODE

#define Pstrcpy						wcscpy
#define Pstrcat						wcscat
#define Pstrncpy					wcsncpy
#define Pstrcmp						wcscmp
#define Pstrncmp					wcsncmp
#define Pstrtol						wcstol
#define Pstrtoul					wcstoul
#define Pstrtod						wcstod
#define Pstrstr						wcsstr
#define Pstrchr						wcschr
#define Pstrrchr					wcsrchr

#define Pisupper					iswupper
#define Pislower					iswlower
#define Ptoupper					towupper
#define Ptolower					towlower
#define Pisdigit					iswdigit
#define Pisblank					iswblank
#define Pisalnum					iswalnum
#define Pisalpha					iswalpha

#else


#define Pstrlen						pstrlen
#define Pstrcpy						pstrcpy
#define Pstrcat						pstrcat
#define Pstrncpy					pstrncpy
#define Pstrcmp						pstrcmp
#define Pstrncmp					pstrncmp
#define Pstrtol						pstrtol
#define Pstrtoul					pstrtoul
#define Pstrtod						pstrtoud
#define Pstrchr						pstrchr
#define Pstrrchr					pstrrchr
#define Pstrstr						pstrstr

#define Pisupper					pisupper
#define Pislower					pislower
#define Ptoupper					ptoupper
#define Ptolower					ptolower
#define Pisdigit					pisdigit
#define Pisblank					pisblank
#define Pisalnum					pisalnum
#define Pisalpha					pisalpha


#define Pstrlen						pstrlen
#define Psprintf					psprintf
#define Pstrdup						pstrdup
#define Pstrcatstr					pstrcatstr
#define Pstrcatchar 				pstrcatchar
#define Pstrncatstr 				pstrncatchar
#define Pvasprintf					pvasprintf
#define Pasprintf					pasprintf

#endif


#define pstrcmp( s1, s2 )			strcmp( pgetstr( s1 ), pgetstr( s2 ) )
#define pstrncmp( s1, s2, n )		strncmp( pgetstr( s1 ), pgetstr( s2 ), n )
#define pstrcpy( s1, s2 )			strcpy( s1, pgetstr( s2 ) )
#define pstrncpy( s1, s2, n )		strncpy( s1, pgetstr( s2 ), n )
#define pstrstr( s1, s2 )			strstr( pgetstr( s1 ), pgetstr( s2 ) )
#define pstrchr( s1, ch )			strchr( pgetstr( s1 ), ch )
#define pstrrchr( s1, ch )			strrchr( pgetstr( s1 ), ch )
#define pstrcat( s1, s2 )			strcat( s1, pgetstr( s2 ) )
#define pstrtol( s, p, b )			strtol( pgetstr( s ), p, b )
#define pstrtoul( s, p, b )			strtoul( pgetstr( s ), p, b )
#define pstrtod( s, p )				strtod( pgetstr( s ), p )

#define pisupper( c )				isupper( c )
#define pislower( c )				islower( c )
#define ptoupper( c )				toupper( c )
#define ptolower( c )				tolower( c )
#define pisdigit( c )				isdigit( c )
#define pisblank( c )				isblank( c )
#define pisalnum( c )				isalnum( c )
#define pisalpha( c )				isalpha( c )

#endif



#ifndef UTF8_H
#define UTF8_H


#define u8_isutf(c) (((c)&0xC0)!=0x80)

#endif



#ifndef PUNION_H
#define PUNION_H


#define PUNION_NULL			0	
#define PUNION_BYTE			1
#define PUNION_CHAR			2
#define PUNION_INT			3
#define PUNION_LONG			4
#define PUNION_ULONG		5
#define PUNION_FLOAT		6
#define PUNION_DOUBLE		7
#define PUNION_STRING		8
#define PUNION_WSTRING		9

#define PUNION_IS_CONSTANT	16	
#define PUNION_IS_CONVERT	32	


typedef struct 
{
	pbyte		type;

	union
	{
		pbyte	b;
		

		uchar	c;
		

		pint	i;
		

		plong	l;
		

		pulong	ul;
		

		pfloat	f;
		

		pdouble	d;
		

		uchar*	s;
		
		

		pchar*	ws;
		
		
	} val;
} punion;


#define punion_set_string_d( var, val ) \
			punion_set_string( var, pstrdup( val ) )
#define punion_set_wstring_d( var, val ) \
			punion_set_wstring( var, Pstrdup( val ) )

#define punion_set_constant( var ) \
			bit_set( (var)->type, PUNION_IS_CONSTANT )
#define punion_unset_constant( var ) \
			bit_unset( (var)->type, PUNION_IS_CONSTANT )
#define punion_set_convertible( var ) \
			bit_set( (var)->type, PUNION_IS_CONVERT )
#define punion_unset_convertible( var ) \
			bit_unset( (var)->type, PUNION_IS_CONVERT )

#define punion_type( var ) \
			( ( var )->type & 0x0F )
#define punion_is_constant( var ) \
			( ( var )->type & PUNION_IS_CONSTANT )
#define punion_is_convertible( var ) \
			( ( var )->type & PUNION_IS_CONVERT )

#endif






#ifndef _XML_H
#define _XML_H

#define XML_BUFSIZE 1024	
#define XML_NAMEM	0x80	
#define XML_TXTM	0x40	
#define XML_DUP		0x20	

typedef struct xml*		XML_T;
struct xml
{
	uchar*		name;		
	uchar **	 attr;		
	uchar*		txt;		
	size_t		off;		
	int			line;		
	XML_T		next;		
	XML_T		sibling;	
	XML_T		ordered;	
	XML_T		child;		
	XML_T		parent;		
	short		flags;		
};

#define xml_next( xml )		\
	( ( xml ) ? xml->next : NULL )

#define xml_next_inorder( xml ) \
	((xml) ? xml->ordered : NULL)

#define xml_name( xml )	\
	( ( xml ) ? xml->name : NULL )

#define xml_txt( xml ) \
	( ( xml ) ? xml->txt : "" )
	
#define xml_line(xml) \
	( ( xml ) ? (xml)->line : 0 )

#define xml_new_d( name ) \
	xml_set_flag( xml_new( pstrdup(name) ),XML_NAMEM )

#define xml_add_child_d( xml, name, off ) \
	xml_set_flag \
	( \
		xml_add_child( xml, pstrdup(name), off ), \
		XML_NAMEM \
	)

#define xml_set_txt_d( xml, txt ) \
	xml_set_flag \
	( \
		xml_set_txt( xml, pstrdup(txt) ), \
		XML_TXTM \
	)

#define xml_set_attr_d( xml, name, value ) \
	xml_set_attr \
	( \
		xml_set_flag( xml, XML_DUP ), \
		pstrdup( name ), \
		pstrdup( value ) \
	)
	
#define xml_add_child_f( xml, name, off ) \
	xml_set_flag \
	( \
		xml_add_child( xml, name, off ), \
		XML_NAMEM \
	)
	
#define xml_set_txt_f( xml, txt ) \
	xml_set_flag \
	( \
		xml_set_txt( xml, txt ), \
		XML_TXTM \
	)

#define xml_set_attr_f( xml, name, value ) \
	xml_set_attr \
	( \
		xml_set_flag( xml, XML_DUP ), \
		pstrdup( name ), \
		(value) \
	)

#define xml_move( xml, dest, off )	\
	xml_insert( xml_cut( xml ),dest,off )

#define xml_remove( xml ) \
	xml_free( xml_cut( xml ) )

#endif 




#define PGERR( txt )				fprintf( stderr, "%s\n", txt )

typedef struct _pggrammar			pggrammar;
typedef struct _pgproduction		pgproduction;
typedef struct _pgsymbol			pgsymbol;
typedef struct _pgparser			pgparser;

typedef enum
{
	PGSYMTYPE_UNDEFINED,			
	PGSYMTYPE_TERMINAL,				
	PGSYMTYPE_NONTERMINAL			
} pgsymtype;

typedef enum
{
	PGASSOC_NONE,					
	PGASSOC_LEFT,					
	PGASSOC_RIGHT,					
	PGASSOC_NOASSOC					
} pgassoc;

typedef enum
{
	PGPARADIGM_UNDEFINED,			
	
	PGPARADIGM_LR0,					
	PGPARADIGM_SLR1,				
	PGPARADIGM_LR1,					
	PGPARADIGM_LALR1,				
	PGPARADIGM_LL1,					
	
	PGPARADIGM_EOP					
} pgparadigm;


struct _pgsymbol
{
	pggrammar*		grammar;		

	int				id;				
	pgsymtype		type;			
	uchar*			name;			

	pboolean		nullable;		

	LIST*			first;			
	LIST*			follow;			

	
	pregex_ptn*		ptn;			
	int				prec;			
	pgassoc			assoc;			

	
	LIST*			productions;	
};

typedef pgsymbol	pgterminal;		
typedef pgsymbol	pgnonterminal;	


struct _pgproduction
{
	pggrammar*		grammar;		

	int				id;				

	pgsymbol*		lhs;			
	LIST*			rhs;			

	int				prec;			
	pgassoc			assoc;			

	LIST*			select;			

	uchar*			strval;			
};


struct _pggrammar
{
	plist*			symbols;		
	LIST*			productions;	

	pregex			lexer;			

	pgnonterminal*	goal;			
	pgterminal*		eoi;			
	pgterminal*		error;			
};


struct _pgparser
{
	pggrammar*		grammar;		
	pgparadigm		paradigm;		

	LIST*			states;			
};






bitset bitset_create( int size );
void bitset_set( bitset set, int bit, pboolean state );
pboolean bitset_get( bitset set, int bit );
bitset bitset_copy( int size, bitset source );


void _dbg_trace( char* file, int line, char* type, char* format, ... );
void _dbg_time( char* file, int line );


pint hashtab_init( HASHTAB* ht, pint size, pint flags );
pint hashtab_free( HASHTAB* hashtab, void (*freefct)(void*) );
HASHELEM* hashtab_insert( HASHTAB* hashtab, uchar* key, void* data );
HASHELEM* hashtab_get( HASHTAB* hashtab, uchar* key );
HASHELEM* hashtab_update( HASHTAB* hashtab, uchar* key, void* data );
HASHELEM* hashtab_discard( HASHTAB* hashtab, uchar* key, void (*freefct)(void*) );
pint hashtab_delete( HASHTAB* hashtab, uchar* key, void (*freefct)(void*) );
void hashtab_print( HASHTAB* hashtab, FILE* channel );
pint hashtab_count( HASHTAB* hashtab );
HASHELEM* hashtab_fetch( HASHTAB* hashtab, HASHELEM* current );
void* hashelem_access( HASHELEM* hashelem );
uchar* hashelem_key( HASHELEM* hashelem );
HASHELEM* hashelem_next( HASHELEM* hashelem );
HASHELEM* hashelem_prev( HASHELEM* hashelem );


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


pboolean plist_init( plist* list, psize size, pbyte flags );
plist* plist_create( psize size, pbyte flags );
pboolean plist_erase( plist* list );
plist* plist_free( plist* list );
punit* plist_insert( plist* list, punit* pos, uchar* key, void* src );
punit* plist_push( plist* list, void* src );
punit* plist_remove( plist* list, punit* e );
pboolean plist_pop( plist* list, void* dest );
punit* plist_get( plist* list, int n );
punit* plist_get_by_key( plist* list, uchar* key );
punit* plist_get_by_ptr( plist* list, void* ptr );
void* plist_access( punit* e );
punit* plist_next( punit* u );
punit* plist_prev( punit* u );
int plist_offset( punit* u );
punit* plist_first( plist* l );
punit* plist_last( plist* l );
int plist_size( plist* l );
int plist_count( plist* l );


void* pmalloc( psize size );
void* prealloc( void* oldptr, psize size );
void* pfree( void* ptr );
void* pmemdup( void* ptr, psize size );


void stack_init( STACK* stack, psize size, psize step );
void stack_free( STACK* stack, void (*ff)( pbyte* ) );
pbyte* stack_push( STACK* stack, pbyte* item );
pbyte* stack_pop( STACK* stack );
pbyte* stack_access( STACK* stack, psize offset );
void stack_dump( uchar* file, int line, uchar* name, STACK* stack, void (*pf)( pbyte* ) );


pchar ccl_max( void );
int ccl_size( CCL ccl );
int ccl_count( CCL ccl );
CCL ccl_dup( CCL ccl );
CCL ccl_negate( CCL ccl );
CCL ccl_union( CCL first, CCL second );
CCL ccl_create( uchar* ccldef );
void ccl_print( FILE* stream, CCL ccl, int break_after );
uchar* ccl_to_str( CCL ccl, pboolean escape );
CCL ccl_addrange( CCL ccl, pchar begin, pchar end );
CCL ccl_delrange( CCL ccl, pchar begin, pchar end );
CCL ccl_add( CCL ccl, pchar ch );
CCL ccl_del( CCL ccl, pchar ch );
pboolean ccl_test( CCL ccl, pchar ch );
pboolean ccl_testrange( CCL ccl, pchar begin, pchar end );
pboolean ccl_instest( CCL ccl, pchar ch );
int ccl_compare( CCL first, CCL second );
CCL ccl_intersect( CCL first, CCL second );
CCL ccl_diff( CCL first, CCL second );


void pregex_dfa_print( FILE* stream, pregex_dfa* dfa );
pregex_dfa* pregex_dfa_free( pregex_dfa* dfa );
int pregex_dfa_from_nfa( pregex_dfa* dfa, pregex_nfa* nfa );
int pregex_dfa_minimize( pregex_dfa* dfa );
int pregex_dfa_match( pregex_dfa* dfa, uchar* str, size_t* len, int* anchors, pregex_range** ref, int* ref_count, int flags );


int pregex_qmatch( uchar* regex, uchar* str, int flags, pregex_range** results );
int pregex_qsplit( uchar* regex, uchar* str, int flags, pregex_range** results );
uchar* pregex_qreplace( uchar* regex, uchar* str, uchar* replace, int flags );


pregex_accept* pregex_accept_init( pregex_accept* accept );
pboolean pregex_check_anchors( uchar* all, uchar* str, psize len, int anchors, int flags );


pregex_nfa_st* pregex_nfa_create_state( pregex_nfa* nfa, uchar* chardef, int flags );
void pregex_nfa_print( pregex_nfa* nfa );
void pregex_nfa_free( pregex_nfa* nfa );
LIST* pregex_nfa_move( pregex_nfa* nfa, LIST* input, pchar from, pchar to );
LIST* pregex_nfa_epsilon_closure( pregex_nfa* nfa, LIST* input, pregex_accept* accept );
int pregex_nfa_match( pregex_nfa* nfa, uchar* str, psize* len, int* anchors, pregex_range** ref, int* ref_count, int flags );
int pregex_nfa_from_string( pregex_nfa* nfa, uchar* str, int flags, int acc );


pregex_ptn* pregex_ptn_create_char( CCL ccl );
pregex_ptn* pregex_ptn_create_string( uchar* str, int flags );
pregex_ptn* pregex_ptn_create_sub( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_alt( pregex_ptn* left, ... );
pregex_ptn* pregex_ptn_create_kle( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_pos( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_opt( pregex_ptn* ptn );
pregex_ptn* pregex_ptn_create_seq( pregex_ptn* first, ... );
pregex_ptn* pregex_ptn_free( pregex_ptn* ptn );
void pregex_ptn_print( pregex_ptn* ptn, int rec );
int pregex_ptn_to_regex( uchar** regex, pregex_ptn* ptn );
int pregex_ptn_to_nfa( pregex_nfa* nfa, pregex_ptn* pattern, pregex_accept* accept );
int pregex_ptn_parse( pregex_ptn** ptn, pregex_accept* accept, uchar* str, int flags );


pregex* pregex_create( void );
pregex* pregex_free( pregex* regex );
pregex* pregex_reset( pregex* regex );
int pregex_compile( pregex* regex, uchar* pattern, int accept );
int pregex_finalize( pregex* regex );
pregex_range* pregex_match_next( pregex* regex, uchar* str );
int pregex_match( pregex* regex, uchar* str, pregex_range** results );
pregex_range* pregex_split_next( pregex* regex, uchar* str );
int pregex_split( pregex* regex, uchar* str, pregex_range** results );
uchar* pregex_replace( pregex* regex, uchar* str, uchar* replacement );
pregex_range* pregex_get_range( pregex* regex );
pregex_range* pregex_get_split( pregex* regex );
pregex_range* pregex_get_ref( pregex* regex, int offset );
int pregex_get_match_count( pregex* regex );
int pregex_get_flags( pregex* regex );
pboolean pregex_set_flags( pregex* regex, int flags );
pregex_fn pregex_get_match_fn( pregex* regex );
pboolean pregex_set_match_fn( pregex* regex, pregex_fn match_fn );


uchar* pregex_range_to_string( pregex_range* range );


int pregex_ref_init( pregex_range** ref, int* ref_count, int ref_all, int flags );
void pregex_ref_update( pregex_range* ref, uchar* strp, psize off );


uchar* pchar_to_uchar( pchar* str, pboolean freestr );
pchar* uchar_to_pchar( uchar* str, pboolean freestr );
uchar* plong_to_uchar( plong l );
pchar* plong_to_pchar( plong l );
uchar* pulong_to_uchar( pulong ul );
pchar* pulong_to_pchar( pulong ul );
uchar* pdouble_to_uchar( pdouble d );
pchar* pdouble_to_pchar( pdouble d );


uchar* pstrcatchar( uchar* str, wchar chr );
uchar* pstrcatstr( uchar* dest, uchar* src, boolean freesrc );
uchar* pstrncatstr( uchar* str, uchar* append, psize n );
uchar* pstrreplace( uchar* str, uchar* find, uchar* replace );
uchar* pstrdup( uchar* str );
uchar* pstrndup( uchar* str, psize len );
psize pstrlen( uchar* str );
int psprintf( uchar* res, uchar* fmt, ... );
int pvasprintf( uchar** str, uchar* fmt, va_list ap );
uchar* pasprintf( uchar* fmt, ... );
uchar* psetstr( uchar** str, uchar* val );
uchar* pgetstr( uchar* str );
uchar* pstrrender( uchar* tpl, ... );
uchar* pstrltrim( uchar* s );
uchar* pstrrtrim( uchar* s );
uchar* pstrtrim( uchar* s );
int pstrsplit( uchar*** tokens, uchar* str, uchar* sep, int limit );
uchar* pstrupr( uchar* s );
uchar* pstrlwr( uchar* s );
int pstrcasecmp( uchar* s1, uchar* s2 );
int pstrncasecmp( uchar* s1, uchar* s2, pint n );
int pstrparsechar( wchar* retc, uchar *str, pboolean escapeseq );
#ifdef UNICODE
pchar* Pstrdup( pchar* str );
int Psprintf( pchar* res, pchar* fmt, ... );
int Pvasprintf( pchar** str, pchar* fmt, va_list ap );
pchar* Pasprintf( pchar* fmt, ... );
pchar* Pstrcatchar( pchar* str, wchar chr );
pchar* Pstrcatstr( pchar* dest, pchar* src, boolean freesrc );
pchar* Pstrncatstr( pchar* str, pchar* append, psize num );
psize Pstrlen( pchar* str );
#endif


int u8_seqlen(uchar *s);
#ifdef UTF8
wchar u8_char( uchar* str );
#else
wchar u8_char( uchar* str );
#endif
uchar* u8_move( uchar* str, int count );
wchar u8_parse_char( uchar** ch );
int u8_toucs(wchar *dest, int sz, uchar *src, int srcsz);
int u8_toutf8(uchar *dest, int sz, wchar *src, int srcsz);
int u8_wc_toutf8(uchar *dest, wchar ch);
int u8_offset(uchar *str, int charnum);
int u8_charnum(uchar *s, int offset);
int u8_strlen(uchar *s);
wchar u8_nextchar(uchar *s, int *i);
void u8_inc(uchar *s, int *i);
void u8_dec(uchar *s, int *i);
int octal_digit(uchar c);
int hex_digit(uchar c);
int u8_read_escape_sequence(uchar *str, wchar *dest);
int u8_unescape(uchar *buf, int sz, uchar *src);
int u8_escape_wchar(uchar *buf, int sz, wchar ch);
int u8_escape(uchar *buf, int sz, uchar *src, int escape_quotes);
uchar *u8_strchr(uchar *s, wchar ch, int *charn);
uchar *u8_memchr(uchar *s, wchar ch, size_t sz, int *charn);
int u8_is_locale_utf8(uchar *locale);


pint to_base64( uchar** outstream, uchar* instream, psize size );
pint from_base64( uchar** outstream, psize* outsize, uchar* instream );


uchar* pwhich( uchar* filename, uchar* directories );
uchar* pbasename( uchar* path );
pboolean pfileexists( uchar* filename );
int map_file( char** cont, uchar* filename );
pint pgetopt( uchar* opt, uchar** param, pint* next, pint argc, uchar** argv, uchar* optstr, uchar* loptstr, pint idx );


void punion_init( punion* var );
void punion_reset( punion* var );


pbyte punion_to_byte( punion* var );
uchar punion_to_char( punion* var );
pint punion_to_int( punion* var );
plong punion_to_long( punion* var );
pulong punion_to_ulong( punion* var );
pfloat punion_to_float( punion* var );
pdouble punion_to_double( punion* var );
uchar* punion_to_string( punion* var );
pchar* punion_to_wstring( punion* var );
pint punion_convert( punion* var, pbyte type );


pbyte punion_get_byte( punion* var );
uchar punion_get_char( punion* var );
pint punion_get_int( punion* var );
plong punion_get_long( punion* var );
pulong punion_get_ulong( punion* var );
pfloat punion_get_float( punion* var );
pdouble punion_get_double( punion* var );
uchar* punion_get_cstring( punion* var );
uchar* punion_get_string( punion* var );
pchar* punion_get_wcstring( punion* var );
pchar* punion_get_wstring( punion* var );


pbyte punion_set_byte( punion* var, pbyte b );
uchar punion_set_char( punion* var, uchar c );
pint punion_set_int( punion* var, pint i );
plong punion_set_long( punion* var, plong l );
pulong punion_set_ulong( punion* var, pulong ul );
pfloat punion_set_float( punion* var, pfloat f );
pdouble punion_set_double( punion* var, pdouble d );
uchar* punion_set_cstring( punion* var, uchar* s );
uchar* punion_set_string( punion* var, uchar* s );
pchar* punion_set_wcstring( punion* var, pchar* ws );
pchar* punion_set_wstring( punion* var, pchar* ws );


XML_T xml_child( XML_T xml, uchar* name );
XML_T xml_idx( XML_T xml, int idx );
uchar* xml_attr( XML_T xml, uchar* attr );
plong xml_int_attr( XML_T xml, uchar* attr );
pdouble xml_float_attr( XML_T xml, uchar* attr );
XML_T xml_vget( XML_T xml, va_list ap );
XML_T xml_get( XML_T xml, ... );
uchar ** xml_pi( XML_T xml, uchar* target );
uchar* xml_decode( uchar* s, uchar ** ent, uchar t );
uchar* xml_str2utf8( uchar ** s, size_t* len );
void xml_free_attr( uchar ** attr );
XML_T xml_parse_str( uchar* s, size_t len );
XML_T xml_parse_fp( FILE* fp );
XML_T xml_parse_file( uchar* file );
uchar* xml_ampencode( uchar* s, size_t len, uchar ** dst, size_t* dlen, size_t* max, short a );
uchar* xml_toxml( XML_T xml );
void xml_free( XML_T xml );
uchar* xml_error( XML_T xml );
XML_T xml_new( uchar* name );
XML_T xml_insert( XML_T xml, XML_T dest, size_t off );
XML_T xml_add_child( XML_T xml, uchar* name, size_t off );
XML_T xml_set_txt( XML_T xml, uchar* txt );
XML_T xml_set_attr( XML_T xml, uchar* name, uchar* value );
XML_T xml_set_int_attr( XML_T xml, uchar* name, plong value );
XML_T xml_set_float_attr( XML_T xml, uchar* name, pdouble value );
XML_T xml_set_flag( XML_T xml, short flag );
int xml_count( XML_T xml );
int xml_count_all( XML_T xml );
XML_T xml_cut( XML_T xml );




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


pgnonterminal* pg_nonterminal_create( pggrammar* grammar, char* name );
pgnonterminal* pg_nonterminal_drop( pgterminal* nonterminal );
pgnonterminal* pg_nonterminal_get( pggrammar* g, int offset );


BOOLEAN pg_parser_lr_closure( pgparser* parser );


pgparser* pg_parser_create( pggrammar* grammar, pgparadigm paradigm );
pgparser* pg_parser_free( pgparser* parser );


pgproduction* pg_production_create( pgnonterminal* lhs, ... );
pgproduction* pg_production_drop( pgproduction* p );
uchar* pg_production_to_string( pgproduction* p );
void pg_production_print( pgproduction* p, FILE* f );
pboolean pg_production_append( pgproduction* p, pgsymbol* sym );
pgproduction* pg_production_get( pggrammar* grammar, int i );
pgproduction* pg_production_get_by_lhs( pgnonterminal* lhs, int i );
pgsymbol* pg_production_get_rhs( pgproduction* p, int i );
int pg_production_get_id( pgproduction* p );
pggrammar* pg_production_get_grammar( pgproduction* p );
pgnonterminal* pg_production_get_lhs( pgproduction* p );
int pg_production_get_rhs_length( pgproduction* p );


pgsymbol* pg_symbol_create( pggrammar* grammar, pgsymtype type, uchar* name );
pgsymbol* pg_symbol_free( pgsymbol* symbol );
BOOLEAN pg_symbol_reset( pgsymbol* s );
void pg_symbol_print( pgsymbol* symbol, FILE* f );
BOOLEAN pg_symbol_is_terminal( pgsymbol* symbol );
BOOLEAN pg_symbol_is_nonterminal( pgsymbol* symbol );
pgsymbol* pg_symbol_get( pggrammar* g, int i );
int pg_symbol_get_id( pgsymbol* s );
pgsymtype pg_symbol_get_type( pgsymbol* s );
pggrammar* pg_symbol_get_grammar( pgsymbol* s );
uchar* pg_symbol_get_name( pgsymbol* s );


pgterminal* pg_terminal_create( pggrammar* grammar, char* name, char* pattern );
pgterminal* pg_terminal_drop( pgterminal* terminal );
pgterminal* pg_terminal_get( pggrammar* g, int offset );
BOOLEAN pg_terminal_parse_pattern( pgterminal* terminal, uchar* pattern );
BOOLEAN pg_terminal_set_pattern( pgterminal* terminal, pregex_ptn* ptn );
pregex_ptn* pg_terminal_get_pattern( pgterminal* terminal );


#endif 

