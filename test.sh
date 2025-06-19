sudo make clean

make $1 file=blink_single
make $1 file=blink

make $1 file=button

make $1 file=switch_simple
make $1 file=switch
make $1 file=switches_simple

make $1 file=timer

make $1 file=uart_usb_simple 
make $1 file=hid_test

make $1 file=vga_simple
make $1 file=vga_simple2
make $1 file=vga_works

make $1 file=vga/screensaver
make $1 file=vga/testCircle
make $1 file=vga/testRectangle
make $1 file=vga/testRectangle2
make $1 file=vga/testScreen