# **************************************************************************** #
#                                                                              #
#             Makefile – Compilation de libgui_sdl.so (SDL2 GUI – macOS)      #
#                                                                              #
# Ce Makefile compile une bibliothèque partagée (.so) avec SDL2 sur macOS.    #
# Assurez-vous que SDL2 est installé via Homebrew :                           #
#      ➤ brew install sdl2                                                     #
#                                                                              #
# Les options Linux sont commentées ci-dessous pour portabilité.              #
#                                                                              #
# **************************************************************************** #

#=================== NAME ===================#
NAME = libgui_sdl.so

#================ COMPILER ==================#
CXX = c++

#=================== FLAGS ==================#
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -fPIC \
		   -I../includes \
		   -I/opt/homebrew/include/SDL2   # ✅ SDL2 headers pour macOS

LDFLAGS = -L/opt/homebrew/lib -lSDL2 -shared  # ✅ SDL2 libs pour macOS

# ✅ Si tu es sous Linux, utilise à la place :
#CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -fPIC -I../includes -I/usr/include/SDL2
#LDFLAGS = -L/usr/lib -lSDL2 -shared

#================== SOURCES =================#
SRCS =  GuiSDL.cpp \
        GuiSDLDraw.cpp \
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
