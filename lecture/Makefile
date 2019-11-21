LECTURE_TEX := $(shell find * -type f -name "lecture_*.tex")
LECTURE_PDF := $(subst .tex,.pdf,$(LECTURE_TEX))
CHAPTER_TEX := $(shell find * -type f -regex "[0-9]+_[a-z]+[.]tex")

all: lecture.pdf $(LECTURE_PDF)

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

lecture_%.pdf: lecture_%.tex %_*.tex declarations.tex
	latexmk -pdf -pdflatex="pdflatex -shell-escape" -use-make $<

lecture.pdf: lecture.tex declarations.tex $(CHAPTER_TEX)
	latexmk -pdf -pdflatex="pdflatex -shell-escape" -use-make $<

clean:
	latexmk -CA
