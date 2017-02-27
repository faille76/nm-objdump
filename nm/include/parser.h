/*
** nm.h for nm in /nm/include/
**
** Made by Fredoddou
** Login   <fredoddou>
**
** Started on  Mon Feb 13 14:53:04 2017 Fredoddou
** Last update Fri Feb 17 09:56:22 2017 Fredoddou
*/

#pragma once

#include <stdbool.h>

#define F_N_STRICT_FORMAT "-"
#define F_STRICT_FORMAT "--"
#define L_F_N_STRICT_FORMAT strlen(F_N_STRICT_FORMAT)
#define L_F_STRICT_FORMAT strlen(F_STRICT_FORMAT)

enum			e_flags_id
  {
    FLAG_PRINT_FILE_NAME,
    FLAG_LINE_NUMBER,
    FLAG_NUMERIC_SORT,
    FLAG_NO_SORT,
    FLAG_REVERSE_SORT,
    FLAG_PRINT_SIZE,
    FLAG_UNDEFINED_ONLY,
    FLAG_DEFINED_ONLY,
    FLAG_DEBUG_SYMS,
    FLAG_NONE
  };

enum			e_flags_strict
  {
    FLAG_STRICT = 0,
    FLAG_NON_STRICT = 1
  };

typedef struct		s_flags_tab
{
  char			*flag;
  enum e_flags_id	id;
  enum e_flags_strict	strict;
  char			*message;
}			t_flags_tab;

typedef char		*t_flag;

bool			parser_flags(int	ac,
				     char	**av,
				     t_flag	flags);
