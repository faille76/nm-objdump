/*
** display.c for display in /nm/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Feb 17 09:33:13 2017 Frederic ODDOU
** Last update Fri Feb 24 12:57:01 2017 Frederic ODDOU
*/

#include <stdio.h>
#include <string.h>
#include "nm.h"

static void	display_sym_line_inf(t_nm	*nm,
				     t_flag	flags,
				     int	i)
{
  if (!flags[FLAG_DEFINED_ONLY] &&
      (nm->list[i].sym)->st_shndx == SHN_UNDEF)
    {
      printf("%*c %s", ((g_architecture == A32BITS) ? 8 : 16) + 2,
	     nm->list[i].type, nm->list[i].name);
      if (flags[FLAG_LINE_NUMBER] && nm->name)
	printf("\t%s:0", nm->name);
    }
  else if (!flags[FLAG_UNDEFINED_ONLY] &&
	   (nm->list[i].sym)->st_shndx != SHN_UNDEF)
    {
      printf("%0*x", ((g_architecture == A32BITS) ? 8 : 16), nm->list[i].value);
      if (flags[FLAG_PRINT_SIZE] &&
	  (nm->list[i].sym)->st_size > 0)
	printf(" %0*x", ((g_architecture == A32BITS) ? 8 : 16),
	       (unsigned int)(nm->list[i].sym)->st_size);
      printf(" %c %s", nm->list[i].type, nm->list[i].name);
    }
}

static void	display_sym_line(t_nm	*nm,
				 t_flag	flags,
				 int	i)
{
  if (nm->list[i].name && strlen(nm->list[i].name) == 0)
    return ;
  if (flags[FLAG_PRINT_FILE_NAME])
    {
      printf("%s:", g_file_name);
      if (nm->name)
	printf("%s:", nm->name);
    }
  display_sym_line_inf(nm, flags, i);
  printf("\n");
}

void		display_sym(t_nm	*nm,
			    t_flag	flags,
			    int		number)
{
  int		i;

  if (!flags[FLAG_NO_SORT])
    {
      sort_list(nm, flags, number, SORT_BY_NAME);
      if (flags[FLAG_NUMERIC_SORT])
	sort_list(nm, flags, number, SORT_BY_NUMBER);
    }
  if (!flags[FLAG_NO_SORT] && flags[FLAG_REVERSE_SORT])
    {
      i = number - 1;
      while (i >= 0)
	display_sym_line(nm, flags, i--);
    }
  else
    {
      i = 0;
      while (i < number)
	display_sym_line(nm, flags, i++);
    }
}
