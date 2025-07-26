# **************************************************************************** #
#                                                                              #
#                 Makefile – Compilation de libgui_ncurses.so (Ncurses GUI)   #
#                                                                              #
# Ce Makefile génère une bibliothèque partagée (libgui_ncurses.so) à partir   #
# des fichiers GuiNcurses.cpp, GuiNcursesDraw.cpp et entrypoint.cpp.          #
# Cette bibliothèque est utilisée dynamiquement via dlopen() dans le projet.  #
#                                                                              #
# Utilisation :                                                                #
#    make         → Compile la bibliothèque .so                                #
#    make clean   → Supprime les fichiers objets (.o)                          #
#    make fclean  → Supprime aussi le .so                                      #
#    make re      → Nettoie puis recompile tout                                #
#                                                                              #
# **************************************************************************** #

#=================== NAME ===================#
NAME = libgui_ncurses.so

#================ COMPILER ==================#
CXX = c++

#=================== FLAGS ==================#
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -fPIC
LDFLAGS = -lncurses -shared

#================== SOURCES =================#
SRCS =  GuiNcurses.cpp \
		GuiNcursesDraw.cpp \
		entrypoint.cpp \
		../core/GameState.cpp \
		../core/Snake.cpp \

#============== OBJECT FILES ================#
OBJS = $(SRCS:.cpp=.o)

#================ UTILS PART ================#
RM = rm -f

#================= COLORS ===================#
GREEN = \033[32m
RESET = \033[0m

#========== GENERATION BINARY FILES =========#
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
	cp $(NAME) ../
	@echo "$(GREEN)[NCURSES] $(NAME) built successfully!$(RESET)"

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -I../includes -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
