NAME			=	webserv

SRCS			=	Server.cpp \
					parsing.cpp \
					handle_requests.cpp \
					main.cpp \

CC				=	g++

CPPFLAGS		=	-Wall -Wextra -Werror -std=c++98

RM				=	rm -rf

OBJS			=	$(SRCS:%.cpp=%.o)

RESET			=	\033[0m
GREEN			=	\033[38;5;46m
WHITE			=	\033[38;5;15m
GREY			=	\033[38;5;8m
ORANGE			=	\033[38;5;202m
RED				=	\033[38;5;160m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)----------------------------------------------------"
	@echo "Executable				./$(NAME) $(RESET)"

.cpp.o:
	@echo "$(GREY)Compiling...				$(RESET)"
	$(CC) $(CPPFLAGS) -c $< -o $(<:.cpp=.o)

clean:
	@echo "$(RED)----------------------------------------------------"
	$(RM) $(OBJS)
	@echo "REMOVED O-FILES"
	@echo "----------------------------------------------------$(RESET)"

fclean: clean
	@echo "$(RED)"
	$(RM) $(NAME)
	@echo "REMOVED EXECUTABLE FILE $(RESET)"
	@echo "----------------------------------------------------$(RESET)"

re: fclean all

.PHONY: all clean fclean re