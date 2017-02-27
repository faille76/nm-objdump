/*
** nm.h for nm in /nm/include/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Tue Feb 14 11:35:43 2017 Frederic ODDOU
** Last update Fri Feb 24 12:19:46 2017 Frederic ODDOU
*/

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <elf.h>
#include <ar.h>
#include "parser.h"

#define MAGIC_ELF ELFMAG
#define MAGIC_AR ARMAG
#define MAGIC_AR_END ARFMAG
#define SIZE_AR_STRUCT sizeof(struct ar_hdr)

#define SYMB_LIST (((char *)ehdr + symtab->sh_offset))
#define SYMB_STR ((char *)ehdr + shdr[symtab->sh_link].sh_offset)
#define SECTION_STR ((char *)ehdr + shdr[ehdr->e_shstrndx].sh_offset)
#define SMALL_CHAR(x) ((x >= 'A' && x <= 'Z') ? x + ('a' - 'A') : x)

enum e_sort_by
{
  SORT_BY_NAME,
  SORT_BY_NUMBER
};

enum e_architecture
{
  A64BITS,
  A32BITS
};

typedef struct	s_list
{
  Elf64_Sym	*sym;
  char		*name;
  unsigned int	value;
  char		type;
}		t_list;

typedef struct	s_nm
{
  char *name;
  Elf64_Ehdr	*ehdr;
  Elf64_Shdr	*shdr;
  Elf64_Shdr	*symtab;
  t_list	*list;
  off_t		size;
}		t_nm;

bool		open_file(t_flag		flags,
			  int			file,
			  int			fd);

bool		exec_nm32(t_nm			*nm,
			  t_flag		flags);
bool		exec_nm64(t_nm			*nm,
			  t_flag		flags);
bool		exec_nm(t_nm			*nm,
			t_flag			flags);

void		sort_list(t_nm			*nm,
			  t_flag		flags,
			  int			number,
			  enum e_sort_by	sort_by);
void		display_sym(t_nm		*nm,
			    t_flag		flags,
			    int			number);
bool		print_error(char		*str);
bool		check_end_map(t_nm		*nm,
			      void		*ptr);
bool		get_each_file(int		fd,
			      t_flag		flags);

bool		get_sym32(t_nm			*nm);
bool		get_sym64(t_nm			*nm);
bool		get_sym(t_nm			*nm);

bool		get_ehdr(t_nm			*nm,
			 int			fd);
void		get_name(t_nm			*nm);

extern char *g_prog_name;
extern char *g_file_name;
extern char *g_header_ar;
extern int g_header_ar_size;
extern enum e_architecture g_architecture;
