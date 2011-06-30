DEVICES=manager floppy keyboard

LIBS = $(addsuffix /lib.a,$(DEVICES))

.PHONY: default depclean clean $(LIBS)
default :
	@for d in $(DEVICES); do make -C $$d; done
	@echo "(AR)"
	rm -f lib.a
	ar -rTcs lib.a $(LIBS)

depclean :
	@for d in $(DEVICES); do make -C $$d depclean; done

clean :
	@for d in $(DEVICES); do make -C $$d clean; done
