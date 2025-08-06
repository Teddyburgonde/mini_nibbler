#=================== NAME ===================#
NAME = libgui_sdl.so

#================ COMPILER ==================#
CXX = c++

#=================== FLAGS ==================#

CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -fPIC -I../includes -I/usr/include/SDL2
LDFLAGS = -L/usr/lib -lSDL2 -shared

#================== SOURCES =================#
SRCS =  GuiSDL.cpp \
        entrypoint.cpp \
        ../core/GameState.cpp \
        ../core/Snake.cpp

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
	@echo "$(GREEN)[SDL] $(NAME) built successfully!$(RESET)"

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
