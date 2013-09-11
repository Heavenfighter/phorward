/*
	This program is a short demostration of the functions
	provided by the Phorward Basis Libray. It covers not all
	available functions, but the really useful ones! ;)
*/

#include <phorward.h>

/* Required for stack functions */
struct person
{
	char	first_name	[ 30 + 1 ];
	char	last_name	[ 30 + 1 ];
};

/* Extended String Functions */
void string_demo( void )
{
	char	str[ 1024 ];
	int	all, i;
	char**	tokens;
	char*	str1;
	char*	str2;

	printf( "\n*** string_demo ***\n\n" );

	/* Dynamic string functions */
	str1 = pstrdup( "Hello " );
	str1 = pstrcatstr( str1, "World", FALSE );
	str1 = pstrcatchar( str1, '!' );

	str2 = pstrreplace( str1, "World", "out there" );

	printf( "str1 = >%s<\n", str1 );
	printf( "str2 = >%s<\n", str2 );
	pfree( str1 ); /* str2 will be freed within next function call! */

	/* String rendering from templates */
	str1 = pstrrender( "<a href=\"$link\" alt=\"$title\">$title</a>",
			"$link", "http://www.phorward-software.com", FALSE,
			"$title", str2, TRUE,
			(char*)NULL );

	printf( "str1 = >%s<\n", str1 );
	pfree( str1 );

	/* String Tokenizer */
	strcpy( str, "Hello World, this is a simple test" );
	all = pstrsplit( &tokens, str, " ", 3 );
	printf( "%d\n", all );

	for( i = 0; i < all; i++ )
		printf( "%d: >%s<\n", i, tokens[i] );

	pfree( tokens );

	/* Self-allocating sprintf extension */
	str1 = pasprintf( "current content of str is >%s<, and all has %d",
						str, all );
	printf( "str1 = >%s<\n", str1 );
	pfree( str1 );
}

/* UTF-8 Functions */
void utf8_demo( void )
{
	char	str		[ 1024 ];
	char*	ptr;

	printf( "\n*** utf8_demo ***\n\n" );

	strcpy( str, "Hällö ich bün ein StrÜng€!" );
	/*             123456789012345678901234567890
	               0        1         2         3
	*/
	printf( "%ld %d\n", pstrlen( str ), u8_strlen( str ) );
	for( ptr = str; *ptr; ptr += u8_seqlen( ptr ) )
		printf( ">%s< %d\n", ptr, u8_char( ptr ) );

	for( ptr = str; *ptr; ptr++ )
		printf( ">%s< >%c< %x %d\n", ptr, *ptr, *ptr, *ptr );

	u8_unescape( str, sizeof( str ), "\\u20AC" );
	printf( ">%s< %d\n", str, u8_char( str ) );
}

/* Unicode-Function replacements */
void unicode_demo( void )
{
	pchar	mystr		[ 255 ];
	pchar*	mydynamicstr;

	printf( "\n*** unicode_demo ***\n\n" );

	wcscpy( mystr, L"Yes, w€ cän üse standard C function "
			L"names for Unicode-strings!" );


	printf( "mystr = >%ls<\n", mystr );
	swprintf( mystr, sizeof( mystr ),
			L"This string was %d characters long!",
			pwcslen( mystr ) );
	printf( "mystr = >%ls<\n", mystr );

	mydynamicstr = pwcsdup( mystr );
	mydynamicstr = pwcscatstr( mydynamicstr,
			L" You can see: The functions are"
			L" used the same way as the standard"
			L" char-functions!", FALSE );

	printf( "mydynamicstr = >%ls<\n", mydynamicstr );
	pfree( mydynamicstr );

	mydynamicstr = pawcsprintf( L"This is €uro symbol %ls of %d",
						mystr, sizeof( mystr ) );
	printf( "mydynamicstr = >%ls<\n", mydynamicstr );
	pfree( mydynamicstr );
}

void ccl_demo( void )
{
	CCL c;
	CCL d;
	char* x;

	printf( "\n*** ccl_demo ***\n\n" );

	/* c = ccl_create( "\\1-\\n€A-ZX-dÄÜÖ" ); */
	c = ccl_create( "^ €A-Z\n" );
	d = ccl_create( "A-NXYZ\n" );

	d = ccl_create( "^alles richtig! :)" );
	ccl_print( stderr, c, -1 );
	ccl_print( stderr, d, -1 );

	c = ccl_union( c, d );
	ccl_print( stderr, c, -1 );

	ccl_negate( c );
	ccl_print( stderr, c, -1 );

	ccl_negate( c );
	ccl_print( stderr, c, -1 );

	/* e = ccl_intersect( c, d ); */
	d = ccl_delrange( d, '\0', CCL_MAX );

	x = ccl_to_str( d, TRUE );
	printf( "e = >%s<\n", x );

	pfree( x );
	ccl_free( c );
	ccl_free( d );
}

void list_demo( void )
{
	LIST*	mylist = (LIST*)NULL; /* This is our main list */
	LIST*	l; /* l, for list iteration */
	char*	values[] = { "Hello", "World", "out there!" };
	char*	tmp;

	printf( "\n*** list_demo ***\n\n" );

	/* Create the list. */
	mylist = list_push( mylist, (void*)values[0] );
	mylist = list_push( mylist, (void*)values[1] );
	mylist = list_push( mylist, (void*)values[2] );

	/* Let's iterate it. */
	printf( "mylist contains %d items\n", list_count( mylist ) );
	for( l = mylist; l; l = list_next( l ) )
	{
		tmp = (char*)list_access( l );
		printf( "%s ", tmp );
	}

	/* Now, we remove one element (identified by its pointer) and iterate
		the list again */
	mylist = list_remove( mylist, (void*)values[1] );
	printf( "\nmylist contains now %d items\n", list_count( mylist ) );

	/* LISTFOR expands in a for-loop as above, but is shorter! ;) */
	LISTFOR( mylist, l )
	{
		tmp = (char*)list_access( l );
		printf( "%s ", tmp );
	}

	printf( "\n" );

	/* Free the entire list */
	mylist = list_free( mylist );
}

static void plist_demo_print( plist* list )
{
	struct
	person*		pp;
	punit*	e;
	
	printf( "\n" );
	for( e = plist_first( list ); e; e = plist_next( e ) )
	{
		pp = (struct person*)plist_access( e );
		printf( "- %s, %s\n", pp->last_name, pp->first_name );
	}
	printf( "~~~\n%d elements\n\n", plist_count( list ) );
}

static void plist_demo_print_by_key( plist* list, char* key )
{
	struct
	person*		pp;
	punit*	e;

	if( !( e = plist_get_by_key( list, key ) ) )
	{
		printf( "<No record found matching '%s'>\n", key );
		return;
	}
	
	pp = (struct person*)plist_access( e );
	printf( "%s => %s, %s\n", key, pp->last_name, pp->first_name );
}

void plist_demo( void )
{
	struct
	person	p;
	plist	my;
	punit*	e;

	printf( "\n*** plist_demo ***\n" );

	plist_init( &my, sizeof( struct person ), PLIST_MOD_RECYCLE );
	
	/* Add some data */
	strcpy( p.first_name, "Melinda" );
	strcpy( p.last_name, "Smith" );
	plist_insert( &my, NULL, "Smith", (pbyte*)&p );

	strcpy( p.first_name, "Brenda" );
	strcpy( p.last_name, "Brandon" );
	plist_insert( &my, NULL, "Brandon", (pbyte*)&p );

	strcpy( p.first_name, "Monique" );
	strcpy( p.last_name, "Joli" );
	e = plist_insert( &my, NULL, "Joli", (pbyte*)&p );

	strcpy( p.first_name, "Susan" );
	strcpy( p.last_name, "Mueller" );
	plist_insert( &my, NULL, "Mueller", (pbyte*)&p );
	
	/* Print content */
	plist_demo_print( &my );
	
	/* Find by key */
	plist_demo_print_by_key( &my, "Joli" );
	
	/* Remove entry */
	plist_remove( &my, e );
	
	/* Find again by key */
	plist_demo_print_by_key( &my, "Joli" );
	
	/* Add more data - first element will be recycled. */
	strcpy( p.first_name, "Rei" );
	strcpy( p.last_name, "Ayanami" );
	plist_insert( &my, NULL, "Ayanami", (pbyte*)&p );
	plist_demo_print_by_key( &my, "Ayanami" );
	
	/* Add data with same key, test collision */
	strcpy( p.first_name, "Throttle" );
	strcpy( p.last_name, "Full" );
	plist_insert( &my, NULL, "Ayanami", (pbyte*)&p );
	
	/* Now print and get by key */
	plist_demo_print( &my );
	plist_demo_print_by_key( &my, "Ayanami" );
	
	plist_erase( &my );
	plist_demo_print( &my );
}

void hashtab_demo( void )
{
	HASHTAB		ht;
	HASHELEM*	e;
	LIST*		l;

	printf( "\n*** hashtab_demo ***\n\n" );

	/* We configure a hash-table with 6 buckets, wide-character enabled and
		list-feature enabled */
	hashtab_init( &ht, 6, HASHTAB_MOD_WCHAR | HASHTAB_MOD_LIST );

	/* Let's insert some data */
	hashtab_insert( &ht, (char*)L"Hello", "This is my first string" );
	hashtab_insert( &ht, (char*)L"World", "And this is my second one" );
	hashtab_insert( &ht, (char*)L"Test", "Last but no least, the third :)" );

	/* Get one entry */
	e = hashtab_get( &ht, (char*)L"World" );
	printf( ">%s<\n", (char*)hashelem_access( e ) );
	printf( "%d items in table\n", hashtab_count( &ht ) );

	/* Loop trough the entries, without any order */
	for( e = hashtab_fetch( &ht, (HASHELEM*)NULL );
			e; e = hashtab_fetch( &ht, e ) )
		printf( ">%ls<: >%s<\n",
			(pchar*)hashelem_key( e ),
				(char*)hashelem_access( e ) );

	/* Loop trough the entries using the list */
	LISTFOR( hashtab_list( &ht ), l )
	{
		e = (HASHELEM*)list_access( l );
		printf( ">%ls<: >%s<\n",
			(pchar*)hashelem_key( e ),
				(char*)hashelem_access( e ) );
	}

	/* Dump the table to stderr */
	hashtab_print( &ht, stderr );

	/* Discard the element with the key "World" */
	hashtab_discard( &ht, (char*)L"World", HASHTAB_NO_CALLBACK );

	/* Print again! */
	hashtab_print( &ht, stderr );

	/* Free entire table, reset all */
	hashtab_free( &ht, HASHTAB_NO_CALLBACK );
}

static void stack_demo_callback( struct person* p )
{
	fprintf( stderr, "--- %s, %s\n", p->last_name, p->first_name );
}

void stack_demo( void )
{
	struct person x;
	struct person* p;

	STACK	s;

	printf( "\n*** stack_demo ***\n\n" );

	stack_init( &s, sizeof( struct person ), 3 );

	strcpy( x.last_name, "Zufall" );
	strcpy( x.first_name, "Reiner" );
	stack_push( &s, (pbyte*)&x );

	strcpy( x.last_name, "Pfahl" );
	strcpy( x.first_name, "Martha" );
	stack_push( &s, (pbyte*)&x );

	strcpy( x.last_name, "Racho" );
	strcpy( x.first_name, "Volker" );
	stack_push( &s, (pbyte*)&x );

	strcpy( x.last_name, "Pete" );
	strcpy( x.first_name, "Dieter" );
	stack_push( &s, (pbyte*)&x );

	stack_dump( __FILE__, __LINE__, "s", &s,
		(STACK_CALLBACK)stack_demo_callback );

	while( ( p = (struct person*)stack_pop( &s ) ) )
		fprintf( stderr, "Pop: %s %s\n", p->first_name, p->last_name );

	stack_free( &s, (STACK_CALLBACK)stack_demo_callback );
}

int dbg_demo( int x )
{
	int ret;

	PROC( "dbg_demo" );
	PARMS( "x", "%d", x );

	if( x < 0 )
	{
		MSG( "Not allowed!" );
		RETURN( ERR_PARMS );
	}
	else if( x == 0 )
	{
		MSG( "x is 0, so faculty is 1" );
		RETURN( 1 );
	}
	else
	{
		MSG( "Calling dbg_demo recurisvely with:" );
		VARS( "x - 1", "%d", x - 1 );
		ret = x * dbg_demo( x - 1 );
	}

	VARS( "ret", "%d", ret );
	RETURN( ret );
}

void xml_demo( void )
{
	XML_T	comp;
	XML_T	div;
	XML_T	emp;
	char*	s;

	comp = xml_new( "company" );

	div = xml_add_child( comp, "division", 0 );
	xml_set_attr( div, "task", "Development" );

	emp = xml_add_child( div, "employee", 0 );
	xml_set_attr( emp, "name", "Eduard Woodstock" );
	emp = xml_add_child( div, "employee", 0 );
	xml_set_attr( emp, "name", "Helga Wacken" );
	emp = xml_add_child( div, "employee", 0 );
	xml_set_attr( emp, "name", "Horst Summerbreeze" );

	xml_set_txt( emp, "Das ist ein Test!" );

	div = xml_add_child( comp, "division", 0 );
	xml_set_attr( div, "task", "Sales" );
	emp = xml_add_child( div, "employee", 0 );
	xml_set_attr( emp, "name", "Peter Paris" );
	emp = xml_add_child( div, "employee", 0 );
	xml_set_attr( emp, "name", "Josephine Julianadorp" );

	s = xml_toxml( comp );

	printf( "%s\n", s );
	pfree( s );
	xml_free( comp );
}

void union_demo( void )
{
	/*
	 * This is a demonstration of the punion data type, which implements
	 * a union type. A union type is a variable which is capable to
	 * store different values, by using a type flag.
	 *
	 * The punion-data type and its support functions of the Phorward
	 * Foundation Libraries allows to store byte, char, int, long,
	 * unsigned long (ulong), float, double, string (char*) and
	 * wide-character string (wstring) and their conversion among each
	 * other.
	 *
	 * String memory is always hold with the punion-object, until the
	 * structure is converted into another type or freed.
	 *
	 * It is recommended to clean-up every punion structure using
	 * punion_reset(), to ensure that all used memory is free again.
	 */
	punion	utest;

	/* Initialize the union structure */
	punion_init( &utest );

	/* Set a string, duplicate its memory (*_d) */
	punion_set_string_d( &utest, "123 Hello World" );

	/* Get the string */
	printf( "utest(str) = %s\n", punion_get_string( &utest ) );
	
	/* Get the string as wide-character value */
	printf( "utest(wstr) = %ls\n", punion_get_wstring( &utest ) );
	
	/* 
	 * Well, this is not possible, because the punion object is
	 * configured to be not convertible by default. Let's enable this.
	 */
	punion_set_convertible( &utest );

	/* Get the string as wide-character value, again. */
	printf( "utest(wstr) = %ls\n", punion_get_wstring( &utest ) );

	/* The the string as integer value - only 123 will be returned! */
	printf( "utest(int) = %d\n", punion_get_int( &utest ) );

	/* Reset the value by a floating point number */
	punion_set_double( &utest, 123.456 );

	printf( "utest(double) = %lf\n", punion_get_double( &utest ) );
	printf( "utest(str) = %s\n", punion_get_string( &utest ) );

	/* Free (possibly) used memory */
	punion_reset( &utest );
}

int main( int argc, char** argv )
{
	setlocale( LC_ALL, "" );

	string_demo();
	unicode_demo();
	utf8_demo();
	list_demo();
	plist_demo();
	hashtab_demo();
	stack_demo();
	printf( "faculty of 3 is %d\n", dbg_demo( 3 ) );
	xml_demo();
	union_demo();

	return EXIT_SUCCESS;
}

