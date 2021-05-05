.POSIX:

PCF=icestick.pcf
DEV=1k
VFILES=top.v #nco.v
CXXFILES=main.cpp sound_driver.cpp

.SUFFIXES: .v .blif .asc .bin

verilate: $(VFILES) $(CXXFILES)
	verilator --cc nco.v --exe $(CXXFILES)
	make -j4 -C obj_dir -f Vnco.mk Vnco


top.blif: $(VFILES)
	yosys -p "synth_ice40 -blif $@" $(VFILES)

top.asc: top.blif $(PCF)
	arachne-pnr -d $(DEV) -p $(PCF) $< -o $@

.asc.bin:
	icepack $< $@

icestick: top.bin

program: top.bin
	iceprog top.bin

clean:
	rm -f *.asc *.blif *.bin
	rm -rf obj_dir
