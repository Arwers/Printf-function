#include <iostream>
#include <stdio.h>
#include <stdarg.h>
using namespace std;

int Printf( const char* format, ... );
int PrintfV( const char* format, va_list arg_list );

void outDec( int ); //znakowo wypisuje liczbe całk
void outChar( char );  // wypisuje znak // putchar
void outStr( char* ); // wypisz znakowo string
void outDouble( double ); //wypisz znakowo double
void outNum( int ); // wypisuje znakowo liczbę int > 0 rekurencyjnie

int main( int argc, char* argv[] ) {
  int n = -0;
  char c = '#';
  double x = 0.3240;
  double y = -.2;
  double z = -1.000010205;
  char* str = ( char* )"A|a m4 k0ta$#^$%";
  Printf("%%s\n%f%c   n=%d \\ % /\ny=%f ` ` z=%f\n\n%", str, x, c, n, y, z);
}


int Printf( const char* format, ... ) {

  va_list args;                  //args - pointer to list of arguments
  va_start( args, format );      // Initialize variable arguments

  int ret_val = PrintfV( format, args );

  //zakonczenie dzialania na liscie argumentow arg
  va_end( args );  // Reset variable arguments
  return ret_val;
}

int PrintfV( const char* format, va_list arg_list ) {
  char c;
  while ( ( c = *format++ ) ) {
    switch ( c ) {
    case '%':
      switch ( c = *format++ ) {
        case 'd': outDec( va_arg( arg_list, int ) ); break;
        case 'f': outDouble( va_arg( arg_list, double ) ); break;
        case 's': outStr( va_arg( arg_list, char* ) ); break;
        case 'c': outChar( va_arg( arg_list, char ) ); break;
        default:
          outChar( '%' );
          if(!c) return 1;
          if( c == '%' ) c = *format--; // możliwa sytuacja %%d, wtedy ominęlibyśmy drugi %
          else outChar( c );
      }
      break;
    case '`': c = '\'';
    default: outChar( c );
    }
  }
  return 1;
}

void outDec( int x ) {
  if ( x < 0 ) {
    outChar( '-' );
    x = -x;
  }
  if ( x == 0 ) {
    outChar( '0' );
  }
  outNum( x );
}

void outChar( char c ) {
  putchar( c );
}

void outStr( char* str ) {
  while ( *str != '\0' ) {
    outChar( *str );
    str++;
  }
}

void outDouble( double d ) {
  if( d < 0 ) {
    outChar( '-' );
    d = -d;
  }
  double dot = d - int( d ); // część liczby po przecinku
  outDec( int( d ) );
  
  if( d == 0 ) return;
  
  outChar( '.' );
  
  for( int i = 0; i < 6 && ( dot - int( dot ) ) >= 1e-6; i++ ) {
    dot *= 10;
    outChar( int( dot ) % 10 + '0' );
  }
}

void outNum( int n ) {
  if( n > 0 ){
    outNum( n / 10 );
    outChar( n % 10 + '0' );
  }
}