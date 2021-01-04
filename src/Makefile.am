AM_CFLAGS =

bin_PROGRAMS = backmap
backmap_SANITIZE = -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer
backmap_SOURCES = backmap.c trie.c
backmap_DEBUG_FLAGS = -g -Wall -Wextra -Werror -Wno-nullability-completeness
# backmap_DEBUG_FLAGS = -g -Wall -Wextra -Werror #-Wno-missing-field-initializers
backmap_CFLAGS = $(backmap_DEBUG_FLAGS) $(backmap_SANITIZE)
backmap_CPPFLAGS = -I$(top_srcdir)/include -I$(LEVMAR_DIR)
# backmap_LDADD = -L$(LEVMAR_DIR) #-llevmar -lblas -llapack -lm
#backmap_LDFLAGS = -static
backmap_LDFLAGS = 

check_SCRIPTS = test.bash test_forw_and_back.bash
TESTS = $(check_SCRIPTS)
CLEANFILES = $(check_SCRIPTS)

test.bash:
	echo ./backmap -t ../data/bin_com.xyz \
                       -t ../data/naph1_com.xyz \
                       -t ../data/naph2_com.xyz \
                       -t ../data/phe1_com.xyz \
                       -t ../data/phe2_com.xyz \
                       ../data/test.dump > $@
	chmod +x $@

test_forw_and_back.bash:
	echo "../../forwardmap/src/forward-cg \
                          ../data/one_npd.pdb \
                          -o /tmp/a \
                          ../data/residues.txt \
                          -t ../data/npd_gas.psf; \
             ./backmap -t ../data/bin_com.xyz \
                       -t ../data/naph1_com.xyz \
                       -t ../data/naph2_com.xyz \
                       -t ../data/phe1_com.xyz \
                       -t ../data/phe2_com.xyz \
                       /tmp/a.dump" > $@
	chmod +x $@

nanomatch:
	module load gnu8/8.3.0
	$(MAKE)

dist:
	rm -rf /tmp/backmap
	mkdir -p /tmp/backmap
	rsync --exclude "*.tgz" -vax ../ /tmp/backmap
	tar -C /tmp -pzcvf backmap.tgz backmap

backup: dist
	rsync -vax backmap.tgz tadaaga:xmos/

.PHONY = $(TESTS)
