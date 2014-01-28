default:
	@ echo "Please specify a target."

install:
	@ echo "Invoking recursive make..."
	@ $(MAKE) -C src/ install
