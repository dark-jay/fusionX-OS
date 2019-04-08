GPP = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
AS = --32
LD = -melf_i386

objects = loader.o IO/io.o libc/itoa.o libc/memory.o libc/string.o gdt.o port.o kernel.o

%.o: %.cpp
	g++ $(GPP) -o $@ -c $<

%.o: %.s
	as $(AS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LD) -T $< -o $@ $(objects)

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

FusionX.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "FusionX" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

clean:
	rm -f $(objects) mykernel.bin mykernel.iso
