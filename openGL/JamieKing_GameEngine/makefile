
RELEASE_MODE :=

.PHONY: release
release: RELEASE_MODE := release
release: all

.PHONY: debug
debug: RELEASE_MODE := debug
debug: all

.PHONY: all
all:
	@$(MAKE) $(RELEASE_MODE) -C engine
	@$(MAKE) $(RELEASE_MODE) -C sandboxGame
#	@$(MAKE) $(RELEASE_MODE) -C project2
#	@$(MAKE) $(RELEASE_MODE) -C project3

.PHONY: clean
clean:
	@$(MAKE) clean -C engine
	@$(MAKE) clean -C sandboxGame
#	@$(MAKE) clean -C project2
#	@$(MAKE) clean -C project3