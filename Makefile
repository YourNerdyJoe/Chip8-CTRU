CC = arm-none-eabi-gcc
LINK = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CTRULIB = e:/git/ctrulib/libctru
CFLAGS += -Wall -march=armv6 -O3 -I"$(CTRULIB)/include" -I$(DEVKITPRO)/libnds/include
LDFLAGS += -T ccd00.ld -L"$(DEVKITARM)/arm-none-eabi/lib" -L"$(CTRULIB)/lib"

SOURCE = .
BUILD = build

CFILES = $(wildcard $(SOURCE)/*.c)
OFILES = $(CFILES:$(SOURCE)/%.c=$(BUILD)/%.o)
DFILES = $(CFILES:$(SOURCE)/%.c=$(BUILD)/%.d)
SFILES = $(wildcard $(SOURCE)/*.s)
OFILES += $(SFILES:$(SOURCE)/%.s=$(BUILD)/%.o)
PROJECTNAME = ${shell basename "$(CURDIR)"}

.PHONY:=all dir

all: dir $(PROJECTNAME).3ds

dir:
	@mkdir -p $(BUILD)

#$(PROJECTNAME).bin: $(PROJECTNAME).elf
#	$(OBJCOPY) -O binary $< $@

$(PROJECTNAME).3ds: $(PROJECTNAME).elf
	@make -f make3ds TARGET=$(PROJECTNAME)

$(PROJECTNAME).elf: $(OFILES)
	$(LINK) $(LDFLAGS) -o $(PROJECTNAME).elf $(filter-out $(BUILD)/crt0.o, $(OFILES)) -lctru -lc -nostartfiles

clean:
	@rm -f $(BUILD)/*.o $(BUILD)/*.d
	@rm -f $(PROJECTNAME).elf $(PROJECTNAME).3ds
	@echo "all cleaned up !"

-include $(DFILES)

$(BUILD)/%.o: $(SOURCE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@$(CC) -MM $< > $(BUILD)/$*.d

$(BUILD)/%.o: $(SOURCE)/%.s
	$(CC) $(CFLAGS) -c $< -o $@
	@$(CC) -MM $< > $(BUILD)/$*.d
