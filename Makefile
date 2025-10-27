BUILD_DIR := build
ISO_DIR := $(BUILD_DIR)/iso
KERNEL := $(BUILD_DIR)/kernel.elf
ISO_IMAGE := $(BUILD_DIR)/meu_kernel.iso

all: iso

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/boot.o: boot/boot.s | $(BUILD_DIR)
	@nasm -f elf32 boot/boot.s -o $(BUILD_DIR)/boot.o

$(BUILD_DIR)/kernel.o: kernel/kernel.c | $(BUILD_DIR)
	@gcc -m32 -ffreestanding -Iinclude -c kernel/kernel.c -o $(BUILD_DIR)/kernel.o

$(BUILD_DIR)/video.o: lib/video.c | $(BUILD_DIR)
	@gcc -m32 -ffreestanding -Iinclude -c lib/video.c -o $(BUILD_DIR)/video.o

$(KERNEL): $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/video.o link.ld
	@ld -m elf_i386 -T link.ld -o $(KERNEL) \
		$(BUILD_DIR)/boot.o \
		$(BUILD_DIR)/kernel.o \
		$(BUILD_DIR)/video.o

iso: $(KERNEL)
	@rm -rf $(ISO_DIR)
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $(KERNEL) $(ISO_DIR)/boot/kernel.elf
	@cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg
	@grub-mkrescue -o $(ISO_IMAGE) $(ISO_DIR)

run: iso
	@qemu-system-i386 -cdrom $(ISO_IMAGE)

clean:
	@rm -rf $(BUILD_DIR) $(ISO_IMAGE)
