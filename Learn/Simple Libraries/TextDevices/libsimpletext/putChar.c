/*
 * @file putChar.c
 * Function to print a char to the default terminal.
 * If c is \n, append \r.
 *
 * Copyright (c) 2013, Parallax Inc.
 * Written by Steve Denson
 * 
 * Modified by Andy Lindsay to correct bug in terminal cursor control
 * with 2, 14, and 15.
 */

/*
#include "simpletext.h"

void putChar(char c)
{
  extern text_t *dport_ptr;
  if(c == '\n')
    dport_ptr->txChar(dport_ptr, '\r');
  dport_ptr->txChar(dport_ptr, c);
}
*/

#include "simpletext.h"

void putChar(char c)
{
  extern text_t *dport_ptr;

  #ifdef ST_SLASH_ReturN
  if(c == '\n')
    dport_ptr->txChar(dport_ptr, '\r');
  dport_ptr->txChar(dport_ptr, c);
  #endif
  
  
  #ifdef SIMPLETEXT_ECS
  /*
  //if( (c == *(dport_ptr->ec)) || (c == *(dport_ptr->ec+1))  || (c == *(dport_ptr->ec+2))  || (c == *(dport_ptr->ec+3)) )
  if( (c == *(dport_ptr->ec)) || (c == *(dport_ptr->ec+1)) )
  { 
    int n = 0;
    while(1)
    {
      if(*(dport_ptr->ecs+n) == 0 || c == 0) break;
      dport_ptr->txChar(dport_ptr, *(dport_ptr->ecs+n));
      n++;
    }
  }
  else
  {
    dport_ptr->txChar(dport_ptr, c);
  }  
  */

  /*
    if( !( (c == *(dport_ptr->ec)) || (c == *(dport_ptr->ec+1)) ) )
    {
      dport_ptr->txChar(dport_ptr, c);  
    }
    else
    {
      int n = 0;
      while(*(dport_ptr->ecs+n)) 
      {
        dport_ptr->txChar(dport_ptr, *(dport_ptr->ecs+n));
        n++;
      }
    }
  */

  //
  //if(c)
  //{
    if( !( (c == *(dport_ptr->ec)) || (c == *(dport_ptr->ec+1)) ) )
    {
      dport_ptr->txChar(dport_ptr, c);  
    }
    else
    {
      char t1 = *(dport_ptr->ecs);
      char t2 = *(dport_ptr->ecs+1);
      if(t1) dport_ptr->txChar(dport_ptr, t1); 
      if(t2) dport_ptr->txChar(dport_ptr, t2); 
    }
  //}    
  //

  #endif 
  
  #ifdef ST_NO_CHAR_SUBS
  dport_ptr->txChar(dport_ptr, c);
  #endif
}

/*
+--------------------------------------------------------------------
| TERMS OF USE: MIT License
+--------------------------------------------------------------------
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
+--------------------------------------------------------------------
*/

