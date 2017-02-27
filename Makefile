##
## Makefile for make in /home/fredoddou/Documents/Epitech/B4-Unix-System-Programming/PSU_2016_nmobjdump/
##
## Made by Frederic ODDOU
## Login   <frederic.oddou@epitech.eu>
##
## Started on  Mon Feb 13 13:58:49 2017 Frederic ODDOU
## Last update Mon Feb 13 14:19:13 2017 Frederic ODDOU
##

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[0;31m"
BLUE		=	"\033[0;34m"

DIR_NM = ./nm/
DIR_OBJDUMP = ./objdump/

all: nm objdump

nmmess:
		@$(ECHO) $(BLUE) " _   _ __  __ " $(DEFAULT)
		@$(ECHO) $(BLUE) "| \\ | |  \\/  |" $(DEFAULT)
		@$(ECHO) $(BLUE) "|  \\| | \\  / |" $(DEFAULT)
		@$(ECHO) $(BLUE) "| . \` | |\\/| |" $(DEFAULT)
		@$(ECHO) $(BLUE) "| |\\  | |  | |" $(DEFAULT)
		@$(ECHO) $(BLUE) "|_| \\_|_|  |_|" $(DEFAULT)

objdumpmess:
		@$(ECHO) $(BLUE) "  ____  ____       _ _____  _    _ __  __ _____  " $(DEFAULT)
		@$(ECHO) $(BLUE) " / __ \\|  _ \\     | |  __ \\| |  | |  \\/  |  __ \\ " $(DEFAULT)
		@$(ECHO) $(BLUE) "| |  | | |_) |    | | |  | | |  | | \\  / | |__) |" $(DEFAULT)
		@$(ECHO) $(BLUE) "| |  | |  _ < _   | | |  | | |  | | |\\/| |  ___/" $(DEFAULT)
		@$(ECHO) $(BLUE) "| |__| | |_) | |__| | |__| | |__| | |  | | |" $(DEFAULT)
		@$(ECHO) $(BLUE) " \\____/|____/ \\____/|_____/ \\____/|_|  |_|_|" $(DEFAULT)

nm: nmmess
		@make -C $(DIR_NM) -f Makefile -s

objdump: objdumpmess
		@make -C $(DIR_OBJDUMP) -f Makefile -s

clean:
		@make clean -C $(DIR_NM) -f Makefile -s
		@make clean -C $(DIR_OBJDUMP) -f Makefile -s

fclean:
		@make fclean -C $(DIR_NM) -f Makefile -s
		@make fclean -C $(DIR_OBJDUMP) -f Makefile -s

re:
		@make re -C $(DIR_NM) -f Makefile -s
		@make re -C $(DIR_OBJDUMP) -f Makefile -s

.PHONY:all nm objdump clean fclean nmmess objdumpmess
