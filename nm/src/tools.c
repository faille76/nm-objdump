/*
** tools.c for tools in /nm/src/
**
** Made by Frederic ODDOU
** Login oddou_f <frederic.oddou@epitech.eu>
**
** Started on  Sat Feb 18 19:42:39 2017 Frederic ODDOU
** Last update Sun Feb 19 04:10:15 2017 Fredoddou
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "nm.h"

bool	print_error(char	*str)
{
  fprintf(stderr, "%s: %s: %s\n", g_prog_name, g_file_name, str);
  return (false);
}

bool	check_end_map(t_nm	*nm,
		      void	*ptr)
{
  if (ptr > (void *)((char *)nm->ehdr + nm->size))
    return (print_error("File truncated"));
  return (true);
}

void	get_name(t_nm		*nm)
{
  int	i;
  int	size;

  i = 0;
  if (nm->name[i] == '/')
    {
      size = atoi(&nm->name[i + 1]);
      if (size < g_header_ar_size)
	nm->name = &g_header_ar[size];
    }
  while (nm->name[i] && nm->name[i] != '/')
    i++;
  nm->name[i] = '\0';
}
