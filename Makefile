#=================== NAME ===================#
NAME = nibbler

#================ COMPILER ==================#
CPP = c++

#=================== FLAGS ==================#
CPPFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lncurses

#================== SOURCES =================#
SRCS = main.cpp \
       core/Game.cpp \
       core/Snake.cpp \
       gui_ncurses/GuiNcurses.cpp

#============== OBJECT FILES ================#
OBJS = $(SRCS:.cpp=.o)

#========== GENERATION BINARY FILES =========#
%.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

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
