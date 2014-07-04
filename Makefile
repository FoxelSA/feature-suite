
#
#   make - Configuration
#

    MAKE_KEYSIFT=feature-key-SIFT
    MAKE_KEYSURF=feature-key-SURF
    MAKE_KEYVIEW=feature-key-view
    MAKE_KEYSCAL=feature-key-scale
    MAKE_MATSIFT=feature-match-SIFT
    MAKE_MATSURF=feature-match-SURF
    MAKE_MATSIEV=feature-match-sieve
    MAKE_MATVIEW=feature-match-view
    MAKE_IMGEQUA=feature-image-equal
    MAKE_IMGEXPO=feature-image-expose
    MAKE_DECENTR=feature-image-decent
    MAKE_GRAYCON=feature-image-gray


#
#   make - Structure
#

    MAKE_BINARY=bin
    MAKE_SOURCE=src

#
#   make - All
#

    all:$(MAKE_KEYSIFT) $(MAKE_KEYSURF) $(MAKE_KEYVIEW) $(MAKE_MATSIFT) $(MAKE_MATSURF) $(MAKE_MATVIEW) $(MAKE_MATSIEV) $(MAKE_IMGEQUA) $(MAKE_DECENTR)

#
#   make - Branches
#

    $(MAKE_KEYSIFT):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYSIFT) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYSIFT) all && cp $(MAKE_SOURCE)/$(MAKE_KEYSIFT)/$(MAKE_BINARY)/$(MAKE_KEYSIFT) $(MAKE_BINARY)/

    $(MAKE_KEYSURF):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYSURF) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYSURF) all && cp $(MAKE_SOURCE)/$(MAKE_KEYSURF)/$(MAKE_BINARY)/$(MAKE_KEYSURF) $(MAKE_BINARY)/

    $(MAKE_KEYVIEW):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYVIEW) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYVIEW) all && cp $(MAKE_SOURCE)/$(MAKE_KEYVIEW)/$(MAKE_BINARY)/$(MAKE_KEYVIEW) $(MAKE_BINARY)/

    $(MAKE_KEYSCAL):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYSCAL) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYSCAL) all && cp $(MAKE_SOURCE)/$(MAKE_KEYSCAL)/$(MAKE_BINARY)/$(MAKE_KEYSCAL) $(MAKE_BINARY)/

    $(MAKE_MATSIFT):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATSIFT) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATSIFT) all && cp $(MAKE_SOURCE)/$(MAKE_MATSIFT)/$(MAKE_BINARY)/$(MAKE_MATSIFT) $(MAKE_BINARY)/

    $(MAKE_MATSURF):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATSURF) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATSURF) all && cp $(MAKE_SOURCE)/$(MAKE_MATSURF)/$(MAKE_BINARY)/$(MAKE_MATSURF) $(MAKE_BINARY)/

    $(MAKE_MATVIEW):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATVIEW) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATVIEW) all && cp $(MAKE_SOURCE)/$(MAKE_MATVIEW)/$(MAKE_BINARY)/$(MAKE_MATVIEW) $(MAKE_BINARY)/

    $(MAKE_MATSIEV):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATSIEV) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATSIEV) all && cp $(MAKE_SOURCE)/$(MAKE_MATSIEV)/$(MAKE_BINARY)/$(MAKE_MATSIEV) $(MAKE_BINARY)/

    $(MAKE_IMGEQUA):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEQUA) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEQUA) all && cp $(MAKE_SOURCE)/$(MAKE_IMGEQUA)/$(MAKE_BINARY)/$(MAKE_IMGEQUA) $(MAKE_BINARY)/

    $(MAKE_IMGEXPO):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEXPO) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEXPO) all && cp $(MAKE_SOURCE)/$(MAKE_IMGEXPO)/$(MAKE_BINARY)/$(MAKE_IMGEXPO) $(MAKE_BINARY)/

    $(MAKE_DECENTR):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_DECENTR) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_DECENTR) all && cp $(MAKE_SOURCE)/$(MAKE_DECENTR)/$(MAKE_BINARY)/$(MAKE_DECENTR) $(MAKE_BINARY)/

    $(MAKE_GRAYCON):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_GRAYCON) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_GRAYCON) all && cp $(MAKE_SOURCE)/$(MAKE_GRAYCON)/$(MAKE_BINARY)/$(MAKE_GRAYCON) $(MAKE_BINARY)/

#
#   make - Directories
#

    directories:
	mkdir -p $(MAKE_BINARY)

#
#   make - Cleaning
#

    clean:
	rm $(MAKE_BINARY)/* -f

