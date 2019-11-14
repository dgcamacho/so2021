all: lecture.pdf lecture_01.pdf lecture_02.pdf lecture_03.pdf lecture_04.pdf

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

%.pdf: %.tex declarations.tex 01_introduction.tex 02_basics.tex 03_operators.tex 04_functions.tex
	latexmk -pdf -pdflatex="pdflatex -shell-escape" -use-make $< #  -silent -interaction=nonstopmode

clean:
	latexmk -CA
