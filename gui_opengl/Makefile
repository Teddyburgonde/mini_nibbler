#=================== NAME ===================#
NAME = libgui_opengl.so

#================ COMPILER ==================#
CXX = c++

#=================== FLAGS ==================#

CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -fPIC \
		   -I../includes \
		   -I/usr/include/GL \
		   -I/usr/include/GLFW


LDFLAGS = -L/usr/lib/x86_64-linux-gnu -lGL -lGLU -lglfw -shared

#================== SOURCES =================#
SRCS =  GuiOpenGL.cpp \
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
	@echo "$(GREEN)[OpenGL] $(NAME) built successfully!$(RESET)"

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
