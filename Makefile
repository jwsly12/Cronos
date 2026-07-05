BUILD_DIR := build
ISO_DIR := $(BUILD_DIR)/iso
KERNEL := $(BUILD_DIR)/kernel.elf
ISO_IMAGE := $(BUILD_DIR)/cronos.iso

.SUFFIXES:

OBJS := $(BUILD_DIR)/boot.o \
        $(BUILD_DIR)/interrupts.o \
        $(BUILD_DIR)/gdt_asm.o \
        $(BUILD_DIR)/gdt.o \
        $(BUILD_DIR)/kernel.o \
        $(BUILD_DIR)/idt.o \
        $(BUILD_DIR)/pic.o \
        $(BUILD_DIR)/io.o \
        $(BUILD_DIR)/video.o \
        $(BUILD_DIR)/string.o \
        $(BUILD_DIR)/npsh.o

CFLAGS := -m32 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector -fno-pie -Iinclude

all: iso

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compilando Assembly
$(BUILD_DIR)/boot.o: boot/boot.s | $(BUILD_DIR)
	@nasm -f elf32 boot/boot.s -o $(BUILD_DIR)/boot.o

$(BUILD_DIR)/interrupts.o: kernel/interrupts.s | $(BUILD_DIR)
	@nasm -f elf32 kernel/interrupts.s -o $(BUILD_DIR)/interrupts.o

$(BUILD_DIR)/gdt_asm.o: kernel/gdt.s | $(BUILD_DIR)
	@nasm -f elf32 kernel/gdt.s -o $(BUILD_DIR)/gdt_asm.o

# --- REGRAS DE COMPILAÇÃO C (Corrigidas para evitar ambiguidade) ---

# Arquivos da pasta kernel/
$(BUILD_DIR)/gdt.o: kernel/gdt.c | $(BUILD_DIR)
	@gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.o: kernel/kernel.c | $(BUILD_DIR)
	@gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/idt.o: kernel/idt.c | $(BUILD_DIR)
	@gcc $(CFLAGS) -c $< -o $@

# Arquivos da pasta lib/
$(BUILD_DIR)/string.o: lib/string.c | $(BUILD_DIR)
	@gcc $(CFLAGS) -c $< -o $@

# Arquivos da pasta drivers/
$(BUILD_DIR)/io.o: drivers/io.c | $(BUILD_DIR)
	@gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/pic.o: drivers/pic.c | $(BUILD_DIR)
	@gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/video.o: drivers/video.c | $(BUILD_DIR)
	@gcc $(CFLAGS) -c $< -o $@

# Arquivos da pasta bin/
$(BUILD_DIR)/npsh.o: bin/npsh.c | $(BUILD_DIR)
	@gcc $(CFLAGS) -c $< -o $@

# -----------------------------------------------------------------

# Linkando tudo no Kernel ELF
$(KERNEL): $(OBJS) link.ld
	@ld -m elf_i386 -T link.ld -o $(KERNEL) $(OBJS)

iso: $(KERNEL)
	@rm -rf $(ISO_DIR)
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $(KERNEL) $(ISO_DIR)/boot/kernel.elf
	@cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	@grub-mkrescue -o $(ISO_IMAGE) $(ISO_DIR)

run: iso
	@qemu-system-i386 -cdrom $(ISO_IMAGE)

clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all iso run clean