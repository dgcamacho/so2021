CHAPTER_TEX := $(shell find * -type f -regex "[0-9]+_[a-z_]+[.]tex")

all: lecture.pdf

# CUSTOM BUILD RULES
%.tex: %.raw
	./raw2tex $< > $@

%.tex: %.dat
	./dat2tex $< > $@

# DUMMY BUILD FOR IGNORED FILES
%.pyg:
	echo "Ignore $@"

%.aex:
	echo "Ignore $@"

%.w18:
	echo "Ignore $@"


# MAIN LATEXMK RULE

lecture.pdf: lecture.tex declarations.tex cover.tex $(CHAPTER_TEX)
	latexmk -pdf -latexoption="--shell-escape" -use-make $<

clean:
	latexmk -CA
	rm -rf *.pyg _minted*/

