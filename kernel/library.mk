LIBS = $(addsuffix /lib.a,$(MODULES))

.PHONY: default depclean clean $(LIBS) test

default :
	@for d in $(MODULES); do make -C $$d; done
	@echo "(AR)"
	rm -f lib.a
	ar -rTcs lib.a $(LIBS)

depclean :
	@for d in $(MODULES); do make -C $$d depclean; done

clean :
	@for d in $(MODULES); do make -C $$d clean; done

test :
	@for d in $(MODULES); do make -C $$d test; done

