
.DEFAULT_GOAL := all

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -MMD -MP -std=c++98

SRCS = \
	main.cpp \
	RPN.cpp \

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)
-include $(DEPS)


NAME = RPN

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
