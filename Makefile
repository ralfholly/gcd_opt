ifneq ($(MAKECMDGOALS),clean)
ifeq ($(CPPFLAGS),)
$(error Please provide CPPFLAGS")
endif
endif

TARGET := gcd_opt

all: test assembly_output

# To be safe, always rebuild target (avoid using old CPPFLAGS for measurements, for instance).
.PHONY: $(TARGET).c

$(TARGET): $(TARGET).o

.PHONY: assembly_output
assembly_output: $(TARGET)
	@objdump -drwC gcd_opt > $(TARGET).s

.PHONY: test
test: $(TARGET)
	@./$(TARGET)

clean:
	@rm -rf $(TARGET) *.o *.s
