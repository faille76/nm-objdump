/*
** exec_objdump.c for exec in /objdump/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Wed Feb 15 21:00:09 2017 Frederic ODDOU
** Last update	Tue Feb 21 12:09:57 2017 Full Name
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objdump.h"

void			display_hexa(uint8_t	*data,
				     int	size)
{
  int			i;

  i = 0;
  while (i < 16)
    {
      if (i < size)
	printf("%02x", data[i]);
      else
	printf("  ");
      if (!((i + 1) % 4))
	printf(" ");
      i++;
    }
  printf(" ");
  i = 0;
  while (i < 16)
    {
      if (i < size)
	printf("%c", IS_PRINTABLE(data[i]) ? data[i] : '.');
      else
	printf(" ");
      i++;
    }
}

bool			exec_objdump(t_objdump		*objdump,
				     t_flag		flags)
{
  if (g_architecture == A32BITS)
    return (exec_objdump32(objdump, flags));
  return (exec_objdump64(objdump, flags));
}
