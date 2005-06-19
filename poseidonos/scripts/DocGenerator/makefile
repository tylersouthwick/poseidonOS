
SRC_FILES = \
			org/northfuse/documentation/DocGenerator.java \
			org/northfuse/documentation/CommentExtractor.java \
			org/northfuse/documentation/LatexMaker.java

CLASS_FILES = $(subst .java,.class, $(SRC_FILES))

$(CLASS_FILES) : $(SRC_FILES)
	javac -verbose $(SRC_FILES)

clean : 
	rm -f org/northfuse/documentation/*.class

jar : DocGenerator.jar
DocGenerator.jar : ${CLASS_FILES}
	jar -cvf DocGenerator.jar ${CLASS_FILES}

