#=================== NAME ===================#
NAME = nibbler

#================ COMPILER ==================#
CXX = c++

#=================== FLAGS ==================#
CXXFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses

#================== SOURCES =================#
SRCS = main.cpp \
       core/Game.cpp \
	   core/GameState.cpp \
       core/Snake.cpp \
       gui_ncurses/GuiNcurses.cpp \
	   gui_ncurses/GuiNcursesDraw.cpp \


#============== OBJECT FILES ================#
OBJS = $(SRCS:.cpp=.o)

#========== GENERATION BINARY FILES =========#
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#================= COLORS ===================#
GREEN = \033[32m
RESET = \033[0m

#================ UTILS PART ================#
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)EXECUTABLE READY!$(RESET)"

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
