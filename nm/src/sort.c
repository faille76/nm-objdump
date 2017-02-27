/*
** sort.c for sort in /nm/src/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Fri Feb 17 09:30:52 2017 Frederic ODDOU
** Last update Sat Feb 18 20:31:49 2017 Frederic ODDOU
*/

#include <string.h>
#include "nm.h"

static short		sort_by_name_char(char		c1,
					  char		c2)
{
  c1 = ((c1 >= 'A' && c1 <= 'Z') ? c1 + ('a' - 'A') : c1);
  c2 = ((c2 >= 'A' && c2 <= 'Z') ? c2 + ('a' - 'A') : c2);
  if (c1 > c2)
    return (1);
  return (-1);
}

static short		sort_by_name_equal(char		*s1,
					   char		*s2,
					   int		i1,
					   int		i2)
{
  if (s1[i1] != '\0' && s2[i2] == '\0')
    return (1);
  if (!s1[i1] && !s2[i2])
    {
      i1 = i2 = 0;
      while (strchr("_@.", s1[i1]) && ++i1);
      while (strchr("_@.", s2[i2]) && ++i2);
      if (i1 < i2)
	return (1);
      if (i1 != 0 && i1 == i2)
	{
	  if (*s1 == '.' && *s2 != '.')
	    return (1);
	}
    }
  return (0);
}

static short		sort_by_name(char		*s1,
				     char		*s2)
{
  int			i1;
  int			i2;

  i1 = i2 = 0;
  while (strchr("_@.", s1[i1]) && ++i1);
  while (strchr("_@.", s2[i2]) && ++i2);
  while (s1[i1] != '\0' && s2[i2] != '\0')
    {
      if (SMALL_CHAR(s1[i1]) != SMALL_CHAR(s2[i2]))
	return ((sort_by_name_char(s1[i1], s2[i2]) == 1) ? 1 : 0);
      i1++;
      i2++;
    }
  return (sort_by_name_equal(s1, s2, i1, i2));
}

static void		swap_ptr(t_list			*t1,
				 t_list			*t2)
{
  t_list		tmp;

  memcpy(&tmp, t1, sizeof(t_list));
  memcpy(t1, t2, sizeof(t_list));
  memcpy(t2, &tmp, sizeof(t_list));
}

void			sort_list(t_nm			*nm,
				  t_flag		flags,
				  int			number,
				  enum e_sort_by	sort_by)
{
  int			i;
  short			val;

  i = 0;
  while (i < number - 1)
    {
      if ((sort_by == SORT_BY_NAME &&
	   (val = sort_by_name(nm->list[i].name, nm->list[i + 1].name)) > 0) ||
	  (sort_by == SORT_BY_NUMBER &&
	   nm->list[i].value > nm->list[i + 1].value))
	{
	  swap_ptr(&nm->list[i], &nm->list[i + 1]);
	  sort_list(nm, flags, number, sort_by);
	}
      i++;
    }
}
