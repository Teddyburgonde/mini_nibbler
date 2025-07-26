#=================== NAME ===================#
NAME = nibbler

#================ COMPILER ==================#
CXX = c++

#=================== FLAGS ==================#
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
LDFLAGS = -ldl

#================== SOURCES =================#
SRCS = main.cpp \
       core/Game.cpp \
	   core/GameState.cpp \
       core/Snake.cpp \

#================= COLORS ===================#
GREEN = \033[32m
RESET = \033[0m

#============== OBJECT FILES ================#
OBJS = $(SRCS:.cpp=.o)


#================ UTILS PART ================#
RM = rm -f

#========== GENERATION BINARY FILES =========#
all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)[MAIN] $(NAME) compiled with dlopen() support.$(RESET)"

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -Iincludes -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
