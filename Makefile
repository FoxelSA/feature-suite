
#
#   make - Configuration
#

    MAKE_FILCONC=feature-file-concat
    MAKE_KEYSIFT=feature-key-SIFT
    MAKE_KEYSURF=feature-key-SURF
    MAKE_KEYVIEW=feature-key-view
    MAKE_MATSIFT=feature-match-SIFT
    MAKE_MATSURF=feature-match-SURF
    MAKE_MATSIEV=feature-match-sieve
    MAKE_MATFFIL=feature-match-ff
    MAKE_MATVIEW=feature-match-view
    MAKE_IMGEQUA=feature-image-equal
    MAKE_IMGEXPO=feature-image-expose
    MAKE_GRAYCON=feature-image-gray
    MAKE_IMGRMEN=feature-image-rment


#
#   make - Structure
#

    MAKE_BINARY=bin
    MAKE_DOCUME=doc
    MAKE_SOURCE=src

#
#   make - All
#

    all:$(MAKE_FILCONC) $(MAKE_KEYSIFT) $(MAKE_KEYSURF) $(MAKE_KEYVIEW) $(MAKE_MATSIFT) $(MAKE_MATSURF) $(MAKE_MATVIEW) $(MAKE_MATSIEV) $(MAKE_IMGEQUA) $(MAKE_IMGEXPO) $(MAKE_GRAYCON) $(MAKE_MATFFIL) $(MAKE_IMGRMEN)

#
#   make - Branches
#

    $(MAKE_FILCONC):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_FILCONC) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_FILCONC) all && cp $(MAKE_SOURCE)/$(MAKE_FILCONC)/$(MAKE_BINARY)/$(MAKE_FILCONC) $(MAKE_BINARY)/

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

    $(MAKE_MATFFIL):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATFFIL) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATFFIL) all && cp $(MAKE_SOURCE)/$(MAKE_MATFFIL)/$(MAKE_BINARY)/$(MAKE_MATFFIL) $(MAKE_BINARY)/

    $(MAKE_IMGEQUA):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEQUA) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEQUA) all && cp $(MAKE_SOURCE)/$(MAKE_IMGEQUA)/$(MAKE_BINARY)/$(MAKE_IMGEQUA) $(MAKE_BINARY)/

    $(MAKE_IMGEXPO):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEXPO) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEXPO) all && cp $(MAKE_SOURCE)/$(MAKE_IMGEXPO)/$(MAKE_BINARY)/$(MAKE_IMGEXPO) $(MAKE_BINARY)/

    $(MAKE_GRAYCON):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_GRAYCON) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_GRAYCON) all && cp $(MAKE_SOURCE)/$(MAKE_GRAYCON)/$(MAKE_BINARY)/$(MAKE_GRAYCON) $(MAKE_BINARY)/

    $(MAKE_IMGRMEN):directories
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGRMEN) clean && $(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGRMEN) all && cp $(MAKE_SOURCE)/$(MAKE_IMGRMEN)/$(MAKE_BINARY)/$(MAKE_IMGRMEN) $(MAKE_BINARY)/

#
#   make - Documentation
#

    documentation:directories
	mkdir -p $(MAKE_DOCUME)/html && rm $(MAKE_DOCUME)/html/* -f
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_FILCONC) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_FILCONC)/$(MAKE_DOCUME)/html $(MAKE_FILCONC) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYSIFT) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_KEYSIFT)/$(MAKE_DOCUME)/html $(MAKE_KEYSIFT) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYSURF) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_KEYSURF)/$(MAKE_DOCUME)/html $(MAKE_KEYSURF) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_KEYVIEW) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_KEYVIEW)/$(MAKE_DOCUME)/html $(MAKE_KEYVIEW) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATSIFT) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_MATSIFT)/$(MAKE_DOCUME)/html $(MAKE_MATSIFT) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATSURF) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_MATSURF)/$(MAKE_DOCUME)/html $(MAKE_MATSURF) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATVIEW) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_MATVIEW)/$(MAKE_DOCUME)/html $(MAKE_MATVIEW) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATSIEV) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_MATSIEV)/$(MAKE_DOCUME)/html $(MAKE_MATSIEV) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_MATFFIL) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_MATFFIL)/$(MAKE_DOCUME)/html $(MAKE_MATFFIL) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEQUA) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_IMGEQUA)/$(MAKE_DOCUME)/html $(MAKE_IMGEQUA) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGEXPO) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_IMGEXPO)/$(MAKE_DOCUME)/html $(MAKE_IMGEXPO) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_GRAYCON) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_GRAYCON)/$(MAKE_DOCUME)/html $(MAKE_GRAYCON) && cd -
	$(MAKE) -C $(MAKE_SOURCE)/$(MAKE_IMGRMEN) documentation && cd $(MAKE_DOCUME)/html/ && ln -s ../../$(MAKE_SOURCE)/$(MAKE_IMGRMEN)/$(MAKE_DOCUME)/html $(MAKE_IMGRMEN) && cd -

#
#   make - Directories
#

    directories:
	mkdir -p $(MAKE_BINARY)
	mkdir -p $(MAKE_DOCUME)

#
#   make - Cleaning
#

    clean:
	rm $(MAKE_BINARY)/* -f

