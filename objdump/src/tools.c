/*
** tools.c for tools in /objdump/src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Feb 18 19:42:39 2017 Frederic ODDOU
** Last update Tue Feb 21 01:18:35 2017 Fredoddou
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "objdump.h"

bool	print_error(char	*str)
{
  fprintf(stderr, "%s: %s: %s\n", g_prog_name, g_file_name, str);
  return (false);
}

bool	check_end_map(t_objdump	*objdump,
		      void	*ptr)
{
  if (ptr > (void *)((char *)objdump->ehdr + objdump->size))
    return (print_error("File truncated"));
  return (true);
}

void	get_name(t_objdump	*objdump)
{
  int	i;
  int	size;

  i = 0;
  if (objdump->name[i] == '/')
    {
      size = atoi(&objdump->name[i + 1]);
      if (size < g_header_ar_size)
	objdump->name = &g_header_ar[size];
    }
  while (objdump->name[i] && objdump->name[i] != '/')
    i++;
  objdump->name[i] = '\0';
}
