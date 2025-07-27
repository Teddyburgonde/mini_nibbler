#=================== NAME ===================#
NAME = nibbler

#================ COMPILER ==================#
CXX = c++

#=================== FLAGS ==================#
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -Iincludes -I/opt/homebrew/include/SDL2
LDFLAGS = -ldl -lncurses -L/opt/homebrew/lib -lSDL2

#================== SOURCES =================#
SRCS = main.cpp \
       core/Game.cpp \
	   core/GameState.cpp \
       core/Snake.cpp

#============== OBJECT FILES ================#
OBJS = $(SRCS:.cpp=.o)

#================= COLORS ===================#
GREEN = \033[32m
RESET = \033[0m

#================== SUBDIRECTORIES ==========#
SUBDIRS = gui_ncurses gui_sdl

#================ UTILS PART ================#
RM = rm -f

#========== GENERATION BINARY FILES =========#
all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)[MAIN] $(NAME) compiled with dlopen() support.$(RESET)"

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -Iincludes -c $< -o $@

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(RM) $(OBJS)

fclean: clean
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir fclean; \
	done
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

