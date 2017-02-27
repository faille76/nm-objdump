/*
** objdump.h for objdump in /objdump/include/
**
** Made by Frederic ODDOU
** Login   <frederic.oddou@epitech.eu>
**
** Started on  Tue Feb 14 11:35:43 2017 Frederic ODDOU
** Last update Fri Feb 24 16:16:26 2017 Frederic ODDOU
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

#define SECTION_STR ((char *)ehdr + shdr[ehdr->e_shstrndx].sh_offset)
#define SMALL_CHAR(x) ((x >= 'A' && x <= 'Z') ? x + ('a' - 'A') : x)
#define IS_PRINTABLE(x)	(x >= 32 && x <= 126)
#define GET_SIZE(x) (sizeof(x) / sizeof(*x))

#define HAS_RELOC      0x01
#define EXEC_P         0x02
#define HAS_LINENO     0x04
#define HAS_DEBUG      0x08
#define HAS_SYMS       0x10
#define HAS_LOCALS     0x20
#define DYNAMIC        0x40
#define WP_TEXT        0x80
#define D_PAGED        0x100
#define BFD_IS_RELAXABLE 0x200
#define HAS_LOAD_PAGE 0x1000

enum e_architecture
{
  A64BITS,
  A32BITS
};

typedef struct	s_type
{
  int		id;
  char		*value;
}		t_type;

typedef struct	s_objdump
{
  char		*name;
  Elf64_Ehdr	*ehdr;
  Elf64_Shdr	*shdr;
  off_t		size;
}		t_objdump;

bool		open_file(t_flag			flags,
			  int				fd);
bool		exec_objdump32(t_objdump		*objdump,
			       t_flag			flags);
bool		exec_objdump64(t_objdump		*objdump,
			       t_flag			flags);
bool		exec_objdump(t_objdump			*objdump,
			t_flag				flags);
bool		print_error(char			*str);
bool		check_end_map(t_objdump			*objdump,
			      void			*ptr);
bool		get_each_file(int			fd,
			      t_flag			flags);
bool		get_sym32(t_objdump			*objdump);
bool		get_sym64(t_objdump			*objdump);
bool		get_sym(t_objdump			*objdump);
bool		get_ehdr(t_objdump			*objdump,
			 int				fd);
void		display_hexa(uint8_t			*data,
			     int			size);
void		get_name(t_objdump			*objdump);
void		display_header(t_objdump		*objdump,
			       t_flag			flags);

extern char *g_prog_name;
extern char *g_file_name;
extern char *g_header_ar;
extern int g_header_ar_size;
extern enum e_architecture g_architecture;
