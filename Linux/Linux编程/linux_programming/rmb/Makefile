#Makefile

CFLAG = #-DDEBUG


TARGET = capital_digit
OBJS   = capital_digit.o



$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(OBJS) $(CFLAG)

clean:
	rm -f $(TARGET) $(OBJS)
	
%.o:%.c
	gcc -c $< $(CFLAG)
%.o:%.cpp
	g++ -c $< $(CFLAG)
