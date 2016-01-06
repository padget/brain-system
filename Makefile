.PHONY: clean All

All:
	@echo "----------Building project:[ brain - Release ]----------"
	@"$(MAKE)" -f  "brain.mk"
clean:
	@echo "----------Cleaning project:[ brain - Release ]----------"
	@"$(MAKE)" -f  "brain.mk" clean
