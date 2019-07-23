.PHONY: clean run install uninstall

program/uppercase: math/libmath.a data/libdata.a system/libsystem.a
	$(MAKE) -C program uppercase

math/libmath.a:
	$(MAKE) -C math libmath.a

data/libdata.a:
	$(MAKE) -C data libdata.a
	
system/libsystem.a:
	$(MAKE) -C system libsystem.a

clean:
	$(MAKE) -C program clean
	$(MAKE) -C math clean
	$(MAKE) -C data clean
	$(MAKE) -C system clean

run: program/uppercase
	program/uppercase testfile.u

