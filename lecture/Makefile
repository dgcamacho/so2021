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

%.pdf: %.tex declarations.tex 01_introduction.tex 02_basics.tex 03_operators.tex
	latexmk -pdf -pdflatex="pdflatex -shell-escape" -use-make $< #  -silent -interaction=nonstopmode

clean:
	latexmk -CA
