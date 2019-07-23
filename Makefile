.PHONY: clean run install uninstall

uppercase/uppercase: math/libmath.a data/libdata.a system/libsystem.a
	$(MAKE) -C uppercase uppercase

math/libmath.a:
	$(MAKE) -C math libmath.a

data/libdata.a:
	$(MAKE) -C data libdata.a
	
system/libsystem.a:
	$(MAKE) -C system libsystem.a

clean:
	$(MAKE) -C uppercase clean
	$(MAKE) -C math clean
	$(MAKE) -C data clean
	$(MAKE) -C system clean

run: uppercase/uppercase
	uppercase/uppercase testfile.u

